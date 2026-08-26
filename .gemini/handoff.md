# VibeArtemis Build, Architecture & Maintenance Handoff

## 1. Project & Repository Overview

- **Repository**: `gabrielcruzg3/VibeArtemis` (Next-Gen Apollo & Moonlight Desktop Client)
- **Active Branch**: `dev/agy`
- **Current Version**: `0.1.0-alpha.1-agy`
- **Platforms Supported**: Linux (Kubuntu 26.04+ / Debian / Generic Linux x86_64) and Windows (Windows 11 x64)
- **Local Directory**: `/home/g3/Moonshine/VibeArtemis`
- **Workspace Ecosystem**: Part of `~/Moonshine` (Vibepollo host, Artemis Android client, VibeArtemis desktop client)

---

## 2. Artemis Features for Desktop Overview

VibeArtemis implements all features from Artemis Android on Linux and Windows desktop:

| Feature | Subsystem / Implementation | Host Compatibility |
| :--- | :--- | :--- |
| **Apollo Virtual Display Negotiation** | `VirtualDisplayManager` calculates display timings, aspect ratios (21:9, 32:9, 16:10, 16:9), custom refresh rates (120/144/165/240Hz), and scale factors (e.g. 120%, 150%). | Apollo / Vibepollo |
| **Smart Two-Way Clipboard Sync** | `ClipboardSyncManager` synchronizes host and client clipboards via `/actions/clipboard` (GET/POST) and control packets (`0x3001`). Includes loopback detection. | Apollo / Vibepollo |
| **Remote Server Commands** | `ApolloClient` executes remote commands (lock host, switch display, toggle HDR, audio sinks, power states) via `/actions/servercmd` and control stream `0x3000`. | Apollo / Vibepollo |
| **In-Game Overlay HUD & Back Menu** | `InGameOverlay` provides floating HUD / sidebar (`Ctrl+Alt+Shift+Q` or `Guide+Back`) with runtime video scaling, stats telemetry, mouse modes, and server commands. | All hosts |
| **Video Scaling & Rotation** | Dynamic Fit / Fill / Stretch / Zoom modes and 90°/180°/270° stream rotation. | All hosts |
| **Arbitrary Custom Resolutions & Bitrates** | Full custom resolution support and 1 Mbps step bitrate adjustments up to 150+ Mbps. | All hosts |
| **Mouse & Touchpad Modes** | Relative capture, absolute cursor, trackpad gesture scrolling, and local hardware cursor emulation. | All hosts |
| **Modern Dark-Mode Aesthetic** | Clean, responsive UI with host discovery (mDNS), pairing manager, and app grid. | All hosts |

---

## 3. Build & Test Commands

From `/home/g3/Moonshine/VibeArtemis`:

### Step 1: Configure CMake
```bash
cmake -B build -G Ninja -S . \
  -DBUILD_TESTS=ON \
  -DCMAKE_BUILD_TYPE=Release
```

### Step 2: Build Binaries & Test Suite
```bash
ninja -C build -j$(nproc)
```

### Step 3: Run Full Test Suite
```bash
ctest --test-dir build --output-on-failure
```

### Step 4: Generate `.deb` Packages (Linux)
```bash
mkdir -p build/cpack_artifacts
cpack --config build/CPackConfig.cmake -G DEB
```

---

## 4. Release History & Milestones

| Version / Tag | Status | Test Suite | Release Description |
| :--- | :--- | :--- | :--- |
| **`v0.1.0-alpha.1-agy`** | **Active Milestone** | 100% Passing | Initial working desktop client with Apollo Virtual Display negotiation, Smart Clipboard Sync, In-game Overlay HUD, Server Commands, and custom resolution support. |

---

## 5. Architectural Data Flow

```
+-------------------------------------------------------------------------+
|                              VibeArtemis UI                            |
|       (Host Discovery, Pairing Manager, App Grid, Settings, HUD)        |
+-------------------+--------------------------------+--------------------+
                    |                                |
        +-----------v-----------+        +-----------v-----------+
        |     Apollo Client     |        |   Session Coordinator |
        | (HTTP/S + OTP + REST) |        |    (Streaming Engine) |
        +-----------+-----------+        +-----------+-----------+
                    |                                |
        +-----------+-----------+        +-----------+-----------+
        |   Apollo Endpoints    |        |  moonlight-common-c   |
        |  - /actions/clipboard |        |  - Video/Audio RTP    |
        |  - /actions/servercmd |        |  - Control Stream     |
        |  - /bitrate           |        |    - 0x3000 ServerCmd |
        |  - /serverinfo        |        |    - 0x3001 Clipboard |
        +-----------------------+        |  - Input Stream       |
                                         +-----------------------+
```

---

## 6. Service & Environment Reference

| Subsystem | Port / Transport | Purpose |
| :--- | :--- | :--- |
| **GameStream HTTP** | `47989/TCP` | Legacy host discovery & pairing probe |
| **GameStream HTTPS** | `47984/TCP` | Secure host launch, resume, app list, `/actions/clipboard`, `/bitrate` |
| **Sunshine / Apollo Web** | `47990/HTTPS` | Web management & pairing |
| **RTSP Handshake** | `48010/TCP` | Video / Audio session parameters setup |
| **Control Stream** | `47999/UDP` (ENet) | Loss stats, IDR frame requests, server commands (`0x3000`), clipboard (`0x3001`) |
| **Video Stream** | `47998/UDP` | RTP H.264 / HEVC / AV1 video packet flow |
| **Audio Stream** | `48000/UDP` | RTP Opus audio packet flow |
