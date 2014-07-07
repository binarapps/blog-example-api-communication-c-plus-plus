#include "jsonparser.h"

JsonParser::JsonParser()
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
}

int JsonParser::getEntryId() const
{
    return entryId;
}

QString JsonParser::getName() const
{
    return name;
}

QImage JsonParser::getFile() const
{
    return file;
}

QDateTime JsonParser::getCreatedAt() const
{
    return created_at;
}

QDateTime JsonParser::getUpdatedAt() const
{
    return updated_at;
}

void JsonParser::obtainImage(const Json::Value &fileRoot)
{
    QString base64encoded = QString::fromStdString(fileRoot.get("base64encoded", "").asString());
    QString checksum = QString::fromStdString(fileRoot.get("checksum", "").asString());
    if(!compareChecksum(base64encoded, checksum))
        file = QImage();
    else
        file = decodeImage(base64encoded);
}

bool JsonParser::compareChecksum(const QString &encodedImage, const QString &orginal) const
{
    CryptoPP::SHA256 hash;
    byte digest[ CryptoPP::SHA256::DIGESTSIZE ];
    std::string message = encodedImage.toStdString();
    hash.CalculateDigest( digest, (byte *)message.c_str(), message.length() );
    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach( new CryptoPP::StringSink( output ) );
    encoder.Put( digest, sizeof(digest) );
    encoder.MessageEnd();

    return QString::fromStdString(output).toUpper() == orginal.toUpper();
}

QImage JsonParser::decodeImage(const QString &encodedImage)
{
    QByteArray imgData = QByteArray::fromBase64(encodedImage.toAscii());
    QImage img;
    img.loadFromData(imgData);
    return img;
}

bool JsonParser::parseJson(const QString &pureJson)
{
    Json::Value root;
    Json::Reader reader;
    bool parsingSuccesful = reader.parse(pureJson.toStdString(), root);
    if(!parsingSuccesful)
        return false;
    entryId = root.get("id", -1).asInt();
    name = QString::fromStdString(root.get("name", "").asString());
    created_at = QDateTime::fromString(
                QString::fromStdString(root.get("created_at", "").asString()),
                Qt::ISODate);
    updated_at = QDateTime::fromString(
                QString::fromStdString(root.get("updated_at", "").asString()),
                Qt::ISODate);
    obtainImage(root["file"]);
    return true;
}
