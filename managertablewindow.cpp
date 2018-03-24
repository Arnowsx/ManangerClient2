#include "managertablewindow.h"
#include "ui_managertablewindow.h"

ManagerTableWindow::ManagerTableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerTableWindow)
{
    ui->setupUi(this);
    projectAllList = new QStringList();
    userAllList =new QStringList();
    deviceAllList = new QStringList();

    getSelectTabTable = NetworkApi::getInstance();
    initWindow();
    connects();

}

void ManagerTableWindow::initWindow(){
    ui->newPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                           "color : #ffffff;"
                                           "border-radius:10px}"
                                           "QPushButton:pressed{background-color: #2b5a52;"
                                                                 "color : #ffffff;"
                                                                 "border-radius:10px}");

    ui->updatePushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                           "color : #ffffff;"
                                           "border-radius:10px}"
                                           "QPushButton:pressed{background-color: #2b5a52;"
                                                                 "color : #ffffff;"
                                                                 "border-radius:10px}");

    ui->deletePushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                           "color : #ffffff;"
                                           "border-radius:10px}"
                                           "QPushButton:pressed{background-color: #2b5a52;"
                                                                 "color : #ffffff;"
                                                                 "border-radius:10px}");

    ui->searchPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                           "color : #ffffff;"
                                           "border-radius:10px}"
                                           "QPushButton:pressed{background-color: #2b5a52;"
                                                                 "color : #ffffff;"
                                                                 "border-radius:10px}");

    tableType = ui->tabWidget->currentIndex();
    QStringList projectHeaderLabels;
    QStringList userHeaderLabels;
    QStringList deviceHeaderLabels;
    projectHeaderLabels << "项目名称" << "项目地址" << "自动巡检" << "自动测试" << "自动打印" << "自动巡检时间" << "自动测试时间" << "打开阀门前最低压力" << "打开阀门前最高压力" << "打开阀门后最低压力" << "打开阀门最高压力" << "最高流量" << "最低流量" << "最高温度" << "最低温度" << "备注";
    userHeaderLabels << "用户编号" << "用户名" << "用户类型" << "所属项目ID" << "所属项目名称";
    deviceHeaderLabels << "设备编号" << "设备名称" << "设备管径" << "设备描述" << "管道地址" << "K系数" << "当前状态" << "阀门状态" << "当前温度" << "当前压力" << "所属项目ID" << "所属项目名称" << "备注";

    ui->projectTableWidget->setHorizontalHeaderLabels(projectHeaderLabels);
    ui->projectTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->projectTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->projectTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->projectTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 2; i <= 4; i++){
        ui->projectTableWidget->resizeColumnToContents(i);
    }
    ui->userTableWidget->setHorizontalHeaderLabels(userHeaderLabels);
    ui->userTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->userTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->userTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->userTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->deviceTableWidget->setHorizontalHeaderLabels(deviceHeaderLabels);
    ui->deviceTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->deviceTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->deviceTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->deviceTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setTabShow(tableType);
}

void ManagerTableWindow::connects(){
    connect(getSelectTabTable, SIGNAL(signalGetProjectInfoRequestFinished(QJsonObject*)), this, SLOT(slotGetProjectAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetProjectInfoRequestError(QString)), this ,SLOT(slotGetProjectAllRequestError(QString)));

    connect(getSelectTabTable, SIGNAL(signalGetUserAllRequestFinished(QJsonObject*)), this, SLOT(slotGetUserAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetUserAllRequestError(QString)), this ,SLOT(slotGetUserAllRequestError(QString)));

    connect(getSelectTabTable, SIGNAL(signalGetDeviceAllRequestFinished(QJsonObject*)), this, SLOT(slotGetDeviceAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetDeviceAllRequestError(QString)), this ,SLOT(slotGetDeviceAllRequestError(QString)));

    connect(ui->returnPushButton, SIGNAL(clicked(bool)), this, SLOT(slotReturnButtonClicked()));
    connect(ui->updatePushButton, SIGNAL(clicked(bool)), this, SLOT(slotUpdateInfoButtonClicked()));
    connect(ui->deletePushButton, SIGNAL(clicked(bool)), this, SLOT(slotDeleteInfoButtonClicked()));
    connect(ui->searchPushButton, SIGNAL(clicked(bool)), this, SLOT(slotSearchInfoButtonClicked()));
}

void ManagerTableWindow::setTabShow(int tabType){
    ui->tabWidget->setCurrentIndex(tabType);
    getSelectTabTable->getProjectAllRequest();
    getSelectTabTable->getUserAllRequest();
    getSelectTabTable->getDeviceAllRequest();
}

void ManagerTableWindow::slotGetProjectAllRequestFinished(QJsonObject *reply){
    projectAllList->clear();
    QJsonArray result  = reply->value("resultList").toArray();
    int rowNum;
    ui->projectTableWidget->setRowCount(result.count());

    for(int i = 0; i < result.count(); i++){
        rowNum = i;
        QJsonObject jsonProjectAllObject = result.at(i).toObject();

        QTableWidgetItem *nameItem = new QTableWidgetItem();
        QTableWidgetItem *addressItem = new QTableWidgetItem();
        QTableWidgetItem *isAutoInspectItem = new QTableWidgetItem();
        QTableWidgetItem *isAutoTestItem = new QTableWidgetItem();
        QTableWidgetItem *isAutoPrint = new QTableWidgetItem();
        QTableWidgetItem *inspectTime = new QTableWidgetItem();
        QTableWidgetItem *testTime = new QTableWidgetItem();
        QTableWidgetItem *beforeOpenValveLowerPressure = new QTableWidgetItem();
        QTableWidgetItem *beforeOpenValveUpperPressure = new QTableWidgetItem();
        QTableWidgetItem *afterOpenValveLowerPressure = new QTableWidgetItem();
        QTableWidgetItem *afterOpenValveUpperPressure = new QTableWidgetItem();
        QTableWidgetItem *upperFlow = new QTableWidgetItem();
        QTableWidgetItem *lowerFlow = new QTableWidgetItem();
        QTableWidgetItem *upperTemper = new QTableWidgetItem();
        QTableWidgetItem *lowerTemper = new QTableWidgetItem();

        QTableWidgetItem *remark = new QTableWidgetItem();

        nameItem->setText(jsonProjectAllObject.value("name").toString());
        ui->projectTableWidget->setItem(rowNum, 0, nameItem);
        addressItem->setText(jsonProjectAllObject.value("address").toString());
        ui->projectTableWidget->setItem(rowNum, 1, addressItem);
        isAutoInspectItem->setText(QString::number(jsonProjectAllObject.value("isAutoInspect").toInt()));
        ui->projectTableWidget->setItem(rowNum, 2, isAutoInspectItem);
        isAutoTestItem->setText(QString::number(jsonProjectAllObject.value("isAutoTestItem").toInt()));
        ui->projectTableWidget->setItem(rowNum, 3, isAutoTestItem);
        isAutoPrint->setText(QString::number(jsonProjectAllObject.value("isAutoPrint").toInt()));
        ui->projectTableWidget->setItem(rowNum, 4, isAutoPrint);
        inspectTime->setText(QString::number(jsonProjectAllObject.value("isAutoPrint").toInt()));
        ui->projectTableWidget->setItem(rowNum, 5, inspectTime);
        testTime->setText(QString::number(jsonProjectAllObject.value("isAutoPrint").toInt()));
        ui->projectTableWidget->setItem(rowNum, 6, testTime);
        beforeOpenValveLowerPressure->setText(QString::number(jsonProjectAllObject.value("beforeOpenValveLowerPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 7, beforeOpenValveLowerPressure);
        beforeOpenValveUpperPressure->setText(QString::number(jsonProjectAllObject.value("beforeOpenValveUpperPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 8, beforeOpenValveUpperPressure);
        afterOpenValveLowerPressure->setText(QString::number(jsonProjectAllObject.value("afterOpenValveLowerPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 9, afterOpenValveLowerPressure);
        afterOpenValveUpperPressure->setText(QString::number(jsonProjectAllObject.value("afterOpenValveUpperPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 10, afterOpenValveUpperPressure);
        upperFlow->setText(QString::number(jsonProjectAllObject.value("upperFlow").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 11, upperFlow);
        lowerFlow->setText(QString::number(jsonProjectAllObject.value("lowerFlow").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 12, lowerFlow);
        upperTemper->setText(QString::number(jsonProjectAllObject.value("upperTemper").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 13, upperTemper);
        lowerTemper->setText(QString::number(jsonProjectAllObject.value("LowerTemper").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 14, lowerTemper);

        remark->setText(jsonProjectAllObject.value("remarks").toString());
        ui->projectTableWidget->setItem(rowNum, 15, remark);
    }

//    ui->projectTableWidget->setSpan(1,0,1,14);
}

void ManagerTableWindow::slotGetProjectAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", errorInfo, QMessageBox::Ok);
}

void ManagerTableWindow::slotGetUserAllRequestFinished(QJsonObject *reply){
    userAllList->clear();
    QJsonArray result = reply->value("resultList").toArray();
    int rowNum;
    ui->userTableWidget->setRowCount(result.count());
    qDebug() << result.count() << " == result.count()";

    for(int i = 0; i < result.count(); i++){
        rowNum = i;
        QJsonObject jsonUserAllObject = result.at(i).toObject();

        QTableWidgetItem *userId = new QTableWidgetItem();
        QTableWidgetItem *userName = new QTableWidgetItem();
        QTableWidgetItem *type = new QTableWidgetItem();
        QTableWidgetItem *projectId = new QTableWidgetItem();
        QTableWidgetItem *projectName = new QTableWidgetItem();

        userId->setText(QString::number(jsonUserAllObject.value("userId").toInt()));
        ui->userTableWidget->setItem(rowNum, 0, userId);
        userName->setText(jsonUserAllObject.value("userName").toString());
        ui->userTableWidget->setItem(rowNum, 1, userName);
        type->setText(jsonUserAllObject.value("type").toString());
        ui->userTableWidget->setItem(rowNum, 2, type);
        projectId->setText(QString::number(jsonUserAllObject.value("project").toObject().value("projectId").toInt()));
        ui->userTableWidget->setItem(rowNum, 3, projectId);
        projectName->setText(jsonUserAllObject.value("project").toObject().value("name").toString());
        ui->userTableWidget->setItem(rowNum, 4, projectName);
    }
}

void ManagerTableWindow::slotGetUserAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", "获取用户失败"+errorInfo, QMessageBox::Ok);
}

void ManagerTableWindow::slotGetDeviceAllRequestFinished(QJsonObject *reply){
    deviceAllList->clear();
    QJsonArray result = reply->value("resultList").toArray();
    int rowNum;
    ui->deviceTableWidget->setRowCount(result.count());

    qDebug() <<  "result" << result;

    for(int i = 0; i < result.count(); i++){
        rowNum = i;
        QJsonObject jsonDeviceAllObject = result.at(i).toObject();

        QTableWidgetItem *number = new QTableWidgetItem();
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *pipeDiameter = new QTableWidgetItem();
        QTableWidgetItem *pipeDescribe = new QTableWidgetItem();
        QTableWidgetItem *address = new QTableWidgetItem();
        QTableWidgetItem *remarks = new QTableWidgetItem();
        QTableWidgetItem *k = new QTableWidgetItem();
        QTableWidgetItem *cDeviceState = new QTableWidgetItem();
        QTableWidgetItem *gateState = new QTableWidgetItem();
        QTableWidgetItem *cTemperature = new QTableWidgetItem();
        QTableWidgetItem *cPressure = new QTableWidgetItem();
        QTableWidgetItem *project = new QTableWidgetItem();
        QTableWidgetItem *projectName = new QTableWidgetItem();

        number->setText(QString::number(jsonDeviceAllObject.value("number").toInt()));
        ui->deviceTableWidget->setItem(rowNum, 0, number);
//        deviceId->setText(QString::number(jsonDeviceAllObject.value("deviceId").toInt()));
//        ui->deviceTableWidget->setItem(rowNum, 1, deviceId);
        name->setText(jsonDeviceAllObject.value("name").toString());
        ui->deviceTableWidget->setItem(rowNum, 1, name);
        pipeDiameter->setText(QString::number(jsonDeviceAllObject.value("pipeDiameter").toDouble()));
        ui->deviceTableWidget->setItem(rowNum, 2, pipeDiameter);
        pipeDescribe->setText(jsonDeviceAllObject.value("pipeDescribe").toString());
        ui->deviceTableWidget->setItem(rowNum, 3, pipeDescribe);
        address->setText(jsonDeviceAllObject.value("address").toString());
        ui->deviceTableWidget->setItem(rowNum, 4, address);

        k->setText(QString::number(jsonDeviceAllObject.value("k").toInt()));
        ui->deviceTableWidget->setItem(rowNum, 5, k);
        cDeviceState->setText(jsonDeviceAllObject.value("cDeviceState").toString());
        ui->deviceTableWidget->setItem(rowNum, 6, cDeviceState);
        gateState->setText(jsonDeviceAllObject.value("gateState").toString());
        ui->deviceTableWidget->setItem(rowNum, 7, gateState);
        cTemperature->setText(QString::number(jsonDeviceAllObject.value("cTemperature").toDouble()));
        ui->deviceTableWidget->setItem(rowNum, 8, cTemperature);
        cPressure->setText(QString::number(jsonDeviceAllObject.value("cPressure").toDouble()));
        ui->deviceTableWidget->setItem(rowNum, 9, cPressure);
        project->setText(QString::number(jsonDeviceAllObject.value("project").toObject().value("projectId").toInt()));
        ui->deviceTableWidget->setItem(rowNum, 10, project);
        remarks->setText(jsonDeviceAllObject.value("remarks").toString());
        ui->deviceTableWidget->setItem(rowNum, 12, remarks);
        projectName->setText(jsonDeviceAllObject.value("project").toObject().value("name").toString());
        ui->deviceTableWidget->setItem(rowNum, 11, projectName);
    }
}

void ManagerTableWindow::slotGetDeviceAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", "获取设备失败"+errorInfo, QMessageBox::Ok);
}

//button of all function
void ManagerTableWindow::slotUpdateInfoButtonClicked(){
    ;
}

void ManagerTableWindow::slotDeleteInfoButtonClicked(){
    ;
}

void ManagerTableWindow::slotReturmButtonClicked(){
    ;
}

void ManagerTableWindow::slotSearchInfoButtonClicked(){
    ;
}

ManagerTableWindow::~ManagerTableWindow()
{
    delete ui;
}
