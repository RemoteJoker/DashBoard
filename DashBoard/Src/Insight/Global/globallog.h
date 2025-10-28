#ifndef GLOBALLOG_H
#define GLOBALLOG_H

#include <QString>

#define Log(v_log_flag,v_log_text) GlobalLog::SaveLog(v_log_flag,v_log_text);

enum LogType{
    L_INFO,
    L_WARN,
    L_ERROR,
    L_UNDEFINE,
};

//全局日志类
class GlobalLog
{
private:
    GlobalLog();

public:
    static void SaveLog(LogType v_log_type,const std::string& v_message);

private:
    GlobalLog(const GlobalLog&) = delete;
    GlobalLog& operator=(const GlobalLog&) = delete;
    ~GlobalLog();

private:
};

#endif // GLOBALLOG_H
