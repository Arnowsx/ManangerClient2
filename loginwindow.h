#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include "networkapi.h"

namespace  Ui {
class LoginWindow;
}

class LoginWindow:public QWidget{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void refresh();

private:
    Ui::LoginWindow *ui;
    NetworkApi *loginAccess;

    void initWindow();
    void connects();

signals:
    void signalLoginButtonClicked();

private slots:
    void slotLoginButtonClicked();
    void slotLoginRequestFinished(QJsonObject *reply);
    void slotLoginRequestError(QString errorInfo);
};

#endif // LOGINWINDOW_H
