#ifndef LOCALCACHE_H
#define LOCALCACHE_H

#include <QObject>
#include <QDebug>
#include <QCoreApplication>
#include <QSettings>

class LocalCache : public QObject
{
    Q_OBJECT
public:
    explicit LocalCache(QObject *parent = nullptr);
    void save(QString key, QVariant value);
    void save(QString key, QVariant value, QString group);

    QVariant get(QString key);
    QVariant get(QString key, QString group);

    void remove(QString key);

private:
    void sync();
    void printAllGroup();

signals:

private:
    QSettings *settings;

};

#endif // LOCALCACHE_H
