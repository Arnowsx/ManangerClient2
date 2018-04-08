#ifndef NEWANDUPDATEUSERWINDOW_H
#define NEWANDUPDATEUSERWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QJsonObject>
#include <QCryptographicHash>
#include "networkapi.h"
#include "globle.h"

namespace Ui {
class NewAndUpdateUserWindow;
}

class NewAndUpdateUserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit NewAndUpdateUserWindow(QVector<QString> *rowAllString, QWidget *parent = 0);
    ~NewAndUpdateUserWindow();

private:
    Ui::NewAndUpdateUserWindow *ui;

    NetworkApi *getInfoApi;
     void initWindow();
     void connects();
     int userId;
signals:
     void signalResfreshTable(int);
private slots:
     void slotSaveButtonClicked();
     void slotCancelButtonClicked();
     void slotUpdateSuccess();
     void slotUpdateFailed(QString error);
};

#endif // NEWANDUPDATEUSERWINDOW_H
