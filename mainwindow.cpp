#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "IOCcontainer.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Lab_3_Tikhomirov"); // заголовок окна
    setGeometry(0, 0, 800, 600);

   /******************************************************** КОМПАНОВКА ********************************************************/

    horizontal_layout=new QHBoxLayout(this);
    vertical_left_layout = new QVBoxLayout();
    vertical_right_layout = new QVBoxLayout();
    horizontal_graph_settings_layout = new QHBoxLayout();
    horizontal_layout->addLayout(vertical_left_layout);
    horizontal_layout->addLayout(vertical_right_layout);
    vertical_right_layout->addLayout(horizontal_graph_settings_layout);

    splitter_left = new QSplitter;
    splitter_right = new QSplitter;
    vertical_left_layout->addWidget(splitter_left);
    vertical_right_layout->addWidget(splitter_right);

   /******************************************************** ФАЙЛОВАЯ СИСТЕМА ********************************************************/

    button_directory = new QPushButton ("Open directory"); //кнопка выбора папки

    table_model =  new QFileSystemModel(this);// модель представления для файлов
    table_model->setFilter(QDir::NoDotAndDotDot | QDir::AllEntries);//фильтры файловой модели

    directory_name = QDir::homePath(); //изначальная отображаемая папка
    table_model->setRootPath(directory_name); //изначальная открытая папка
    table_view = new QTableView;//табличное представления файлов
    table_view->setModel(table_model);//дружим представление с моделью
    table_view->hideColumn(1);//убираем лишний столбец


    QItemSelectionModel *selectionModel = table_view->selectionModel();

    /******************************************************** ГРАФИКИ ********************************************************/

    button_print_chart = new QPushButton ("Print graph");
    chbox_bw_chart = new QCheckBox("B/w graph");
    combobox_chart_type = new QComboBox();


    this->chart = new MyPieChart(); //подобная строка будет в слоте от окна выбора типа графика и реализована с помощью IOC-контейнера
    //this->chart_view = new QChartView;

    //остальное реализуется в слоте выбора файла

    /******************************************************** РАЗМЕЩЕНИЕ ********************************************************/


    splitter_left->addWidget(table_view);//представление файлов в папке
    vertical_left_layout->addWidget(button_directory);//кнопка выбора папки

    splitter_right->addWidget(chart->getChartView());//график

    horizontal_graph_settings_layout->addWidget(button_print_chart); //кнопка печати
    horizontal_graph_settings_layout->addWidget(chbox_bw_chart); //галочка ч-б графика
    horizontal_graph_settings_layout->addWidget(combobox_chart_type);//выбор типа графика

    /******************************************************** СИГНАЛЫ-СЛОТЫ ********************************************************/
    connect (button_directory, SIGNAL(clicked()), this, SLOT(open_directory_slot())); //открытие директории
    connect (button_print_chart, SIGNAL(clicked()), this, SLOT(print_chart_slot())); //печать графика
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(file_chose_slot(const QItemSelection &, const QItemSelection &)));

}




void MainWindow::open_directory_slot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        directory_name = dialog.selectedFiles().first();;

   table_view->setRootIndex(table_model->setRootPath(directory_name));
}

void MainWindow::print_chart_slot()
{
    //Печать графика с помощью QPdfWriter(класс для создания pdf файлов)

    //todo: разобраться, исправить если нужно.

    QPdfWriter writer("out.pdf");

    writer.setCreator("Someone");//Указываем создателя документа
    writer.setPageSize(QPageSize::A4);//Устанавливаем размер страницы


    QPainter painter(&writer);

    //chart_view->render(&painter);
    painter.end();
}


void MainWindow::file_chose_slot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);


    //получаем путь:
    QModelIndexList indexs =  selected.indexes();
    filePath = "";
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = table_model->filePath(ix);
    }


   //if (конец файла = .sqlite)

    gContainer.RegisterInstance<IChartData, ChartDataSqlite>();
    //pie_chart = new MyPieChart();
    chart->createChart(gContainer.GetObject<IChartData>()->getData(filePath));

    //chart_view = chart->getChartView();
}

MainWindow::~MainWindow()
{

}

