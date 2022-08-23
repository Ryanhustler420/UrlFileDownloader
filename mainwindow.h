#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDesktopServices>
#include <QApplication>
#include <QMainWindow>
#include <QSettings>
#include <QTimer>
#include <QDebug>
#include <QList>

#include <QThread>
#include <QFuture>
#include <QtConcurrent>
#include <QFutureSynchronizer>

#include <QMap>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <QUrl>
#include <QFileDialog>

#include "predownloadconfigwindow.h"
#include "qprogressindicator.h"
#include "localcache.h"
#include "downloader.h"

#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onTextChanged();
    void onKeywordChanged();

private slots:
    void on_download_btn_clicked();
    void on_actionExit_triggered();
    void on_change_dir_location_btn_clicked();
    void on_pre_download_config_btn_clicked();

private:
    void reloadReplacement();

private:
    Ui::MainWindow *ui;
    QList<QString> valid_urls;
    QMap<QString, QString> replacements;

    QTimer timer;
    QProgressIndicator *pi;

    QString saving_path = QDir::root().path();
    QStringList keywords;

    bool isLoading = false;

    Downloader downloader;

    QDir dir;
    LocalCache lc;
    QString KEY_REPLACEMENT_KEYWORDS = "REPLACEMENT_KEYWORDS";
    QString KEY_FILE_LOCATION = "FILE_LOCATION";
    QString KEY_KEYWORDS = "KEYWORDS";
};
#endif // MAINWINDOW_H
