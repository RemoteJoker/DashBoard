#ifndef RUNLOG_H
#define RUNLOG_H

#define Log(v_log_flag,v_log_text) RunLog::SaveLog(v_log_flag,v_log_text);

enum LogType{
    L_INFO,
    L_WARN,
    L_ERROR,
    L_UNDEFINE,
};

//全局日志类
class RunLog
{
private:
    RunLog();

public:
    static void SaveLog(LogType v_log_type,const std::string& v_message);

private:
    RunLog(const RunLog&) = delete;
    RunLog& operator=(const RunLog&) = delete;
    ~RunLog();

private:
};

#endif // RUNLOG_H
