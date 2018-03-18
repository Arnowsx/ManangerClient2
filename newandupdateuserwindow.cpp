#include "newandupdateuserwindow.h"
#include "ui_newandupdateuserwindow.h"

NewAndUpdateUserWindow::NewAndUpdateUserWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateUserWindow)
{
    ui->setupUi(this);
}

NewAndUpdateUserWindow::~NewAndUpdateUserWindow()
{
    delete ui;
}
