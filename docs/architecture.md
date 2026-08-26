# VibeArtemis Architecture Guide

## 1. High-Level Design

VibeArtemis follows a modular, thread-safe modern C++20 architecture designed for high throughput, sub-frame input latency, and zero-copy rendering where possible.

```
+-------------------------------------------------------------------------------+
|                                VibeArtemis Core                               |
+-------------------+--------------------+-------------------+------------------+
|      Backend      |    Stream Core     |    Media Pipeline |      UI / HUD    |
+-------------------+--------------------+-------------------+------------------+
| - ApolloClient    | - Session          | - VideoDecoder    | - MainWindow     |
| - Discovery       | - StreamUtils      | - AudioPlayer     | - OverlayHUD     |
| - ClipboardSync   | - moonlight-core   | - InputManager    | - ServerCmdView  |
| - VDisplayManager | - ENet / Nanors    | - StatsCollector  | - SettingsView   |
+-------------------+--------------------+-------------------+------------------+
```

---

## 2. Media Pipeline Details

### Video Decoding
- Video packets arrive via RTP UDP -> depacketized by `moonlight-common-c`.
- Submitted to the hardware decoder pipeline (FFmpeg / VAAPI / NVDEC / D3D11VA).
- Frames are formatted and rendered to the display viewport with dynamic matrix transformations for video scale modes (Fit, Fill, Stretch, Zoom, Rotate).

### Audio Playback
- Opus packets arrive via RTP UDP -> decoded using `libopus`.
- Queued into low-latency circular audio buffers and played back via SDL2 / ALSA / Pulse / WASAPI.

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

### Clipboard Synchronization
- `ClipboardSyncManager` runs a background thread.
- On client focus, requests latest host clipboard text via `/actions/clipboard?type=text`.
- On local clipboard update, posts new text to `/actions/clipboard`.
- Hashes clipboard payloads and checks markers to prevent recursive sync loops.
