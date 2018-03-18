#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    widget = new QWidget(this);
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

MainWindow::~MainWindow()
{
    delete ui;
}
