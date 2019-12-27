#include "dialog.h"
#include "ui_dialog.h"
#include <QString>
#include "settings.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    assign();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::assign()
{
    Settings& sets=Settings::instance();
    ui->port->setText(QString::number(sets.getPort()));
    ui->interval->setText(QString::number(sets.getInterval()));
    ui->width->setText(QString::number(sets.getWidth()));
    ui->height->setText(QString::number(sets.getHeight()));
    ui->BFMModel->setText(sets.getBFMModel());
    ui->G8MModel->setText(sets.getG8MModel());
    ui->BFMKeyIndexes->setText(sets.getBFMKeyIndexes());
    ui->G8MKeyIndexes->setText(sets.getG8MKeyIndexes());
    ui->G8M2BFM->setText(sets.getG8M2BFM());
    ui->BFM2G8M->setText(sets.getBFM2G8M());
    ui->SelectEB->setText(sets.getSelectEB());
    ui->DlibModel->setText(sets.getDlibModel());
    //ui->outputDir->setText(sets.getOutputDir());
}

void Dialog::on_save_clicked()
{
    Settings& set = Settings::instance();
    set.setPort(ui->port->text().toInt());
    set.setInterval(ui->interval->text().toInt());
    set.setWidth( ui->width->text().toInt());
    set.setHeight( ui->height->text().toInt());
    set.setG8M2BFM(ui->G8M2BFM->text());
    set.setBFM2G8M(ui->BFM2G8M->text());

    set.setBFMModel(ui->BFMModel->text());
    set.setG8MModel(ui->G8MModel->text());
    set.setSelectEB(ui->SelectEB->text());
    set.setDlibModel( ui->DlibModel->text());
    set.setBFMKeyIndexes(ui->BFMKeyIndexes->text());
    //set.setOutputDir(ui->outputDir->text());
    set.saveSettings();
    accept();
}

void Dialog::on_reset_clicked()
{
    Settings& sets = Settings::instance();
    sets.reset();
    assign();
}

void Dialog::on_cancel_clicked()
{
    reject();
}
