#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QWidget>
#include <QJsonObject>
#include <QString>
#include "networkapi.h"

namespace  Ui {
class ManagerWindow;
}

class ManagerWindow:public QWidget{
    Q_OBJECT

public:
    explicit ManagerWindow(QWidget *parent = 0);
    ~ManagerWindow();

    void initWindow();
    void connects();

private:
    Ui::ManagerWindow *ui;
    NetworkApi *getProjectAccess;
    QStringList *projectList;

signals:
    void signalOpenProjectTableButtonClicked(int tabType);
    void signalOpenUserTableButtonClicked(int tabType);
    void signalOpenDeviceTableButtonClicked(int tabType);

private slots:
    void slotNewProjectButtonClicked();
    void slotNewUserButtonClicked();
    void slotNewDeviceButtonClicked();

    void slotOpenProjectTableButton();
    void slotOpenUserTableButton();
    void slotOpenDeviceTableButton();

    void slotGetProjectInfoRequestFinished(QJsonObject *reply);
    void slotGetProjectInfoRequestError(QString errorinfo);
};


#endif // MANAGERWINDOW_H
