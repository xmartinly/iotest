#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    m_pTmr = new QTimer(this);
    connect(m_pTmr, &QTimer::timeout, this, &MainWindow::sendCmd);
    connect(&m_req, &HttpRequest::sendResp, this, &MainWindow::getResp);
}

MainWindow::~MainWindow() {
    if(m_pTmr != nullptr && m_pTmr->isActive()) {
        m_pTmr->stop();
    }
    delete ui;
}


void MainWindow::on_btn_start_clicked() {
    if(m_pTmr->isActive()) {
        return;
    }
    m_pTmr->start(500);
}


void MainWindow::on_btn_stop_clicked() {
    if(!m_pTmr->isActive()) {
        return;
    }
    m_pTmr->stop();
}

void MainWindow::sendCmd() {
    QList<QUrl> urls;
    foreach (auto s, m_urls) {
        urls.append(QUrl(s));
    }
    m_req.sendRequest(urls);
}

void MainWindow::getResp(const QString& resp) {
    qDebug() << resp;
}


