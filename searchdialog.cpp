#include "searchdialog.h"
#include "ui_searchdialog.h"

SearchDialog::SearchDialog(int type, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchDialog)
{
    this->type = type;
    ui->setupUi(this);
    SetType(type);
    connects();
    initDialog();
}

void SearchDialog::connects(){
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(slotPushButtonClickedFinished()));
}

void SearchDialog::initDialog(){
    ui->pushButton->setStyleSheet("QPushButton{background-color: #0b7664;"
                                  "color : #ffffff;"
                                  "border-radius:10px}"
                                  "QPushButton:pressed{background-color: #2b5a52;"
                                                        "color : #ffffff;"
                                                        "border-radius:10px}");
    this->setWindowModality(Qt::ApplicationModal);
}

void SearchDialog::SetType(int type){
    switch (type) {
    case 0:
        ui->tipLabel->setText("搜索项目内容：");
        break;
    case 1:
        ui->tipLabel->setText("搜索用户内容：");
        break;
    case 2:
        ui->tipLabel->setText("搜索设备内容：");
        break;
    default:
        break;
    }
}

void SearchDialog::slotPushButtonClickedFinished(){
    QString text = ui->lineEdit->text();
    emit signalReturnText(type, text);
    this->hide();
}

SearchDialog::~SearchDialog()
{
    delete ui;
}
