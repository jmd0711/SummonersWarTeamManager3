#include "boxmenu.h"
#include "ui_boxmenu.h"

BoxMenu::BoxMenu(MonsterListModel *mLM, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BoxMenu),
    mListModel{ mLM }
{
    ui->setupUi(this);

    t = MonsterDisplay::DELETE;
    proxyModel = new MonsterFilterProxyModel(this);

    listView = new QListView(this);
    listView->setViewMode(QListView::IconMode);
    listView->setFlow(QListView::LeftToRight);
    //listView->setResizeMode(QListView::Adjust);
    listView->setTextElideMode(Qt::ElideRight);
    listView->setGridSize(QSize(128, 135));
    //listView->setItemAlignment(Qt::AlignLeft);
    ui->verticalLayout->addWidget(listView);

    //  TODO:   sorting and filtering

    //proxyModel->setSourceModel(proxyModel);
    //proxyModel->sort(-1);

    //QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(mListModel);
    proxyModel->setDynamicSortFilter(true);
    listView->setModel(proxyModel);

    ui->comboBox->addItem("Monster id");
    ui->comboBox->addItem("Name");
    ui->comboBox->addItem("Priority");

    connect(listView, &QListView::clicked, this, &BoxMenu::monsterSelected);
}

BoxMenu::~BoxMenu()
{
    delete ui;
}

void BoxMenu::monsterSelected(const QModelIndex &proxyIndex)
{
    QModelIndex index = proxyModel->mapToSource(proxyIndex);
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

MonsterDisplay::Task BoxMenu::getTask() const
{
    return t;
}

void BoxMenu::setTask(const MonsterDisplay::Task &value)
{
    t = value;
}


void BoxMenu::on_comboBox_currentTextChanged(const QString &arg1)
{
    //  sorts twice to force a sort when "lessThan" method is changed. NOT INTENDED AND NEEDS FIX
    //  TODO:   Fix
    if (arg1 == "Name")
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::NAME);
        proxyModel->sort(0, Qt::DescendingOrder);
        proxyModel->sort(0, Qt::AscendingOrder);
    }
    else if (arg1 == "Priority")
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::PRIORITY);
        proxyModel->sort(0, Qt::AscendingOrder);
        proxyModel->sort(0, Qt::DescendingOrder);
    }
    else
    {
        proxyModel->setSortBy(MonsterFilterProxyModel::DEFAULT);
        proxyModel->sort(0, Qt::DescendingOrder);
        proxyModel->sort(0, Qt::AscendingOrder);
    }

    //listView->reset();
}

void BoxMenu::on_lineEdit_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegExp(QRegExp(arg1, Qt::CaseInsensitive, QRegExp::FixedString));
}
