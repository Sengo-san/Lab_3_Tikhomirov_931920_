#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>
#include <QFileSystemModel>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QPainter>
#include <QPdfWriter>
#include <QGridLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QPdfWriter>
#include <QtSql>
#include <QItemSelectionModel>

#include "graph.h"

//class MainWindow : public QWidget
class MainWindow : public QWidget
{
    Q_OBJECT

private slots:
    void open_directory_slot(); //слот открытия диалоговоого окна с папками
    void print_chart_slot();
    void file_chose_slot(const QItemSelection &, const QItemSelection &);
    void chart_repaint (QString path, QString type, bool bw);
    void recoloring_chart_slot ();
    void type_change_slot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString open_directory_name; //имя открытой директории
    QString open_file_name;//имя открытого файла
    QString saving_path;

    //компановка
    QSplitter *splitter_left; //разделитель
    QSplitter *splitter_right;

    QVBoxLayout *vertical_left_layout;
    QVBoxLayout *vertical_right_layout;
    QHBoxLayout *horizontal_layout;
    QHBoxLayout *horizontal_graph_settings_layout;
    //виджеты
    QPushButton *button_directory;
    QPushButton *button_print_chart;
    QTableView *table_view;// таблица выбора файла (базы данных)
    QFileSystemModel *table_model;//файловая модель для таблицы выбора файла
    QCheckBox *chbox_bw_chart;
    QComboBox *combobox_chart_type;

    //графики
    QChart *empt = new QChart; //пустой график, на случай выбора нечитаемого файла
    QPainter painter;
    Graph* graph;
    QChartView* view;
    /*
    //база
    QSqlDatabase dbase;

    //тестовые мусорные данные
    QString filePath;
    QTableView *view;
    QSqlTableModel *model;
    */

    bool chart_is_open = 0;
};
#endif // MAINWINDOW_H
