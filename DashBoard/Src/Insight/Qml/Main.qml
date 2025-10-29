import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    width: 1000
    height: 700
    title: "软件界面"
    visible: true

    // 菜单栏
    menuBar: MenuBar {
        Menu {
            title: "功能"
            MenuItem { text: "指令发送" }
            MenuItem { text: "软件设置" }
        }

        Menu {
            title: "视图"
            MenuItem { text: "进程信息" }
            MenuItem { text: "崩溃转储" }
            MenuItem { text: "日志文件" }
            MenuItem { text: "版本列表" }
        }

        Menu {
            title: "关于"
            MenuItem { text: "关于软件" }
        }
    }

    // 工具栏
    header: ToolBar {
        Row {
            ToolButton { text: "进程信息" }
            ToolButton { text: "崩溃转储" }
            ToolButton { text: "日志文件" }
            ToolButton { text: "版本列表" }
        }
    }

    // 状态栏
    footer: StatusBar {
    }

    // 主界面 - TabWidget
    TabBar {
        id: tabBar
        width: parent.width
        TabButton { text: "进程信息" }
        TabButton { text: "崩溃转储" }
        TabButton { text: "日志文件" }
        TabButton { text: "版本列表" }
    }

    StackLayout {
        width: parent.width
        height: parent.height - tabBar.height
        currentIndex: tabBar.currentIndex
        Item { }
        Item { }
        Item { }
        Item { }
    }
}