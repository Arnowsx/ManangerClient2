#ifndef NEWANDUPDATEPROJECTWINDOW_H
#define NEWANDUPDATEPROJECTWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QTime>
#include <QJsonObject>
#include "networkapi.h"

namespace Ui {
class NewAndUpdateProjectWindow;
}

class NewAndUpdateProjectWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateProjectWindow(QVector<QString> *rowAllString, QWidget *parent = 0);
    ~NewAndUpdateProjectWindow();

private:
    Ui::NewAndUpdateProjectWindow *ui;


    NetworkApi *getInfoApi;
    void initWindow();
    void connects();

signals:
    void signalRefreshTable(int);

private slots:
    void slotSaveButtonClicked();
    void slotReset();
    void slotUpdateSuccess();
    void slotUpdateFailed(QString error);
};

#endif // NEWANDUPDATEPROJECTWINDOW_H
