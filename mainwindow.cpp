#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new QWidget();
    loginWindow = new LoginWindow();
    mainLayout = new QStackedLayout(this);

    this->setCentralWidget(widget);
    widget->setLayout(mainLayout);

    mainLayout->addWidget(loginWindow);
    mainLayout->setCurrentWidget(loginWindow);

    connectsBeforeLogin();
}

void MainWindow::connectsBeforeLogin(){
    connect(loginWindow,SIGNAL(signalLoginButtonClicked()), this, SLOT(slotLoginButtonClicked()));
}

void MainWindow::connects(){
    connect(managerWindow, SIGNAL(signalOpenProjectTableButtonClicked(int)), this, SLOT(slotOpenTableWindow(int)));
    connect(managerWindow, SIGNAL(signalOpenUserTableButtonClicked(int)), this, SLOT(slotOpenTableWindow(int)));
    connect(managerWindow, SIGNAL(signalOpenDeviceTableButtonClicked(int)), this, SLOT(slotOpenTableWindow(int)));


//    connect(managerTableWindow, SIGNAL(signalUpdateInfoButtonClicked(int, QVector<QString>*)), this, SLOT(slotOpenUpdateWindow(int, QVector<QString>*)));
}

void MainWindow::slotLoginButtonClicked(){
    managerWindow = new ManagerWindow();
    mainLayout->addWidget(managerWindow);
    mainLayout->setCurrentWidget(managerWindow);
    connects();
}

void MainWindow::slotOpenTableWindow(int tabType){
    qDebug()<< tabType;
    managerTableWindow = new ManagerTableWindow();
    connect(managerTableWindow, SIGNAL(signalReturnButtonClicked()), this, SLOT(slotOpenManagerWindow()));
   switch (tabType) {
   case 1:
      managerTableWindow->setTabShow(0);
       break;
   case 2:
       managerTableWindow->setTabShow(1);
       break;
   case 3:
       managerTableWindow->setTabShow(2);
       break;
   default:
       break;
   }
   mainLayout->addWidget(managerTableWindow);
   mainLayout->setCurrentWidget(managerTableWindow);
}

void MainWindow::slotOpenManagerWindow(){
    managerWindow->refresh();
    mainLayout->setCurrentWidget(managerWindow);
}



//void MainWindow::slotOpenUpdateWindow(int type, QVector<QString> *rowAllString){
//    switch (type) {
//    case 0:
//        updateProjectWindow = new NewAndUpdateProjectWindow(rowAllString);
//        mainLayout->addWidget(updateProjectWindow);
//        mainLayout->setCurrentWidget(updateProjectWindow);
//        break;
//    case 1:
//        updateUserWindow = new NewAndUpdateUserWindow(rowAllString);
//        mainLayout->addWidget(updateUserWindow);
//        mainLayout->setCurrentWidget(updateUserWindow);
//        break;
//    case 2:
//        updateDeviceWindow = new NewAndUpdateDeviceWindow(rowAllString);
//        mainLayout->addWidget(updateDeviceWindow);
//        mainLayout->setCurrentWidget(updateDeviceWindow);
//    default:
//        break;
//    }
//}

MainWindow::~MainWindow()
{
    delete ui;
}
