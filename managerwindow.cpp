#include "managerwindow.h"
#include "ui_managerwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ManagerWindow){
        ui->setupUi(this);

        getProjectAccess = NetworkApi::getInstance();
        getProjectAccess->getProjectInfoRequest();

        projectList = new QStringList();

        initWindow();
        connects();
}

void ManagerWindow::initWindow(){
    ui->userPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->userProjectBelongToCombox->addItem("[请选择]");
    ui->userTypeCombox->addItem("[请选择]");
    ui->deviceProjectBelongToComboBox->addItem("[请选择]");
    ui->kValueComboBox->addItem("[请选择]");



    for(int i = 0; i < Globle::userTypeList.size(); i++){
        ui->userTypeCombox->addItem(Globle::userTypeList.at(i));
    }

    for (int i = 0; i < 6; i++) {
        ui->kValueComboBox->addItem(QString::number(Globle::kValueList[i]));
    }
}

void ManagerWindow::connects(){
    connect(getProjectAccess, SIGNAL(signalGetProjectInfoRequestFinished(QJsonObject*)), this, SLOT(slotGetProjectInfoRequestFinished(QJsonObject*)));
    connect(getProjectAccess, SIGNAL(signalGetProjectInfoRequestError(QString)), this ,SLOT(slotGetProjectInfoRequestError(QString)));

    connect(ui->openProjectPushButton, SIGNAL(clicked(bool)), this, SLOT(slotOpenProjectTableButton()));
    connect(ui->openUserPushButton, SIGNAL(clicked(bool)), this, SLOT(slotOpenUserTableButton()));
    connect(ui->openDevicePushButton, SIGNAL(clicked(bool)), this, SLOT(slotOpenDeviceTableButton()));
    
    connect(ui->newProjectPushButton, SIGNAL(clicked(bool)), this, SLOT(slotNewProjectButtonClicked()));
    connect(ui->newUserPushButton, SIGNAL(clicked(bool)), this, SLOT(slotNewUserButtonClicked()));
    connect(ui->newDevicePushButton, SIGNAL(clicked(bool)), this, SLOT(slotNewDeviceButtonClicked()));

}

void ManagerWindow::slotGetProjectInfoRequestFinished(QJsonObject *reply){
    projectList->clear();
    QJsonArray result = reply->value("resultList").toArray();
    qDebug() << "total" << reply->value("total");
    qDebug() << "resultList" << reply->value("resultList");

    for(int i = 0; i < result.count(); i++){
        QJsonObject jsonProjectObject = result.at(i).toObject();
        ui->userProjectBelongToCombox->addItem(QString::number(jsonProjectObject.value("projectId").toInt()));
        ui->deviceProjectBelongToComboBox->addItem(QString::number(jsonProjectObject.value("projectId").toInt()));
    }
}

void ManagerWindow::slotGetProjectInfoRequestError(QString errorinfo){
   QMessageBox::warning(this, "错误", errorinfo, QMessageBox::Ok) ;
}

void ManagerWindow::slotNewProjectButtonClicked(){
     QString projecLocation;
     QString projectName;
     QString projectRemarks;

     projecLocation = ui->projectLocationLineEdit->text();
     projectName =ui->projectNameLineEdit->text();
     projectRemarks = ui->projectNoteTextEdit->toPlainText();

    QJsonObject projectAddJson;
    projectAddJson.insert("name", projectName);
    projectAddJson.insert("address", projecLocation);
    projectAddJson.insert("remarks", projectRemarks);

    NetworkApi::getInstance()->addProjectRequest(projectAddJson);
}

void ManagerWindow::slotNewUserButtonClicked(){
     QString userName;
     QString userPasswordMd5;
     QString userTypeString = ui->userTypeCombox->currentText();
     char userTypeChar ='0';
     int project = ui->userProjectBelongToCombox->currentText().toInt();
     bool isRightNewUser = true;

     QByteArray baMd5;
     baMd5 = QCryptographicHash::hash(ui->userPasswordLineEdit->text().toLocal8Bit(), QCryptographicHash::Md5);
     userPasswordMd5.append(baMd5.toHex());

      if(userTypeString == "系统管理员"){
          userTypeChar = 1;
      } else if(userTypeString == "项目管理员"){
          userTypeChar = 2;
      } else if(userTypeString == "设备管理员"){
          userTypeChar = 3;
      } else if(userTypeString == "[请选择]"){
          QMessageBox::warning(this, "错误", "请选择类型！", QMessageBox::Ok);
          isRightNewUser = false;
      }  else {
          QMessageBox::warning(this, "错误", "未知类型错误", QMessageBox::Ok);
          isRightNewUser = false;
      }

      if(isRightNewUser){
          QJsonObject userJson;
          userJson.insert("userName", ui->userNameLineEdit->text());
          userJson.insert("password", userPasswordMd5);
          userJson.insert("type", userTypeChar);
          userJson.insert("project", project);

          qDebug() << userJson;
          NetworkApi::getInstance()->addUserRequest(userJson);
      }

}

void ManagerWindow::slotNewDeviceButtonClicked(){
    QString deviceId;
    QString name;
    double pipeDiameter = 0;
    QString pipeDescribe;
    QString address;
    int number = 0;
    QString remarks;
    int K;
    char cDeviceState;
    char gateState;
    double cTemperature;
    double cPressure;
    int project;

    deviceId = ui->deviceIdLineEdit->text();
    name = ui->deviceNameLineEdit->text();
    address = ui->deviceAdressLineEdit->text();
    project = ui->deviceProjectBelongToComboBox->currentText().toInt();
    K = ui->kValueComboBox->currentText().toInt();

    QJsonObject deviceNewJson;
    deviceNewJson.insert("deviceId", deviceId);
    deviceNewJson.insert("name", name);
    deviceNewJson.insert("address", address);
    deviceNewJson.insert("project", project);
    deviceNewJson.insert("k", K);

    qDebug() << deviceNewJson;
    NetworkApi::getInstance()->addDeviceRequest(deviceNewJson);
}

void ManagerWindow::slotOpenProjectTableButton(){
    emit signalOpenProjectTableButtonClicked(1);
}

void ManagerWindow::slotOpenUserTableButton(){
    emit signalOpenUserTableButtonClicked(2);
}

void ManagerWindow::slotOpenDeviceTableButton(){
    emit signalOpenDeviceTableButtonClicked(3);
}

ManagerWindow::~ManagerWindow(){
    delete ui;
}
