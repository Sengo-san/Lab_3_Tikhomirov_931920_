#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ichart.h"
#include "ichartdata.h"

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QSplitter>
#include <QTableView>
#include <QFileSystemModel>

#include <QPainter>
#include <QPdfWriter>

#include <QGridLayout>

#include <QCheckBox>
#include <QComboBox>


#include <QPdfWriter>


#include <QItemSelectionModel>


//class MainWindow : public QWidget
class MainWindow : public QWidget
{
    Q_OBJECT

private slots:
    void open_directory_slot(); //слот открытия диалоговоого окна с папками
    void print_chart_slot();//слот печати
    void file_chose_slot(const QItemSelection &, const QItemSelection &);//слот выбора файа
    void chart_type_change_slot ();//слот смены типа графика

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void chart_repaint();//перерисовка графика

    QString directory_name;//имя открытой директории
    QString filePath; //путь к файлу

    //компановка
    QSplitter *splitter_left;
    QSplitter *splitter_right;
    QVBoxLayout *vertical_left_layout;
    QVBoxLayout *vertical_right_layout;
    QHBoxLayout *horizontal_layout;
    QHBoxLayout *horizontal_graph_settings_layout;

    //виджеты
    QPushButton *button_directory;//кнопка открытия директории
    QPushButton *button_print_chart;//кнопка печати
    QTableView *table_view; //таблица выбора файла
    QFileSystemModel *table_model;  //файловая модель для таблицы выбора файла
    QCheckBox *chbox_bw_chart; //чекбокс ч/б график
    QComboBox *combobox_chart_type; //типы графика

    //графики
    QChartView *chart_view;
    IChart *chart;
};
#endif // MAINWINDOW_H
