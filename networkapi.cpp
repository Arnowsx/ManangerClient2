#include "networkapi.h"

NetworkApi* NetworkApi::instance = new NetworkApi();
NetworkApi* NetworkApi::getInstance(){
    return instance;
}

NetworkApi::NetworkApi(QObject *parent) : QObject(parent)
{
    networkManager = new QNetworkAccessManager();

    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slotRequestFinished(QNetworkReply*)));

}

NetworkApi::~NetworkApi(){

}

NetworkApi::NetworkApi(const NetworkApi&){

}

NetworkApi& NetworkApi::operator =(const NetworkApi&){

}


void NetworkApi::slotRequestFinished(QNetworkReply *reply){
    if(reply->url() == QUrl(QString(LOGIN_URL))){
        QString cookie = QString(reply->rawHeader("Set-Cookie"));
        qDebug()<<cookie;
        QRegExp rx("JSESSIONID=([a-zA-Z0-9]+)");
        cookie.indexOf(rx);
        Globle::cookieNumber = rx.cap(0);
        qDebug()<<rx.cap(0);
        QByteArray bytes = reply->readAll();
        qDebug()<<bytes;
        QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalLoginRequestFinished(&replyJson);
        }
        else{
            QString error = replyJson.value("error").toString();
            emit signalLoginRequestError(error);
        }
    }
//start
    else if(reply->url() == QUrl(GET_PROJECT_URL)){//server post linking
        QByteArray bytes = reply->readAll();
        qDebug() << bytes;
        QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();//linking
        QJsonArray resultList = replyJson.value("resultList").toArray();
        qDebug() << "projectResultList" << resultList;
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            emit signalGetProjectInfoRequestFinished(&replyJson);
            return;
        } else {
            QString error = replyJson.value("error").toString();
            qDebug() << error;
            emit signalGetProjectInfoRequestError(error);
            return;
        }
    }

    else if(reply->url() == QUrl(GET_ALLDEVICE_URL)){
        QByteArray bytes = reply->readAll();
        qDebug() << bytes;
        QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
        QJsonArray resultList = replyJson.value("resultList").toArray();

        qDebug() << "deviceResultList" << resultList;
        int code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            qDebug() << "code 200";
            emit signalGetDeviceAllRequestFinished(&replyJson);
            return;
        } else {
            QString error = replyJson.value("error").toString();
            qDebug() << error;
            emit signalGetDeviceAllRequestError(error);
            return;
        }
    }

    else if(reply->url() == QUrl(GET_DEVICE_URL)){
        QByteArray bytes = reply->readAll();
        qDebug() << bytes;
        QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
        QJsonArray resultList = replyJson.value("resultList").toArray();
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            qDebug() << "code : 200";
            if(resultList.at(0).toObject().size() == 1){
                int k =resultList.at(0).toObject().value("k").toInt();
                emit signalGetKFinished(k);
            }
            else{
                emit signalGetDeviceInfoRequestFinished(&replyJson);
            }
            return;
        }
        else{
            QString error = replyJson.value("error").toString();
            qDebug() << error;
            emit signalGetDeviceInfoRequestError(error);
            return;
        }
    }
    else if(reply->url() == QUrl(LOGOUT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalLogoutRequestSuccess();
        }
        else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalLogoutRequestError(error);
        }
    }
    else if(reply->url() == QUrl(ADD_PROJECT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalAddProjectRequestFinished(0);
            return;
        }else{
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalAddProjectRequestError(error);
            return;
        }
    } else if(reply->url() == QUrl(DELETE_PROJECT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204){
            emit signalDeleteProjectRequestFinished(0);
            return;
        }else{
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalDeleteProjectRequestError(0,error);
            return;
        }
    } else if(reply->url() == QUrl(UPDATE_PROJECT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalUpdateProjectRequestFinished();
            return;
        }else{
            QByteArray bytes = reply->readAll();
            qDebug()<< QString(bytes);
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalUpdateProjectRequestError(error);
            return;
        }
    } else if(reply->url() == QUrl(GET_USER_URL)){
        QByteArray bytes = reply->readAll();
        qDebug() << bytes;
        QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
        QJsonArray resultList = replyJson.value("resultList").toArray();
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            emit signalGetUserAllRequestFinished(&replyJson);
            return;
        }else{
            QString error = replyJson.value("error").toString();
            emit signalGetUserAllRequestError(error);
            return;
        }
    } else if(reply->url() == QUrl(ADD_USER_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalAddUserRequestFinished(1);
            return;
        }else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalAddUsertRequestError(error);
            return;
        }
    } else if(reply->url() == QUrl(DELETE_USER_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204){
            emit signalDeleteUserRequestFinished(1);
            return;
        }else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalDeleteUserRequestError(1,error);
            return;
        }
    } else if(reply->url() == QUrl(UPDATE_USER_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalUpdateUserRequestFinished();
            return;
        } else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalUpdateUserRequestError(error);
            return;
        }
    }
    //end of mine
    else if(reply->url() == QUrl(ADD_DEVICE_URL)){
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalAddDeviceRequestFinished(2);
            return;
        }
        else{
            QByteArray bytes = reply->readAll();
            qDebug() << QString(bytes);
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalAddDeviceReuqestError(error);
            return;
        }
    }
    else if(reply->url() == QUrl(DELETE_DEVICE_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 204){
            emit signalDeleteDeviceReuqestFinished(2);
            return;
        }
        else{
            QByteArray bytes = reply->readAll();
            qDebug()<< bytes;
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalDeleteDeviceReuqestError(2,error);
            return;
        }
    }
    else if(reply->url() == QUrl(UPDATE_DEVICE_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalUpdateDeviceRequestFinished();
            return;
        }else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalDeleteDeviceReuqestError(2,error);
            return;
        }
    }
    else if(reply->url() == QUrl(ADD_REPORT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalAddReportRequestFinished();
            return;
        }else{
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalAddReportRequestError(error);
            return;
        }
    }
    else if(reply->url() == QUrl(GET_REPORT_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            emit signalGetReportRequestFinished();
            return;
        }else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalGetReportRequestError(error);
            return;
        }
    }
    else if(reply->url() == QUrl(ADD_ALARM_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 201){
            emit signalAddAlarmRequestFinished();
            return;
        }else{
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalAddReportRequestError(error);
            return;
        }
    }
    else if(reply->url() == QUrl(GET_ALARM_URL)){
        if(reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200){
            emit signalGetAlarmRequestFinished();
            return;
        }else {
            QByteArray bytes = reply->readAll();
            QJsonObject replyJson = QJsonDocument::fromJson(bytes).object();
            QString error = replyJson.value("error").toString();
            emit signalGetReportRequestError(error);
            return;
        }
    }
}
void NetworkApi::loginRequest(QJsonObject info){
    QByteArray array;
    array.append("userName="+info.value("userName").toString().toUtf8().toPercentEncoding());
    array.append("&password="+info.value("password").toString().toUtf8().toPercentEncoding());

    QNetworkRequest networkRequest;
    networkRequest.setUrl(QUrl(LOGIN_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::getProjectInfoRequest(){//post project for id
    QByteArray array;
    QString keys = "projectId+name";
    array.append("keys="+keys.toUtf8().toPercentEncoding());

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_PROJECT_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::getProjectAllRequest(){
    QByteArray array;
    array.append("keys=");

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_PROJECT_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::getUserInfoRequest(){
    QByteArray array;
    array.append("keys=userName");

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_USER_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::getUserAllRequest(){
    QByteArray array;
    array.append("keys=");
//    array.append("&keys=userId");
//    array.append("&keys=projectId");
//    array.append("&keys=type");
//    array.append("&keys=projectName");

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_USER_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::addProjectRequest(QJsonObject info){
    QByteArray array;
    array.append("name="+info.value("name").toString().toUtf8().toPercentEncoding());
    array.append("&address="+info.value("address").toString().toUtf8().toPercentEncoding());
    array.append("&remarks="+info.value("remarks").toString().toUtf8().toPercentEncoding());

    qDebug()<<array;

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(ADD_PROJECT_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::addUserRequest(QJsonObject info){
    QByteArray array;
    array.append("userName="+info.value("userName").toString().toUtf8().toPercentEncoding());
    array.append("&password="+info.value("password").toString().toUtf8().toPercentEncoding());
    array.append("&type="+QString::number(info.value("type").toInt()).toUtf8().toPercentEncoding());
    array.append("&project="+QString::number(info.value("project").toInt()).toUtf8().toPercentEncoding());

    qDebug() << array;

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(ADD_USER_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::deleteProjectRequest(QString itemId){
    QByteArray array;
    array.append("ids="+ itemId.toUtf8().toPercentEncoding());
    qDebug() << array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(DELETE_PROJECT_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::deleteUserRequest(QString itemId){
    QByteArray array;
    array.append("ids="+itemId.toUtf8().toPercentEncoding());
    qDebug() << array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(DELETE_USER_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::updateProjectRequest(QJsonObject info){
    QByteArray array;
    QString keys = "name+address+remarks";

    array.append("ids="+QString::number(info.value("ids").toInt()).toUtf8().toPercentEncoding());
    array.append("&keys="+keys.toUtf8().toPercentEncoding());
    //+isAutoInspect+isAutoTest+isAutoPrint+inspectTime+beforeOpenValveLowerPressure+beforeOpenValveUpperPressure+afterOpenValveLowerPressure+afterOpenValveUpperPressure+upperFlow+lowerFlow+upperTemper+lowerTemper

    array.append("&name="+info.value("name").toString().toUtf8().toPercentEncoding());
    array.append("&address="+info.value("address").toString().toUtf8().toPercentEncoding());
    array.append("&remarks="+info.value("remarks").toString().toUtf8().toPercentEncoding());
//    array.append("&isAutoInspect="+QString::number(info.value("isAutoInspect").toBool()));
//    array.append("&isAutoTest="+QString::number(info.value("isAutoTest").toBool()));
//    array.append("&isAutoPrint="+QString::number(info.value("isAutoPrint").toBool()));
//    array.append("&inspectTime="+QString::number(info.value("inspectTime").toDouble()));
////    array.append("&testTime="+QString::number(info.value("testTime").toDouble()));
//    array.append("&beforeOpenValveLowerPressure="+QString::number(info.value("beforeOpenValveLowerPressure").toDouble()));
//    array.append("&beforeOpenValveUpperPressure="+QString::number(info.value("beforeOpenValveUpperPressure").toDouble()));
//    array.append("&afterOpenValveLowerPressure="+QString::number(info.value("afterOpenValveLowerPressure").toDouble()));
//    array.append("&afterOpenValveUpperPressure="+QString::number(info.value("afterOpenValveUpperPressure").toDouble()));
//    array.append("&upperFlow="+QString::number(info.value("upperFlow").toDouble()));
//    array.append("&lowerFlow="+QString::number(info.value("lowerFlow").toDouble()));
//    array.append("&upperTemper="+QString::number(info.value("upperTemper").toDouble()));
//    array.append("&lowerTemper="+QString::number(info.value(" lowerTemper").toDouble()));

    qDebug() << array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(UPDATE_PROJECT_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::updateUserRequest(QJsonObject info){
    QByteArray array;
    QString keys = "password+type";
    array.append("ids="+QString::number(info.value("ids").toInt()).toUtf8().toPercentEncoding());
    array.append("&keys="+keys.toUtf8().toPercentEncoding());
    array.append("&password="+info.value("password").toString().toUtf8().toPercentEncoding());
    array.append("&type="+QString::number(info.value("type").toInt()).toUtf8().toPercentEncoding());

    qDebug() << array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(UPDATE_USER_URL));
    networkManager->post(networkRequest, array);
}
//end of mine
void NetworkApi::getDeviceRequest(){
    QByteArray array;
    array.append("project="+Globle::projectId);

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_DEVICE_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::getDeviceAllRequest(){
    QByteArray array;
    array.append("keys=");

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_ALLDEVICE_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::logoutRequest(){
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(LOGOUT_URL));
    networkManager->post(networkRequest, "");
}

void NetworkApi::addDeviceRequest(QJsonObject info){
    QByteArray array;
    array.append("deviceId="+info.value("deviceId").toString().toUtf8().toPercentEncoding());
    array.append("&name="+info.value("name").toString().toUtf8().toPercentEncoding());
    array.append("&address="+info.value("address").toString().toUtf8().toPercentEncoding());
    array.append("&k="+QString::number(info.value("k").toInt()).toUtf8().toPercentEncoding());
    array.append("&project="+QString::number(info.value("project").toInt()).toUtf8().toPercentEncoding());
    array.append("&pipeDescribe=null");
    array.append("&pipeDiameter=25");
    array.append("&number=0");
    array.append("&cDeviceState=1");
    array.append("&remarks=null");

    qDebug()<<array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie",getCookie());
    networkRequest.setUrl(QUrl(ADD_DEVICE_URL));
    networkManager->post(networkRequest, array);
}

void NetworkApi::deleteDeviceRequest(QString itemId){
    QByteArray array;
    array.append("ids="+itemId.toUtf8().toPercentEncoding());
    qDebug() << array;

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(DELETE_DEVICE_URL));

    networkManager->post(networkRequest, array);
}

void NetworkApi::updateDeviceRequest(QJsonObject info){
    QByteArray array;
    QString keys = "name+pipeDiameter+pipeDescribe+address+number+remarks+k+project";
    array.append("ids="+info.value("ids").toString().toUtf8().toPercentEncoding());
    array.append("&keys="+keys.toUtf8().toPercentEncoding());
    array.append("&name="+info.value("name").toString().toUtf8().toPercentEncoding());
    array.append("&pipeDiameter="+QString::number(info.value("pipeDiameter").toDouble()).toUtf8().toPercentEncoding());
    array.append("&pipeDescribe="+info.value("pipeDescribe").toString().toUtf8().toPercentEncoding());
    array.append("&address="+info.value("address").toString().toUtf8().toPercentEncoding());
    array.append("&number="+QString::number(info.value("number").toInt()).toUtf8().toPercentEncoding());
    array.append("&k="+QString::number(info.value("k").toInt()).toUtf8().toPercentEncoding());
    array.append("&project="+QString::number(info.value("project").toInt()).toUtf8().toPercentEncoding());

    qDebug() << array;
    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(UPDATE_DEVICE_URL));

    networkManager->post(networkRequest, array);
}

//void NetworkApi::getReportRecordRequest(QJsonObject info){

//}

void NetworkApi::getKRequest(QString deviceId){
    QByteArray array;
    array.append("keys=k");
    array.append("&ids="+deviceId);
    qDebug()<<array;

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_DEVICE_URL));

    qDebug()<<"getting K!!!";
    networkManager->post(networkRequest, array);
}

void NetworkApi::addReportRequest(QJsonObject info)
{
    QByteArray array;
    array.append("date=" + info.value("date").toString().toUtf8().toPercentEncoding());
    array.append("&pressure=" + QString::number(info.value("pressure").toDouble()));
    array.append("&temperature=" + QString::number(info.value("temperature").toDouble()));
    array.append("&averageFlow=" + QString::number(info.value("averageFlow").toDouble()));
    array.append("&totalFlow=" + QString::number(info.value("totalFlow").toDouble()));
    array.append("&judge1=" + info.value("judge1").toString());
    array.append("&judge2=" + info.value("judge1").toString());
    array.append("&device=" + info.value("device").toString());

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(ADD_REPORT_URL));

    networkManager->post(networkRequest, array);
}

void NetworkApi::getReportRequest(QString deviceId){
    QByteArray array;
    array.append("deviceId=" + deviceId);

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_REPORT_URL));

    networkManager->post(networkRequest, array);
}

void NetworkApi::addAlarmRequest(QJsonObject info){
    QByteArray array;
    array.append("date=" + info.value("date").toString().toUtf8().toPercentEncoding());
    array.append("&temperatureAlarm=" + info.value("temperatureAlarm").toString().toUtf8().toPercentEncoding());
    array.append("&deviceTrouble=" + info.value("deviceTrouble").toString().toUtf8().toPercentEncoding());
    array.append("&device=" + info.value("device").toString().toUtf8().toPercentEncoding());

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(ADD_ALARM_URL));

    networkManager->post(networkRequest, array);
}

void NetworkApi::getAlarmRequest(QString deviceId){
    QByteArray array;
    array.append("deviceId=" + deviceId);

    QNetworkRequest networkRequest;
    networkRequest.setRawHeader("Set-Cookie", getCookie());
    networkRequest.setUrl(QUrl(GET_ALARM_URL));

    networkManager->post(networkRequest, array);
}

QByteArray NetworkApi::getCookie(){
    QByteArray cookie;
    cookie.append(Globle::cookieNumber);
    return cookie;
}
