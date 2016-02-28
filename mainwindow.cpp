#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_dialogabout.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

    ui->setupUi(this);

    QMenu *helpMenu = new QMenu(tr("&Help"), this);
    QAction *aboutAction = helpMenu->addAction(tr("&About"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(showAboutBox()));
    ui->menuBar->addMenu(helpMenu);

    QStringList list;
    list << ConstStrings::number1;
    list << ConstStrings::number2;

    // Create a new model
    model = new QStandardItemModel(0,2,this);
    model->setHorizontalHeaderLabels(list);

    // Attach the model to the view
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0, 180);
    ui->tableView->setColumnWidth(1, 180);

    lbl = new QLabel("", this);
    progress = new QProgressBar(this);


    lblFrom = new QLabel(ConstStrings::from);
    ui->toolBar->addWidget(lblFrom);

    txtFrom = new QLineEdit(this);
    ui->toolBar->addWidget(txtFrom);
    txtFrom->setText(ConstStrings::one);

    lblTo = new QLabel(ConstStrings::to);
    ui->toolBar->addWidget(lblTo);

    txtTo = new QLineEdit(this);
    ui->toolBar->addWidget(txtTo);
    txtTo->setText(ConstStrings::fivemil);

    btnSearch = new QPushButton(ConstStrings::search, this);
    ui->toolBar->addWidget(btnSearch);

    connect(btnSearch, SIGNAL (released()),this, SLOT (released()));

    ui->statusBar->addPermanentWidget(lbl);
    ui->statusBar->addPermanentWidget(progress);
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::showAboutBox(){
    DialogAbout *about = new DialogAbout(this);
    about->setModal(true);
    about->show();
}

void MainWindow::released(){
    if(btnSearch->text() == QString(ConstStrings::search)){
        btnSearch->setText(QString(ConstStrings::cancel));
        model->removeRows(0, model->rowCount());
        int nFrom = txtFrom->text().toInt();
        int nTo = txtTo->text().toInt();

        thread = new QThread();
        worker = new Worker(nFrom, nTo);
        worker->moveToThread(thread);
        workerThread();
        thread->start();

    }else{
        worker->exit();
        btnSearch->setText(QString(ConstStrings::search));
    }
}

void MainWindow::workerThread(){
    connect(worker, SIGNAL(error(QString)), this, SLOT(errorString(QString)));
    connect(thread, SIGNAL(started()), worker, SLOT(process()));

    connect(worker, SIGNAL(numberFound(int, int)), this, SLOT(numberFound(int, int)));
    connect(worker, SIGNAL(numberProcessed(int, int, int)), this, SLOT(numberProcessed(int, int, int)));

    connect(worker, SIGNAL(finished()), thread, SLOT(quit()));
    connect(worker, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
}

void MainWindow::errorString(QString error){
    QMessageBox msgBox;
    msgBox.setText(QString(ConstStrings::error + " %1").arg(error));
    msgBox.exec();
}

void MainWindow::numberProcessed(int nStart, int nEnd, int nNumber){
    if(nNumber < nEnd){
        lbl->setText(QString(ConstStrings::current + " %1").arg(nNumber));
        progress->setValue((nNumber - nStart) / ((nEnd - nStart) / 100));
    }else{
        lbl->setText(QString(""));
        progress->setValue(0);
        btnSearch->setText(QString(ConstStrings::search));
    }
}

void MainWindow::numberFound(int nNumber1, int nNumber2){
    QList<QStandardItem*> newRow;
    for (int y = 0; y < model->columnCount(); y++)
    {
        QStandardItem* itm = new QStandardItem(QString("%1").arg(y == 0 ? nNumber1 : nNumber2 ));
        newRow.append(itm);
    }
    model->appendRow(newRow);
    ui->tableView->scrollTo(model->index(model->rowCount()-1, 0));
    //ui->tableView->resizeColumnsToContents();
}
