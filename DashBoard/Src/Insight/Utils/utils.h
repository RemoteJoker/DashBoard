#ifndef UTILS_H
#define UTILS_H

#include "Global/globalset.h"
#include "Global/globaldata.h"

#ifdef _WIN32
#define _WIN32_WINNT 0x0602  // Windows 8 及以上
#define NTDDI_VERSION 0x06020000
#include <windows.h>
#include <wbemidl.h>
#include <comdef.h>
#include <dxgi.h>
#include <dxgi1_2.h>  // 包含 CreateDXGIFactory2 定义
#include <comutil.h>
#include <tchar.h>
#include <psapi.h>
#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "comsuppw.lib")

#else

#endif
//杂项工具类，不可实例化，不可继承
class Utils final
{
private:
    Utils();
    Utils(const Utils&) = delete;
    Utils& operator=(const Utils&) = delete;

public:
    static bool InitApp();//初始化界面
    static void SetRunPath();//设置运行时路径

    static qint64 GetTimeStampS();//获取时间戳S
    static qint64 GetTimeStampMS();//获取时间戳MS
    static QString GetRunPath();//获取运行时路径
    static QString DeCryptData();//解密
    static QString EnCryptData();//加密
    //检查目标路径下是否有文件夹
    static bool CheckDirExist(QString);
    //检查目标路径下是否有文件
    static bool CheckFileExist(QString);
    //验证MYSQL服务是否在运行
    static bool CheckMySqlSrv();
    //验证文件完整性
    static bool CheckFileIntegrity();
private:
};

#endif // UTILS_H
