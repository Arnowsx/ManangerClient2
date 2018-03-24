#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include "loginwindow.h"
#include "managerwindow.h"
#include "managertablewindow.h"
#include "networkapi.h"
#include "newandupdatedevicewindow.h"
#include "newandupdateprojectwindow.h"
#include "newandupdateuserwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *widget;
    LoginWindow *loginWindow;
    ManagerWindow *managerWindow;
    ManagerTableWindow *managerTableWindow;
    NewAndUpdateDeviceWindow *updateDeviceWindow;
    NewAndUpdateProjectWindow *updateProjectWindow;
    NewAndUpdateUserWindow *updateUserWindow;
    QStackedLayout *mainLayout;

    void connectsBeforeLogin();
    void connects();

private slots:
    void slotLoginButtonClicked();
    void slotOpenTableWindow(int tabType);
    void slotOpenUpdateWindow(int type);
};

#endif // MAINWINDOW_H
