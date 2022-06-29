#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
//#include "ichart.h"

#include "GraphGenerator.h"
#include "IOCContainer.h"
#include "IScanner.h"


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Lab_3_Tikhomirov"); // заголовок окна
    setGeometry(0,0,800,600);

   /******************************************************** КОМПАНОВКА ********************************************************/

    horizontal_layout = new QHBoxLayout(this);
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

    open_directory_name = QDir::homePath(); //изначальная отображаемая папка
    table_model->setRootPath(open_directory_name); //изначальная открытая папка
    table_view = new QTableView;//табличное представления файлов
    table_view->setModel(table_model);//дружим представление с моделью
    //table_view->hideColumn(1);//убираем лишний столбец


    QItemSelectionModel *selectionModel = table_view->selectionModel();

    /******************************************************** ГРАФИКИ ********************************************************/

    button_print_chart = new QPushButton ("Print graph");
    chbox_bw_chart = new QCheckBox("B/w graph");
    combobox_chart_type = new QComboBox();
    combobox_chart_type->insertItem(1, QString("Pie chart"));
    combobox_chart_type->insertItem(2, QString("Bar chart"));

    view = new QChartView;
    view->setRenderHint(QPainter::Antialiasing);
    /******************************************************** РАЗМЕЩЕНИЕ ********************************************************/

    splitter_left->addWidget(table_view);
    vertical_left_layout->addWidget(button_directory);
    horizontal_graph_settings_layout->addWidget(button_print_chart);
    horizontal_graph_settings_layout->addWidget(chbox_bw_chart);
    horizontal_graph_settings_layout->addWidget(combobox_chart_type);

    vertical_right_layout ->addWidget(view);

    /******************************************************** СИГНАЛЫ-СЛОТЫ ********************************************************/
    connect (button_directory, SIGNAL(clicked()), this, SLOT(open_directory_slot())); //открытие директории
    connect (button_print_chart, SIGNAL(clicked()), this, SLOT(print_chart_slot())); //печать графика
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(file_chose_slot(const QItemSelection &, const QItemSelection &)));//выбор файла на чтение
    connect (chbox_bw_chart, SIGNAL(toggled(bool)), this, SLOT(recoloring_chart_slot()));//изменение цвета выведенного графика
    connect (combobox_chart_type, SIGNAL(currentIndexChanged(int)), this, SLOT(type_change_slot()));//изменение типа выведенного графика
}

void MainWindow::chart_repaint (QString path, QString type_in_combobox, bool bw)
{
    chart_is_open = 0;
    //связываем получателя данных с конкретным наследником:
    bool data_type_finded = 0;
    if (path.endsWith(".sqlite")) {
        //gContainer.RegisterFactory<IScanner, SqliteScanner, DataGraph>();
        gContainer.RegisterInstance<IScanner, SqliteScanner>();
        data_type_finded = 1;
    }
    else if (path.endsWith(".json")) {
        //gContainer.RegisterFactory<IScanner, JsonScanner, DataGraph>();
        gContainer.RegisterInstance<IScanner, JsonScanner>();
        data_type_finded = 1;
    }
    else {//если открыт файл неизвестного типа
        QMessageBox file_type_err;
        file_type_err.setText("Unknown file type");
        file_type_err.exec();
    }

    if (data_type_finded) {//если тип файла читаемый, собираем данные, какой график строить
        QString coloring = ""; //расцветка
        if (bw)
            coloring = "bw";
        else
            coloring = "colored";

        QString chart_type = "";//тип графика
        bool chart_type_finded = 0;
        if (type_in_combobox == "Bar chart") {
            chart_type = "barchart";
            chart_type_finded = 1;
        }
        else if (type_in_combobox == "Pie chart") {
            chart_type = "piechart";
            chart_type_finded = 1;
        }
        else { //в комбобоксе неизвестный тип графика
            QMessageBox chart_type_err;
            chart_type_err.setText("Unknown chart type");
            chart_type_err.exec();
        }
        if (chart_type != "" && chart_type_finded) {//если тип графика найден
            GraphGenerator graph_generator;//создаем фабрику графиков
            graph = graph_generator.getGraph( //создаем график с помощью фабрики
                                              gContainer.GetObject<IScanner>()->getData(open_file_name), //создаем и передаем данные
                                              chart_type, coloring); //имя расцветки, имя типа графика
            //view->setChart(graph->getChart());
            view->setChart(graph->getChart());
            chart_is_open = 1;
        }
    }

    if (!chart_is_open)
        view->setChart(empt);//заменяем отображаемый график пустым
}

void MainWindow::recoloring_chart_slot ()
{
    if (chart_is_open)
        chart_repaint (open_file_name, combobox_chart_type->currentText(), chbox_bw_chart->checkState());
}

void  MainWindow::type_change_slot()
{
    if (chart_is_open) {
        chart_repaint (open_file_name, combobox_chart_type->currentText(), chbox_bw_chart->checkState());
    }

}

void MainWindow::open_directory_slot()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
        open_directory_name = dialog.selectedFiles().first();;
   table_view->setRootIndex(table_model->setRootPath(open_directory_name));
}

void MainWindow::print_chart_slot()
{
    if (chart_is_open){
        //получаем путь сохранения
        QString saving_path ("");
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        if (dialog.exec()){
            saving_path = dialog.selectedFiles().first();
            //печатаем
            QPdfWriter* writer = new QPdfWriter (saving_path + "/out.pdf");
            writer->setCreator("Someone");//Указываем создателя документа
            writer->setPageSize(QPageSize::A4);//Устанавливаем размер страницы
            QPainter painter(writer);
            view->render(&painter);
            painter.end();
        }
    }
    else {
        QMessageBox nochart;
        nochart.setText("No chart to print");
        nochart.exec();
    }
}

void MainWindow::file_chose_slot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);

    //получаем путь к файлу:
    QModelIndexList indexs =  selected.indexes();
    open_file_name = "";
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        open_file_name = table_model->filePath(ix);
    }

    if (open_file_name != "")
        chart_repaint(open_file_name,
                      combobox_chart_type->currentText(),
                      chbox_bw_chart->checkState());
    else {
        QMessageBox path_err;
        path_err.setText("Can`t see file");
        path_err.exec();
        view->setChart(empt);
    }
}

MainWindow::~MainWindow()
{

}

