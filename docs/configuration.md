# VibeArtemis Configuration Reference

This document explains all settings configurable in VibeArtemis.

## 1. Video Settings

| Key | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| `width` | integer | `1920` | Target horizontal resolution in pixels. |
| `height` | integer | `1080` | Target vertical resolution in pixels. |
| `fps` | integer | `60` | Stream frame rate (e.g. 30, 60, 90, 120, 144, 165, 240). |
| `bitrate_kbps` | integer | `20000` | Target video stream bitrate in Kbps (1 Mbps = 1000 Kbps). |
| `scale_mode` | string | `"fit"` | Video scale mode: `"fit"`, `"fill"`, `"stretch"`, `"pan_zoom"`. |
| `rotation_deg` | integer | `0` | Stream rotation in degrees: `0`, `90`, `180`, `270`. |
| `scale_factor` | float | `1.0` | Apollo virtual display scale factor (e.g. `1.2` = 120% resolution). |
| `use_virtual_display`| bool | `true` | Request Apollo host to create/switch to virtual display matching client. |
| `enable_hdr` | bool | `false` | Enable 10-bit HDR video stream if supported by host and client display. |

---

## 2. Audio Settings

| Key | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| `audio_channels` | integer | `2` | Number of audio channels (`2` for stereo, `6` for 5.1 surround). |
| `mute_host_audio`| bool | `true` | Mute audio output on the host PC while streaming. |

---

## 3. Input & Controls Settings

| Key | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| `mouse_mode` | string | `"relative"`| `"relative"` for gaming, `"absolute"` for desktop pointer, `"touchpad"` for trackpad gestures. |
| `trackpad_scrolling` | bool | `true` | Enable smooth trackpad gesture scrolling. |
| `swap_mouse_buttons` | bool | `false` | Swap left and right mouse buttons. |

---

## 4. Apollo Extensions Settings

| Key | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| `smart_clipboard_sync` | bool | `true` | Automatically synchronize client and host clipboards. |
| `clipboard_toast` | bool | `true` | Show notification toast when clipboard contents are synchronized. |
| `enable_server_commands` | bool | `true` | Enable triggering remote host commands from in-game HUD and app menu. |
