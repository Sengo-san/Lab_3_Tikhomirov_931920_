#include "iscanner.h"

#include <QSqlDatabase>
#include <QSqlQuery>

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

DataGraph* SqliteScanner::getData(QString source_path)
{
    DataGraph* data = new DataGraph ();

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE"); //создаем соединение по умолчанию с драйвером "QSQLITE"
    dbase.setDatabaseName(source_path);

/*
    //идея выкидывать окно из сканнера забракована, т.к. сканнер - низкоуровневый класс
    if (!dbase.open()) {//открываем, проверяем на открытие
        QMessageBox msg;
        msg.setText("Can`t open database " + path_);
        msg.exec();
    }
*/
    if (dbase.open()) {
        //собираем данные из базы в data:
        QSqlQuery query ("SELECT * FROM " + dbase.tables().takeFirst() + " LIMIT 0,10"); //запрос на первую таблицу базы, для графика возьмем только первые 10 элементов
        while (query.next()) {
            data->push (query.value(0).toString() , query.value(1).toFloat()); //складываем элемент в данные
            }
    data->dataGot(); //помечаем в данных, что они успешно собраны
    }
    return data;
}

DataGraph* JsonScanner::getData(QString source_path)
{
    DataGraph* data = new DataGraph ();
       QString val;
       QFile file;
       file.setFileName(source_path);
       if  (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

           val = file.readAll();
           file.close();
           QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
           QJsonObject jsonObject = doc.object();

           QStringList keys (jsonObject.keys());
           //QList<float> vals;
           //QList<DataElement> scandata;//необработанные данные
           int i = 0;
           foreach (QJsonValueRef x, jsonObject){
               if (x.isDouble()) {//если объект НЕ переменная [дата, значение] - пропускаем
                   data->push(keys.at(i), x.toDouble());
                   //data->push(keys.at(i), x.toDouble());
               }
               i++;
               if (i > 9) break; //для графика возьмем только первые 10 элементов
           }
           data->dataGot();
       }

       return data;
}
