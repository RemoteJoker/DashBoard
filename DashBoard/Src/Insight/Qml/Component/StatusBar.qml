// Component/StatusBar.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle {
    id: statusBar
    height: 30
    color: "#e0e0e0"
    
    RowLayout {
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        
        Label {
            text: qsTr("就绪")
            font.pixelSize: 12
        }
        
        Item {
            Layout.fillWidth: true
        }
        
        Label {
            text: Qt.formatDateTime(new Date(), "yyyy-MM-dd hh:mm:ss")
            font.pixelSize: 12
        }
    }
    
    // 顶部边框线
    Rectangle {
        anchors.top: parent.top
        width: parent.width
        height: 1
        color: "#cccccc"
    }
}