#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <json/json.h>
#include <QString>
#include <QImage>
#include <QDateTime>
#include <QTextCodec>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>

#include <iostream>
class JsonParser
{
public:
    JsonParser();
    bool parseJson(const QString & pureJson);
    int getEntryId() const;
    QString getName() const;
    QImage getFile() const;
    QDateTime getCreatedAt() const;
    QDateTime getUpdatedAt() const;
private:
    void obtainImage(const Json::Value & fileRoot);
    bool compareChecksum(const QString &encodedImage, const QString &orginal) const;
    QImage decodeImage(const QString & encodedImage);
    int entryId;
    QString name;
    QImage file;
    QDateTime created_at;
    QDateTime updated_at;

};

#endif // JSONPARSER_H
