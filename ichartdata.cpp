#include "ichartdata.h"
#include <QMessageBox>


bool operator== (const DataElement x, const DataElement y)//для поиска по заголовку
{
    if (x.head == y.head) return 1;
    else return 0;
}

bool operator!= (const DataElement x, const DataElement y)
{
    if (x.head != y.head) return 1;
    else return 0;
}

bool operator< (const DataElement x, const DataElement y) //для сортировки вектора
{
    if (x.val > y.val) return 1;
    else return 0;
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
                int index_of_header = data.indexOf(DataElement(header, -2));// ищем значение в списке заголвков (-2 проигнорируется перегруженным опреатором сравнения)

                if (index_of_header == -1) {//если еще нет такого заголовка (значение не попало в уже известный интервал)
                    data.push_back(DataElement(header, 1));//заводим новый счетчик
                }
                else{//если счетчик уже есть, увеличиваем
                    data[index_of_header].val ++;
                }
            }
    }

   std::sort (data.begin(), data.end());
   return data;
}

QVector <DataElement> ChartDataJson::getData(QString path_)
{
    //QVector <int> data = new QVector <int>;
      QVector <DataElement> data;
    //получение списка из json-файла, пока что просто случайные числа
    data.push_back(DataElement(2,5));
    data.push_back(DataElement(3,1));
    data.push_back(DataElement(4,2));

    return data;
}
