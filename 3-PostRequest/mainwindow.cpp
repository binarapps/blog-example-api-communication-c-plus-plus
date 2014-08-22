#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->urlLineEdit->setText(QString("http://localhost:3000/entries"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dataSent()
{
    ui->debugTextBrowser->append("Sending successful");
}

void MainWindow::dataSent(QNetworkReply::NetworkError err)
{
    ui->debugTextBrowser->append(QString("%1").arg(err));
}

void MainWindow::dataSent(const QString &str)
{
    ui->debugTextBrowser->append(str);
}

void MainWindow::on_sendRequestButton_clicked()
{
    sender = new DataSender(ui->urlLineEdit->text());
    senderThread = new QThread(this);
    senderThread->wait();

    sender->setData(ui->titleLineEdit->text(),
                    ui->textPlainTextEdit->toPlainText(),
                    ui->filepathLabel->text()
                    );
    connect(senderThread, SIGNAL(started()), sender, SLOT(start()));
    connect(sender, SIGNAL(sendingFinished()), senderThread, SLOT(quit()));
    connect(sender, SIGNAL(sendingFinished()), sender, SLOT(deleteLater()));
    connect(sender, SIGNAL(sendingFinished()), this, SLOT(dataSent()));
    connect(senderThread, SIGNAL(finished()), senderThread, SLOT(deleteLater()));
    connect(sender, SIGNAL(sendDataFailure(QString)), this, SLOT(dataSent(QString)));
    connect(sender, SIGNAL(sendDataFailure(QNetworkReply::NetworkError)), this, SLOT(dataSent(QNetworkReply::NetworkError)));
    connect(sender, SIGNAL(sendDataFailure(QNetworkReply::NetworkError)), senderThread, SLOT(quit()));

    ui->debugTextBrowser->append("Sending started");
    senderThread->start();
}

void MainWindow::on_selectFilePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Select image"),
                                tr("."),
                                tr("Image files (*.jpg *.png *.gif)"));
    if (!fileName.isEmpty())
        ui->filepathLabel->setText(fileName);
}


