#include "globle.h"

int Globle::userId = 1;
QString Globle::userTypeString = "项目管理员,设备管理员";
int Globle::kValueList[6] = {80, 115, 161, 202, 242, 363};
QStringList Globle::userTypeList = Globle::userTypeString.split(",");
int Globle::userType = 1;
QString  Globle::userName = "";
int Globle::projectId = 0;
bool Globle::isProjectIdSet = false;
QString Globle::cookieNumber = "";
bool Globle::isAutoInspect = true;
bool Globle::isAutoTest = true;
int Globle::inspectTime = 5;
int Globle::testTime = 15;
bool Globle::isAutoPrint = false;
double Globle::beforeOpenValveLowerPressure = 0.00;
double Globle::beforeOpenValveUpperPressure = 0.00;
double Globle::afterOpenValveLowerPressure = 0.00;
double Globle::afterOpenValveUpperPressure = 0.00;
double Globle::upperFlow = 0.00;
double Globle::lowerFlow = 0.00;
double Globle::upperTemper = 0.00;
double Globle::lowerTemper = 0.00;

Globle::Globle()
{

}
