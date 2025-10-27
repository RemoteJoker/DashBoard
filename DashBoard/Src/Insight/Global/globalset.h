#ifndef GLOBALSET_H
#define GLOBALSET_H

#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QDateTime>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QUuid>
#include <QProcess>
#include <QQueue>
#include <QString>
#include <QSettings>
#include <QString>

//命令类型
enum Command{
    Dump,
    Version,
    LogInfo,
};

//数据模式
enum DataModel{
    Auto,//自动更新
    UnAuto//手动更新
};

//更新请求
enum SettingFlag{
    Enable,//启动
    UnEnable//关闭
};

class GlobalSet
{
//属性设置
public:
    static void SetDataModel(quint32);
    static void GetDataModel(quint32&);
    static void SetAttribute(quint32,quint32,quint32);
    static void GetAttribute(quint32&,quint32&,quint32&);
    static void SetFlag(quint32);
    static void GetFlag(quint32&);

private:
    static quint32 m_data_model;
    static quint32 m_set_width;
    static quint32 m_set_height;
    static quint32 m_set_flag;


//UI设置
public:
    static void SetWindowsSize(quint32,quint32);
    static void GetWindowsSize(quint32&,quint32&);

    static void SetMainWindow(QString,QString,QString,quint32,quint32,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString,QString);
    static void GetMainWindow(QString&,QString&,QString&,quint32&,quint32&,QString&,QString&,QString&,QString&,QString&,QString&,QString&,QString&,QString&,QString&,QString&,QString&);

    static void SetSetWindow(QString,QString);
    static void GetSetWindow(QString&,QString&);

    static void SetCmdWindow(QString,QString,QString,QString,QString);
    static void GetCmdWindow(QString&,QString&,QString&,QString&,QString&);

    static void SetProcessWindow(QString,QString,quint32,QStringList,QString,QString);
    static void GetProcessWindow(QString&,QString&,quint32&,QStringList&,QString&,QString&);

    static void SetDumpWindow(QString,QString,QString,QString);
    static void GetDumpWindow(QString&,QString&,QString&,QString&);

    static void SetVersionWindow(QString,QString,QString,QString);
    static void GetVersionWindow(QString&,QString&,QString&,QString&);

    static void SetLogWindow(QString,QString,QString,QString);
    static void GetLogWindow(QString&,QString&,QString&,QString&);

    static void SetAboutWindow(QString,QString);
    static void GetAboutWindow(QString&,QString&);


private:
    static QString m_mainwindow_name;
    static QString m_mainwindow_version;
    static QString m_mainwindow_style;
    static quint32 m_mainwindow_width;
    static quint32 m_mainwindow_height;
    static QString m_mainwindow_menu0_title;
    static QString m_mainwindow_menu1_title;
    static QString m_mainwindow_menu1_cmdview;
    static QString m_mainwindow_menu1_setview;
    static QString m_mainwindow_menu2_title;
    static QString m_mainwindow_menu2_processview;
    static QString m_mainwindow_menu2_dumpview;
    static QString m_mainwindow_menu2_versionview;
    static QString m_mainwindow_menu2_logview;
    static QString m_mainwindow_menu3_title;
    static QString m_mainwindow_menu4_title;
    static QString m_mainwindow_menu4_aboutview;

    static QString m_setwindow_name;
    static QString m_setwindow_style;

    static QString m_cmdwindow_name;
    static QString m_cmdwindow_style;
    static QString m_cmdwindow_button_1;
    static QString m_cmdwindow_button_2;
    static QString m_cmdwindow_button_3;

    static QString m_processwindow_name;
    static QString m_processwindow_style;
    static quint32 m_processwindow_num;
    static QStringList m_processwindow_list;
    static QString m_processwindow_flush;
    static QString m_processwindow_hide;

    static QString m_dumpwindow_name;
    static QString m_dumpwindow_style;
    static QString m_dumpwindow_flush;
    static QString m_dumpwindow_hide;

    static QString m_versionwindow_name;
    static QString m_versionwindow_style;
    static QString m_versionwindow_flush;
    static QString m_versionwindow_hide;

    static QString m_logwindow_name;
    static QString m_logwindow_style;
    static QString m_logwindow_flush;
    static QString m_logwindow_hide;

    static QString m_aboutwindow_name;
    static QString m_aboutwindow_style;

private:
    GlobalSet(){}
    GlobalSet(const GlobalSet&) = delete;
    GlobalSet& operator=(const GlobalSet&) = delete;
    ~GlobalSet(){}
};

#endif // GLOBALSET_H
