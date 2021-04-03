#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(MonsterListModel *mLM, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    mListModel{ mLM }
{
    ui->setupUi(this);
    t = MonsterDisplay::DELETE;
    ui->comboBox->addItem("Name");
    ui->comboBox->addItem("Priority");
    ui->comboBox->addItem("Monster id");

    sortMethod = ui->comboBox->currentText();

    //  TODO:   sorting and filtering
    auto proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mListModel);

    ui->listView->setModel(proxyModel);
    connect(ui->listView, &QListView::clicked, this, &BoxMenu::monsterSelected);
}

BoxMenu::~BoxMenu()
{
    delete ui;
}

void BoxMenu::monsterSelected(const QModelIndex &index)
{
    Monster *monster = mListModel->data(index, Qt::UserRole).value<Monster*>();
    MonsterDisplay monDisplay(t);
    monDisplay.editContents(monster);

    switch (monDisplay.exec())
    {
    case MonsterDisplay::ADD:
        emit addSelected(monster);
        //  ADD is only used in a QDialog request;
        qobject_cast<QDialog*>(this->parent())->close();
        break;
    case MonsterDisplay::DELETE:
        mListModel->removeRow(index.row());
        break;
    case MonsterDisplay::EDIT:
    {
        QVariant mon = QVariant::fromValue(monDisplay.getDataChange());
        mListModel->setData(index, mon, Qt::EditRole);
        break;
    }
    default:
        break;
    }
}

void BoxMenu::on_addButton_released()
{
    //  TODO
}

MonsterDisplay::Task BoxMenu::getTask() const
{
    return t;
}

void BoxMenu::setTask(const MonsterDisplay::Task &value)
{
    t = value;
}

void BoxMenu::on_comboBox_currentIndexChanged(const QString &arg1)
{

}
