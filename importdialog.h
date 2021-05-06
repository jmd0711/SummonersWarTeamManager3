#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>

namespace Ui {
class ImportDialog;
}

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    enum Task
    {
        Merge,
        New
    };
    explicit ImportDialog(QWidget *parent = nullptr);
    ~ImportDialog();

    static QString getInput(QWidget *parent, Task *t, bool *ok);

private:
    Ui::ImportDialog *ui;

    QLineEdit* name;
    QList<QRadioButton*> radios;
};

#endif // IMPORTDIALOG_H
