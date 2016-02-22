#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;
    list << "Number 1";
    list << "Number 2";

    // Create a new model
    model = new QStandardItemModel(0,2,this);
    model->setHorizontalHeaderLabels(list);
    // Attach the model to the view
    ui->tableView->setModel(model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QList<int> *list = new QList<int>();
void MainWindow::on_pushButton_clicked()
{

    int nFrom = ui->lineEdit->text().toInt();
    int nTo = ui->lineEdit_2->text().toInt();

    int nIdx = 0;
    for(int i = nFrom; i < nTo; i++){

        if(!list->contains(i)){
            int nQuer = calcSum(i);
            if(nQuer != i){
                if(i == calcSum(nQuer)){
                    list->append(nQuer);
                    QList<QStandardItem*> newRow;
                    for (int y = 0; y < model->columnCount(); y++)
                    {
                        QStandardItem* itm = new QStandardItem(QString("%1").arg(y == 0 ? i : nQuer ));
                        newRow.append(itm);
                    }
                    model->appendRow(newRow);
                }
            }
        }
        nIdx++;
    }
}

int MainWindow::calcSum(int nNum){

    int nSum = 1;

    for(int i = 2; i <= qSqrt(nNum); i++){
        if(nNum % i == 0){
            nSum += i + (nNum / i);
        }
    }
    return nSum;
}
