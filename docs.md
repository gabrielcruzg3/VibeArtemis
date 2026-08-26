# VibeArtemis Comprehensive Documentation

## Overview

VibeArtemis is designed to provide the ultimate desktop streaming experience by pairing modern C++20 with the Apollo host extension protocol.

---

## 1. Subsystems

### 1.1 Apollo Client (`src/backend/apollo_client.*`)
Handles HTTP and HTTPS REST communication with Apollo and Sunshine hosts:
- Server discovery and details probe (`/serverinfo`)
- Pairing handshake (Legacy PIN & OTP fast pairing)
- Bidirectional clipboard exchange (`/actions/clipboard`)
- Dynamic bitrate adjustment during an active stream (`/bitrate?bitrate=...`)
- Host server command execution (`/actions/servercmd`)

### 1.2 Virtual Display Manager (`src/backend/vdisplay_manager.*`)
Computes optimal display configuration when connecting to an Apollo host:
- Matches native client monitor resolution and refresh rate
- Applies user-defined scale factors (e.g. 1.2x for supersampling)
- Computes aspect ratios and letterboxing geometry for ultrawide (21:9, 32:9) and standard (16:9, 16:10) monitors
- Formats launch/resume URL query parameters (`vdisplay=1&vdisplay_res=...&vdisplay_fps=...`)

### 1.3 Smart Clipboard Sync Manager (`src/backend/clipboard_sync.*`)
Maintains a two-way synchronization loop between client and host:
- Reads local clipboard changes and uploads to `/actions/clipboard`
- Polls or receives host clipboard updates on focus gain
- Uses deduplication hashing and loopback markers (`VibeArtemisStreaming`) to prevent endless echo loops

### 1.4 Streaming Engine & Session Coordinator (`src/streaming/session.*`)
Manages the end-to-end stream lifecycle:
- Handshake via RTSP
- Media streaming using `moonlight-common-c`
- Video decoding and rendering
- Audio decoding and playback
- Input event capture (keyboard, mouse, gamepad, touchpad)

### 1.5 In-Game Overlay HUD (`src/streaming/overlay/in_game_overlay.*`)
Interactive overlay rendered directly over the stream:
- Video scale switcher (Fit, Fill, Stretch, Zoom, Rotate)
- Live telemetry HUD (FPS, decode latency, render latency, network jitter, packet loss)
- Server Commands trigger panel
- Mouse / Trackpad mode selector

---

## 2. Protocol Extensions Reference

| Protocol Extension | Opcode / Endpoint | Description |
| :--- | :--- | :--- |
| **Server Command (Control Stream)** | `0x3000` (ENet Reliable) | Send numeric command ID to execute on host |
| **Clipboard Sync (Control Stream)** | `0x3001` (ENet Reliable) | Send UTF-8 clipboard buffer to host |
| **File Transfer Nonce** | `0x3002` (ENet Reliable) | Request authorization nonce for file transfer |
| **Clipboard REST GET** | `GET /actions/clipboard?type=text` | Fetch host clipboard content |
| **Clipboard REST POST** | `POST /actions/clipboard?type=text` | Push client clipboard text to host |
| **Dynamic Bitrate REST** | `GET /bitrate?bitrate=<Kbps>` | Update encoder bitrate on-the-fly |

---

## 3. Configuration Properties

All settings are persisted in JSON format (`~/.config/VibeArtemis/config.json`):

```json
{
  "video": {
    "width": 1920,
    "height": 1080,
    "fps": 60,
    "bitrate_kbps": 20000,
    "scale_mode": "fit",
    "rotation_deg": 0,
    "scale_factor": 1.0,
    "use_virtual_display": true
  },
  "audio": {
    "channels": 2,
    "mute_host_audio": true
  },
  "input": {
    "mouse_mode": "relative",
    "trackpad_scrolling": true,
    "swap_mouse_buttons": false
  },
  "apollo": {
    "smart_clipboard_sync": true,
    "clipboard_toast": true,
    "enable_server_commands": true
  }
}
```
