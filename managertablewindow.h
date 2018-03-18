#ifndef MANAGERTABLEWIND
#define MANAGERTABLEWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include "networkapi.h"

namespace Ui {
class ManagerTableWindow;
}

class ManagerTableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerTableWindow(QWidget *parent = 0);
    ~ManagerTableWindow();

     void setTabShow(int tabType);
     void initWindow();
     void connects();

private:
    Ui::ManagerTableWindow *ui;
//    QTableWidget *projectTable;
//    QTableWidget *userTable;
//    QTableWidget *deviceTable;
    NetworkApi *getSelectTabTable;
    QStringList *projectAllList;
    QStringList *userAllList;
    QStringList *deviceAllList;

    int tableType;


private slots:
    void slotGetProjectAllRequestFinished(QJsonObject *reply);
    void slotGetUserAllRequestFinished(QJsonObject *reply);
    void slotGetDeviceAllRequestFinished(QJsonObject *reply);

    void slotGetProjectAllRequestError(QString errorInfo);
    void slotGetUserAllRequestError(QString errorInfo);
    void slotGetDeviceAllRequestError(QString errorInfo);

    void slotUpdateInfoButtonClicked();
    void slotDeleteInfoButtonClicked();
    void slotNewInfoButtonClicked();
    void slotSearchInfoButtonClicked();
};

#endif // MANAGERTABleWINDOW_H
