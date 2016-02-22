#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QStringList>
#include <QTableView>
#include <QItemDelegate>
#include <QStandardItemModel>
#include <QList>
#include <QtCore/qmath.h>

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
    void on_pushButton_clicked();

private:
    int calcSum(int nNum);
    Ui::MainWindow *ui;

    // QStandardItemModel provides a classic
    // item-based approach to working with the model.
    QStandardItemModel *model;
};

#endif // MAINWINDOW_H
