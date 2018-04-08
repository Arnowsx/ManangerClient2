#include "managerwindow.h"
#include "ui_managerwindow.h"

ManagerWindow::ManagerWindow(QWidget *parent):
    QWidget(parent),
    ui(new Ui::ManagerWindow){
        ui->setupUi(this);

        getProjectAccess = NetworkApi::getInstance();
        getProjectAccess->getProjectInfoRequest();
        getInfoApi = NetworkApi::getInstance();

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

    QRegExp rx("[0-9a-fA-F]{8}");
    QValidator *validator = new QRegExpValidator(rx, ui->deviceIdLineEdit);
    ui->deviceIdLineEdit->setValidator(validator);

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

    connect(getInfoApi,SIGNAL(signalAddProjectRequestFinished(int)), this, SLOT(slotAddSuccess(int)));
    connect(getInfoApi,SIGNAL(signalAddUserRequestFinished(int)), this, SLOT(slotAddSuccess(int)));
    connect(getInfoApi,SIGNAL(signalAddDeviceRequestFinished(int)), this, SLOT(slotAddSuccess(int)));

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
    QString projectSelectBox;
    ui->deviceProjectBelongToComboBox->clear();
    ui->userProjectBelongToCombox->clear();
    ui->deviceProjectBelongToComboBox->addItem("[请选择]");
    ui->userProjectBelongToCombox->addItem("[请选择]");
    for(int i = 0; i < result.count(); i++){
        QJsonObject jsonProjectObject = result.at(i).toObject();
        projectSelectBox = QString::number(jsonProjectObject.value("projectId").toInt())+"-"+jsonProjectObject.value("name").toString();
        ui->userProjectBelongToCombox->addItem(projectSelectBox);
        ui->deviceProjectBelongToComboBox->addItem(projectSelectBox);
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
    getInfoApi->addProjectRequest(projectAddJson);
//    NetworkApi::getInstance()->addProjectRequest(projectAddJson);
}

void ManagerWindow::slotNewUserButtonClicked(){
     QString userName;
     QString userPasswordMd5;
     QString userTypeString = ui->userTypeCombox->currentText();
     QString userProjectString = ui->userProjectBelongToCombox->currentText();
     char userTypeChar ='0';
     QString projectIdString;
     QJsonObject userJson;
     int project;
     if(userProjectString == "[请选择]"){
         project = 0;
     }else{
         projectIdString = ui->userProjectBelongToCombox->currentText().split("-").at(0);
         project = projectIdString.toInt();
     }
     bool isRightNewUser = true;

     QByteArray baMd5;
     baMd5 = QCryptographicHash::hash(ui->userPasswordLineEdit->text().toLocal8Bit(), QCryptographicHash::Md5);
     userPasswordMd5.append(baMd5.toHex());

      if(userTypeString == "系统管理员"){
          userTypeChar = 1;
          userJson.insert("project", project);
      } else if(userTypeString == "项目管理员"){
          userTypeChar = 2;
          userJson.insert("project", project);
      } else if(userTypeString == "设备管理员"){
          userTypeChar = 3;
          userJson.insert("project", project);
      } else if(userTypeString == "[请选择]"){
          QMessageBox::warning(this, "错误", "请选择类型！", QMessageBox::Ok);
          isRightNewUser = false;
      }  else {
          QMessageBox::warning(this, "错误", "未知类型错误", QMessageBox::Ok);
          isRightNewUser = false;
      }

      if(isRightNewUser){
          userJson.insert("userName", ui->userNameLineEdit->text());
          userJson.insert("password", userPasswordMd5);
          userJson.insert("type", userTypeChar);
          qDebug() << userJson;
          getInfoApi->addUserRequest(userJson);
      }

}

void ManagerWindow::slotNewDeviceButtonClicked(){
    QString name;
    QString address;
    QString deviceId;
    int K;
    int project;

    name = ui->deviceNameLineEdit->text();
    address = ui->deviceAdressLineEdit->text();
    if(ui->deviceProjectBelongToComboBox->currentText() == "[请选择]"){
        QMessageBox::warning(this, "错误","请选择所属项目！", QMessageBox::Ok);
    }else{
        QString projectIdString = ui->deviceProjectBelongToComboBox->currentText().split("-").at(0);
        project = projectIdString.toInt();
        K = ui->kValueComboBox->currentText().toInt();

        deviceId = ui->deviceIdLineEdit->text();
        QJsonObject deviceNewJson;
        deviceNewJson.insert("deviceId", deviceId);
        deviceNewJson.insert("name", name);
        deviceNewJson.insert("address", address);
        deviceNewJson.insert("project", project);
        deviceNewJson.insert("k", K);

        qDebug() << deviceNewJson;
        getInfoApi->addDeviceRequest(deviceNewJson);
    }
}

void ManagerWindow::slotAddSuccess(int type){
    switch (type) {
    case 0:
        QMessageBox::warning(this, "成功","添加项目成功！", QMessageBox::Ok);
        break;
    case 1:
        QMessageBox::warning(this, "成功","添加用户成功！", QMessageBox::Ok);
        break;
    case 2:
        QMessageBox::warning(this, "成功","添加设备成功！", QMessageBox::Ok);
        break;
    default:
        break;
    };
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

void ManagerWindow::refresh(){
    getProjectAccess->getProjectInfoRequest();
}

ManagerWindow::~ManagerWindow(){
    delete ui;
}
