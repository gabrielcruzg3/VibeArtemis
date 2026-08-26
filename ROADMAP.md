# VibeArtemis Roadmap

This document outlines the planned milestones, upcoming features, and future development roadmap for **VibeArtemis**.

---

## 🎯 Current Priorities & Next Steps

### 🎨 Further UI / Theme Enhancements
- **Color Palette & Glassmorphism**: Polish obsidian/slate dark theme palettes, glass blur effects, and refined accent styling.
- **Card Animations & Transitions**: Smooth scale/glow transitions on host and application cards, spring physics, and focus animations for gamepad/keyboard navigation.
- **Typography & Assets**: Enhanced typography hierarchy, custom SVGs, artwork, and crisp status badge icons.

### 🎮 Gamepad / Controller Mapping Screen
- **GamepadMapper UI (`GamepadMapper.qml`)**: Complete and refine the interactive controller remapping and calibration interface.
- **Visual Button Binding**: Visual controller diagram with live button/axis state indicators and deadzone adjustment sliders.
- **Profile Export / Import**: Support saving and loading controller mapping profiles (`gamecontrollerdb.txt` and custom per-game bindings).

### 🖥️ In-Stream Radial / Quick Action Overlay
- **Apollo Popup / Radial Action Menu**: Triggerable during active stream (via gamepad hotkey or customizable key combo).
- **Stream Controls**: Instant display switching, HDR toggle, host audio mute/unmute, resolution/bitrate tuning on the fly.
- **Remote Host Management**: Quick Apollo server commands (sleep, restart, display configuration).

### 📦 Windows Packaging & Cross-Compilation Setup
- **Windows Builds**: Add CMake/CPack and GitHub Actions CI/CD workflows for Windows `.zip` and `.exe` installer releases.
- **Toolchain Automation**: Cross-compilation scripts using MinGW-w64 / MSVC with automated dependency packaging (SDL2, Qt6, FFmpeg).

---

## 🚀 Future Milestones

### 🛰️ Deep Vibepollo Host Integration
- **Live Host Telemetry**: Real-time streaming metrics (GPU load, VRAM usage, encoder temperatures, network latency) via Apollo REST endpoints.
- **Interactive Virtual Display Routing**: Manage and create virtual displays directly from the client interface before or during sessions.
- **Dynamic Bitrate Control**: Real-time automatic bitrate adjustments based on network congestion and frame drop telemetry.

### ⚡ Transport & Protocol Exploration
- **WebRTC Hybrid Data Channel**: Low-latency control stream and clipboard sync over WebRTC channels alongside RTSP/ENet.
- **DualSense / Advanced Haptics**: Full adaptive trigger feedback and haptic vibration integration across all platforms.
