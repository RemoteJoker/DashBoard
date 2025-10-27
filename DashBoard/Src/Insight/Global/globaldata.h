#ifndef GLOBALDATA_H
#define GLOBALDATA_H

#include <QAtomicPointer>
#include <QAtomicInt>
#include <QList>
#include <QMap>
#include <QMutex>
#include <QMutexLocker>
#include <QQueue>
#include <QReadWriteLock>
#include <QRecursiveMutex>
#include <QSet>
#include <QString>
#include <QStringList>
#include <QSemaphore>
#include <QWaitCondition>

#define m_log_flag ON //日志开启标志

#define m_version_request "/vlmu/version/request"
#define m_version_report "/vlmu/version/report"
#define m_coredump_request "/vlmu/coredump/request"
#define m_coredump_report "/vlmu/coredump/report"
#define m_loginfo_request "/vlmu/loginfo/request"
#define m_loginfo_report "/vlmu/loginfo/report"
#define m_process_request "/vlmu/process/basic/request"
#define m_process_report "/vlmu/process/basic/report"
#define m_heartbeat_dashboard "/vlmu/heartbeat/dashboard"
#define m_heartbeat_edge "/vlmu/heartbeat/edge"

//全局数据类
class GlobalData
{
//全局MQTT数据缓存--
/*通道配置配置*/
public:
    static void SetProcessSub(QString v_str_in,QString v_str_out);
    static void GetProcessSub(QString &v_str_in,QString &v_str_out);
    static void SetCoreDumpSub(QString v_str_in,QString v_str_out);
    static void GetCoreDumpSub(QString &v_str_in,QString &v_str_out);
    static void SetVersionSub(QString v_str_in,QString v_str_out);
    static void GetVersionSub(QString &v_str_in,QString &v_str_out);
    static void SetLogInfoSub(QString v_str_in,QString v_str_out);
    static void GetLogInfoSub(QString &v_str_in,QString &v_str_out);
    static void SetHeartSub(QString v_str_in,QString v_str_out);
    static void GetHeartSub(QString &v_str_in,QString &v_str_out);

/*接收相关*/
public:
    static void SetProcessMsg(QString v_str);//设置进程信息
    static void SetCoreMsg(QString v_str);//设置存储信息
    static void SetVersionMsg(QString v_str);//设置版本信息
    static void SetLogInfoMsg(QString v_str);//设置日志信息
    static QString GetProcessMsg();//获取进程信息
    static int GetProcessMsgNum();//获取进程信息数量
    static QString GetCoreMsg();//获取存储信息
    static int GetCoreMsgNum();//获取存储信息数量
    static QString GetVersionMsg();//获取版本信息
    static int GetVersionMsgNum();//获取版本信息数量
    static QString GetLogInfoMsg();//获取日志信息
    static int GetLogInfoMsgNum();//获取日志信息数量

/*发送相关*/
public:
    static QString GetCoreInfo();//获取存储信息
    static void SetCoreInfo(QString v_str);//设置存储信息
    static QString GetVersionInfo();//获取版本信息
    static void SetVersionInfo(QString v_str);//设置版本信息
    static QString GetLogInfo();//获取日志信息
    static void SetLogInfo(QString v_str);//设置日志信息

//全局MQTT数据缓存--

public:
    // 删除拷贝构造函数和赋值操作符，确保单例唯一性
    GlobalData(const GlobalData&) = delete;
    GlobalData& operator=(const GlobalData&) = delete;

    // 获取单例实例的静态方法
    static GlobalData& getInstance()
    {
        static GlobalData instance;  // C++11保证线程安全
        return instance;
    }

private:
    // 私有构造函数，防止外部实例化
    GlobalData(){}

private:

    static QQueue<QString>g_source_process_msg;

    static QQueue<QString>g_source_version_msg;

    static QQueue<QString>g_source_coredump_msg;

    static QQueue<QString>g_source_log_info_msg;

    static QString g_source_coredump_get;

    static QString g_source_version_get;

    static QString g_source_log_info_get;

    static QString g_version_request;

    static QString g_version_report;

    static QString g_coredump_request;

    static QString g_coredump_report;

    static QString g_loginfo_request;

    static QString g_loginfo_report;

    static QString g_process_request;

    static QString g_process_report;

    static QString g_heartbeat_dashboard;

    static QString g_heartbeat_edge;
};

#endif // GLOBALDATA_H
