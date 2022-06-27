#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "IOCcontainer.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Lab_3_Tikhomirov"); // заголовок окна
    setGeometry(0, 0, 1200, 600);
    int visuable_parts_amount = 7; //количество "видимых частей" графика (остальные суммируются в "Others")

    for (int i = 0; i <= visuable_parts_amount + 1; i++){
        int r = rand()%250;
        int g = rand()%250;
        int b = rand()%250;
        int bw = (r+g+b)/3;
        colored_colors.push_back(QColor(r,g,b));
        black_white_colors.push_back(QColor(bw, bw, bw));
    }

    chart_is_open = 0;
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
    combobox_chart_type->insertItem(1, QString("Pie chart"));
    combobox_chart_type->insertItem(2, QString("Bar chart"));

    /******************************************************** РАЗМЕЩЕНИЕ ********************************************************/

    splitter_left->addWidget(table_view);
    vertical_left_layout->addWidget(button_directory);
    horizontal_graph_settings_layout->addWidget(button_print_chart);
    horizontal_graph_settings_layout->addWidget(chbox_bw_chart);
    horizontal_graph_settings_layout->addWidget(combobox_chart_type);

    vertical_left_layout->addWidget(view);

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
    if (chart_is_open){
        QString saving_path ("");
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        if (dialog.exec())
            saving_path = dialog.selectedFiles().first();
        if (saving_path != "")
            graph->printToPdf(saving_path);
        else {
            QMessageBox nowae;
            nowae.setText("Cant open saving way");
            nowae.exec();
        }
        }
        else {
            QMessageBox nowae;
            nowae.setText("No chart to print");
            nowae.exec();
        }



}

void MainWindow::file_chose_slot(const QItemSelection &selected, const QItemSelection &deselected)
{
    Q_UNUSED(deselected);
    bool file_format_right = 0;
    bool chart_type_right = 0;

    //проверяем тип:
    QString chart_type (combobox_chart_type->currentText());
     if (chart_type == "Pie chart"){
         gContainer.RegisterInstance<IChart, MyPieChart>();
         chart_type_right = 1;
     }
     else if (chart_type == "Bar chart"){
         gContainer.RegisterInstance<IChart, MyBarChart>();
         chart_type_right = 1;
     }
     else {
         QMessageBox uct;
         uct.setText("Unknown chart type: " + chart_type);
         uct.exec();
      }

    //получаем путь:
    QModelIndexList indexs = selected.indexes();
    if (indexs.count() >= 1) {
        QModelIndex ix =  indexs.constFirst();
        filePath = table_model->filePath(ix);
    }

    //связываем интерфейс получения данных с конкретным читателем:
    if (filePath.endsWith(".sqlite")){
        gContainer.RegisterInstance<IChartData, ChartDataSqlite>();
        file_format_right = 1;
    }

    else if (filePath.endsWith(".json")){
        gContainer.RegisterInstance<IChartData, ChartDataJson>();
        file_format_right = 1;
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

