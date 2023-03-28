#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>


#include "http_request.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}


QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

  private slots:
    void on_btn_start_clicked();

    void on_btn_stop_clicked();


    void sendCmd();

    void getResp(const QString& resp);

  private:
    Ui::MainWindow* ui;

    QTimer* m_pTmr = nullptr;

    HttpRequest m_req;

    QStringList m_urls = {
        "http://192.168.1.101/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.5.110/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.99.101/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.99.102/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.99.103/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.99.104/mmsp/electronicsInfo/serialNumber/get",
        "http://192.168.99.105/mmsp/electronicsInfo/serialNumber/get"
    };
};
#endif // MAINWINDOW_H
