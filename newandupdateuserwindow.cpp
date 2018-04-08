#include "newandupdateuserwindow.h"
#include "ui_newandupdateuserwindow.h"

NewAndUpdateUserWindow::NewAndUpdateUserWindow(QVector<QString>*rowAllString, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateUserWindow)
{
    ui->setupUi(this);
    getInfoApi = NetworkApi::getInstance();
    initWindow();
    userId = rowAllString->at(0).toInt();
    if(rowAllString->at(1) != NULL && rowAllString->at(2) != NULL){
        ui->userIdLabel->setText(rowAllString->at(1));
        switch (rowAllString->at(2).toInt()) {
        case 1:
            ui->userTypeComboBox->setCurrentIndex(0);
            break;
        case 2:
            ui->userTypeComboBox->setCurrentIndex(1);
            break;
        case 3:
            ui->userTypeComboBox->setCurrentIndex(2);
            break;
        default:
            break;
        }

    }else{
        ui->userIdLabel->setText("未知用户");
    }
    connects();
}

void NewAndUpdateUserWindow::initWindow(){
    ui->savePushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                      "color : #ffffff;"
                                      "border-radius:10px}"
                                      "QPushButton:pressed{background-color: #2b5a52;"
                                                            "color : #ffffff;"
                                                            "border-radius:10px}");
    ui->cancelPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                      "color : #ffffff;"
                                      "border-radius:10px}"
                                      "QPushButton:pressed{background-color: #2b5a52;"
                                                            "color : #ffffff;"
                                                            "border-radius:10px}");
    ui->userTypeComboBox->addItem("系统管理员");
    ui->userTypeComboBox->addItems(Globle::userTypeList);
}

void NewAndUpdateUserWindow::connects(){
    connect(ui->savePushButton, SIGNAL(clicked(bool)), this, SLOT(slotSaveButtonClicked()));
    connect(ui->cancelPushButton, SIGNAL(clicked(bool)), this, SLOT(slotCancelButtonClicked()));

    connect(getInfoApi,SIGNAL(signalUpdateUserRequestFinished()), this, SLOT(slotUpdateSuccess()));
    connect(getInfoApi,SIGNAL(signalUpdateUserRequestError(QString)), this, SLOT(slotUpdateFailed(QString)));
}

void NewAndUpdateUserWindow::slotSaveButtonClicked(){
    QJsonObject userJson;
    int type = ui->userTypeComboBox->currentIndex()+1;
    userJson.insert("ids", userId);
    QString pwdFirst = ui->passwordFirstLineEdit->text();
    QString pwdRepeat = ui->passwordRepeatLineEdit->text();
    QByteArray baMd5;
    if((pwdFirst.compare(pwdRepeat) == 0)&&pwdFirst != NULL){
        baMd5 = QCryptographicHash::hash(ui->passwordFirstLineEdit->text().toLocal8Bit(), QCryptographicHash::Md5);
        QString pwdMd5;
        pwdMd5.append(baMd5.toHex());
        userJson.insert("password", pwdMd5);
        userJson.insert("type", type);
        qDebug() << userJson;
        getInfoApi->updateUserRequest(userJson);
    }else if((pwdFirst.compare(pwdRepeat) != 0)&&pwdFirst != NULL){
        QMessageBox::warning(this, "错误", "两次密码输入不一致！", QMessageBox::Ok);
    }
}

void NewAndUpdateUserWindow::slotCancelButtonClicked(){
    this->hide();
}

void NewAndUpdateUserWindow::slotUpdateSuccess(){
    QMessageBox::warning(this, "成功","更新用户成功！", QMessageBox::Ok);
    emit signalResfreshTable(1);
    this->hide();
}

void NewAndUpdateUserWindow::slotUpdateFailed(QString error){
    QMessageBox::warning(this, "失败","失败原因："+error, QMessageBox::Ok);
}

NewAndUpdateUserWindow::~NewAndUpdateUserWindow()
{
    delete ui;
}
