#include "newandupdatedevicewindow.h"
#include "ui_newandupdatedevicewindow.h"

NewAndUpdateDeviceWindow::NewAndUpdateDeviceWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateDeviceWindow)
{
    ui->setupUi(this);
}

NewAndUpdateDeviceWindow::~NewAndUpdateDeviceWindow()
{
    delete ui;
}
