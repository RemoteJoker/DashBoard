#include "versionmodel.h"

VersionModel::VersionModel()
{

}

QString VersionModel::Serial(const QStringList v_list){
    QJsonObject v_obj;
    QJsonDocument v_document;
    v_document.setObject(v_obj);
    QByteArray simpbyte_array = v_document.toJson(QJsonDocument::Compact);
    QString simpjson_str(simpbyte_array);
    return simpjson_str;
}

QStringList VersionModel::AntiSerial(const QString v_str){
    QJsonObject v_obj = QJsonDocument::fromJson(v_str.toLocal8Bit().data()).object();
    QStringList v_list;
    g_version_msg.clear();
    if (v_obj.contains("version_info")) {
        QString v_processesArray = v_obj["version_info"].toString();
        //解析字符串
        v_list = v_processesArray.split('\n', Qt::SkipEmptyParts);

        // 可选：去除每行首尾的空白字符
        for (int i = 0; i < v_list.size(); ++i) {
            v_list[i] = v_list[i].trimmed();
        }
        for (QString v_str:v_list){
            g_version_msg.append(v_list);
        }
    }
    return v_list;
}

QList<QString> VersionModel::GetVersionMsg(){
    return g_version_msg;
}
