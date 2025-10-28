#include "globallog.h"
#include <QDebug>

GlobalLog::GlobalLog() {
}

GlobalLog::~GlobalLog() {
}

void GlobalLog::SaveLog(LogType v_log_type, const std::string& v_message) {
#if m_log_flag == ON //开启日志
#ifdef QT_DEBUG
    switch (v_log_type) {
        case 0: qDebug()<<" INFO:"<<QString::fromStdString(v_message); break;
        case 1: qDebug()<<"WARN:"<<QString::fromStdString(v_message); break;
        case 2: qDebug()<<"ERROR:"<<QString::fromStdString(v_message); break;
        default: qDebug()<<"UNDEFINE:"<<QString::fromStdString(v_message); break;
    }
#else
    switch (v_log_type) {
        case 0: qDebug()<<" INFO:"<<QString::fromStdString(v_message); break;
        case 1: qDebug()<<"WARN:"<<QString::fromStdString(v_message); break;
        case 2: qDebug()<<"ERROR:"<<QString::fromStdString(v_message); break;
        default: qDebug()<<"UNDEFINE:"<<QString::fromStdString(v_message); break;
    }
#endif
#else //关闭日志
#endif
}
