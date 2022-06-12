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

#include <QtSql> //для теста

//class MainWindow : public QWidget
class MainWindow : public QWidget
{
    Q_OBJECT

private slots:
    void open_directory_slot(); //слот открытия диалоговоого окна с папками
    void print_chart_slot();
    void file_chose_slot();

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString directory_name;//имя открытой директории


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
    QChartView *chart_view;
    QChart *chart;
    QPieSeries *series;
    QPieSlice *hit_slice;
    QPainter painter;

    //база
    QSqlDatabase dbase;

};
#endif // MAINWINDOW_H
