#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Lab_3_Tikhomirov"); // заголовок окна
    resize(800, 600); // размер окна



    /***компановка****/
    splitter = new QSplitter();//создаем разделитель
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // поведение разделителя
    //horizontal_layout = new QHBoxLayout(this); // горизонтальный компановщик
    vertical_layout = new QVBoxLayout(this);
    //vertical_layout->addLayout(horizontal_layout);
    vertical_layout->addWidget(splitter);
    setCentralWidget(splitter);



    //horizontal_layout->addLayout(vertical_layout);

    //кнопка
    directory_button = new QPushButton();
    directory_button->setText("Open directory");
    //horizontal_layout->addWidget(directory_button);

    table_model =  new QFileSystemModel(this);
    table_model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);//фильтры файловой модели

    directory_name = QDir::homePath();
    table_model->setRootPath(directory_name); //изначальная открытая папка
    table_view = new QTableView();//табличное представления файлов
    table_view->setModel(table_model);//дружим представление с моделью
    //horizontal_layout->addWidget(table_view);
    //setCentralWidget(splitter);

    /***размещение****/
    splitter->addWidget(directory_button);
    splitter->addWidget(table_view);
    //QPushButton *but = new QPushButton();
    //splitter->addWidget(but);

    /***сигналы-слоты****/
   connect(directory_button, SIGNAL(clicked()), this, SLOT(open_directory_slot())); //сигнал-слот открытия директории

}

void MainWindow::open_directory_slot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        directory_name = dialog.selectedFiles().first();;

   table_view->setRootIndex(table_model->setRootPath(directory_name));
}



MainWindow::~MainWindow()
{

}

