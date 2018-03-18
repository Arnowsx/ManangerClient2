#ifndef NEWANDUPDATEDEVICEWINDOW_H
#define NEWANDUPDATEDEVICEWINDOW_H

#include <QMainWindow>

namespace Ui {
class NewAndUpdateDeviceWindow;
}

class NewAndUpdateDeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateDeviceWindow(QWidget *parent = 0);
    ~NewAndUpdateDeviceWindow();

private:
    Ui::NewAndUpdateDeviceWindow *ui;
};

#endif // NEWANDUPDATEDEVICEWINDOW_H
