#ifndef PREDOWNLOADCONFIGWINDOW_H
#define PREDOWNLOADCONFIGWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QSettings>
#include <QDebug>
#include <QMap>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "localcache.h"

#include <iostream>

namespace Ui {
class PreDownloadConfigWindow;
}

class PreDownloadConfigWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PreDownloadConfigWindow(QWidget *parent = nullptr);
    ~PreDownloadConfigWindow();

private slots:
    void on_cancel_button_clicked();
    void on_ok_button_clicked();
    void on_add_button_clicked();
    void on_remove_button_clicked();

private:
    Ui::PreDownloadConfigWindow *ui;
    QMap<QString, QString> map;
    QList<QString> keys;

    LocalCache lc;
    QString KEY_REPLACEMENT_KEYWORDS = "REPLACEMENT_KEYWORDS";
};

#endif // PREDOWNLOADCONFIGWINDOW_H
