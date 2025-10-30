import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import "./View"
import "./Component"

ApplicationWindow {
    visible: true
    width: 800
    height: 600
    title: "DashBoard"

    menuBar:MenuBar{
        Menu {
            title : qsTr("功能")
            Action {
                text : qsTr("指令操作")
            }
            Action {
                text : qsTr("软件设置")
            }
        }
        Menu {
            title : qsTr("视图")
            Action {
                text : qsTr("进程展示")
            }
            Action {
                text : qsTr("内核转储")
            }
            Action {
                text : qsTr("版本信息")
            }
            Action {
                text : qsTr("日志文件")
            }
        }
        Menu {
            title : qsTr("关于")
            Action {
                text : qsTr("关于软件")
                onTriggered : {
                    aboutView.open()
                }
            }
        }
    }

    header:ToolBar{
        RowLayout {
            anchors.fill: parent
            spacing: 0
        
            ToolButton {
                text: qsTr("进程展示")
                Layout.fillWidth: true
            }
        
            ToolButton {
                text: qsTr("内核转储")
                Layout.fillWidth: true
            }
        
            ToolButton {
                text: qsTr("版本信息")
                Layout.fillWidth: true
            }
        
            ToolButton {
                text: qsTr("日志文件")
                Layout.fillWidth: true
            }
        }
    }

    ColumnLayout {
        anchors.fill: parent

        TabBar {
            id: tabBar
            Layout.fillWidth: true

            TabButton { text: qsTr("系统概览") }
            TabButton { text: qsTr("CPU") }
            TabButton { text: qsTr("MEM") }
            TabButton { text: qsTr("进程&&线程") }
        }

        StackLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabBar.currentIndex
            Page{ Text{ anchors.centerIn: parent; text: "This is page1" } }
            Page{ Text{ anchors.centerIn: parent; text: "This is page2" } }
            Page{ Text{ anchors.centerIn: parent; text: "This is page3" } }
            Page{ Text{ anchors.centerIn: parent; text: "This is page4" } }
        }
    }

    footer : StatusBar

    AboutView {
        id : aboutView
        anchors.centerIn: parent
    }
}