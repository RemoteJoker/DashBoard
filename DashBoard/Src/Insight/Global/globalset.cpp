#include "globalset.h"

quint32 GlobalSet::m_data_model = Auto;

quint32 GlobalSet::m_set_width;

quint32 GlobalSet::m_set_height;

quint32 GlobalSet::m_set_flag = UnEnable;

void GlobalSet::SetDataModel(quint32 v_str){
    m_data_model = v_str;
}
void GlobalSet::GetDataModel(quint32& v_str){
    v_str = m_data_model;
}

void GlobalSet::SetAttribute(quint32 v_str_0,quint32 v_str_1,quint32 v_str_2){
    m_set_width = v_str_0;
    m_set_height = v_str_1;
    m_data_model = v_str_2;
}

void GlobalSet::GetAttribute(quint32 &v_str_0,quint32 &v_str_1,quint32 &v_str_2){
    v_str_0 = m_set_width;
    v_str_1 = m_set_height;
    v_str_2 = m_data_model;
}

void GlobalSet::SetFlag(quint32 v_str_0){
    m_set_flag = v_str_0;
}

void GlobalSet::GetFlag(quint32& v_str_0){
    v_str_0 = m_set_flag;
}

QString GlobalSet::m_mainwindow_name = "VLMUInsight";
QString GlobalSet::m_mainwindow_version = "0.0.2";
QString GlobalSet::m_mainwindow_style = ":/Src/Style/mainwindow.qss";
quint32 GlobalSet::m_mainwindow_width = 1400;
quint32 GlobalSet::m_mainwindow_height = 900;
QString GlobalSet::m_mainwindow_menu0_title = "文件";
QString GlobalSet::m_mainwindow_menu1_title = "功能";
QString GlobalSet::m_mainwindow_menu1_cmdview = "指令";
QString GlobalSet::m_mainwindow_menu1_setview = "设置";
QString GlobalSet::m_mainwindow_menu2_title = "视窗";
QString GlobalSet::m_mainwindow_menu2_processview = "进程";
QString GlobalSet::m_mainwindow_menu2_dumpview = "转储";
QString GlobalSet::m_mainwindow_menu2_versionview = "版本";
QString GlobalSet::m_mainwindow_menu2_logview = "日志";
QString GlobalSet::m_mainwindow_menu3_title = "插件";
QString GlobalSet::m_mainwindow_menu4_title = "帮助";
QString GlobalSet::m_mainwindow_menu4_aboutview = "关于软件";

QString GlobalSet::m_setwindow_name = "设置";
QString GlobalSet::m_setwindow_style = ":/Src/Style/setview.qss";

QString GlobalSet::m_cmdwindow_name = "指令";
QString GlobalSet::m_cmdwindow_style = ":/Src/Style/cmdview.qss";
QString GlobalSet::m_cmdwindow_button_1 = "转储";
QString GlobalSet::m_cmdwindow_button_2 = "版本";
QString GlobalSet::m_cmdwindow_button_3 = "日志";

QString GlobalSet::m_processwindow_name = "进程视图";
QString GlobalSet::m_processwindow_style = ":/Src/Style/processview.qss";
quint32 GlobalSet::m_processwindow_num = 5;
QStringList GlobalSet::m_processwindow_list = {"进程名", "进程号", "存活状态", "启动时间", "持续时间"};
QString GlobalSet::m_processwindow_flush = "刷新";
QString GlobalSet::m_processwindow_hide = "隐藏";

QString GlobalSet::m_dumpwindow_name = "转储";
QString GlobalSet::m_dumpwindow_style = ":/Src/Style/dumpview.qss";
QString GlobalSet::m_dumpwindow_flush = "刷新";
QString GlobalSet::m_dumpwindow_hide = "隐藏";

QString GlobalSet::m_versionwindow_name = "版本";
QString GlobalSet::m_versionwindow_style = ":/Src/Style/versionview.qss";
QString GlobalSet::m_versionwindow_flush = "刷新";
QString GlobalSet::m_versionwindow_hide = "隐藏";

QString GlobalSet::m_logwindow_name = "日志";
QString GlobalSet::m_logwindow_style = ":/Src/Style/logview.qss";
QString GlobalSet::m_logwindow_flush = "刷新";
QString GlobalSet::m_logwindow_hide = "隐藏";

QString GlobalSet::m_aboutwindow_name = "关于软件";
QString GlobalSet::m_aboutwindow_style = ":/Src/Style/aboutview.qss";

void GlobalSet::SetWindowsSize(quint32 v_w,quint32 v_h){
    m_mainwindow_width = v_w;
    m_mainwindow_height = v_h;
}

void GlobalSet::GetWindowsSize(quint32 &v_w,quint32 &v_h){
    v_w = m_mainwindow_width;
    v_h = m_mainwindow_height;
}

void GlobalSet::SetMainWindow(QString v_str_0,QString v_str_1,QString v_str_2,quint32 v_str_3,
                              quint32 v_str_4,QString v_str_5,QString v_str_6,QString v_str_7,
                              QString v_str_8,QString v_str_9,QString v_str_10,QString v_str_11,
                              QString v_str_12,QString v_str_13,QString v_str_14,QString v_str_15,
                              QString v_str_16){
    m_mainwindow_name = v_str_0;
    m_mainwindow_version = v_str_1;
    m_mainwindow_style = v_str_2;
    m_mainwindow_width = v_str_3;
    m_mainwindow_height = v_str_4;
    m_mainwindow_menu0_title = v_str_5;
    m_mainwindow_menu1_title = v_str_6;
    m_mainwindow_menu1_cmdview = v_str_7;
    m_mainwindow_menu1_setview = v_str_8;
    m_mainwindow_menu2_title = v_str_9;
    m_mainwindow_menu2_processview = v_str_10;
    m_mainwindow_menu2_dumpview = v_str_11;
    m_mainwindow_menu2_versionview = v_str_12;
    m_mainwindow_menu2_logview = v_str_13;
    m_mainwindow_menu3_title = v_str_14;
    m_mainwindow_menu4_title = v_str_15;
    m_mainwindow_menu4_aboutview = v_str_16;
}
void GlobalSet::GetMainWindow(QString &v_str_0,QString &v_str_1,QString &v_str_2,quint32 &v_str_3,
                   quint32 &v_str_4,QString &v_str_5,QString &v_str_6,QString &v_str_7,
                   QString &v_str_8,QString &v_str_9,QString &v_str_10,QString &v_str_11,
                   QString &v_str_12,QString &v_str_13,QString &v_str_14,QString &v_str_15,
                   QString &v_str_16){
    v_str_0 = m_mainwindow_name;
    v_str_1 = m_mainwindow_version;
    v_str_2 = m_mainwindow_style;
    v_str_3 = m_mainwindow_width;
    v_str_4 = m_mainwindow_height;
    v_str_5 = m_mainwindow_menu0_title;
    v_str_6 = m_mainwindow_menu1_title;
    v_str_7 = m_mainwindow_menu1_cmdview;
    v_str_8 = m_mainwindow_menu1_setview;
    v_str_9 = m_mainwindow_menu2_title;
    v_str_10 = m_mainwindow_menu2_processview;
    v_str_11 = m_mainwindow_menu2_dumpview;
    v_str_12 = m_mainwindow_menu2_versionview;
    v_str_13 = m_mainwindow_menu2_logview;
    v_str_14 = m_mainwindow_menu3_title;
    v_str_15 = m_mainwindow_menu4_title;
    v_str_16 = m_mainwindow_menu4_aboutview;
}

void GlobalSet::SetSetWindow(QString v_str_0,QString v_str_1){
    m_setwindow_name = v_str_0;
    m_setwindow_style = v_str_1;
}
void GlobalSet::GetSetWindow(QString&v_str_0,QString&v_str_1){
    v_str_0 = m_setwindow_name;
    v_str_1 = m_setwindow_style;
}

void GlobalSet::SetCmdWindow(QString v_str_0,QString v_str_1,QString v_str_2,QString v_str_3,QString v_str_4){
    m_cmdwindow_name = v_str_0;
    m_cmdwindow_style = v_str_1;
    m_cmdwindow_button_1 = v_str_2;
    m_cmdwindow_button_2 = v_str_3;
    m_cmdwindow_button_3 = v_str_4;
}
void GlobalSet::GetCmdWindow(QString &v_str_0,QString &v_str_1,QString &v_str_2,QString &v_str_3,QString &v_str_4){
    v_str_0 = m_cmdwindow_name;
    v_str_1 = m_cmdwindow_style;
    v_str_2 = m_cmdwindow_button_1;
    v_str_3 = m_cmdwindow_button_2;
    v_str_4 = m_cmdwindow_button_3;
}

void GlobalSet::SetProcessWindow(QString v_str_0,QString v_str_1,quint32 v_str_2,QStringList v_str_3,
                                 QString v_str_4,QString v_str_5){
    m_processwindow_name = v_str_0;
    m_processwindow_style = v_str_1;
    m_processwindow_num = v_str_2;
    m_processwindow_list = v_str_3;
    m_processwindow_flush = v_str_4;
    m_processwindow_hide = v_str_5;
}

void GlobalSet::GetProcessWindow(QString &v_str_0,QString &v_str_1,quint32 &v_str_2,QStringList &v_str_3,
                                 QString &v_str_4,QString &v_str_5){
    v_str_0 = m_processwindow_name;
    v_str_1 = m_processwindow_style;
    v_str_2 = m_processwindow_num;
    v_str_3 = m_processwindow_list;
    v_str_4 = m_processwindow_flush;
    v_str_5 = m_processwindow_hide;
}

void GlobalSet::SetDumpWindow(QString v_str_0,QString v_str_1,QString v_str_2,QString v_str_3){
    m_dumpwindow_name = v_str_0;
    m_dumpwindow_style = v_str_1;
    m_dumpwindow_flush = v_str_2;
    m_dumpwindow_hide = v_str_3;
}
void GlobalSet::GetDumpWindow(QString &v_str_0,QString &v_str_1,QString &v_str_2,QString &v_str_3){
    v_str_0 = m_dumpwindow_name;
    v_str_1 = m_dumpwindow_style;
    v_str_2 = m_dumpwindow_flush;
    v_str_3 = m_dumpwindow_hide;
}

void GlobalSet::SetVersionWindow(QString v_str_0,QString v_str_1,QString v_str_2,QString v_str_3){
    m_versionwindow_name = v_str_0;
    m_versionwindow_style = v_str_1;
    m_versionwindow_flush = v_str_2;
    m_versionwindow_hide = v_str_3;
}
void GlobalSet::GetVersionWindow(QString &v_str_0,QString &v_str_1,QString &v_str_2,QString &v_str_3){
    v_str_0 = m_versionwindow_name;
    v_str_1 = m_versionwindow_style;
    v_str_2 = m_versionwindow_flush;
    v_str_3 = m_versionwindow_hide;
}

void GlobalSet::SetLogWindow(QString v_str_0,QString v_str_1,QString v_str_2,QString v_str_3){
    m_logwindow_name = v_str_0;
    m_logwindow_style = v_str_1;
    m_logwindow_flush = v_str_2;
    m_logwindow_hide = v_str_3;
}
void GlobalSet::GlobalSet::GetLogWindow(QString &v_str_0,QString &v_str_1,QString &v_str_2,QString &v_str_3){
    v_str_0 = m_logwindow_name;
    v_str_1 = m_logwindow_style;
    v_str_2 = m_logwindow_flush;
    v_str_3 = m_logwindow_hide;
}

void GlobalSet::SetAboutWindow(QString v_str_0,QString v_str_1){
    m_aboutwindow_name = v_str_0;
    m_aboutwindow_style = v_str_1;
}

void GlobalSet::GetAboutWindow(QString &v_str_0,QString &v_str_1){
    v_str_0 = m_aboutwindow_name;
    v_str_1 = m_aboutwindow_style;
}
