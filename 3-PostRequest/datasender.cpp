#include "datasender.h"
#include <qDebug>
DataSender::DataSender(const QString &url, QObject *parent) :
    QObject(parent), url(url), manager(0)
{
}

DataSender::~DataSender()
{
    if(manager)
        delete manager;
}

void DataSender::setData(const QString &name, const QString &text, const QString & filepath)
{
    this->name = name;
    this->text = text;
    this->filepath = filepath;
}

QHttpMultiPart * DataSender::prepareMultipart()
{
    QHttpMultiPart * multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart utf8part;
    utf8part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"utf8\""));
    utf8part.setBody("✓");
    multiPart->append(utf8part);

    multiPart->append(createPart("form-data; name=\"entry[name]\"", this->name));
    multiPart->append(createPart("form-data; name=\"entry[text]\"", this->text));
    multiPart->append(createPart("form-data; name=\"commit\"", "Submit"));

    QFile file(this->filepath);
    file.open(QIODevice::ReadOnly);
    if(file.isOpen())
        multiPart->append(createFilePart("form-data; name=\"entry[file]\"", &file));

    return multiPart;
}

QHttpPart DataSender::createPart(const QString &header, const QString &body)
{
    QHttpPart part;
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(header));
    part.setBody(body.toUtf8());
    return part;
}

QHttpPart DataSender::createFilePart(const QString &header, QFile * file)
{
    QHttpPart part;
    QFileInfo info(*file);
    QString extension = info.suffix();
    QString filename = info.fileName();
    part.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(QString("image/%1").arg(extension)));
    part.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(
                       QString("%1; filename=\"%2\"").arg(header).arg(filename)));
    part.setBody(file->readAll());
    return part;
}

void DataSender::start()
{
    manager = new QNetworkAccessManager();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(httpRequestFinished(QNetworkReply*)), Qt::DirectConnection);
    QNetworkRequest request(url);
    QHttpMultiPart * multipart = prepareMultipart();

    manager->post(request, multipart);

}

void DataSender::httpRequestFinished(QNetworkReply * reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        emit sendingFinished();
    }
    else
    {
        emit sendDataFailure(reply->error());
    }
}
