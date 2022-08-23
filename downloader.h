#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QObject>
#include <QUrl>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = nullptr);

    void downloadFileFromURL(const QString &url, const QString &filePath);

signals:

};

#endif // DOWNLOADER_H
