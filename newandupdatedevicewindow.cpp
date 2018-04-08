#include "newandupdatedevicewindow.h"
#include "ui_newandupdatedevicewindow.h"

NewAndUpdateDeviceWindow::NewAndUpdateDeviceWindow(QVector<QString> *rowAllString, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateDeviceWindow)
{
    ui->setupUi(this);

    getInfoApi = NetworkApi::getInstance();
    ui->savePushButtton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                      "color : #ffffff;"
                                      "border-radius:10px}"
                                      "QPushButton:pressed{background-color: #2b5a52;"
                                                            "color : #ffffff;"
                                                            "border-radius:10px}");

    ui->resetPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                       "color : #ffffff;"
                                       "border-radius:10px}"
                                       "QPushButton:pressed{background-color: #2b5a52;"
                                                             "color : #ffffff;"
                                                             "border-radius:10px}");

    getProjectIdRequest = NetworkApi::getInstance();

    if(rowAllString->size() == 0){
        initWindow();
    }else if(rowAllString->size() == 14){
        ui->deviceIdLabel->setText(rowAllString->at(0));
        ui->deviceNameLineEdit->setText(rowAllString->at(1));
        ui->deviceAddressLineEdit->setText(rowAllString->at(4));
        ui->deviceNumberLineEdit->setText(rowAllString->at(0));
        ui->pipeDiameterDoubleSpinBox->setValue(rowAllString->at(2).toDouble());
        ui->pipeDescibeTextEdit->setText(rowAllString->at(3));
        ui->remarkTextEdit->setText(rowAllString->at(12));
    }
    initWindow();
    connects();
}

void NewAndUpdateDeviceWindow::initWindow(){
    for(int i = 0; i < 6; i++){
        ui->kComboBox->addItem(QString::number(Globle::kValueList[i]));
    }
    NetworkApi::getInstance()->getProjectInfoRequest();
}


void NewAndUpdateDeviceWindow::connects(){
    connect(getProjectIdRequest, SIGNAL(signalGetProjectInfoRequestFinished(QJsonObject*)),this, SLOT(slotGetProjectInfoRequestFinished(QJsonObject*)));
    connect(ui->savePushButtton, SIGNAL(clicked(bool)), this, SLOT(slotSaveButtonClicked()));
    connect(ui->resetPushButton, SIGNAL(clicked(bool)), this, SLOT(slotReset()));

    connect(getInfoApi,SIGNAL(signalUpdateDeviceRequestFinished()), this, SLOT(slotUpdateSuccess()));
    connect(getInfoApi,SIGNAL(signalUpdateDeviceRequestError(QString)), this, SLOT(slotUpdateFailed(QString)));
}

void NewAndUpdateDeviceWindow::slotGetProjectInfoRequestFinished(QJsonObject *reply){
    QJsonArray result = reply->value("resultList").toArray();
    qDebug() << "total" << reply->value("total");
    qDebug() << "resultList" << reply->value("resultList");
    QString projectSelectBox;

    for(int i = 0; i < result.count(); i++){
        QJsonObject jsonProjectObject = result.at(i).toObject();
        projectSelectBox = QString::number(jsonProjectObject.value("projectId").toInt())+"-"+jsonProjectObject.value("name").toString();
        QString name = jsonProjectObject.value("name").toString();
        ui->projectIdComboBox->addItem(projectSelectBox);
    }
}

void NewAndUpdateDeviceWindow::slotSaveButtonClicked(){
    QJsonObject deviceJson;
    QString deviceId = ui->deviceIdLabel->text();
    QString deviceName = ui->deviceNameLineEdit->text();
    QString deviceAddress = ui->deviceAddressLineEdit->text();
    QString remark = ui->remarkTextEdit->toPlainText();
    int number = ui->deviceNumberLineEdit->text().toInt();

    int kValue = ui->kComboBox->currentText().toInt();
    QString projectIdString = ui->projectIdComboBox->currentText().split("-").at(0);
    int projectId = projectIdString.toInt();
    double pipeDiameter = ui->pipeDiameterDoubleSpinBox->value();
    QString pipeDescribe = ui->pipeDescibeTextEdit->toPlainText();

    deviceJson.insert("ids", deviceId);
    deviceJson.insert("name", deviceName);
    deviceJson.insert("pipeDiameter", pipeDiameter);
    deviceJson.insert("pipeDescribe", pipeDescribe);
    deviceJson.insert("address", deviceAddress);
    deviceJson.insert("remarks", remark);
    deviceJson.insert("number", number);

    deviceJson.insert("k", kValue);
    deviceJson.insert("project", projectId);

    qDebug() << deviceJson;
    getInfoApi->updateDeviceRequest(deviceJson);
    qDebug() << "修改设备";

}

void NewAndUpdateDeviceWindow::slotReset(){
    initWindow();
    ui->deviceNameLineEdit->setText("[请设置设备名称]");
    ui->deviceAddressLineEdit->setText("[请设置设备地址]");
    ui->deviceNumberLineEdit->setText("[请设置设备编号]");
    ui->pipeDiameterDoubleSpinBox->setValue(0);
    ui->pipeDescibeTextEdit->clear();
    ui->remarkTextEdit->clear();
}

void NewAndUpdateDeviceWindow::slotUpdateSuccess(){
    QMessageBox::warning(this, "成功","更新设备成功！", QMessageBox::Ok);
    this->hide();
    emit signalRefreshTable(2);
}

void NewAndUpdateDeviceWindow::slotUpdateFailed(QString error){
    QMessageBox::warning(this, "失败","失败原因："+error, QMessageBox::Ok);
}

NewAndUpdateDeviceWindow::~NewAndUpdateDeviceWindow()
{
    delete ui;
}
