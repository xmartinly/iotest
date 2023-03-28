#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QNetworkCookieJar>
#include <QNetworkCookie>
#include <QtConcurrent/QtConcurrent>
#include <QDebug>


using namespace std;


class HttpRequest: public QObject {
    Q_OBJECT
  public:

    HttpRequest();
    ~HttpRequest();
    void sendRequest(const QList<QUrl>& urls);

    static QString httpRequest(const QUrl& url);

  signals:

    void sendResp(const QString& resp);

  private:
    QList<QUrl> m_urls;

};




#endif // HTTP_REQUEST_H
