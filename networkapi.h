#ifndef NETWORKAPI_H
#define NETWORKAPI_H

#define LOGIN_URL "http://47.94.192.188/com_sys/actions/user_login.action"
#define LOGOUT_URL "http://47.94.192.188/com_sys/actions/user_signOut.action"

#define GET_DEVICE_URL "http://47.94.192.188/com_sys/actions/device_getByIds.action"
#define GET_DEVICE_K_URL "http://47.94.192.188/com_sys/actions/device_getByProjectAndName.action"
#define ADD_DEVICE_URL "http://47.94.192.188/com_sys/actions/device_add.action"
#define DELETE_DEVICE_URL "http://47.94.192.188/com_sys/actions/device_deleteByIds.action"
#define UPDATE_DEVICE_URL "http://47.94.192.188/com_sys/actions/device_updateByIds.action"

#define ADD_REPORT_URL "http://47.94.192.188/com_sys/actions/reportRecord_add.action"
#define GET_REPORT_URL "http://47.94.192.188/com_sys/actions/reportView_getByDeviceId.action"
#define ADD_ALARM_URL "http://47.94.192.188/com_sys/actions/alarmRecord_add.action"
#define GET_ALARM_URL "http://47.94.192.188/com_sys/actions/alarmView_getByDeviceId.action"

#define GET_PROJECT_URL "http://47.94.192.188/com_sys/actions/project_getAll.action"//url--get project
#define ADD_PROJECT_URL "http://47.94.192.188/com_sys/actions/project_add.action"
#define DELETE_PROJECT_URL "http://47.94.192.188/com_sys/actions/project_deleteByIds.action"
#define UPDATE_PROJECT_URL "http://47.94.192.188/com_sys/actions/project_updateByIds.action"

#define GET_USER_URL "http://47.94.192.188/com_sys/actions/user_getAll.action"
#define ADD_USER_URL "http://47.94.192.188/com_sys/actions/user_add.action"
#define DELETE_USER_URL "http://47.94.192.188/com_sys/actions/user_deleteByIds.action"
#define UPDATE_USER_URL "http://47.94.192.188/com_sys/actions/user_updateByIds.action"

#define GET_ALLDEVICE_URL "http://47.94.192.188/com_sys/actions/device_getAll.action"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>
#include "globle.h"

class NetworkApi : public QObject
{
    Q_OBJECT
public:

    static NetworkApi* getInstance();

    void loginRequest(QJsonObject info);
    void logoutRequest();

    void getProjectInfoRequest();//get project info;
    void getProjectAllRequest();
    void getUserInfoRequest();
    void getUserAllRequest();
    void addProjectRequest(QJsonObject info);
    void addUserRequest(QJsonObject info);
    void deleteProjectRequest(QString itemId);
    void deleteUserRequest(QString itemId);
    void updateProjectRequest(QJsonObject info);
    void updateUserRequest(QJsonObject info);

    void getDeviceRequest();
    void getDeviceAllRequest();
    void addDeviceRequest(QJsonObject info);
    void deleteDeviceRequest(QString itemId);
    void updateDeviceRequest(QJsonObject info);
    void getKRequest(QString deviceId);
    void addReportRequest(QJsonObject info);
    void getReportRequest(QString deviceId);
    void addAlarmRequest(QJsonObject info);
    void getAlarmRequest(QString deviceId);
//    void getReportRecordRequest(QJsonObject info);
private:
    QNetworkAccessManager *networkManager;
    static NetworkApi* instance;

    explicit NetworkApi(QObject *parent = nullptr);
    NetworkApi(const NetworkApi&);
    NetworkApi& operator =(const NetworkApi&);
    ~NetworkApi();

    QByteArray getCookie();
signals:
    void signalLoginRequestFinished(QJsonObject *reply);
    void signalLoginRequestError(QString errorInfo);
//author W
    void signalGetProjectInfoRequestFinished(QJsonObject *reply);
    void signalGetProjectInfoRequestError(QString errorInfo);//get project info signals request&error;
    void signalAddProjectRequestFinished(int type);
    void signalAddProjectRequestError(QString erroInfo);
    void signalDeleteProjectRequestFinished(int type);
    void signalDeleteProjectRequestError(int type,QString errorInfo);
    void signalUpdateProjectRequestFinished();
    void signalUpdateProjectRequestError(QString errorInfo);

    void signalGetUserAllRequestFinished(QJsonObject *reply);
    void signalGetUserAllRequestError(QString errorInfo);
    void signalAddUserRequestFinished(int type);
    void signalAddUsertRequestError(QString erroInfo);
    void signalDeleteUserRequestFinished(int type);
    void signalDeleteUserRequestError(int type,QString errorInfo);
    void signalUpdateUserRequestFinished();
    void signalUpdateUserRequestError(QString errorInfo);
//end of author W
    void signalGetDeviceAllRequestFinished(QJsonObject *reply);
    void signalGetDeviceAllRequestError(QString errorInfo);
    void signalGetDeviceInfoRequestFinished(QJsonObject *reply);
    void signalGetDeviceInfoRequestError(QString errorInfo);
    void signalLogoutRequestSuccess();
    void signalLogoutRequestError(QString errorInfo);

    void signalAddDeviceRequestFinished(int type);
    void signalAddDeviceReuqestError(QString errorInfo);
    void signalDeleteDeviceReuqestFinished(int type);
    void signalDeleteDeviceReuqestError(int type,QString errorInfo);
    void signalUpdateDeviceRequestFinished();
    void signalUpdateDeviceRequestError(QString errorInfo);

    void signalGetKFinished(int k);
    void signalAddReportRequestFinished();
    void signalAddReportRequestError(QString errorInfo);
    void signalGetReportRequestFinished();
    void signalGetReportRequestError(QString errorInfo);
    void signalAddAlarmRequestFinished();
    void signalAddAlarmRequestError(QString errorInfo);
    void signalGetAlarmRequestFinished();
    void signalGetAlarmRequestError(QString errorInfo);
private slots:
    void slotRequestFinished(QNetworkReply *reply);
};

#endif // NETWORKAPI_H
