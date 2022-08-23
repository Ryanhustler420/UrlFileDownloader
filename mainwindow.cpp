#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , pi(new QProgressIndicator)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    connect(ui->urls_editor, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    connect(ui->keywords_lineEdit, &QLineEdit::textChanged, this, &MainWindow::onKeywordChanged);

    ui->saving_path_lineEdit->setEnabled(false);
    ui->saving_path_lineEdit->setText(saving_path);
    if (!lc.get(KEY_FILE_LOCATION).isNull())
    {
        if (dir.exists(lc.get(KEY_FILE_LOCATION).toString()))
        {
            ui->saving_path_lineEdit->setText(saving_path = lc.get(KEY_FILE_LOCATION).toString());
        }
    }

    if (!lc.get(KEY_KEYWORDS).isNull())
    {
        keywords.clear();
        keywords.append(lc.get(KEY_KEYWORDS).toString().split(", "));
        ui->keywords_lineEdit->setText(keywords.join(", "));
    }
    else
    {
        keywords.append("png");
        keywords.append("jpg");
        keywords.append("watermark");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTextChanged()
{
    QString text = ui->urls_editor->toPlainText().trimmed();
    if (text.isEmpty()) return;

    QStringList lst = text.split("\n");

    valid_urls.clear();
    for (int i=0; i<lst.size(); i++) {
        if (QUrl::fromUserInput(lst.at(i)).isValid()) {
            for (const QString &e: keywords) {
                if (!e.isEmpty() && lst.at(i).contains(e)) {
                    valid_urls.append(lst.at(i));
                }
            }
        }
    }

    ui->url_count_lbl->setText(QString("%1/%2").arg(valid_urls.size()).arg(lst.size()));
}

void MainWindow::onKeywordChanged()
{
    keywords.clear();
    keywords.append(ui->keywords_lineEdit->text().trimmed().split(","));
    onTextChanged();

    lc.save(KEY_KEYWORDS, keywords.join(", "));
}

void MainWindow::on_download_btn_clicked()
{
    if (!dir.exists(saving_path)) return;
    if (valid_urls.size() == 0) return;
    if (isLoading) return;
    isLoading = true;

    pi->startAnimation();
    pi->setAnimationDelay(50);

    statusBar()->addPermanentWidget(pi);
    statusBar()->showMessage("Downloading...");

    QtConcurrent::run([=](){
        QFutureSynchronizer <void> sync;
        for (QString img: valid_urls) {

            reloadReplacement();

            QMapIterator<QString, QString> i(replacements);
            while (i.hasNext()) {
                i.next();
                img.replace(i.key(), i.value());
            }

            QFuture<void> f = QtConcurrent::run(&downloader, &Downloader::downloadFileFromURL, img, saving_path);
            sync.addFuture(f);
        }
        sync.waitForFinished();

        QDesktopServices::openUrl(saving_path);
        isLoading = false;
        pi->stopAnimation();
        statusBar()->clearMessage();
    });
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_change_dir_location_btn_clicked()
{
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    saving_path = dialog.getExistingDirectory(0, tr("Select Saving Location"), QDir::root().path());
    if (!saving_path.isEmpty()) {
        ui->saving_path_lineEdit->setText(saving_path);
        lc.save(KEY_FILE_LOCATION, saving_path);
    }
}

void MainWindow::on_pre_download_config_btn_clicked()
{
    PreDownloadConfigWindow *pdw = new PreDownloadConfigWindow;
    pdw->setWindowModality(Qt::WindowModality::ApplicationModal);
    pdw->raise();
    pdw->show();
}

void MainWindow::reloadReplacement()
{
    if (!lc.get(KEY_REPLACEMENT_KEYWORDS).isNull())
    {
        QJsonArray arr = QJsonDocument::fromJson(lc.get(KEY_REPLACEMENT_KEYWORDS).toByteArray()).array();
        replacements.clear();
        for (int i = 0; i < arr.size() ; i++ ) {
            replacements.insert(arr.at(i).toObject().value("From").toString(), arr.at(i).toObject().value("To").toString());
        }
    }
}
