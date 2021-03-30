#include "monsterdisplay.h"
#include "ui_monsterdisplay.h"

MonsterDisplay::MonsterDisplay(Task t, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonsterDisplay),
    task{ t }
{
    ui->setupUi(this);

//    setAttribute(Qt::WA_DeleteOnClose);
    switch (task)
    {
    case MonsterDisplay::DELETE:
        ui->doButton->setText("Delete");
        break;
    case MonsterDisplay::ADD:
        ui->doButton->setText("Add");
        break;
    case MonsterDisplay::REMOVE:
        ui->doButton->setText("Remove");
        break;
    default:
        //  TODO handle EDIT. EDIT is only meant for returning.
        //  Throw exception?
        break;
    }
}

MonsterDisplay::~MonsterDisplay()
{
    delete ui;
}

void MonsterDisplay::editContents(QVariant monsterData)
{
    const Monster monster = monsterData.value<Monster>();
    setWindowTitle(monster.getName());
    ui->imageLabel->setPixmap(QPixmap::fromImage(monster.getImage()));

    ui->nameLabel->setText(monster.getName());
    //TODO Awakened & element

    ui->prioritySpinBox->setValue(monster.getPriority());
    ui->levelSpinBox->setValue(monster.getLevel());
    ui->hpSpinBox->setValue(monster.getHp());
    ui->defenseSpinBox->setValue(monster.getDefense());
    ui->attackSpinBox->setValue(monster.getAttack());
    ui->speedSpinBox->setValue(monster.getSpeed());
    ui->critRateSpinBox->setValue(monster.getCritRate());
    ui->critDamageSpinBox->setValue(monster.getCritDamage());
    ui->accuracySpinBox->setValue(monster.getAccuracy());
    ui->resistanceSpinBox->setValue(monster.getResistance());
    ui->descriptionEdit->setText(monster.getDescription());
    ui->starsSpinBox->setValue(monster.getStars());
}

void MonsterDisplay::on_editButton_released()
{ 
    dataChange.setAccuracy(ui->accuracySpinBox->value());
    dataChange.setAttack(ui->attackSpinBox->value());
    dataChange.setCritDamage(ui->critDamageSpinBox->value());
    dataChange.setCritRate(ui->critRateSpinBox->value());
    dataChange.setDefense(ui->defenseSpinBox->value());
    dataChange.setDescription(ui->descriptionEdit->toPlainText());
    dataChange.setHp((ui->hpSpinBox->value()));
    dataChange.setLevel((ui->levelSpinBox->value()));
    dataChange.setName(ui->nameLabel->text());  //  change to textedit
    dataChange.setPriority(ui->prioritySpinBox->value());
    dataChange.setResistance(ui->resistanceSpinBox->value());
    dataChange.setSpeed(ui->speedSpinBox->value());
    dataChange.setStars(ui->starsSpinBox->value());
    done(MonsterDisplay::EDIT);
}

void MonsterDisplay::on_doButton_released()
{
    done(task);
}

Monster MonsterDisplay::getDataChange() const
{
    return dataChange;
}


