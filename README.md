# VibeArtemis

**VibeArtemis** is a next-generation desktop client for [Apollo / Vibepollo](https://github.com/gabrielcruzg3/Vibepollo), [Sunshine](https://github.com/LizardByte/Sunshine), and NVIDIA GameStream, bringing advanced mobile features from Artemis to Linux (Kubuntu 26.04+) and Windows 11.

> [!WARNING]
> **Disclaimer / Use at Your Own Risk**
> These pre-built `.deb` packages are unofficial community binaries provided as-is without warranties of any kind. Installing and running pre-built packages is entirely at the user's own discretion, safety, and risk. If you have security or compatibility concerns, you are strongly encouraged to inspect the source code and compile the binaries directly on your machine.

---

## ✨ Features

- 🖥️ **Apollo Virtual Display Auto-Negotiation**: Automatically calculates host virtual display resolution, arbitrary aspect ratios (16:9, 16:10, 21:9, 32:9), and high refresh rates to match your client display.
- ⚡ **Resolution & Refresh Rate Profile Manager**: Quickly switch between custom presets (1080p, 1440p, 4K, 21:9 Ultrawide, 32:9 Super Ultrawide, 16:10 Laptop/Deck, Esports 240Hz).
- 🛠️ **Custom DIY Resolution & FPS Creator**: Enter and save arbitrary custom resolutions and frame rates directly from settings.
- 📋 **Smart Two-Way Clipboard Sync**: Seamless real-time bidirectional clipboard text sharing with loopback suppression and optional content masking.
- 🚀 **Ultra-Low Latency Mode & Frame Balancing**: Zero-buffering decoder pipeline for sub-frame response and jitter smoothing over wireless networks.
- 🛡️ **Aggressive Packet Loss Protection (FEC)**: Extra Forward Error Correction to eliminate visual compression artifacts on unstable Wi-Fi.
- 🎨 **Full Color Range (0-255 RGB)**: Expanded dynamic color reproduction for vibrant displays.
- 🎮 **Apollo Protocol Extensions**: Remote server commands (Display Switch, HDR Toggle, Sleep/Reboot) and DualSense adaptive triggers (`0x5503`).
- 🏎️ **Hardware Accelerated Video Decoding**: Native VA-API, VDPAU, DRM, EGL, and DXGI/Direct3D11 decoding engines.

---

## 📦 Installation & Downloads

### Debian / Ubuntu (`.deb`)
Download the latest `.deb` release package from the [Releases](https://github.com/gabrielcruzg3/VibeArtemis/releases) page and install:

```bash
sudo dpkg -i vibeartemis-0.1.0-alpha.1-agy-Linux.deb
```

Then launch from your application menu or terminal:
```bash
vibeartemis
```

---

## 🔨 Building from Source

### Dependencies (Debian / Ubuntu / Kubuntu)
```bash
sudo apt update && sudo apt install -y qt6-base-dev qt6-declarative-dev libqt6svg6-dev qt6-wayland qml6-module-qtquick-controls qml6-module-qtquick-templates qml6-module-qtquick-layouts qml6-module-qtqml-workerscript qml6-module-qtquick-window qml6-module-qtquick libsdl2-dev libsdl2-ttf-dev libavcodec-dev libavformat-dev libswscale-dev libva-dev libvdpau-dev libxkbcommon-dev wayland-protocols libdrm-dev libopus-dev libssl-dev libegl1-mesa-dev libgl1-mesa-dev ninja-build cmake
```

### Build with Qt6 / QMake
```bash
qmake6 moonlight-qt.pro
make -j$(nproc)
./app/moonlight
```

### Build & Run Tests with CMake
```bash
cmake -B build -G Ninja -S . -DBUILD_TESTS=ON
ninja -C build
ctest --test-dir build --output-on-failure
```

---

## 📜 License
Licensed under GNU General Public License v3.0 (GPLv3).
