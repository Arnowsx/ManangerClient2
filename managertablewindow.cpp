#include "managertablewindow.h"
#include "ui_managertablewindow.h"


ManagerTableWindow::ManagerTableWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerTableWindow)
{
    ui->setupUi(this);
    getInfoApi = NetworkApi::getInstance();
    projectAllList = new QStringList();
    userAllList =new QStringList();
    deviceAllList = new QStringList();
    initWindow();
    connects();

}

void ManagerTableWindow::initWindow(){
    ui->refreshPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
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
    ui->returnPushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                       "color : #ffffff;"
                                       "border-radius:10px}"
                                       "QPushButton:pressed{background-color: #2b5a52;"
                                                             "color : #ffffff;"
                                                             "border-radius:10px}");

    tableType = ui->tabWidget->currentIndex();
    QStringList projectHeaderLabels;
    QStringList userHeaderLabels;
    QStringList deviceHeaderLabels;
    projectHeaderLabels << "项目ID" << "项目名称" << "项目地址" << "自动巡检" << "自动测试" << "自动打印" << "自动巡检时间" << "自动测试时间" << "打开阀门前最低压力" << "打开阀门前最高压力" << "打开阀门后最低压力" << "打开阀门最高压力" << "最高流量" << "最低流量" << "最高温度" << "最低温度" << "备注";
    userHeaderLabels << "用户ID" << "用户名" << "用户类型" << "所属项目ID" << "所属项目名称" ;
    deviceHeaderLabels << "设备ID" << "设备名称" << "设备管径" << "设备描述" << "管道地址" << "K系数" << "当前状态" << "阀门状态" << "当前温度" << "当前压力" << "所属项目ID" << "所属项目名称" << "备注" << "设备编号";

    ui->projectTableWidget->setHorizontalHeaderLabels(projectHeaderLabels);
    ui->projectTableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    ui->projectTableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->projectTableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->projectTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    for(int i = 3; i <= 5; i++){
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


//信号槽链接1、table获取所有项目、用户和设备；2、返回、修改、删除、搜索button；
void ManagerTableWindow::connects(){
    connect(getSelectTabTable, SIGNAL(signalGetProjectInfoRequestFinished(QJsonObject*)), this, SLOT(slotGetProjectAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetProjectInfoRequestError(QString)), this ,SLOT(slotGetProjectAllRequestError(QString)));

    connect(getSelectTabTable, SIGNAL(signalGetUserAllRequestFinished(QJsonObject*)), this, SLOT(slotGetUserAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetUserAllRequestError(QString)), this ,SLOT(slotGetUserAllRequestError(QString)));

    connect(getSelectTabTable, SIGNAL(signalGetDeviceAllRequestFinished(QJsonObject*)), this, SLOT(slotGetDeviceAllRequestFinished(QJsonObject*)));
    connect(getSelectTabTable, SIGNAL(signalGetDeviceAllRequestError(QString)), this ,SLOT(slotGetDeviceAllRequestError(QString)));

    connect(ui->refreshPushButton, SIGNAL(clicked(bool)), this, SLOT(slotRefreshButtonClicked()));
    connect(ui->returnPushButton, SIGNAL(clicked(bool)), this, SLOT(slotReturnButtonClicked()));
    connect(ui->updatePushButton, SIGNAL(clicked(bool)), this, SLOT(slotUpdateInfoButtonClicked()));
    connect(ui->deletePushButton, SIGNAL(clicked(bool)), this, SLOT(slotDeleteInfoButtonClicked()));
    connect(ui->searchPushButton, SIGNAL(clicked(bool)), this, SLOT(slotSearchInfoButtonClicked()));

    connect(getInfoApi,SIGNAL(signalDeleteProjectRequestFinished(int)), this, SLOT(slotDeleteSuccess(int)));
    connect(getInfoApi,SIGNAL(signalDeleteUserRequestFinished(int)), this, SLOT(slotDeleteSuccess(int)));
    connect(getInfoApi,SIGNAL(signalDeleteDeviceRequestFinished(int)), this, SLOT(slotDeleteSuccess(int)));

    connect(getInfoApi,SIGNAL(signalDeleteProjectRequestError(int,QString)), this, SLOT(slotDeleteFailed(int,QString)));
    connect(getInfoApi,SIGNAL(signalDeleteUserRequestError(int,QString)), this, SLOT(slotDeleteSuccess(int,QString)));
    connect(getInfoApi,SIGNAL(signalDeleteDeviceRequestError(int,QString)), this, SLOT(slotDeleteSuccess(int,QString)));

    connect(this, SIGNAL(signalUpdateInfoButtonClicked(int, QVector<QString>*)), this, SLOT(slotOpenUpdateWindow(int,QVector<QString>*)));
    connect(this, SIGNAL(signalDeleteInfoButtonClicked(int,QString)), this, SLOT(slotDeleteItem(int,QString)));
    connect(this, SIGNAL(signalSearchInfoButtonClicked(int)), this, SLOT(slotOpenSearchDialog(int)));
    //connect(this, SIGNAL(signalUpdateInfoButtonClicked(int, QVector<QString>*)), this, SLOT(slotOpenUpdateWindow(int,QVector<QString>*)));
}


//根据manager页面传来的tabType参数设置tab
void ManagerTableWindow::setTabShow(int tabType){
    getSelectTabTable = NetworkApi::getInstance();
    ui->tabWidget->setCurrentIndex(tabType);
    getSelectTabTable->getProjectAllRequest();
    getSelectTabTable->getUserAllRequest();
    getSelectTabTable->getDeviceAllRequest();
}

//槽函数：填充项目表格
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
        QTableWidgetItem *isAutoInspectItem = new QTableWidgetItem();//
        QTableWidgetItem *isAutoTestItem = new QTableWidgetItem();//
        QTableWidgetItem *isAutoPrint = new QTableWidgetItem();//
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
        QTableWidgetItem *itemId = new QTableWidgetItem();

        itemId->setText(QString::number(jsonProjectAllObject.value("projectId").toInt()));
        ui->projectTableWidget->setItem(rowNum, 0, itemId);
        nameItem->setText(jsonProjectAllObject.value("name").toString());
        ui->projectTableWidget->setItem(rowNum, 1, nameItem);
        addressItem->setText(jsonProjectAllObject.value("address").toString());
        ui->projectTableWidget->setItem(rowNum, 2, addressItem);

        bool isAutoInspectBool = jsonProjectAllObject.value("isAutoInspect").toBool();
        QString isAutoInspectString;
        bool isAutoTestBool = jsonProjectAllObject.value("isAutoTest").toBool();
        QString isAutoTestString;
        bool isAutoPrintBool = jsonProjectAllObject.value("isAutoPrint").toBool();
        QString isAutoPrintString;
        switch (isAutoInspectBool) {
        case true:
            isAutoInspectString = "是";
            break;
        default:
            isAutoInspectString = "否";
            break;
        }

        switch (isAutoTestBool) {
        case true:
            isAutoTestString = "是";
            break;
        default:
            isAutoTestString = "否";
            break;
        }

        switch (isAutoPrintBool) {
        case true:
            isAutoPrintString = "是";
            break;
        default:
            isAutoPrintString = "否";
            break;
        }

        isAutoInspectItem->setText(isAutoInspectString);
        ui->projectTableWidget->setItem(rowNum, 3, isAutoInspectItem);
        isAutoTestItem->setText(isAutoTestString);
        ui->projectTableWidget->setItem(rowNum, 4, isAutoTestItem);
        isAutoPrint->setText(isAutoPrintString);

        ui->projectTableWidget->setItem(rowNum, 5, isAutoPrint);
        inspectTime->setText(QString::number(jsonProjectAllObject.value("inspectTime").toInt()));
        ui->projectTableWidget->setItem(rowNum, 6, inspectTime);
        testTime->setText(QString::number(jsonProjectAllObject.value("testTime").toInt()));
        ui->projectTableWidget->setItem(rowNum, 7, testTime);
        beforeOpenValveLowerPressure->setText(QString::number(jsonProjectAllObject.value("beforeOpenValveLowerPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 8, beforeOpenValveLowerPressure);
        beforeOpenValveUpperPressure->setText(QString::number(jsonProjectAllObject.value("beforeOpenValveUpperPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 9, beforeOpenValveUpperPressure);
        afterOpenValveLowerPressure->setText(QString::number(jsonProjectAllObject.value("afterOpenValveLowerPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 10, afterOpenValveLowerPressure);
        afterOpenValveUpperPressure->setText(QString::number(jsonProjectAllObject.value("afterOpenValveUpperPressure").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 11, afterOpenValveUpperPressure);
        upperFlow->setText(QString::number(jsonProjectAllObject.value("upperFlow").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 12, upperFlow);
        lowerFlow->setText(QString::number(jsonProjectAllObject.value("lowerFlow").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 13, lowerFlow);
        upperTemper->setText(QString::number(jsonProjectAllObject.value("upperTemper").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 14, upperTemper);
        lowerTemper->setText(QString::number(jsonProjectAllObject.value("LowerTemper").toDouble()));
        ui->projectTableWidget->setItem(rowNum, 15, lowerTemper);
        remark->setText(jsonProjectAllObject.value("remarks").toString());
        ui->projectTableWidget->setItem(rowNum, 16, remark);


    }
//    ui->projectTableWidget->setSpan(1,0,1,14);
}


//获取项目错误
void ManagerTableWindow::slotGetProjectAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", errorInfo, QMessageBox::Ok);
}

//槽函数：填充用户表格
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

        QString typeString;
        int typeStr = jsonUserAllObject.value("type").toString().toInt();
        switch (typeStr) {
        case 1:
            typeString = "系统管理员";
            break;
        case 2:
            typeString = "项目管理员";
            break;
        case 3:
            typeString = "设备管理员";
            break;
        default:
            break;
        }
        type->setText(typeString);
        ui->userTableWidget->setItem(rowNum, 2, type);

        projectId->setText(QString::number(jsonUserAllObject.value("project").toObject().value("projectId").toInt()));
        ui->userTableWidget->setItem(rowNum, 3, projectId);
        projectName->setText(jsonUserAllObject.value("project").toObject().value("name").toString());
        ui->userTableWidget->setItem(rowNum, 4, projectName);
    }
}


//获取用户失败
void ManagerTableWindow::slotGetUserAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", "获取用户失败"+errorInfo, QMessageBox::Ok);
}

//槽函数：填充设备表格
void ManagerTableWindow::slotGetDeviceAllRequestFinished(QJsonObject *reply){
    deviceAllList->clear();
    QJsonArray result = reply->value("resultList").toArray();
    int rowNum;
    ui->deviceTableWidget->setRowCount(result.count());

    qDebug() <<  "result" << result;

    for(int i = 0; i < result.count(); i++){
        rowNum = i;
        QJsonObject jsonDeviceAllObject = result.at(i).toObject();

        QTableWidgetItem *deviceId = new QTableWidgetItem();
        QTableWidgetItem *name = new QTableWidgetItem();
        QTableWidgetItem *pipeDiameter = new QTableWidgetItem();
        QTableWidgetItem *pipeDescribe = new QTableWidgetItem();
        QTableWidgetItem *address = new QTableWidgetItem();
        QTableWidgetItem *remarks = new QTableWidgetItem();
        QTableWidgetItem *k = new QTableWidgetItem();
        QTableWidgetItem *cDeviceState = new QTableWidgetItem();//
        QTableWidgetItem *gateState = new QTableWidgetItem();//
        QTableWidgetItem *cTemperature = new QTableWidgetItem();
        QTableWidgetItem *cPressure = new QTableWidgetItem();
        QTableWidgetItem *project = new QTableWidgetItem();
        QTableWidgetItem *projectName = new QTableWidgetItem();
        QTableWidgetItem *number = new QTableWidgetItem();

        deviceId->setText(jsonDeviceAllObject.value("deviceId").toString());
        ui->deviceTableWidget->setItem(rowNum, 0, deviceId);
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

        bool gateStateBool = jsonDeviceAllObject.value("gateState").toBool();
        QString gateStateString;
        switch (gateStateBool) {
        case true:
            gateStateString = "开";
            break;
        default:
            gateStateString = "关";
            break;
        }

        int cDeviceStateInt = jsonDeviceAllObject.value("cDeviceState").toInt();
        QString cDeviceStateString;
        switch (cDeviceStateInt) {
        case 0:
            cDeviceStateString = "离线";
            break;
        case 1:
            cDeviceStateString = "设备正常";
            break;
        case 2:
            cDeviceStateString = "阀门异常";
            break;
        case 3:
            cDeviceStateString = "温度超限";
            break;
        case 4:
            cDeviceStateString = "压力传感器异常";
            break;
        default:
            cDeviceStateString = "其他异常";
            break;
        }
        cDeviceState->setText(cDeviceStateString);
        ui->deviceTableWidget->setItem(rowNum, 6, cDeviceState);
        gateState->setText(gateStateString);
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
        number->setText(QString::number(jsonDeviceAllObject.value("number").toInt()));
        ui->deviceTableWidget->setItem(rowNum, 13, number);
    }
}


//获取设备失败
void ManagerTableWindow::slotGetDeviceAllRequestError(QString errorInfo){
   QMessageBox::warning(this, "错误", "获取设备失败："+errorInfo, QMessageBox::Ok);
}

//槽函数：修改button
void ManagerTableWindow::slotUpdateInfoButtonClicked(){
    int type = ui->tabWidget->currentIndex();
    QVector<QString>*rowItemAll = new QVector<QString>;
    switch (type) {
    case 0:
        if(ui->projectTableWidget->currentItem() != Q_NULLPTR){
            for(int i = 0; i < 17; i++){
                rowItemAll->append(ui->projectTableWidget->item(ui->projectTableWidget->currentItem()->row(), i)->text());
            }
            emit signalUpdateInfoButtonClicked(type, rowItemAll);
        }else{
            QMessageBox::warning(this, "提示", "请选择修改项", QMessageBox::Ok);
        }
        break;
    case 1:
        if(ui->userTableWidget->currentItem() != Q_NULLPTR){
            for(int i = 0; i < 5; i++){
                rowItemAll->append(ui->userTableWidget->item(ui->userTableWidget->currentItem()->row(), i)->text());
            }
            emit signalUpdateInfoButtonClicked(type, rowItemAll);
        } else{
            QMessageBox::warning(this, "提示", "请选择修改项", QMessageBox::Ok);
        }
        break;
    case 2:
        if(ui->deviceTableWidget->currentItem() != Q_NULLPTR){
            for(int i = 0; i < 14; i++){
                rowItemAll->append(ui->deviceTableWidget->item(ui->deviceTableWidget->currentItem()->row(), i)->text());
            }
            emit signalUpdateInfoButtonClicked(type, rowItemAll);
        }else{
            QMessageBox::warning(this, "提示", "请选择修改项", QMessageBox::Ok);
        }
        break;
    default:
        break;
    }
}


//槽函数：打卡修改页面
void ManagerTableWindow::slotOpenUpdateWindow(int type, QVector<QString> *rowAllString){
    switch (type) {
    case 0:
        updateProjectWindow = new NewAndUpdateProjectWindow(rowAllString);
        connect(updateProjectWindow, SIGNAL(signalRefreshTable(int)), this, SLOT(slotRefreshTable(int)));
        updateProjectWindow->show();
        break;
    case 1:
        updateUserWindow = new NewAndUpdateUserWindow(rowAllString);
        connect(updateUserWindow, SIGNAL(signalResfreshTable(int)), this, SLOT(slotRefreshTable(int)));
        updateUserWindow->show();
        break;
    case 2:
        updateDeviceWindow = new NewAndUpdateDeviceWindow(rowAllString);
        connect(updateDeviceWindow, SIGNAL(signalRefreshTable(int)), this, SLOT(slotRefreshTable(int)));
        updateDeviceWindow->show();
        break;
    default:
        break;
    }
}


//槽函数：删除信息
void ManagerTableWindow::slotDeleteInfoButtonClicked(){
    int type = ui->tabWidget->currentIndex();
    QString itemId;
    switch (type) {
    case 0:
        if(ui->projectTableWidget->currentItem() != Q_NULLPTR){
            itemId = ui->projectTableWidget->item(ui->projectTableWidget->currentItem()->row(), 0)->text();
            emit signalDeleteInfoButtonClicked(type, itemId);
        }else{
            QMessageBox::warning(this, "提示", "请选择删除项", QMessageBox::Ok);
        }
        break;
    case 1:
        if(ui->userTableWidget->currentItem() != Q_NULLPTR){
            QString typeString = ui->userTableWidget->item(ui->userTableWidget->currentItem()->row(), 2)->text();
            if(typeString == "系统管理员"){
                QMessageBox::warning(this, "提示", "无法删除系统管理员", QMessageBox::Ok);
            }else{
                itemId = ui->userTableWidget->item(ui->userTableWidget->currentItem()->row(), 0)->text();
                emit signalDeleteInfoButtonClicked(type, itemId);
            }
        }else{
            QMessageBox::warning(this, "提示", "请选择删除项", QMessageBox::Ok);
        }
        break;
    case 2:
        if(ui->deviceTableWidget->currentItem() != Q_NULLPTR){
            itemId = ui->deviceTableWidget->item(ui->deviceTableWidget->currentItem()->row(), 0)->text();

            emit signalDeleteInfoButtonClicked(type, itemId);
        }else{
            QMessageBox::warning(this, "提示", "请选择删除项", QMessageBox::Ok);
        }
        break;
    default:
        break;
    }
}

//槽函数：删除信息调用NetWork API
void ManagerTableWindow::slotDeleteItem(int type, QString itemId){
    switch (type) {
    case 0:
        getInfoApi->deleteProjectRequest(itemId);
        ui->projectTableWidget->removeRow(ui->projectTableWidget->currentItem()->row());
        break;
    case 1:
        getInfoApi->deleteUserRequest(itemId);
        ui->userTableWidget->removeRow(ui->userTableWidget->currentItem()->row());
        break;
    case 2:
        getInfoApi->deleteDeviceRequest(itemId);
        ui->deviceTableWidget->removeRow(ui->deviceTableWidget->currentItem()->row());
        break;
    default:
        break;
    }
}

void ManagerTableWindow::slotReturnButtonClicked(){
    emit signalReturnButtonClicked();
}

void ManagerTableWindow::slotSearchInfoButtonClicked(){
    int type = ui->tabWidget->currentIndex();
    searchDialog = new SearchDialog(type);
    connect(searchDialog, SIGNAL(signalReturnText(int,QString)), this, SLOT(slotSearchResultSetTable(int,QString)));
    searchDialog->show();
}

void ManagerTableWindow::slotSearchResultSetTable(int type, QString text){
    switch (type) {
    case 0:
        if(text == ""){
            for(int i = 0; i < ui->projectTableWidget->rowCount(); i++){
                ui->projectTableWidget->setRowHidden(i, false);
            }
        }else{
            QList <QTableWidgetItem *> item = ui->projectTableWidget->findItems(text, Qt::MatchContains);
            for (int i = 0; i < ui->projectTableWidget->rowCount(); i++){
                ui->projectTableWidget->setRowHidden(i, true);//隐藏所有行
            }
            if (!item.isEmpty())//不为空{
                for (int i = 0; i < item.count(); i++){
                    ui->projectTableWidget->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
                }
        }
        break;
    case 1:
        if(text == ""){
            for(int i = 0; i < ui->userTableWidget->rowCount(); i++){
                ui->userTableWidget->setRowHidden(i, false);
            }
        }else{
            QList <QTableWidgetItem *> item = ui->userTableWidget->findItems(text, Qt::MatchContains);
            for (int i = 0; i < ui->userTableWidget->rowCount(); i++){
                ui->userTableWidget->setRowHidden(i, true);//隐藏所有行
            }
            if (!item.isEmpty())//不为空{
                for (int i = 0; i < item.count(); i++){
                    ui->userTableWidget->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
                }
        }
        break;
    case 2:
        if(text == ""){
            for(int i = 0; i < ui->deviceTableWidget->rowCount(); i++){
                ui->deviceTableWidget->setRowHidden(i, false);
            }
        }else{
            QList <QTableWidgetItem *> item = ui->deviceTableWidget->findItems(text, Qt::MatchContains);
            for (int i = 0; i < ui->deviceTableWidget->rowCount(); i++){
                ui->deviceTableWidget->setRowHidden(i, true);//隐藏所有行
            }
            if (!item.isEmpty())//不为空{
                for (int i = 0; i < item.count(); i++){
                    ui->deviceTableWidget->setRowHidden(item.at(i)->row(),false);//item.at(i).row()输出行号
                }
        }
        break;
    default:
        break;
    };
}

void ManagerTableWindow::slotDeleteSuccess(int type){
    switch (type) {
    case 0:
        QMessageBox::warning(this, "成功","删除项目成功！", QMessageBox::Ok);
        break;
    case 1:
        QMessageBox::warning(this, "成功","删除用户成功！", QMessageBox::Ok);
        break;
    case 2:
        QMessageBox::warning(this, "成功","删除设备成功！", QMessageBox::Ok);
        break;
    default:
        break;
    };
}

void ManagerTableWindow::slotDeleteFailed(int type, QString error){
    switch (type) {
    case 0:
        QMessageBox::warning(this, "失败","错误原因："+error, QMessageBox::Ok);
        break;
    case 1:
        QMessageBox::warning(this, "失败","错误原因："+error, QMessageBox::Ok);
        break;
    case 2:
        QMessageBox::warning(this, "失败","错误原因："+error, QMessageBox::Ok);
        break;
    default:
        break;
    };
}

void ManagerTableWindow::slotRefreshButtonClicked(){
    int type = ui->tabWidget->currentIndex();
    switch (type) {
    case 0:
        ui->projectTableWidget->clearContents();
        NetworkApi::getInstance()->getProjectAllRequest();
        qDebug() << "refresh success";
        break;
    case 1:
        ui->userTableWidget->clearContents();
        NetworkApi::getInstance()->getUserAllRequest();
        qDebug() << "refresh success";
        break;
    case 2:
        ui->deviceTableWidget->clearContents();
        NetworkApi::getInstance()->getDeviceAllRequest();
        qDebug() << "refresh success";
        break;
    default:
        break;
    }
}

void ManagerTableWindow::slotRefreshTable(int type){
    QTime t;
     t.start();
     while(t.elapsed()<1500)
            QCoreApplication::processEvents();
    switch (type) {
    case 0:
        ui->projectTableWidget->clearContents();
        NetworkApi::getInstance()->getProjectAllRequest();
        qDebug() << "update success";
        break;
    case 1:
        ui->userTableWidget->clearContents();
        NetworkApi::getInstance()->getUserAllRequest();
        qDebug() << "update success";
        break;
    case 2:
        ui->deviceTableWidget->clearContents();
        NetworkApi::getInstance()->getDeviceAllRequest();
        qDebug() << "update success";
        break;
    default:
        break;
    }
}

ManagerTableWindow::~ManagerTableWindow()
{
    delete ui;
}
