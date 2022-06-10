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

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:
    void open_directory_slot(); //слот открытия диалоговоого окна с папками

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QString directory_name;//имя открытой директории

     QSplitter *splitter; //разделитель
    QVBoxLayout *vertical_layout;
    QHBoxLayout *horizontal_layout;
    QPushButton *directory_button;
    QTableView *table_view;// таблица выбора файла (базы данных)
    QFileSystemModel *table_model;//файловая модель для таблицы выбора файла

};
#endif // MAINWINDOW_H
