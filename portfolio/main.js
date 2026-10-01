/* Madhav K Pradeep — scroll-driven portfolio
   GSAP + ScrollTrigger (cdnjs) and Lenis (jsDelivr), loaded with `defer` before this file.
   Content is never hidden unless <html class="js"> was set in <head>, which only
   happens when motion is allowed; if anything here fails, the head failsafe un-hides it. */
(function () {
  'use strict';

  var root = document.documentElement;
  var hasGsap = typeof window.gsap !== 'undefined' && typeof window.ScrollTrigger !== 'undefined';
  var reduceMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;
  var finePointer = window.matchMedia('(hover: hover) and (pointer: fine)').matches;

  if (!hasGsap) { root.classList.remove('js'); return; }

  var animate = root.classList.contains('js'); // false → reduced motion, or failsafe already fired
  window.__mkpReady = true;

  gsap.registerPlugin(ScrollTrigger);
  var $ = function (s, ctx) { return (ctx || document).querySelector(s); };
  var $$ = function (s, ctx) { return Array.prototype.slice.call((ctx || document).querySelectorAll(s)); };

  /* ── Smooth scrolling ─────────────────────────────────────────────── */
  if (!reduceMotion && typeof window.Lenis !== 'undefined') {
    var lenis = new Lenis({ lerp: 0.1, anchors: true, autoRaf: false });
    window.__lenis = lenis;
    lenis.on('scroll', ScrollTrigger.update);
    gsap.ticker.add(function (t) { lenis.raf(t * 1000); });
    gsap.ticker.lagSmoothing(0);
  }

  /* ── Scroll-progress line in the nav ──────────────────────────────── */
  gsap.to('.n-progress', {
    scaleX: 1, ease: 'none',
    scrollTrigger: { start: 0, end: 'max', scrub: reduceMotion ? true : 0.3 }
  });

  initHero();
  if (animate) initReveals();

  // Fonts and lazy images change heights; re-measure once they settle.
  if (document.fonts && document.fonts.ready) document.fonts.ready.then(function () { ScrollTrigger.refresh(); });
  window.addEventListener('load', function () { ScrollTrigger.refresh(); });

  /* ════════════════════════════════════════════════════════════════════
     HERO — desktop: pinned, video scrubbed by scroll
            mobile (<768px): autoplaying muted loop, no scrub, light parallax
            reduced motion: static poster only
     If the video can't load, a canvas network animation takes over (0-credit fallback).
     ════════════════════════════════════════════════════════════════════ */
  function initHero() {
    var home = $('#home');
    var media = $('.h-media', home);
    var video = $('.h-video', home);
    var canvas = $('.h-canvas', home);
    var content = $('.h-content', home);
    var deco = $('.h-deco', home);
    if (reduceMotion) return; // static poster, no scrub/parallax

    var net = null; // canvas fallback, created on demand
    function fallback() {
      video.removeAttribute('src');
      video.classList.remove('ready');
      if (!net) net = goldNetwork(canvas, home);
    }

    var mm = gsap.matchMedia();

    mm.add('(min-width: 768px)', function () {
      var dur = 0, target = 0, current = 0, ready = false, objectUrl = null;
      var source = pickSource([
        ['assets/hero.mp4', 'video/mp4; codecs="avc1.64001F"'],
        ['assets/hero.webm', 'video/webm; codecs="vp9"']
      ]);

      // Pin the hero while the video scrubs. If the hero is taller than the
      // viewport (short laptop screens) the pin starts once its bottom is visible.
      var tl = gsap.timeline({
        defaults: { ease: 'none' },
        scrollTrigger: {
          trigger: home,
          start: function () { return home.offsetHeight > window.innerHeight + 1 ? 'bottom bottom' : 'top top'; },
          end: function () { return '+=' + Math.round(window.innerHeight * 1.1); },
          pin: true,
          scrub: true,
          invalidateOnRefresh: true,
          onUpdate: function (self) { target = self.progress * dur; }
        }
      });
      tl.to(media, { scale: 1.07, duration: 1 }, 0)
        .to(content, { y: -70, duration: 1 }, 0)
        .to(deco, { y: -160, duration: 1 }, 0)
        .to(content, { opacity: 0, duration: 0.28 }, 0.72);

      // Ease currentTime toward the scroll target; with every frame a keyframe each seek is cheap.
      function tick() {
        if (!ready) return;
        current += (target - current) * 0.2;
        if (Math.abs(target - current) < 0.002) current = target;
        var t = Math.min(current, dur - 0.04);
        if (!video.seeking && Math.abs(video.currentTime - t) > 0.008) video.currentTime = t;
      }
      gsap.ticker.add(tick);

      // Fetch the whole file once (after page load) so seeking never waits on range requests.
      var aborter = 'AbortController' in window ? new AbortController() : null;
      whenLoaded(function () {
        if (!source) return fallback();
        fetch(source, aborter ? { signal: aborter.signal } : undefined)
          .then(function (r) { if (!r.ok) throw new Error(r.status); return r.blob(); })
          .then(function (blob) {
            objectUrl = URL.createObjectURL(blob);
            video.addEventListener('loadeddata', function onData() {
              video.removeEventListener('loadeddata', onData);
              dur = video.duration || 5;
              target = (tl.scrollTrigger ? tl.scrollTrigger.progress : 0) * dur;
              current = target;
              video.currentTime = Math.min(current, dur - 0.04);
              ready = true;
              video.classList.add('ready');
            });
            video.addEventListener('error', fallback);
            video.preload = 'auto';
            video.src = objectUrl;
          })
          .catch(function (e) { if (!e || e.name !== 'AbortError') fallback(); });
      });

      return function () { // leaving desktop layout
        gsap.ticker.remove(tick);
        video.removeEventListener('error', fallback);
        if (aborter) aborter.abort();
        ready = false;
        video.classList.remove('ready');
        video.removeAttribute('src');
        video.load();
        if (objectUrl) URL.revokeObjectURL(objectUrl);
      };
    });

    mm.add('(max-width: 767px)', function () {
      var source = pickSource([
        ['assets/hero-loop.mp4', 'video/mp4; codecs="avc1.64001E"'],
        ['assets/hero-loop.webm', 'video/webm; codecs="vp9"']
      ]);
      var saveData = navigator.connection && navigator.connection.saveData;

      gsap.to(content, {
        y: -36, ease: 'none',
        scrollTrigger: { trigger: home, start: 'top top', end: 'bottom top', scrub: true }
      });

      if (source && !saveData) {
        whenLoaded(function () {
          video.poster = 'assets/hero-poster.webp';
          video.loop = true;
          video.autoplay = true;
          video.addEventListener('playing', function () { video.classList.add('ready'); }, { once: true });
          video.addEventListener('error', fallback);
          video.src = source;
          var p = video.play();
          if (p && p.catch) p.catch(function () { /* autoplay refused: poster stays */ });
        });
      }

      return function () {
        video.removeEventListener('error', fallback);
        video.autoplay = false;
        video.loop = false;
        video.removeAttribute('poster');
        video.pause();
        video.classList.remove('ready');
        video.removeAttribute('src');
        video.load();
      };
    });
  }

  function pickSource(list) {
    var probe = document.createElement('video');
    for (var i = 0; i < list.length; i++) if (probe.canPlayType(list[i][1])) return list[i][0];
    return null;
  }

  function whenLoaded(fn) {
    if (document.readyState === 'complete') setTimeout(fn, 60);
    else window.addEventListener('load', function () { setTimeout(fn, 60); }, { once: true });
  }

  /* Canvas fallback: drifting gold nodes linked into a transaction network,
     with one pulsing "flagged" node. Pauses when the hero is off screen. */
  function goldNetwork(canvas, host) {
    var ctx = canvas.getContext('2d');
    if (!ctx) return null;
    canvas.classList.add('on');
    var w = 0, h = 0, dpr = 1, nodes = [], running = false, raf = 0, flag;
    var N = window.innerWidth < 768 ? 34 : 72;
    var LINK = window.innerWidth < 768 ? 110 : 150;

    function resize() {
      dpr = Math.min(window.devicePixelRatio || 1, 1.5);
      w = canvas.clientWidth; h = canvas.clientHeight;
      canvas.width = Math.round(w * dpr); canvas.height = Math.round(h * dpr);
      ctx.setTransform(dpr, 0, 0, dpr, 0, 0);
    }
    function seed() {
      nodes = [];
      for (var i = 0; i < N; i++) {
        nodes.push({ x: Math.random() * w, y: Math.random() * h, vx: 0.15 + Math.random() * 0.35, vy: (Math.random() - 0.5) * 0.12, r: 0.8 + Math.random() * 1.6, ph: Math.random() * 6.28 });
      }
      flag = nodes[Math.floor(N * 0.6)];
      flag.x = w * 0.68; flag.y = h * 0.42; flag.vx = 0.05; flag.r = 2.6;
    }
    function frame(t) {
      ctx.clearRect(0, 0, w, h);
      var i, j, a, b, dx, dy, d;
      for (i = 0; i < N; i++) {
        a = nodes[i];
        a.x += a.vx; a.y += a.vy + Math.sin(t * 0.0006 + a.ph) * 0.08;
        if (a.x > w + 20) { a.x = -20; a.y = Math.random() * h; }
        if (a.y < -20) a.y = h + 20; else if (a.y > h + 20) a.y = -20;
      }
      ctx.lineWidth = 0.7;
      for (i = 0; i < N; i++) {
        a = nodes[i];
        for (j = i + 1; j < N; j++) {
          b = nodes[j]; dx = a.x - b.x; dy = a.y - b.y;
          if (Math.abs(dx) > LINK || Math.abs(dy) > LINK) continue;
          d = Math.sqrt(dx * dx + dy * dy);
          if (d < LINK) {
            ctx.strokeStyle = 'rgba(200,168,76,' + (0.32 * (1 - d / LINK)).toFixed(3) + ')';
            ctx.beginPath(); ctx.moveTo(a.x, a.y); ctx.lineTo(b.x, b.y); ctx.stroke();
          }
        }
      }
      ctx.fillStyle = 'rgba(212,180,90,.85)';
      for (i = 0; i < N; i++) { a = nodes[i]; ctx.beginPath(); ctx.arc(a.x, a.y, a.r, 0, 6.283); ctx.fill(); }
      var pulse = (t * 0.0008) % 1;
      ctx.strokeStyle = 'rgba(200,168,76,' + (0.7 * (1 - pulse)).toFixed(3) + ')';
      ctx.lineWidth = 1.2;
      ctx.beginPath(); ctx.arc(flag.x, flag.y, 6 + pulse * 26, 0, 6.283); ctx.stroke();
      ctx.fillStyle = '#D4B45A';
      ctx.beginPath(); ctx.arc(flag.x, flag.y, 3.4, 0, 6.283); ctx.fill();
      if (running) raf = requestAnimationFrame(frame);
    }
    function start() { if (!running && !document.hidden) { running = true; raf = requestAnimationFrame(frame); } }
    function stop() { running = false; cancelAnimationFrame(raf); }

    resize(); seed();
    window.addEventListener('resize', function () { resize(); });
    document.addEventListener('visibilitychange', function () { document.hidden ? stop() : start(); });
    ScrollTrigger.create({ trigger: host, start: 'top bottom', end: 'bottom top', onToggle: function (s) { s.isActive ? start() : stop(); } });
    start();
    return { start: start, stop: stop };
  }

  /* ════════════════════════════════════════════════════════════════════
     SECTION ANIMATIONS (replace the old IntersectionObserver reveal)
     ════════════════════════════════════════════════════════════════════ */
  function initReveals() {
    var mobile = window.matchMedia('(max-width: 767px)').matches;
    var shown = typeof WeakSet !== 'undefined' ? new WeakSet() : null;
    function once(el) { if (!shown) return true; if (shown.has(el)) return false; shown.add(el); return true; }
    // Fire on enter, and also if the page loads already scrolled past the element.
    function onReveal(selector, start, fn) {
      var run = function (els) { els = els.filter(once); if (els.length) fn(els); };
      ScrollTrigger.batch(selector, { start: start, once: true, onEnter: run, onLeave: run });
    }

    /* Section backgrounds: slow parallax (lighter on phones). */
    $$('.sec-bg').forEach(function (bg) {
      var amt = mobile ? 4 : 9;
      gsap.fromTo(bg, { yPercent: -amt }, {
        yPercent: amt, ease: 'none',
        scrollTrigger: { trigger: bg.parentNode, start: 'top bottom', end: 'bottom top', scrub: true }
      });
    });

    /* Generic fade-up for headings, paragraphs, about columns, education, contact. */
    onReveal('.reveal:not(.pillar):not(.exp-card):not(.sk-card):not(.cert-card):not(.reg-box)', 'top 90%', function (els) {
      gsap.fromTo(els, { opacity: 0, y: 18 }, { opacity: 1, y: 0, duration: 0.75, ease: 'power2.out', stagger: 0.08, clearProps: 'transform' });
    });

    /* Fintech pillars: stagger up, top bar draws, counters count. */
    onReveal('.pillar', 'top 88%', function (els) {
      els.forEach(function (el, i) {
        var tl = gsap.timeline({ delay: i * 0.14 });
        tl.fromTo(el, { opacity: 0, y: 34 }, { opacity: 1, y: 0, duration: 0.8, ease: 'power3.out', clearProps: 'transform' })
          .fromTo(el, { '--bar': 0 }, { '--bar': 1, duration: 0.9, ease: 'power2.inOut' }, 0.15);
        $$('[data-count]', el).forEach(function (n) { tl.add(countUp(n), 0.25); });
      });
    });

    /* Experience: cards slide in staggered; the gold left border draws with scroll. */
    $$('.exp-card').forEach(function (card) { gsap.set(card, { '--draw': 0 }); });
    onReveal('.exp-card', 'top 86%', function (els) {
      els.forEach(function (card, i) {
        var tl = gsap.timeline({ delay: i * 0.15 });
        tl.fromTo(card, { opacity: 0, x: mobile ? -24 : -56 }, { opacity: 1, x: 0, duration: 0.9, ease: 'power3.out', clearProps: 'transform' })
          .fromTo($$('.exp-sub, .exp-ul li', card), { opacity: 0, x: -12 }, { opacity: 1, x: 0, duration: 0.5, ease: 'power2.out', stagger: 0.045, clearProps: 'transform' }, 0.25);
      });
    });
    $$('.exp-card').forEach(function (card) {
      gsap.to(card, {
        '--draw': 1, ease: 'none',
        scrollTrigger: { trigger: card, start: 'top 82%', end: 'bottom 62%', scrub: 0.4 }
      });
    });

    /* Skills: cards rise, tags cascade, card numbers count up. */
    onReveal('.sk-card', 'top 88%', function (els) {
      els.forEach(function (card, i) {
        var tl = gsap.timeline({ delay: i * 0.12 });
        tl.fromTo(card, { opacity: 0, y: 30 }, { opacity: 1, y: 0, duration: 0.7, ease: 'power3.out', clearProps: 'transform' })
          .fromTo($$('.tag', card), { opacity: 0, y: 10, scale: 0.94 }, { opacity: 1, y: 0, scale: 1, duration: 0.4, ease: 'back.out(2)', stagger: 0.04, clearProps: 'transform' }, 0.2)
          .add(countUp($('.sk-num', card), { pad: 2, duration: 0.9 }), 0.1);
      });
    });

    /* Certifications: staggered reveal, then a gentle 3D tilt on hover (desktop pointers only). */
    onReveal('.cert-card', 'top 90%', function (els) {
      gsap.fromTo(els, { opacity: 0, y: 36, rotationX: mobile ? 0 : -8, transformPerspective: 900 }, {
        opacity: 1, y: 0, rotationX: 0, duration: 0.8, ease: 'power3.out', stagger: 0.1, clearProps: 'transform',
        onComplete: function () { if (finePointer && !mobile) els.forEach(tilt); }
      });
    });

    /* Regulatory: each list item ticks in like a checklist being cleared. */
    onReveal('.reg-box', 'top 82%', function (els) {
      els.forEach(function (box, b) {
        var tl = gsap.timeline({ delay: b * 0.2 });
        tl.fromTo(box, { opacity: 0, y: 26 }, { opacity: 1, y: 0, duration: 0.7, ease: 'power3.out', clearProps: 'transform' });
        $$('li', box).forEach(function (li, i) {
          var at = 0.35 + i * 0.16;
          tl.fromTo(li, { opacity: 0, x: -10, '--tick': 0 }, { opacity: 1, x: 0, '--tick': 1, duration: 0.42, ease: 'back.out(3.2)', clearProps: 'transform' }, at)
            .fromTo(li, { '--sweep': 0, '--sweep-o': 1 }, { '--sweep': 1, duration: 0.32, ease: 'power2.out' }, at + 0.05)
            .to(li, { '--sweep-o': 0, duration: 0.55, ease: 'power1.out' }, at + 0.32);
        });
      });
    });

    // Anything still hidden that is already above the viewport (e.g. reload mid-page) → show it.
    ScrollTrigger.addEventListener('refresh', function () {
      $$('.reveal, .reg-ul li').forEach(function (el) {
        if (el.getBoundingClientRect().bottom < 0 && getComputedStyle(el).opacity === '0') gsap.set(el, { opacity: 1 });
      });
    });
  }

  /* Count a number element up from 0. Returns a tween (for timelines). */
  function countUp(el, opts) {
    if (!el) return gsap.to({}, { duration: 0 });
    opts = opts || {};
    var raw = el.getAttribute('data-count') || el.textContent;
    var end = parseInt(raw, 10) || 0;
    var pad = opts.pad || 0;
    var fmt = function (v) { var s = String(Math.round(v)); while (s.length < pad) s = '0' + s; return s; };
    var o = { v: 0 };
    el.textContent = fmt(0);
    return gsap.to(o, { v: end, duration: opts.duration || 1.3, ease: 'power2.out', onUpdate: function () { el.textContent = fmt(o.v); } });
  }

  function tilt(card) {
    var rx = gsap.quickTo(card, 'rotationX', { duration: 0.5, ease: 'power3' });
    var ry = gsap.quickTo(card, 'rotationY', { duration: 0.5, ease: 'power3' });
    var ty = gsap.quickTo(card, 'y', { duration: 0.4, ease: 'power3' });
    gsap.set(card, { transformPerspective: 900 });
    card.addEventListener('pointerenter', function () { ty(-4); });
    card.addEventListener('pointermove', function (e) {
      var r = card.getBoundingClientRect();
      ry(((e.clientX - r.left) / r.width - 0.5) * 9);
      rx(-((e.clientY - r.top) / r.height - 0.5) * 9);
    });
    card.addEventListener('pointerleave', function () { rx(0); ry(0); ty(0); });
  }
})();
