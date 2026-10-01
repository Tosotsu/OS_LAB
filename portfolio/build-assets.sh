#!/usr/bin/env bash
# Downloads the Higgsfield generations used by this site (still b + the hero
# video) and encodes them into ./assets/. Needs: curl and ffmpeg built with
# libx264, libvpx-vp9 and libwebp (Homebrew's / apt's ffmpeg include all three).
#
#   ./build-assets.sh            # download + encode
#   ./build-assets.sh --local    # skip download, re-encode from ./.raw/
set -euo pipefail
cd "$(dirname "$0")"

CDN="https://d8j0ntlcm91z4.cloudfront.net/user_3Jv9vOXBUSWIYDzD0wntnKNKa8R"
MONITOR_STILL="$CDN/hf_20260930_170425_aa811394-7bc5-440e-a506-7574ad335d7b.png" # still (b)
HERO_VIDEO="$CDN/hf_20260930_170545_f072c0ee-2ced-45df-89f1-1e663a1fa7e4.mp4"    # video from still (a)
# Still (a) itself (job 7f761aa4) is not needed: the poster is taken from the video's first frame.

FFMPEG="${FFMPEG:-ffmpeg}"
MAX_IMG_BYTES=$((300 * 1024))

mkdir -p assets .raw
if [[ "${1:-}" != "--local" ]]; then
  curl -fSL -o .raw/monitoring.png "$MONITOR_STILL"
  curl -fSL -o .raw/hero-raw.mp4  "$HERO_VIDEO"
fi

ff() { "$FFMPEG" -hide_banner -loglevel error -y "$@"; }
bytes() { wc -c < "$1" | tr -d ' '; }

# Encode an image to WebP, stepping quality down until it is under 300 KB.
webp() { # src dst width
  local q
  for q in 80 74 68 62 56 50 44; do
    ff -i "$1" -vf "scale=$3:-2:flags=lanczos" -c:v libwebp -quality "$q" -compression_level 6 "$2"
    (( $(bytes "$2") < MAX_IMG_BYTES )) && return 0
  done
  echo "warning: $2 is still $(bytes "$2") bytes at q$q" >&2
}

# 1. Scrub video: every frame a keyframe (-g 1) so seeking to any time is instant.
ff -i .raw/hero-raw.mp4 -an -c:v libx264 -preset slow -crf 26 -g 1 \
   -pix_fmt yuv420p -movflags +faststart assets/hero.mp4
# WebM fallback (browsers without H.264). VP9 all-intra came out at 8.8 MB, so
# it gets a keyframe every 6 frames (0.25 s) instead: ~1.5 MB, same PSNR.
ff -i .raw/hero-raw.mp4 -an -c:v libvpx-vp9 -crf 44 -b:v 0 -g 6 -keyint_min 6 \
   -row-mt 1 -deadline good -cpu-used 3 -pix_fmt yuv420p assets/hero.webm

# 2. Mobile loop (no scrubbing on phones): forward + reverse so the loop is
#    seamless, normal GOP and 540p so it stays light.
LOOP='[0:v]split[f][b];[b]reverse[r];[f][r]concat=n=2:v=1:a=0,scale=960:-2,format=yuv420p'
ff -i .raw/hero-raw.mp4 -filter_complex "$LOOP" -an -c:v libx264 -preset slow -crf 28 \
   -movflags +faststart assets/hero-loop.mp4
ff -i .raw/hero-raw.mp4 -filter_complex "$LOOP" -an -c:v libvpx-vp9 -crf 42 -b:v 0 \
   -row-mt 1 -deadline good -cpu-used 2 assets/hero-loop.webm

# 3. Poster = the video's first frame, so there is no jump when the video takes over.
ff -i .raw/hero-raw.mp4 -frames:v 1 .raw/poster.png
webp .raw/poster.png assets/hero-poster.webp 1280

# 4. Section background (still b). Shown at ~20% opacity, so 1600px is plenty.
webp .raw/monitoring.png assets/monitoring.webp 1600

echo
for f in assets/*; do printf '%-26s %8s bytes\n' "$f" "$(bytes "$f")"; done
