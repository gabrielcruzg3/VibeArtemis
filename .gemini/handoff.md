# VibeArtemis — Project Handoff & Technical Summary

## 1. Project Overview
- **Name**: VibeArtemis
- **Role**: Next-Gen Apollo & Moonlight Desktop Client (Linux Kubuntu 26.04+ & Windows 11)
- **Repository Root**: `/home/g3/Moonshine/VibeArtemis`
- **Active Branch**: `dev/agy` (initial empty root on `main`)
- **Release Milestone**: `v0.1.0-alpha.1-agy` (Commit: `b7e9aea`)
- **Release URL**: [https://github.com/gabrielcruzg3/VibeArtemis/releases/tag/v0.1.0-alpha.1-agy](https://github.com/gabrielcruzg3/VibeArtemis/releases/tag/v0.1.0-alpha.1-agy)

---

## 2. Implemented Subsystems & Architecture

### A. Apollo Virtual Display Auto-Negotiation
- Location: [`app/backend/vdisplay_manager.h`](file:///home/g3/Moonshine/VibeArtemis/app/backend/vdisplay_manager.h), [`app/backend/vdisplay_manager.cpp`](file:///home/g3/Moonshine/VibeArtemis/app/backend/vdisplay_manager.cpp)
- Functionality: Dynamically computes client monitor timings, arbitrary aspect ratios (16:9, 16:10, 21:9, 32:9), high refresh rates (up to 360Hz), and scale factors (20%-200%). Integrated directly into HTTP `/launch` requests in `NvHTTP::startApp`.

### B. Resolution & Refresh Rate Profile Manager
- Location: [`app/backend/profile_manager.h`](file:///home/g3/Moonshine/VibeArtemis/app/backend/profile_manager.h), [`app/backend/profile_manager.cpp`](file:///home/g3/Moonshine/VibeArtemis/app/backend/profile_manager.cpp)
- Features:
  - Presets for 1080p, Ultrawide 21:9, Super Ultrawide 32:9, 16:10 Laptop/Deck, 4K HDR Cinema, and Esports 240Hz.
  - DIY Custom Resolution & FPS creator with instant apply and profile saving.
  - JSON persistence in `~/.config/VibeArtemis/profiles.json`.

### C. Smart Bidirectional Clipboard Sync
- Location: [`app/backend/clipboardsync.h`](file:///home/g3/Moonshine/VibeArtemis/app/backend/clipboardsync.h), [`app/backend/clipboardsync.cpp`](file:///home/g3/Moonshine/VibeArtemis/app/backend/clipboardsync.cpp)
- Features: Automatic clipboard sync between host and client with 64-bit FNV hash deduplication and loopback suppression.

### D. Apollo Protocol Extensions in C Core
- Location: [`moonlight-common-c/moonlight-common-c/src/ControlStream.c`](file:///home/g3/Moonshine/VibeArtemis/moonlight-common-c/moonlight-common-c/src/ControlStream.c), [`Limelight.h`](file:///home/g3/Moonshine/VibeArtemis/moonlight-common-c/moonlight-common-c/src/Limelight.h)
- Features:
  - `0x3000`: Apollo Server Commands (`LiSendExecServerCmd`)
  - `0x3001`: Apollo Clipboard payloads
  - `0x3002`: Apollo Nonce requests
  - `0x5503`: DualSense Adaptive Triggers

### E. Advanced Desktop Settings UI
- Location: [`app/gui/SettingsView.qml`](file:///home/g3/Moonshine/VibeArtemis/app/gui/SettingsView.qml), [`app/settings/streamingpreferences.h`](file:///home/g3/Moonshine/VibeArtemis/app/settings/streamingpreferences.h)
- Controls: Profiles, DIY Custom Resolution/FPS, Virtual Display toggle & scale factor, Smart Clipboard toggles, Ultra-Low Latency mode, Low-Latency Frame Balancing, Aggressive FEC Packet Loss Protection, Full Color Range RGB (0-255), and Lite/Bottom Performance Overlays.

---

## 3. Test & Build Commands

```bash
# Run automated tests
cmake -B build -G Ninja -S . -DBUILD_TESTS=ON && ninja -C build && ctest --test-dir build --output-on-failure

# Build Qt6 GUI Client
qmake6 moonlight-qt.pro && make -j$(nproc)

# Re-package Debian distribution
cp app/moonlight build/deb_staging/usr/bin/vibeartemis
dpkg-deb --build --root-owner-group build/deb_staging build/cpack_artifacts/vibeartemis-0.1.0-alpha.1-agy-Linux.deb
```

---

## 4. Upcoming Versions Roadmap

### 🎨 Phase 2: Visual Overhaul & Vibepollo Design Language
1. **Modern Dark Glassmorphism UI**:
   - Custom sleek Obsidian/Slate palette (`#0b0f19`, `#111827`) with translucent glass panels and neon accents (Neon Violet `#a855f7`, Electric Cyan `#06b6d4`).
   - Redesigned host cards with animated live status, encoder badges (NVENC, QuickSync, VA-API, AMF), and ping metrics.
2. **Revamped In-Stream HUD & Quick Action Menu**:
   - Translucent stream telemetry HUD.
   - Quick popup / radial menu for remote Apollo commands (Display switch, HDR toggle, sleep, reboot).

### 🚀 Phase 3: Deep Vibepollo Host Integration
1. **Live Host Telemetry**: Real-time GPU load, encoder FPS, and network statistics via Vibepollo REST API.
2. **Interactive Display Routing**: Select and configure host virtual displays directly from client UI.
3. **WebRTC Transport Exploration**: WebRTC data-channel and streaming protocol support.
