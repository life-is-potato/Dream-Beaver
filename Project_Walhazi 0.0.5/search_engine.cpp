#include "search_engine.h"


QNetworkReply * search_engine::search( QString query ){
    QNetworkAccessManager* manager = new QNetworkAccessManager();
   // Get the search query from the line edit
   if (!query.isEmpty()) {
       // Construct the API URL with the search query
       QUrl apiUrl("https://www.googleapis.com/customsearch/v1?key=AIzaSyDlJTLRZ76Hw_tyGgHQI538SN1S9PN1yl4" + query);
       QNetworkRequest request(apiUrl);
       // Send a GET request to the API
       return manager->get(request) ;
   }
   return nullptr ;
}

QStandardItemModel * search_engine::onNetworkReply(QNetworkReply *reply) {
     QStandardItemModel * resultModel = new QStandardItemModel() ;
    if (reply->error() == QNetworkReply::NoError) {

        QByteArray responseData = reply->readAll();
        QJsonDocument jsonResponse = QJsonDocument::fromJson(responseData);

        if (jsonResponse.isObject()) {
            QJsonObject jsonObject = jsonResponse.object();
            if (jsonObject.contains("items")) {
                QJsonValue itemsValue = jsonObject.value("items");
                if (itemsValue.isArray()) {
                    QJsonArray items = itemsValue.toArray();

                    // Clear the existing data in the result model
                    resultModel->removeRows(0, resultModel->rowCount());

                    int count = 0;
                    // Iterate through the search results
                    for (const QJsonValue &item : items) {
                        // Break the loop if 6 results are already added
                        if (count >= 6)
                            break;

                        // Extract title and link from the search result
                        QString title = item.toObject()["title"].toString();
                        QString link = item.toObject()["link"].toString();

                        // Add the title and link to the result model
                        int row = resultModel->rowCount();
                        resultModel->insertRow(row);
                        resultModel->setData(resultModel->index(row, 0), title);
                        resultModel->setData(resultModel->index(row, 1), link);
                        count++;
                    }
                } else {
                    qDebug() << "Items is not an array";
                }
            } else {
                qDebug() << "No 'items' array found in JSON response";
            }
        } else {
            qDebug() << "JSON response is not an object";
        }
    } else {
        // Display an error message if network request fails
        QMessageBox::critical(nullptr, "Error", "Network Error: " + reply->errorString());
    }

    // Clean up
    reply->deleteLater();
    return resultModel;
}
