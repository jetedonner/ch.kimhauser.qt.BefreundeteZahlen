#include "dialogabout.h"
#include "ui_dialogabout.h"

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);
    Qt::WindowFlags flags = 0;
    flags = Qt::Dialog;
    flags |= Qt::MSWindowsFixedSizeDialogHint;
    flags |= Qt::WindowMaximizeButtonHint;
    this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}
