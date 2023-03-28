#include "http_request.h"
#include <iostream>



//HttpRequest::HttpRequest(const QList<QUrl>& urls): m_urls(urls) {
//}

HttpRequest::HttpRequest() {
}

HttpRequest::~HttpRequest() {
}

void HttpRequest::sendRequest(const QList<QUrl>& urls) {
    QVector<QFutureWatcher<QString>*>watchers;
    QEventLoop loop;
    for (const auto& url : urls) {
        auto* watcher = new QFutureWatcher<QString>;
        QObject::connect(watcher, &QFutureWatcher<QString>::finished, [ = ]() {
            QString response = watcher->result();
            if(response.length() > 0) {
                emit sendResp(response);
            }
            watcher->deleteLater();
        });
        QObject::connect(watcher, &QFutureWatcher<QString>::finished, &loop, &QEventLoop::quit);
        watcher->setFuture(QtConcurrent::run(httpRequest, url));
        watchers.push_back(watcher);
    }
    loop.exec();
}

QString HttpRequest::httpRequest(const QUrl& url) {
    QNetworkAccessManager manager;
    manager.setProxy(QNetworkProxy::NoProxy);
    manager.setTransferTimeout(100);
    QNetworkRequest request(url);
    QNetworkReply* reply = manager.get(request);
    QEventLoop loop;
    QThread::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() != QNetworkReply::NoError) {
        cerr << "Network error: " << reply->errorString().toStdString() << endl;
        return "";
    }
    QList<QNetworkCookie> lc_cookie =  manager.cookieJar()->cookiesForUrl(reply->url());
    return reply->readAll() + ":" + lc_cookie.value(0).domain();
}
