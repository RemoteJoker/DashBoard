// Component/AboutView.qml
import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Dialog {
    id: aboutDialog
    title: qsTr("关于软件")
    modal: true
    standardButtons: Dialog.Ok
    width: 500
    height: 200
    
    ColumnLayout {
        anchors.fill: parent
        spacing: 10
        
        Label {
            text: "软件: DashBoard - 前端展示"
            font.bold: true
            font.pixelSize: 16
            Layout.alignment: Qt.AlignHCenter
        }
        
        Label {
            text: "使用 Qt 框架，包含 QChart 库"
            Layout.alignment: Qt.AlignHCenter
        }
        
        Label {
            text: "遵循 LGPL 协议"
            Layout.alignment: Qt.AlignHCenter
        }
        
        Item {
            Layout.fillHeight: true
        }
    }
}