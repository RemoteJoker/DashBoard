#include "processmodel.h"

ProcessModel::ProcessModel()
{

}

QString ProcessModel::Serial(const QStringList v_list){
    QJsonObject v_obj;
    QJsonDocument v_document;
    v_document.setObject(v_obj);
    QByteArray simpbyte_array = v_document.toJson(QJsonDocument::Compact);
    QString simpjson_str(simpbyte_array);
    return simpjson_str;
}

QStringList ProcessModel::AntiSerial(const QString v_str){
    QJsonObject v_obj = QJsonDocument::fromJson(v_str.toLocal8Bit().data()).object();
    QStringList v_list;
    if (v_obj.contains("processes") && v_obj["processes"].isArray()) {
        QJsonArray v_processesArray = v_obj["processes"].toArray();
        g_process_msg.clear();
        // 遍历所有进程信息
        for (const QJsonValue &processValue : v_processesArray) {
            if (processValue.isObject()) {
                QJsonObject v_processObj = processValue.toObject();

                // 提取每个字段
                QString v_processName = v_processObj["process_name"].toString();
                ProcessMsg v_process_msg;
                v_process_msg.start_time = v_processObj["start_time"].toString();
                v_process_msg.elapsed_time = v_processObj["elapsed_time"].toString();
                v_process_msg.process_id = v_processObj["pid"].toString();
                v_process_msg.alive = v_processObj["alive"].toBool();
                g_process_msg.insert(v_processName,v_process_msg);
                //此处数据已经存入全局变量
                v_list<<v_processName<<"生存状态"<<v_process_msg.start_time<<v_process_msg.elapsed_time;
            }
        }
    }
    return v_list;
}

QMap<QString,ProcessMsg> ProcessModel::GetProcessMsg(){
    return g_process_msg;
}
