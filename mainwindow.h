#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QStackedLayout>

#include "loginwindow.h"
#include "managerwindow.h"
#include "managertablewindow.h"
#include "networkapi.h"

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
    QStackedLayout *mainLayout;

    void connectsBeforeLogin();
    void connects();

private slots:
    void slotLoginButtonClicked();
    void slotOpenTableWindow(int tabType);
};

#endif // MAINWINDOW_H
