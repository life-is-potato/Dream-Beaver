#ifndef SEARCH_ENGINE_H
#define SEARCH_ENGINE_H

#include <QApplication>
#include <QtWidgets>
#include <QtNetwork>
#include <QtGui>
#include <QtCore>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QCoreApplication>
#include <QNetworkRequest>
#include <QDebug>
#include <QUrl>
#include <QDebug>
#include <QSslSocket>


class search_engine
{
public:
    search_engine();

    QNetworkReply *  search( QString query );
    QStandardItemModel * onNetworkReply(QNetworkReply * );
};
#endif // SEARCH_ENGINE_H
