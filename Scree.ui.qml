

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.2
import QtQuick.Controls 6.2
import QtQuick3D 6.4
import QtMultimedia 6.3
import MyModule.Constants 1.0

Rectangle {
    id: rectangle2
    width: Constants.width
    height: Constants.height

    color: Constants.backgroundColor
    radius: 1
    border.color: "#ffffff"
    Rectangle {
        id: rectangle
        x: 715
        y: 907
        width: 526
        height: 80
        opacity: 0.307
        color: "#2d2d2d"
        radius: 21
        border.color: "#0c0c0c"
        border.width: 2
        clip: true
    }

    Button {
        id: button
        x: 771
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
        font.family: "Verdana"

        Connections {
            id: connections
            target: button
            onClicked: rectangle2.state = ""
        }
    }

    Button {
        id: button1
        x: 848
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
    }

    Button {
        id: button2
        x: 922
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
    }

    Button {
        id: button3
        x: 994
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
    }

    Button {
        id: button4
        x: 1061
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
    }

    Button {
        id: button5
        x: 1131
        y: 927
        width: 50
        height: 40
        text: qsTr("Button")
    }

    Rectangle {
        id: rectangle1
        x: 498
        y: 684
        width: 200
        height: 200
        color: "#ffffff"
    }

    Item {
        id: __materialLibrary__
    }

}


