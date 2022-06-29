#include "IchartData.h"
#include <QMessageBox>

bool operator== (const DataElement x, const DataElement y) //для поиска по заголовку
{
    if (x.head == y.head) return 1;
    else return 0;
}
bool operator!= (const DataElement x, const DataElement y)
{
    if (x == y) return 0;
    else return 1;
}

QVector <DataElement> ChartDataSqlite::getData (QString path_)
{    
    QVector <DataElement> data; //вектор заголвков и счетчиков

    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE"); //создаем соединение по умолчанию с драйвером "QSQLITE"
    dbase.setDatabaseName(path_);

    if (!dbase.open()) {//открываем, проверяем на открытие
        QMessageBox msg;
        msg.setText("Can`t open database " + path_);
        msg.exec();
    }

    else {//собираем данные из базы в data
        QSqlQuery query("SELECT * FROM " + dbase.tables().takeFirst()); //запрос на первую таблицу базы
            while (query.next()) {
                int header = floor(query.value(1).toDouble()); //округленное вниз
                int index_of_header = data.indexOf(DataElement(header, -2));// ищем значение в списке заголвков (-2 проигнорируется перегруженным опреатором)

                if (index_of_header == -1) {//если значение не попало в известный интервал
                    data.push_back(DataElement(header, 1));//заводим новый
                }
                else{//если интервал уже есть, увеличиваем счетчик
                    data[index_of_header].val ++;
                }
            }
    }

   return data;
}

QVector <DataElement> ChartDataJson::getData(QString path_)
{
    QVector <DataElement> data;

    QString val;
    QFile file;
    file.setFileName(path_);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jsonObject = doc.object();

    foreach (QJsonValueRef x, jsonObject){
        int header = floor(x.toDouble()); //округленное вниз
        int index_of_header = data.indexOf(DataElement(header, -2));// ищем значение в списке заголвков (-2 проигнорируется перегруженным опреатором сравнения)

        if (index_of_header == -1) {//если еще нет такого заголовка (значение не попало в уже известный интервал)
            data.push_back(DataElement(header, 1));//заводим новый счетчик
        }
        else{//если счетчик уже есть, увеличиваем
            data[index_of_header].val ++;
        }
    }




    return data;
}
