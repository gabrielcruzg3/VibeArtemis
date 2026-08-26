import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import ComputerModel 1.0

import ComputerManager 1.0
import StreamingPreferences 1.0
import SystemProperties 1.0
import SdlGamepadKeyNavigation 1.0

CenteredGridView {
    property ComputerModel computerModel : createModel()

    id: pcGrid
    focus: true
    activeFocusOnTab: true
    topMargin: 20
    bottomMargin: 5
    cellWidth: 310; cellHeight: 330;
    objectName: qsTr("Computers")

    Component.onCompleted: {
        // Don't show any highlighted item until interacting with them.
        // We do this here instead of onActivated to avoid losing the user's
        // selection when backing out of a different page of the app.
        currentIndex = -1
    }

    // Note: Any initialization done here that is critical for streaming must
    // also be done in CliStartStreamSegue.qml, since this code does not run
    // for command-line initiated streams.
    StackView.onActivated: {
        // Setup signals on CM
        ComputerManager.computerAddCompleted.connect(addComplete)

        // Highlight the first item if a gamepad is connected
        if (currentIndex === -1 && SdlGamepadKeyNavigation.getConnectedGamepads() > 0) {
            currentIndex = 0
        }
    }

    StackView.onDeactivating: {
        ComputerManager.computerAddCompleted.disconnect(addComplete)
    }

    function pairingComplete(error)
    {
        // Close the PIN dialog
        pairDialog.close()

        // Display a failed dialog if we got an error
        if (error !== undefined) {
            errorDialog.text = error
            errorDialog.helpText = ""
            errorDialog.open()
        }
    }

    function addComplete(success, detectedPortBlocking)
    {
        if (!success) {
            errorDialog.text = qsTr("Unable to connect to the specified PC.")

            if (detectedPortBlocking) {
                errorDialog.text += "\n\n" + qsTr("This PC's Internet connection is blocking Moonlight. Streaming over the Internet may not work while connected to this network.")
            }
            else {
                errorDialog.helpText = qsTr("Click the Help button for possible solutions.")
            }

            errorDialog.open()
        }
    }

    function createModel()
    {
        var model = Qt.createQmlObject('import ComputerModel 1.0; ComputerModel {}', parent, '')
        model.initialize(ComputerManager)
        model.pairingCompleted.connect(pairingComplete)
        model.connectionTestCompleted.connect(testConnectionDialog.connectionTestComplete)
        return model
    }

    Row {
        anchors.centerIn: parent
        spacing: 5
        visible: pcGrid.count === 0

        BusyIndicator {
            id: searchSpinner
            visible: StreamingPreferences.enableMdns
            running: visible
        }

        Label {
            height: searchSpinner.height
            elide: Label.ElideRight
            text: StreamingPreferences.enableMdns ? qsTr("Searching for compatible hosts on your local network...")
                                                  : qsTr("Automatic PC discovery is disabled. Add your PC manually.")
            font.pointSize: 20
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.Wrap
        }
    }

    model: computerModel

    delegate: NavigableItemDelegate {
        id: hostCardDelegate
        width: 300; height: 320;
        grid: pcGrid

        property alias pcContextMenu : pcContextMenuLoader.item

        Rectangle {
            id: cardBackground
            anchors.fill: parent
            anchors.margins: 6
            radius: 16
            color: hostCardDelegate.activeFocus ? "#1e2640" : (hostCardDelegate.hovered ? "#161e33" : "#0f1626")
            border.color: hostCardDelegate.activeFocus ? "#a855f7" : (hostCardDelegate.hovered ? "#38bdf8" : "rgba(255, 255, 255, 0.1)")
            border.width: hostCardDelegate.activeFocus ? 2 : 1

            Behavior on color { ColorAnimation { duration: 150 } }
            Behavior on border.color { ColorAnimation { duration: 150 } }

            // --- Card Header: Apollo Badge & Status Pill ---
            Row {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 12
                spacing: 8

                // Apollo / Sunshine Badge
                Rectangle {
                    height: 22
                    width: isApolloText.width + 14
                    radius: 6
                    color: model.isApollo ? "#6366f1" : "#0284c7"

                    Text {
                        id: isApolloText
                        anchors.centerIn: parent
                        text: model.isApollo ? "APOLLO" : "HOST"
                        font.bold: true
                        font.pixelSize: 10
                        color: "#ffffff"
                    }
                }

                Item { Layout.fillWidth: true; width: cardBackground.width - 24 - 150 }

                // Status Pill
                Rectangle {
                    height: 22
                    width: statusRow.width + 12
                    radius: 11
                    color: model.online ? (model.paired ? "rgba(16, 185, 129, 0.2)" : "rgba(245, 158, 11, 0.2)") : "rgba(100, 116, 139, 0.2)"
                    border.color: model.online ? (model.paired ? "#10b981" : "#f59e0b") : "#64748b"
                    border.width: 1

                    Row {
                        id: statusRow
                        anchors.centerIn: parent
                        spacing: 5

                        Rectangle {
                            width: 6; height: 6; radius: 3
                            color: model.online ? (model.paired ? "#10b981" : "#f59e0b") : "#64748b"
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        Text {
                            text: model.statusUnknown ? qsTr("Checking...") : (model.online ? (model.paired ? qsTr("Online") : qsTr("Pairing")) : qsTr("Offline"))
                            font.pixelSize: 10
                            font.bold: true
                            color: model.online ? (model.paired ? "#34d399" : "#fbbf24") : "#94a3b8"
                        }
                    }
                }
            }

            // --- Center Host Icon ---
            Image {
                id: pcIcon
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: parent.top
                anchors.topMargin: 48
                source: "qrc:/res/desktop_windows-48px.svg"
                sourceSize {
                    width: 110
                    height: 110
                }
                opacity: model.online ? 1.0 : 0.45
            }

            Image {
                id: stateIcon
                anchors.horizontalCenter: pcIcon.horizontalCenter
                anchors.verticalCenter: pcIcon.verticalCenter
                visible: !model.statusUnknown && (!model.online || !model.paired)
                source: !model.online ? "qrc:/res/warning_FILL1_wght300_GRAD200_opsz24.svg" : "qrc:/res/baseline-lock-24px.svg"
                sourceSize {
                    width: 48
                    height: 48
                }
            }

            BusyIndicator {
                id: statusUnknownSpinner
                anchors.centerIn: pcIcon
                width: 48
                height: 48
                visible: model.statusUnknown
                running: visible
            }

            // --- Host Name & Subtext ---
            Column {
                anchors.top: pcIcon.bottom
                anchors.topMargin: 10
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 12
                spacing: 3

                Label {
                    id: pcNameText
                    text: model.name
                    width: parent.width
                    font.pixelSize: 18
                    font.bold: true
                    horizontalAlignment: Text.AlignHCenter
                    color: "#ffffff"
                    elide: Text.ElideRight
                }

                Label {
                    text: model.hostIp ? model.hostIp : "127.0.0.1"
                    width: parent.width
                    font.pixelSize: 12
                    horizontalAlignment: Text.AlignHCenter
                    color: "#94a3b8"
                    elide: Text.ElideRight
                }
            }

            // --- Bottom Quick Action Button ---
            Rectangle {
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 12
                height: 32
                radius: 8
                color: model.online ? (model.paired ? (hostCardDelegate.hovered ? "#9333ea" : "#7c3aed") : "#d97706") : "#334155"

                Text {
                    anchors.centerIn: parent
                    text: model.online ? (model.paired ? qsTr("Connect") : qsTr("Pair Host")) : qsTr("Options")
                    font.pixelSize: 12
                    font.bold: true
                    color: "#ffffff"
                }
            }
        }

        Loader {
            id: pcContextMenuLoader
            asynchronous: true
            sourceComponent: NavigableMenu {
                id: pcContextMenu
                initiator: pcContextMenuLoader.parent
                MenuItem {
                    text: qsTr("PC Status: %1").arg(model.online ? qsTr("Online") : qsTr("Offline"))
                    font.bold: true
                    enabled: false
                }
                NavigableMenuItem {
                    text: qsTr("View All Apps")
                    onTriggered: {
                        var component = Qt.createComponent("AppView.qml")
                        var appView = component.createObject(stackView, {"computerIndex": index, "objectName": model.name, "showHiddenGames": true})
                        stackView.push(appView)
                    }
                    visible: model.online && model.paired
                }
                NavigableMenuItem {
                    text: qsTr("Wake PC")
                    onTriggered: computerModel.wakeComputer(index)
                    visible: !model.online && model.wakeable
                }
                NavigableMenuItem {
                    text: qsTr("Test Network")
                    onTriggered: {
                        computerModel.testConnectionForComputer(index)
                        testConnectionDialog.open()
                    }
                }

                NavigableMenuItem {
                    text: qsTr("Rename PC")
                    onTriggered: {
                        renamePcDialog.pcIndex = index
                        renamePcDialog.originalName = model.name
                        renamePcDialog.open()
                    }
                }
                NavigableMenuItem {
                    text: qsTr("Delete PC")
                    onTriggered: {
                        deletePcDialog.pcIndex = index
                        deletePcDialog.pcName = model.name
                        deletePcDialog.open()
                    }
                }
                NavigableMenuItem {
                    text: qsTr("View Details")
                    onTriggered: {
                        showPcDetailsDialog.pcDetails = model.details
                        showPcDetailsDialog.open()
                    }
                }
            }
        }

        onClicked: {
            if (model.online) {
                if (!model.serverSupported) {
                    errorDialog.text = qsTr("The version of GeForce Experience on %1 is not supported by this build of Moonlight. You must update Moonlight to stream from %1.").arg(model.name)
                    errorDialog.helpText = ""
                    errorDialog.open()
                }
                else if (model.paired) {
                    // go to game view
                    var component = Qt.createComponent("AppView.qml")
                    var appView = component.createObject(stackView, {"computerIndex": index, "objectName": model.name})
                    stackView.push(appView)
                }
                else {
                    var pin = computerModel.generatePinString()

                    // Kick off pairing in the background
                    computerModel.pairComputer(index, pin)

                    // Display the pairing dialog
                    pairDialog.pin = pin
                    pairDialog.open()
                }
            } else if (!model.online) {
                // Using open() here because it may be activated by keyboard
                pcContextMenu.open()
            }
        }

        onPressAndHold: {
            // popup() ensures the menu appears under the mouse cursor
            if (pcContextMenu.popup) {
                pcContextMenu.popup()
            }
            else {
                // Qt 5.9 doesn't have popup()
                pcContextMenu.open()
            }
        }

        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton;
            onClicked: {
                parent.pressAndHold()
            }
        }

        Keys.onMenuPressed: {
            // We must use open() here so the menu is positioned on
            // the ItemDelegate and not where the mouse cursor is
            pcContextMenu.open()
        }

        Keys.onDeletePressed: {
            deletePcDialog.pcIndex = index
            deletePcDialog.pcName = model.name
            deletePcDialog.open()
        }
    }

    ErrorMessageDialog {
        id: errorDialog

        // Using Setup-Guide here instead of Troubleshooting because it's likely that users
        // will arrive here by forgetting to enable GameStream or not forwarding ports.
        helpUrl: "https://github.com/moonlight-stream/moonlight-docs/wiki/Setup-Guide"
    }

    NavigableMessageDialog {
        id: pairDialog
        closePolicy: Popup.CloseOnEscape

        // don't allow edits to the rest of the window while open
        property string pin : "0000"
        text:qsTr("Please enter %1 on your host PC. This dialog will close when pairing is completed.").arg(pin)+"\n\n"+
             qsTr("If your host PC is running Sunshine, navigate to the Sunshine web UI to enter the PIN.")
        standardButtons: Dialog.Cancel
        onRejected: {
            // FIXME: We should interrupt pairing here
        }
    }

    NavigableMessageDialog {
        id: deletePcDialog
        // don't allow edits to the rest of the window while open
        property int pcIndex : -1
        property string pcName : ""
        text: qsTr("Are you sure you want to remove '%1'?").arg(pcName)
        standardButtons: Dialog.Yes | Dialog.No

        onAccepted: {
            computerModel.deleteComputer(pcIndex)
        }
    }

    NavigableMessageDialog {
        id: testConnectionDialog
        closePolicy: Popup.CloseOnEscape
        standardButtons: Dialog.Ok

        onAboutToShow: {
            testConnectionDialog.text = qsTr("Moonlight is testing your network connection to determine if any required ports are blocked.") + "\n\n" + qsTr("This may take a few seconds…")
            showSpinner = true
        }

        function connectionTestComplete(result, blockedPorts)
        {
            if (result === -1) {
                text = qsTr("The network test could not be performed because none of Moonlight's connection testing servers were reachable from this PC. Check your Internet connection or try again later.")
                imageSrc = "qrc:/res/baseline-warning-24px.svg"
            }
            else if (result === 0) {
                text = qsTr("This network does not appear to be blocking Moonlight. If you still have trouble connecting, check your PC's firewall settings.") + "\n\n" + qsTr("If you are trying to stream over the Internet, install the Moonlight Internet Hosting Tool on your gaming PC and run the included Internet Streaming Tester to check your gaming PC's Internet connection.")
                imageSrc = "qrc:/res/baseline-check_circle_outline-24px.svg"
            }
            else {
                text = qsTr("Your PC's current network connection seems to be blocking Moonlight. Streaming over the Internet may not work while connected to this network.") + "\n\n" + qsTr("The following network ports were blocked:") + "\n"
                text += blockedPorts
                imageSrc = "qrc:/res/baseline-error_outline-24px.svg"
            }

            // Stop showing the spinner and show the image instead
            showSpinner = false
        }
    }

    NavigableDialog {
        id: renamePcDialog
        property string label: qsTr("Enter the new name for this PC:")
        property string originalName
        property int pcIndex : -1;

        standardButtons: Dialog.Ok | Dialog.Cancel

        onOpened: {
            // Force keyboard focus on the textbox so keyboard navigation works
            editText.forceActiveFocus()
        }

        onClosed: {
            editText.clear()
        }

        onAccepted: {
            if (editText.text) {
                computerModel.renameComputer(pcIndex, editText.text)
            }
        }

        ColumnLayout {
            Label {
                text: renamePcDialog.label
                font.bold: true
            }

            TextField {
                id: editText
                placeholderText: renamePcDialog.originalName
                Layout.fillWidth: true
                focus: true

                Keys.onReturnPressed: {
                    renamePcDialog.accept()
                }

                Keys.onEnterPressed: {
                    renamePcDialog.accept()
                }
            }
        }
    }

    NavigableMessageDialog {
        id: showPcDetailsDialog
        property string pcDetails : "";
        text: showPcDetailsDialog.pcDetails
        imageSrc: "qrc:/res/baseline-help_outline-24px.svg"
        standardButtons: Dialog.Ok
    }

    ScrollBar.vertical: ScrollBar {}
}
