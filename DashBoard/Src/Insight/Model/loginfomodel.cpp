#include "loginfomodel.h"

LogInfoModel::LogInfoModel()
{

}

QString LogInfoModel::Serial(const QStringList v_list){
    QJsonObject v_obj;
    QJsonDocument v_document;
    v_document.setObject(v_obj);
    QByteArray simpbyte_array = v_document.toJson(QJsonDocument::Compact);
    QString simpjson_str(simpbyte_array);
    return simpjson_str;
}

QStringList LogInfoModel::AntiSerial(const QString v_str){
    QJsonObject v_obj = QJsonDocument::fromJson(v_str.toLocal8Bit().data()).object();
    QStringList v_list;
    g_log_info_msg.clear();
    // 检查JSON解析是否成功
    if (!v_obj.isEmpty()) {
        // 获取cores数组
        QJsonArray coresArray = v_obj.value("log_list").toArray();

        // 遍历数组，提取所有core文件路径
        for (const QJsonValue &value : coresArray) {
            if (value.isString()) {
                g_log_info_msg.append(value.toString());
                v_list.append(value.toString());
            }
        }
    }
    return v_list;
}

QList<QString> LogInfoModel::GetLogInfoMsg(){
    return g_log_info_msg;
}
