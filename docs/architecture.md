# VibeArtemis Architecture & Visual Evolution Guide

## 1. High-Level Design

VibeArtemis follows a modular, thread-safe modern architecture designed for high throughput, sub-frame input latency, and zero-copy rendering where possible.

```
+-------------------------------------------------------------------------------+
|                                VibeArtemis Core                               |
+-------------------+--------------------+-------------------+------------------+
|      Backend      |    Stream Core     |    Media Pipeline |      UI / HUD    |
+-------------------+--------------------+-------------------+------------------+
| - ApolloClient    | - Session          | - VideoDecoder    | - PcView / Apps  |
| - Discovery       | - StreamUtils      | - AudioPlayer     | - StreamOverlay  |
| - ClipboardSync   | - moonlight-core   | - InputManager    | - SettingsView   |
| - VDisplayManager | - ENet / Nanors    | - StatsCollector  | - ProfilesView   |
| - ProfileManager  | - Server Commands  | - Pacer / HWAccel | - Vibepollo HUD  |
+-------------------+--------------------+-------------------+------------------+
```

---

## 2. Media Pipeline Details

### Video Decoding
- Video packets arrive via RTP UDP -> depacketized by `moonlight-common-c`.
- Submitted to the hardware decoder pipeline (FFmpeg / VA-API / VDPAU / NVDEC / D3D11VA / DRM).
- Frames are formatted and rendered to the display viewport with dynamic matrix transformations for video scale modes (Fit, Stretch, Pixel-Exact).

### Audio Playback
- Opus packets arrive via RTP UDP -> decoded using `libopus`.
- Queued into low-latency circular audio buffers and played back via SDL2 / ALSA / Pulse / PipeWire / WASAPI.

### Input Capture & Injection
- Key, mouse, trackpad, and gamepad events captured via native platform hooks and SDL.
- High-precision relative mouse deltas and high-resolution scroll wheel deltas sent to host via encrypted control stream.
- Gamepad rumble and adaptive triggers dispatched to local controllers based on host feedback packets (`0x5500` / `0x5503`).

---

## 3. Apollo Host Extensions Integration

### Virtual Display Negotiation
When launching or resuming an app session:
1. `VirtualDisplayManager` inspects current client display mode.
2. Generates query parameters:
   - `vdisplay=1`
   - `vdisplay_res=<width>x<height>`
   - `vdisplay_fps=<fps>`
   - `vdisplay_scale=<scale_factor>`
3. Appends query parameters to `/launch` and `/resume` HTTP requests.
4. Apollo automatically creates or matches virtual displays with the requested dimensions and refresh rate.

### Resolution & Refresh Rate Profiles
- `ProfileManager` manages resolution presets (1080p, 1440p, 4K, 21:9 Ultrawide, 32:9 Super Ultrawide, 16:10 Laptop/Deck, Esports 240Hz).
- Provides live custom DIY resolution and FPS creator with JSON persistence.

### Clipboard Synchronization
- `ClipboardSyncManager` runs a background thread.
- On client focus, requests latest host clipboard text via `/actions/clipboard?type=text`.
- On local clipboard update, posts new text to `/actions/clipboard`.
- Hashes clipboard payloads and checks markers to prevent recursive sync loops.

---

## 4. Visual Revamp & Vibepollo Integration Roadmap (Upcoming Versions)

### 🎯 Immediate Next Steps
- 🎨 **Further UI / Theme Enhancements**: Customize colors, card animations, typography, or add icons and artwork.
- 🎮 **Gamepad / Controller Mapping Screen**: Complete or refine the Gamepad Mapper UI (`GamepadMapper.qml`).
- 🖥️ **In-Stream Radial / Quick Action Overlay**: Build an in-stream Apollo popup menu (to switch displays, toggle HDR, mute host, etc. during active stream).
- 📦 **Windows Packaging / Cross-Compilation Setup**: Add CMake/CPack or GitHub Actions workflows for Windows `.zip` / `.exe` releases.

### 🎨 Visual & UI Revamp Plan
1. **Modern Dark Glassmorphism Theme**:
   - Replace legacy controls with custom Vibepollo-inspired theme tokens:
     - Background: Deep Obsidian / Slate (`#0b0f19`, `#111827`)
     - Glass surfaces: `rgba(255, 255, 255, 0.05)` with subtle borders (`rgba(255, 255, 255, 0.1)`)
     - Accents: Neon Violet (`#a855f7`), Electric Cyan (`#06b6d4`), Rose Pink (`#f43f5e`)
   - Rounded host cards with subtle glow focus and hover transitions.
2. **Rich Host & App Presentation**:
   - Dynamic host badges: Online status, Apollo/Sunshine detection, GPU & Encoder type (NVENC, QuickSync, VA-API, AMF).
   - High-resolution boxart grid with animated hover cards and quick-launch shortcuts.
3. **In-Stream Overlay & Apollo Quick Actions**:
   - Modern semi-transparent sliding HUD for stream telemetry (FPS, render latency, network jitter, bitrate).
   - Radial / popup Quick Action menu for remote Apollo commands (Display switch, HDR toggle, sleep, reboot).

### 🚀 Deep Vibepollo Feature Integration
1. **Live Host Telemetry**: Real-time stats from Vibepollo's HTTP API (GPU load, encoder temperature, packet drops).
2. **Multi-Monitor / Display Routing**: Interactive display switcher and virtual display manager directly from the client.
3. **WebRTC Hybrid Transport**: Optional modern WebRTC data-channel and streaming protocol exploration alongside classic RTSP/ENet.

