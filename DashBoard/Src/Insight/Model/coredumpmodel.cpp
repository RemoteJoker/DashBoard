#include "coredumpmodel.h"

CoreDumpModel::CoreDumpModel()
{

}

QString CoreDumpModel::Serial(const QStringList v_list){
    QJsonObject v_obj;
    QJsonDocument v_document;
    v_document.setObject(v_obj);
    QByteArray simpbyte_array = v_document.toJson(QJsonDocument::Compact);
    QString simpjson_str(simpbyte_array);
    return simpjson_str;
}

QStringList CoreDumpModel::AntiSerial(const QString v_str){
    QJsonObject v_obj = QJsonDocument::fromJson(v_str.toLocal8Bit().data()).object();
    QStringList v_list;
    g_coredump_msg.clear();

    // 检查JSON解析是否成功
    if (!v_obj.isEmpty() && v_obj.contains("cores")) {
        // 获取cores数组
        QJsonArray coresArray = v_obj.value("cores").toArray();
        // 遍历数组，提取所有core文件路径
        for (const QJsonValue &value : coresArray) {
            if (value.isObject()) {
                QJsonObject coreObj = value.toObject();
                if (coreObj.contains("core")) {
                    QString corePath = coreObj.value("core").toString();
                    QString createTime = coreObj.value("create_time").toString();
                    g_coredump_msg.append(corePath+"@"+createTime);
                    v_list.append(corePath);
                }
            }
        }
    }
    return v_list;
}

QList<QString> CoreDumpModel::GetCoreMsg(){
    return g_coredump_msg;
}
