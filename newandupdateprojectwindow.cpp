#include "newandupdateprojectwindow.h"
#include "ui_newandupdateprojectwindow.h"

NewAndUpdateProjectWindow::NewAndUpdateProjectWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateProjectWindow)
{
    ui->setupUi(this);
}

NewAndUpdateProjectWindow::~NewAndUpdateProjectWindow()
{
    delete ui;
}
