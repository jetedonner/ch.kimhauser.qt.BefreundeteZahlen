#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QThread>
#include <QtCore/qmath.h>
#include <QMessageBox>
#include "worker.h"
#include "conststrings.h"
#include "dialogabout.h"
#include <QProgressBar>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void released();

public slots:
    void numberFound(int nNumber1, int nNumber2);
    void numberProcessed(int nStart, int nEnd, int nNumber);
    void errorString(QString error);
    void showAboutBox();

private:
    //int calcSum(int nNum);
    void workerThread();

    Ui::MainWindow *ui;
    QThread* thread;
    Worker* worker;
    // QStandardItemModel provides a classic
    // item-based approach to working with the model.
    QStandardItemModel *model;
    QLabel *lbl;
    QProgressBar *progress;
    QLabel *lblFrom;
    QLineEdit * txtFrom;
    QLabel *lblTo;
    QLineEdit *txtTo;
    QPushButton *btnSearch;

};

#endif // MAINWINDOW_H
