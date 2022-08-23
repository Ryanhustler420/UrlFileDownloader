#include "localcache.h"


LocalCache::LocalCache(QObject *parent)
{
    QCoreApplication::setOrganizationName("Raisehand");
    QCoreApplication::setApplicationName("Url File Downloader");
    QCoreApplication::setOrganizationDomain("www.raisehand.software");
    settings = new QSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
}

void LocalCache::save(QString key, QVariant value)
{
    settings->setValue(key, value);
    sync();
}

void LocalCache::save(QString key, QVariant value, QString group)
{
    settings->beginGroup(group);
    settings->setValue(key, value);
    settings->endGroup();
    sync();
}

QVariant LocalCache::get(QString key)
{
    return settings->value(key);
}

QVariant LocalCache::get(QString key, QString group)
{
    settings->beginGroup(group);
    if (!settings->contains(key)) {
        settings->endGroup();
        return -1;
    }
    QVariant value = settings->value(key);
    settings->endGroup();
    return value;
}

void LocalCache::remove(QString key)
{
    if (settings->contains(key)) {
        settings->remove(key);
    }
}

void LocalCache::sync()
{
    settings->sync();
}

void LocalCache::printAllGroup()
{
    foreach (QString group, settings->childGroups()) {
        settings->beginGroup(group);
        qInfo() << "Group: " << group;
        foreach (QString key, settings->childKeys()) {
            qInfo() << "... key:" << key << " = " << settings->value(key).toString();
        }
        settings->endGroup();
    }
}
