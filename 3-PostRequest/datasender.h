#ifndef DATASENDER_H
#define DATASENDER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QHttpPart>
#include <QHttpMultiPart>
#include <QNetworkReply>
#include <QFile>
#include <QFileInfo>

class DataSender : public QObject
{
    Q_OBJECT
public:
    explicit DataSender(const QString &url, QObject *parent = 0);
    ~DataSender();
    void setData(const QString & name, const QString & text, const QString & filepath);
private:
    QString name;
    QString text;
    QString filepath;
    QUrl url;
    QNetworkAccessManager * manager;

    QHttpMultiPart *prepareMultipart();
    QHttpPart createPart(const QString & header, const QString & body);
    QHttpPart createFilePart(const QString & header, QFile *file);
signals:
    void sendDataFailure(QNetworkReply::NetworkError);
    void sendDataFailure(QString);
    void sendingFinished();
public slots:
    void start();
private slots:
    void httpRequestFinished(QNetworkReply*reply);
};

#endif // DATASENDER_H
