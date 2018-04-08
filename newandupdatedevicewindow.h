#ifndef NEWANDUPDATEDEVICEWINDOW_H
#define NEWANDUPDATEDEVICEWINDOW_H

#include <QMainWindow>
#include <QVector>
#include "networkapi.h"

namespace Ui {
class NewAndUpdateDeviceWindow;
}

class NewAndUpdateDeviceWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateDeviceWindow(QVector<QString> *rowAllString, QWidget *parent = 0);
    ~NewAndUpdateDeviceWindow();

private:
    Ui::NewAndUpdateDeviceWindow *ui;

    NetworkApi *getProjectIdRequest;
    NetworkApi *getInfoApi;

    void initWindow();
    void connects();

signals:
    void signalRefreshTable(int);

private slots:
    void slotSaveButtonClicked();
    void slotReset();
    void slotGetProjectInfoRequestFinished(QJsonObject *reply);
    void slotUpdateSuccess();
    void slotUpdateFailed(QString error);
};

#endif // NEWANDUPDATEDEVICEWINDOW_H
