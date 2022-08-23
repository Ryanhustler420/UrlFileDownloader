#include "predownloadconfigwindow.h"
#include "ui_predownloadconfigwindow.h"

PreDownloadConfigWindow::PreDownloadConfigWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PreDownloadConfigWindow)
{
    ui->setupUi(this);
    setFixedSize(width(), height());

    if (!lc.get(KEY_REPLACEMENT_KEYWORDS).isNull()) {
        QJsonArray arr = QJsonDocument::fromJson(lc.get(KEY_REPLACEMENT_KEYWORDS).toByteArray()).array();

        map.clear();
        keys.clear();
        for (int o = 0; o < arr.size(); o++) {
            map.insert(arr.at(o).toObject().value("From").toString(), arr.at(o).toObject().value("To").toString());
        }

        if (map.size() > 0) ui->listWidget->clear();
        QMapIterator<QString, QString> i(map);
        while (i.hasNext()) {
            i.next();
            keys.append(i.key());
            ui->listWidget->addItem(QString("From: [ \"%1\" ] To: [ \"%2\" ]").arg(i.key()).arg(i.value()));
        }
    }
}

PreDownloadConfigWindow::~PreDownloadConfigWindow()
{
    delete ui;
}

void PreDownloadConfigWindow::on_cancel_button_clicked()
{
    close();
}

void PreDownloadConfigWindow::on_ok_button_clicked()
{
    QJsonArray wrap;
    QMapIterator<QString, QString> i(map);
    while (i.hasNext()) {
        i.next();
        QJsonObject o;
        o.insert("From", i.key());
        o.insert("To", i.value());
        wrap.push_back(o);
    }

    lc.save(KEY_REPLACEMENT_KEYWORDS, QJsonDocument(wrap).toJson());
    close();
}

void PreDownloadConfigWindow::on_add_button_clicked()
{
    QString from = ui->from_lineEdit->text();
    QString to = ui->to_lineEdit->text();

    if (from.isEmpty()) return;

    keys.clear();
    map.insert(from, to);

    if (map.size() > 0) ui->listWidget->clear();

    QMapIterator<QString, QString> i(map);
    while (i.hasNext()) {
        i.next();
        keys.append(i.key());
        ui->listWidget->addItem(QString("From: [ \"%1\" ] To: [ \"%2\" ]").arg(i.key()).arg(i.value()));
    }

    ui->to_lineEdit->clear();
    ui->from_lineEdit->clear();
}

void PreDownloadConfigWindow::on_remove_button_clicked()
{
    for (QListWidgetItem *k: ui->listWidget->selectedItems()) {
        map.remove(keys.at(ui->listWidget->row(k)));
        keys.removeAt(ui->listWidget->row(k));
        ui->listWidget->takeItem(ui->listWidget->row(k));
    };
}

