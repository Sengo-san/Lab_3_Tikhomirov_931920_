#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Lab_3_Tikhomirov"); // заголовок окна
    setGeometry(0,0,800,600);

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

    /*
    chart_view = new QChartView;
    chart_view->setRenderHint(QPainter::Antialiasing);

    chart = chart_view->chart();
    chart->setTitle("Beautiful Pie Chart");
    chart->legend()->hide();

    series = new QPieSeries();

    //ввод данных графика
    float hits = 49.0f, misses = 51.0f;
    series->append("Hits", hits);
    series->append("Misses", misses);

    //настройка графика
    QPieSlice *hit_slice = series->slices().at(0);
    hit_slice->setBrush(QColor(87, 147, 243));  // blue

    QPieSlice *miss_slice = series->slices().at(1);
    miss_slice->setBrush(QColor(221, 68, 68)); // red
    chart->addSeries(series);
        */


    /******************************************************** ТАБЛИЧНОЕ ПРЕДСТАВЛЕНИЕ БД (ТЕСТ) *********************************/
    view = new QTableView;


    /******************************************************** РАЗМЕЩЕНИЕ ********************************************************/

    splitter_left->addWidget(table_view);
    vertical_left_layout->addWidget(button_directory);
    //splitter_right->addWidget(chart_view);
    //splitter_right->addWidget(view);



    horizontal_graph_settings_layout->addWidget(button_print_chart);
    horizontal_graph_settings_layout->addWidget(chbox_bw_chart);
    horizontal_graph_settings_layout->addWidget(combobox_chart_type);
    //QPushButton *but = new QPushButton();
    //splitter->addWidget(but);

    /******************************************************** СИГНАЛЫ-СЛОТЫ ********************************************************/
    connect (button_directory, SIGNAL(clicked()), this, SLOT(open_directory_slot())); //открытие директории
    connect (button_print_chart, SIGNAL(clicked()), this, SLOT(print_chart_slot())); //печать графика
    connect(selectionModel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(file_chose_slot(const QItemSelection &, const QItemSelection &)));
    //connect (table_view->selectionModel(), SIGNAL(currentChanged ( const QModelIndex &, const QModelIndex & )), this, SLOT(file_chose_slot())); //выбор файла

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

    chart_view->render(&painter);
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

    //связываемся с датабазой:

    dbase = QSqlDatabase::addDatabase("QSQLITE"); //соединение по умолчанию (неименованое)
    dbase.setDatabaseName(filePath);

    if (!dbase.open()) {//открываем, проверяем на открытие
        QMessageBox msg;
        msg.setText("Cant open database " + filePath);
        msg.exec();
    }

    else {
        model = new QSqlTableModel;
        model->database() = dbase;
        model->setTable(dbase.tables().takeFirst()); //устанавливаем первую таблицу
        model->setEditStrategy(QSqlTableModel::OnFieldChange);

        if (!model->select()){
            QMessageBox msg;
            msg.setText("Cant read table " + model->tableName() + ", database: " + model->database().databaseName());
            msg.exec();
        }

    }

     //загружаем данные в модель
    view->setModel(model);
    splitter_right->addWidget(view);
}

MainWindow::~MainWindow()
{

}

