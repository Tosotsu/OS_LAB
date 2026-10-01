# Higgsfield credits log

Hard budget: **50 credits**. Starting balance: **600** → spend must never take the balance below **550**.

| # | Time (UTC) | Asset | Model / settings | Balance before | Balance after | Cost | Running total |
|---|---|---|---|---|---|---|---|
| 0 | 2026-09-30 | — (starting balance check) | — | 600 | 600 | 0 | 0 |
| 1 | 2026-09-30 17:02 | Still (a) Hero — gold transaction network, flagged node (job 7f761aa4) | seedream_v4_5, basic, 16:9, count 1 | 600 | 599 | **1** | 1 |
| 2 | 2026-09-30 17:04 | Still (b) Monitoring — dark ledger grid with gold traces (job aa811394) | seedream_v4_5, basic, 16:9, count 1 | 599 | 598 | **1** | 2 |
| 3 | 2026-09-30 17:05 | Hero video — image-to-video from still (a), slow forward push (job f072c0ee) | seedance_2_0_mini, 720p, 5 s, 16:9, generate_audio=false, count 1 | 598 | 593 | **5** | 7 |
| — | 2026-10-01 | Closing balance check (asset encoding ran in Higgsfield's sandbox, no charge) | — | 593 | 593 | 0 | 7 |

**Total spent: 7 / 50 credits** (final balance 593). No further generations.

Cost preflights (`get_cost`, no job submitted): Seedream 4.5 basic 16:9 = 1 credit; Seedance 2.0 Mini 720p 5 s no-audio = 5 credits.

**Skipped for budget:** Seedream 4.5 cost 1 credit per still (not 0), so per the brief stills were capped at 2. Stills (c) Screening and (d) Crypto/VASP were not generated; they are replaced by free SVG backgrounds (`assets/screening.svg`, `assets/vasp.svg`).

## Assets

| File | Source | Size |
|---|---|---|
| `assets/hero.mp4` | video f072c0ee → H.264, `-g 1 -crf 26 -an -movflags +faststart` (desktop scrub) | 4.03 MB |
| `assets/hero.webm` | video f072c0ee → VP9, keyframe every 6 frames, CRF 44 (scrub fallback) | 1.49 MB |
| `assets/hero-loop.mp4` / `.webm` | video f072c0ee → forward+reverse loop, 540p (mobile autoplay) | 0.74 MB / 0.66 MB |
| `assets/hero-poster.webp` | first frame of the video | 73 KB |
| `assets/monitoring.webp` | still b (aa811394), 1600 px | 35 KB |
| `assets/screening.svg` | generated locally (0 credits) | 21 KB |
| `assets/vasp.svg` | generated locally (0 credits) | 10 KB |

Still (a) (7f761aa4) is used only as the video's start frame; the poster is the video's own first frame.
The video and WebP files were produced by `./build-assets.sh` (downloads the generations from Higgsfield and encodes them; re-run it to rebuild).
