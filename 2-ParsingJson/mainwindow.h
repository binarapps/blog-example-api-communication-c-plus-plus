#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QnetworkReply>
#include <QNetworkRequest>

#include "jsonparser.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_sendRequestButton_clicked();
    void replyFinished(QNetworkReply *reply);
private:
    void updateGui();
    Ui::MainWindow *ui;
    JsonParser parser;
};

#endif // MAINWINDOW_H
