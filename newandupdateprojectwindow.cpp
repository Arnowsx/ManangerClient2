#include "newandupdateprojectwindow.h"
#include "ui_newandupdateprojectwindow.h"

NewAndUpdateProjectWindow::NewAndUpdateProjectWindow(QVector<QString> *rowAllString, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NewAndUpdateProjectWindow)
{
    ui->setupUi(this);

    getInfoApi = NetworkApi::getInstance();
    ui->savePushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
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

    if(rowAllString->size() == 0){
        initWindow();
    }else if(rowAllString->size() == 17){
        ui->projectNameLineEdit->setText(rowAllString->at(1));
        ui->projectAddressLineEdit->setText(rowAllString->at(2));
//        if(rowAllString->at(2) == 1){//测试一下true和false在text中为何物
//            ui->isAutoInspectCheckBox->setChecked(true);
//        }if(rowAllString->at(3) ==1){
//            ui->isAutoTestCheckBox->setChecked(true);
//        }if(rowAllString->at(4) == 1){
//            ui->isAutoPrintCheckBox->setChecked(true);
//        }
//        ui->autoInspectTime->setValue(rowAllString->at(5).toDouble());
//        ui->autoTestTime->setValue(rowAllString->at(6).toDouble());
//        ui->bLowerPressureDoubleSpinBox->setValue(rowAllString->at(7).toDouble());
//        ui->bUpperPressureDoubleSpinBox->setValue(rowAllString->at(8).toDouble());
//        ui->aLowerPressureDoubleSpinBox->setValue(rowAllString->at(9).toDouble());
//        ui->aUpperPressureDoubleSpinBox->setValue(rowAllString->at(10).toDouble());
//        ui->upperFlowDoubleSpinBox->setValue(rowAllString->at(11).toDouble());
//        ui->lowerFlowDoubleSpinBox->setValue(rowAllString->at(12).toDouble());
//        ui->upperTemperDoubleSpinBox->setValue(rowAllString->at(13).toDouble());
//        ui->lowerTemperDoubleSpinBox->setValue(rowAllString->at(14).toDouble());
        ui->remarkTextEdit->setText(rowAllString->at(16));
        ui->projectIdLabel->setText(rowAllString->at(0));
   }
    connects();
}

void NewAndUpdateProjectWindow::initWindow(){
    ui->projectNameLineEdit->setText("请设置项目名称");
    ui->projectAddressLineEdit->setText("请设置项目地址");
    ui->remarkTextEdit->setText("请设置备注");
//    ui->isAutoInspectCheckBox->setChecked(false);
//    ui->isAutoTestCheckBox->setChecked(false);
//    ui->isAutoPrintCheckBox->setChecked(false);
}

void NewAndUpdateProjectWindow::connects(){
    connect(ui->savePushButton, SIGNAL(clicked(bool)), this, SLOT(slotSaveButtonClicked()));
    connect(ui->resetPushButton,SIGNAL(clicked(bool)),this, SLOT(slotReset()));

    connect(getInfoApi,SIGNAL(signalUpdateProjectRequestFinished()), this, SLOT(slotUpdateSuccess()));
    connect(getInfoApi,SIGNAL(signalUpdateProjectRequestError(QString)), this, SLOT(slotUpdateFailed(QString)));
}

void NewAndUpdateProjectWindow::slotSaveButtonClicked(){
    QJsonObject projectJson;
    int projectId = ui->projectIdLabel->text().toInt();
    QString projectName = ui->projectNameLineEdit->text();
    QString projectAddress = ui->projectAddressLineEdit->text();
//    double  autoInspectTime = ui->autoInspectTime->value();
//    double autoTestTime = ui->autoTestTime->value();
//    bool isAutoInspect = ui->isAutoInspectCheckBox->isChecked();
//    bool isAutoTest = ui->isAutoTestCheckBox->isChecked();
//    bool isAutoPrint = ui->isAutoPrintCheckBox->isChecked();
    QString remark = ui->remarkTextEdit->toPlainText();
//    double beforeOpenValveLowerPressure = ui->bLowerPressureDoubleSpinBox->value();
//    double beforeOpenValveUpperPressure = ui->bUpperPressureDoubleSpinBox->value();
//    double afterOpenValueUpperPressure = ui->aUpperPressureDoubleSpinBox->value();
//    double afterOpenValueLowerPressure = ui->aLowerPressureDoubleSpinBox->value();
//    double upperFlow = ui->upperFlowDoubleSpinBox->value();
//    double lowerFlow = ui->lowerFlowDoubleSpinBox->value();
//    double upperTemper = ui->upperFlowDoubleSpinBox->value();
//    double lowerTemper = ui->lowerTemperDoubleSpinBox->value();

    projectJson.insert("ids", projectId);
    projectJson.insert("name", projectName);
    projectJson.insert("address", projectAddress);
    projectJson.insert("remarks", remark);
//    projectJson.insert("isAutoInspect", isAutoInspect);
//    projectJson.insert("isAutoTest", isAutoTest);
//    projectJson.insert("isAutoPrint", isAutoPrint);
//    projectJson.insert("inspectTime", autoInspectTime);
//    projectJson.insert("autoTestTime", autoTestTime);
//    projectJson.insert("beforeOpenValueLowerPressure", beforeOpenValveLowerPressure);
//    projectJson.insert("beforeOpenValueUpperPressure", beforeOpenValveUpperPressure);
//    projectJson.insert("afterOpenValueLowerPressure", afterOpenValueLowerPressure);
//    projectJson.insert("afterOpenValueUpperPressure", afterOpenValueUpperPressure);
//    projectJson.insert("upperFlow", upperFlow);
//    projectJson.insert("lowerFlow", lowerFlow);
//    projectJson.insert("upperTemper", upperTemper);
//    projectJson.insert("lowerTemper", lowerTemper);

    qDebug() << projectJson;
    getInfoApi->updateProjectRequest(projectJson);
    qDebug() << "修改成功";
}

void NewAndUpdateProjectWindow::slotReset(){
    initWindow();
//    ui->autoInspectTime->setValue(0);
//    ui->autoTestTime->setValue(0);
//    ui->bLowerPressureDoubleSpinBox->setValue(0);
//    ui->bUpperPressureDoubleSpinBox->setValue(0);
//    ui->aLowerPressureDoubleSpinBox->setValue(0);
//    ui->aUpperPressureDoubleSpinBox->setValue(0);
//    ui->lowerFlowDoubleSpinBox->setValue(0);
//    ui->upperFlowDoubleSpinBox->setValue(0);
//    ui->lowerTemperDoubleSpinBox->setValue(0);
//    ui->upperTemperDoubleSpinBox->setValue(0);
}

void NewAndUpdateProjectWindow::slotUpdateSuccess(){
    QMessageBox::warning(this, "成功","更新项目成功！", QMessageBox::Ok);
    emit signalRefreshTable(0);
    this->hide();
}

void NewAndUpdateProjectWindow::slotUpdateFailed(QString error){
    QMessageBox::warning(this, "失败","错误原因："+error, QMessageBox::Ok);
}

NewAndUpdateProjectWindow::~NewAndUpdateProjectWindow()
{
    delete ui;
}
