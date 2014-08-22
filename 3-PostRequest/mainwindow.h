#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QnetworkReply>
#include <QNetworkRequest>
#include <QFileDialog>
#include <QThread>
#include "datasender.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void dataSent();
    void dataSent(QNetworkReply::NetworkError err);
    void dataSent(const QString & str);
private slots:
    void on_sendRequestButton_clicked();
    void on_selectFilePushButton_clicked();
private:
    DataSender * sender;
    Ui::MainWindow *ui;
    QThread * senderThread;
};

#endif // MAINWINDOW_H
