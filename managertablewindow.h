#ifndef MANAGERTABLEWIND
#define MANAGERTABLEWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVector>
#include <QEventLoop>
#include <QTimer>
#include "networkapi.h"
#include "newandupdatedevicewindow.h"
#include "newandupdateprojectwindow.h"
#include "newandupdateuserwindow.h"
#include "searchdialog.h"

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
    NetworkApi *getInfoApi;
    QStringList *projectAllList;
    QStringList *userAllList;
    QStringList *deviceAllList;
    NewAndUpdateDeviceWindow *updateDeviceWindow;
    NewAndUpdateProjectWindow *updateProjectWindow;
    NewAndUpdateUserWindow *updateUserWindow;
    SearchDialog *searchDialog;

    int tableType;

signals:
    void signalUpdateInfoButtonClicked(int type, QVector<QString>*rowAllString);
    void signalDeleteInfoButtonClicked(int type, QString itemId);
    void signalSearchInfoButtonClicked(int type);
    void signalReturnButtonClicked();

private slots:
    void slotGetProjectAllRequestFinished(QJsonObject *reply);
    void slotGetUserAllRequestFinished(QJsonObject *reply);
    void slotGetDeviceAllRequestFinished(QJsonObject *reply);

    void slotGetProjectAllRequestError(QString errorInfo);
    void slotGetUserAllRequestError(QString errorInfo);
    void slotGetDeviceAllRequestError(QString errorInfo);

    void slotUpdateInfoButtonClicked();
    void slotDeleteInfoButtonClicked();
    void slotReturnButtonClicked();
    void slotSearchInfoButtonClicked();

    void slotOpenUpdateWindow(int type, QVector<QString> *rowAllString);
    void slotDeleteItem(int type, QString itemId);
    void slotSearchResultSetTable(int,QString);

    void slotDeleteSuccess(int);
    void slotDeleteFailed(int type, QString error);

    void slotRefreshButtonClicked();
    void slotRefreshTable(int);
};

#endif // MANAGERTABleWINDOW_H
