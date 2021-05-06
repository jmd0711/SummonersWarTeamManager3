#include "importdialog.h"
#include "ui_importdialog.h"

ImportDialog::ImportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImportDialog)
{
    ui->setupUi(this);

    name = ui->lineEdit;
    radios.push_back(ui->radioButton);
    radios.push_back(ui->radioButton_2);
}

ImportDialog::~ImportDialog()
{
    delete ui;
}

QString ImportDialog::getInput(QWidget *parent, ImportDialog::Task *t, bool *ok)
{
    ImportDialog *dialog = new ImportDialog(parent);

    QString text;

    const int rtrn = dialog->exec();
    if (ok)
        *ok = !!rtrn;

    if (rtrn)
    {
        text = dialog->name->text();
        if (dialog->radios[0]->isChecked())
        {
            *t = ImportDialog::Task::Merge;
        }
        if (dialog->radios[1]->isChecked())
        {
            *t = ImportDialog::Task::New;
        }
    }
    dialog->deleteLater();
    return text;
}
