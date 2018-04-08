#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::LoginWindow){
        ui->setupUi(this);

        loginAccess = NetworkApi::getInstance();
        initWindow();
        connects();
    }

void LoginWindow::initWindow(){
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->loginPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                           "color : #ffffff;"
                                           "border-radius:10px}"
                                           "QPushButton:pressed{background-color: #2b5a52;"
                                                                 "color : #ffffff;"
                                                                 "border-radius:10px}");
}

void LoginWindow::connects(){
    connect(ui->loginPushButton,SIGNAL(clicked(bool)),this, SLOT(slotLoginButtonClicked()));
    connect(loginAccess,SIGNAL(signalLoginRequestFinished(QJsonObject*)), this, SLOT(slotLoginRequestFinished(QJsonObject*)));
    connect(loginAccess, SIGNAL(signalLoginRequestError(QString)), this, SLOT(slotLoginRequestError(QString)));
}

void LoginWindow::refresh(){
    ui->idLineEdit->setText("");
    ui->passwordLineEdit->setText("");
}

void LoginWindow::slotLoginButtonClicked(){
    QJsonObject requestData;
    requestData.insert("userName", ui->idLineEdit->text());
    QByteArray baMd5;
    baMd5 = QCryptographicHash::hash(ui->passwordLineEdit->text().toLocal8Bit(), QCryptographicHash::Md5);
    QString passwordMd5;
    passwordMd5.append(baMd5.toHex());
    requestData.insert("password", passwordMd5);

    loginAccess->loginRequest(requestData);
}

void LoginWindow::slotLoginRequestFinished(QJsonObject *reply){
    Globle::userName = ui->idLineEdit->text();
    Globle::userId = reply->value("userId").toInt();
    int type = reply->value("type").toString().toInt();
    switch(type) {
    case 1:
        emit signalLoginButtonClicked();
        break;
    default:
        QMessageBox::warning(this, "错误", "用户名或密码输入错误！", QMessageBox::Ok);
        break;
    }
}

void LoginWindow::slotLoginRequestError(QString errorInfo){
    QMessageBox::warning(this, "错误", errorInfo, QMessageBox::Ok);
}

LoginWindow::~LoginWindow(){
    delete ui;
}
