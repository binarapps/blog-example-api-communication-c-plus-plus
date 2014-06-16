#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_sendRequestButton_clicked()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(QUrl(ui->urlLineEdit->text())));
    ui->debugTextBrowser->append(tr("request sent"));
}
//example from http://developer.nokia.com/community/wiki/Creating_an_HTTP_network_request_in_Qt
void MainWindow::replyFinished(QNetworkReply * reply)
{
    ui->debugTextBrowser->append(tr("got reply"));
    QVariant statusCodeV =
    reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    // Or the target URL if it was a redirect:
    QVariant redirectionTargetUrl =
    reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
    // see CS001432 on how to handle this

    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray bytes = reply->readAll();
        QString string(bytes);

        ui->resultTextBrowser->setText(string);
    }
    else
    {
        //handle errors
    }
    reply->deleteLater();
}
