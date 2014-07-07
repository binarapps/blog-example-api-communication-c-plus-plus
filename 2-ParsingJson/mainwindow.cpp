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
        bool parsingSuccess= parser.parseJson(string);
        if(parsingSuccess)
            ui->debugTextBrowser->append(tr("Parsing JSON successful"));
        else
            ui->debugTextBrowser->append(tr("!!Parsing JSON unsuccessful"));

        updateGui();
    }
    else
    {
        //handle errors
    }
    reply->deleteLater();
}

void MainWindow::updateGui()
{
    ui->resultTextBrowser->append(
                QString("Entry id:%1").arg(parser.getEntryId()));
    ui->resultTextBrowser->append(
                QString("Entry name: %1").arg(parser.getName()));
    ui->resultTextBrowser->append(
                QString("Created at: %1").arg(parser.getCreatedAt().toString("yyyy-MM-dd HH:mm:ss.zzz")));
    ui->resultTextBrowser->append(
                QString("Updated at: %1").arg(parser.getUpdatedAt().toString("yyyy-MM-dd HH:mm:ss.zzz")));
    ui->imageLabel->setPixmap(
                QPixmap::fromImage(parser.getFile()));
}
