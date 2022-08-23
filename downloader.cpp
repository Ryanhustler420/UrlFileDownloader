#include "downloader.h"

Downloader::Downloader(QObject *parent): QObject(parent)
{

}

void Downloader::downloadFileFromURL(const QString &url, const QString &filePath) {
    const QString fileName = filePath + url.right(url.size() - url.lastIndexOf("/")); // your filePath should end with a forward slash "/"

    QFile m_file;
    m_file.setFileName(fileName);
    m_file.open(QIODevice::WriteOnly);
    if (!m_file.isOpen()) {
        return; // TODO: permission check?
    }

    QNetworkRequest netRequest;
    netRequest.setUrl(QUrl(url));

    QNetworkReply *netReply = (new QNetworkAccessManager())->get(netRequest);

    QEventLoop loop;
    QObject::connect(netReply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec(); // it will pause this here

    if (!m_file.isWritable()) {
        return; // TODO: error check
    }

    m_file.write(netReply->readAll());
    m_file.close(); // TODO: delete the file from the system later on

    m_file.deleteLater();
}
