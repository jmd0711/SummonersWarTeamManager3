//#include "teamdisplay.h"
//#include "ui_teamdisplay.h"

//TeamDisplay::TeamDisplay(QString battleName, QWidget *parent) :
//    QDialog(parent),
//    ui(new Ui::TeamDisplay),
//    teamChange(battleName)
//{
//    ui->setupUi(this);
//}

//TeamDisplay::~TeamDisplay()
//{
//    delete ui;
//}

//void TeamDisplay::editContents(QVariant teamData)
//{
//    const Team team = teamData.value<Team>();
//    setWindowTitle(team.getTeamName());

//    ui->lineEdit->setText(team.getTeamName());
//    ui->textEdit->setText(team.getTeamDescription());
//}

//Team TeamDisplay::getTeamChange() const
//{
//    return teamChange;
//}

//void TeamDisplay::on_editButton_released()
//{
//    teamChange.setTeamName(ui->lineEdit->text());
//    teamChange.setTeamDescription(ui->textEdit->toPlainText());

//    done(TeamDisplay::EDIT);
//}

//void TeamDisplay::on_deleteButton_released()
//{
//    done(TeamDisplay::DELETE);
//}
