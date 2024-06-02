import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: chatRoom
    width: 640
    height: 640
    color: "#ffffff"
    border.color: "#cccccc"
    border.width: 1
    radius: 10

    property string roomName: "chatRoom"
    signal closeRoom

    Column {
        anchors.fill: parent

        // Header with Close Button
        Row {
            width: parent.width
            height: 50
            spacing: 10
            padding: 10

            Text {
                text: roomName
                font.pixelSize: 24
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#333333"
            }

            Button {
                text: "Close"
                anchors.right: parent.right
                onClicked: {
                    chatRoom.closeRoom()
                }
            }
        }

        Row {
            width: parent.width
            height: parent.height - inputRow.height - 60

            // Message Display Area
            ListView {
                id: messageListView
                width: parent.width * 0.75
                height: parent.height
                model: ListModel {
                    // Example messages
                    ListElement { message: "User1: Hello" }
                    ListElement { message: "User2: Hi there!" }
                }
                delegate: Text {
                    text: model.message
                    width: parent.width
                    wrapMode: Text.WordWrap
                }
                clip: true
                spacing: 10
                //padding: 10
            }

            // User List
            ListView {
                id: userListView
                width: parent.width * 0.25
                height: parent.height
                model: ListModel {
                    // Example users
                    ListElement { username: "User1" }
                    ListElement { username: "User2" }
                }
                delegate: Text {
                    text: model.username
                    width: parent.width
                    padding: 10
                }
                clip: true
                spacing: 10
                //padding: 10
            }
        }

        // Input Row
        Row {
            id: inputRow
            width: parent.width
            height: 50
            spacing: 10
            padding: 10

            TextField {
                id: inputField
                width: parent.width * 0.55
                placeholderText: "Enter your message here..."
            }

            Button {
                text: "Send"
                onClicked: {
                    // Logic to send message
                }
            }

            Button {
                text: "Send File"
                onClicked: {
                    // Logic to send file
                }
            }

            Button {
                text: "Send Audio"
                onClicked: {
                    // Logic to send audio
                }
            }
        }
    }
}
