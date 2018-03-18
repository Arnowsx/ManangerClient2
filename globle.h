#ifndef GLOBLE_H
#define GLOBLE_H

#include <QObject>

class Globle
{
public:
    static int userId;
    static QString userName;
    static QString userTypeString;
    static QStringList userTypeList;
    static int kValueList[6];
    static int userType;
    static int projectId;
    static bool isProjectIdSet;
    static QString cookieNumber;
    //相关参数
    static bool isAutoInspect;
    static bool isAutoTest;
    static int inspectTime;
    static int testTime;
    static bool isAutoPrint;
    static double beforeOpenValveUpperPressure;
    static double beforeOpenValveLowerPressure;
    static double afterOpenValveUpperPressure;
    static double afterOpenValveLowerPressure;
    static double upperFlow;
    static double lowerFlow;
    static double upperTemper;
    static double lowerTemper;
private:
    Globle();
};

#endif // GLOBLE_H
