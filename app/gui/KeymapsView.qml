import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Window 2.2

import SystemProperties 1.0
import SdlGamepadKeyNavigation 1.0

Flickable {
    id: keymapsPage
    objectName: qsTr("Keymaps & Shortcuts")

    boundsBehavior: Flickable.OvershootBounds
    contentWidth: width
    contentHeight: contentColumn.height + 40

    ScrollBar.vertical: ScrollBar {
        anchors {
            right: parent.right
            rightMargin: 4
        }
    }

    Column {
        id: contentColumn
        width: Math.min(parent.width - 32, 960)
        anchors.horizontalCenter: parent.horizontalCenter
        topPadding: 20
        bottomPadding: 20
        spacing: 18

        // Header Banner
        Rectangle {
            width: parent.width
            height: 70
            radius: 12
            color: "#131a2b"
            border.color: "rgba(255, 255, 255, 0.08)"

            RowLayout {
                anchors.fill: parent
                anchors.margins: 16
                spacing: 12

                Rectangle {
                    width: 38; height: 38; radius: 8
                    color: "#7c3aed"
                    Layout.alignment: Qt.AlignVCenter

                    Text {
                        anchors.centerIn: parent
                        text: "⌨️"
                        font.pixelSize: 18
                    }
                }

                ColumnLayout {
                    spacing: 2
                    Layout.fillWidth: true

                    Label {
                        text: qsTr("Streaming Shortcuts & Controller Combos")
                        font.pixelSize: 16
                        font.bold: true
                        color: "#ffffff"
                    }

                    Label {
                        text: qsTr("Quick reference guide for keyboard hotkeys and gamepad button combinations during active streams.")
                        font.pixelSize: 11
                        color: "#94a3b8"
                    }
                }
            }
        }

        // --- Keyboard Shortcuts Card ---
        Rectangle {
            width: parent.width
            height: kbColumn.height + 32
            radius: 12
            color: "#0f1626"
            border.color: "rgba(255, 255, 255, 0.08)"

            Column {
                id: kbColumn
                width: parent.width - 32
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 8
                    Rectangle { width: 4; height: 18; radius: 2; color: "#a855f7"; anchors.verticalCenter: parent.verticalCenter }
                    Label {
                        text: qsTr("Keyboard Stream Shortcuts")
                        font.pixelSize: 14
                        font.bold: true
                        color: "#e2e8f0"
                    }
                }

                Rectangle { width: parent.width; height: 1; color: "rgba(255, 255, 255, 0.06)" }

                // Key rows
                Component {
                    id: shortcutRowComponent
                    RowLayout {
                        width: kbColumn.width
                        spacing: 10

                        Rectangle {
                            height: 28
                            radius: 6
                            color: "#1e293b"
                            border.color: "#334155"
                            Layout.minimumWidth: keyText.width + 16

                            Text {
                                id: keyText
                                anchors.centerIn: parent
                                text: modelData.keys
                                font.pixelSize: 11
                                font.bold: true
                                color: "#38bdf8"
                            }
                        }

                        Label {
                            text: modelData.action
                            font.pixelSize: 12
                            color: "#f1f5f9"
                            Layout.fillWidth: true
                        }

                        Label {
                            text: modelData.desc
                            font.pixelSize: 11
                            color: "#64748b"
                            Layout.preferredWidth: 260
                            elide: Text.ElideRight
                        }
                    }
                }

                Repeater {
                    model: [
                        { keys: "Ctrl + Alt + Shift + A", action: qsTr("Apollo Quick Actions"), desc: qsTr("Opens in-stream menu to switch displays, toggle HDR, mute, sleep, reboot") },
                        { keys: "Ctrl + Alt + Shift + Q", action: qsTr("Quit / Disconnect"), desc: qsTr("Ends the current streaming session immediately") },
                        { keys: "Ctrl + Alt + Shift + S", action: qsTr("Performance Overlay"), desc: qsTr("Toggles FPS, bitrate, and latency stats HUD") },
                        { keys: "Ctrl + Alt + Shift + M", action: qsTr("Toggle Mouse Mode"), desc: qsTr("Switches between direct capture and remote desktop cursor") },
                        { keys: "Ctrl + Alt + Shift + F", action: qsTr("Toggle Fullscreen"), desc: qsTr("Switches between fullscreen and windowed display") },
                        { keys: "Ctrl + Alt + Shift + L", action: qsTr("Lock Mouse Cursor"), desc: qsTr("Locks/unlocks mouse cursor inside the streaming window") },
                        { keys: "Ctrl + Alt + Shift + C", action: qsTr("Show Local Cursor"), desc: qsTr("Toggles local client cursor visibility") },
                        { keys: "Ctrl + Alt + Shift + V", action: qsTr("Paste Clipboard Text"), desc: qsTr("Sends client clipboard text as keystrokes to the host") },
                        { keys: "Ctrl + Alt + Shift + D", action: qsTr("Minimize Window"), desc: qsTr("Minimizes streaming window to taskbar") },
                        { keys: "Ctrl + Alt + Shift + Z", action: qsTr("Raw Mouse / Accel"), desc: qsTr("Toggles mouse acceleration and raw input curve") }
                    ]
                    delegate: shortcutRowComponent
                }
            }
        }

        // --- Gamepad Shortcuts Card ---
        Rectangle {
            width: parent.width
            height: gpColumn.height + 32
            radius: 12
            color: "#0f1626"
            border.color: "rgba(255, 255, 255, 0.08)"

            Column {
                id: gpColumn
                width: parent.width - 32
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 8
                    Rectangle { width: 4; height: 18; radius: 2; color: "#ec4899"; anchors.verticalCenter: parent.verticalCenter }
                    Label {
                        text: qsTr("Gamepad & Controller Combos")
                        font.pixelSize: 14
                        font.bold: true
                        color: "#e2e8f0"
                    }
                }

                Rectangle { width: parent.width; height: 1; color: "rgba(255, 255, 255, 0.06)" }

                Repeater {
                    model: [
                        { keys: "Start + Select + L1 + R1", action: qsTr("Quit / Disconnect Stream"), desc: qsTr("Terminates active stream from your controller") },
                        { keys: "Select + L1 + R1 + X", action: qsTr("Toggle Performance HUD"), desc: qsTr("Shows or hides stream telemetry overlay") },
                        { keys: "Select + L1 + R1 + Y", action: qsTr("Toggle Controller Mouse"), desc: qsTr("Emulates mouse cursor using controller stick") },
                        { keys: "Select + L1 + R1 + B", action: qsTr("Toggle Fullscreen"), desc: qsTr("Switches display between windowed and fullscreen") },
                        { keys: "Hold Start (3 seconds)", action: qsTr("Stick Mouse Mode"), desc: qsTr("Quick stick-to-mouse emulation toggle") }
                    ]
                    delegate: shortcutRowComponent
                }
            }
        }

        // --- Artemis & Apollo Smart Features Card ---
        Rectangle {
            width: parent.width
            height: apColumn.height + 32
            radius: 12
            color: "#0f1626"
            border.color: "rgba(255, 255, 255, 0.08)"

            Column {
                id: apColumn
                width: parent.width - 32
                anchors.centerIn: parent
                spacing: 10

                Row {
                    spacing: 8
                    Rectangle { width: 4; height: 18; radius: 2; color: "#06b6d4"; anchors.verticalCenter: parent.verticalCenter }
                    Label {
                        text: qsTr("Artemis & Apollo Smart Features")
                        font.pixelSize: 14
                        font.bold: true
                        color: "#e2e8f0"
                    }
                }

                Rectangle { width: parent.width; height: 1; color: "rgba(255, 255, 255, 0.06)" }

                Repeater {
                    model: [
                        { keys: "Auto-Negotiation", action: qsTr("Virtual Display Timing"), desc: qsTr("Calculates client ultrawide resolution and refresh rate on launch") },
                        { keys: "Two-Way Sync", action: qsTr("Smart Clipboard Sharing"), desc: qsTr("Automatically syncs clipboard text between client & host") },
                        { keys: "Zero-Queue", action: qsTr("Ultra-Low Latency Mode"), desc: qsTr("Bypasses frame buffering queues for instant responsiveness") }
                    ]
                    delegate: shortcutRowComponent
                }
            }
        }
    }
}
