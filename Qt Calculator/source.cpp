//Source Files -> calculator.cpp:
#include "calculator.h"
#include "./ui_calculator.h"


double calcVal = 0.0;
double memoryVal = 0.0;
bool divTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool multiTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calcVal));
    QPushButton *numBUttons[10];
    for(int i = 0; i < 10; i++){
        QString butName = "Button"+QString::number(i);
        numBUttons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numBUttons[i], SIGNAL(released()),this,SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()),this,SLOT(MathButtonPressed()));
    connect(ui->Equal, SIGNAL(released()),this,SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()),this,SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this, SLOT(ClearScreen()));
    connect(ui->Memadd, SIGNAL(released()), this, SLOT(AddToMemory()));
    connect(ui->Memclear, SIGNAL(released()), this, SLOT(RemoveFromMemory()));
    connect(ui->Memget, SIGNAL(released()), this, SLOT(GetFromMemory()));


}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butval = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) ||(displayVal.toDouble() == 0.0)){
        ui->Display->setText(butval);
    }else{
        QString newVal = displayVal + butval;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal,'g',16));

    }
}

void Calculator::MathButtonPressed(){

     divTrigger = false;
     addTrigger = false;
     subTrigger = false;
     multiTrigger = false;

     QString displayVal = ui->Display->text();
     calcVal = displayVal.toDouble();
     QPushButton *button = (QPushButton *)sender();
     QString butVal = button->text();
     if(QString::compare(butVal,"/",Qt::CaseInsensitive)==0){
         divTrigger = true;
     }else if(QString::compare(butVal,"*",Qt::CaseInsensitive)==0){
         multiTrigger = true;
     }else if(QString::compare(butVal,"+",Qt::CaseInsensitive)==0){
         addTrigger = true;
     }else if(QString::compare(butVal,"-",Qt::CaseInsensitive)==0){
         subTrigger = true;
     }
     ui->Display->setText("");

}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger||subTrigger||multiTrigger||divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;

        }else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        }else if(multiTrigger){
            solution = calcVal * dblDisplayVal;
        }else if(divTrigger){
            solution = calcVal / dblDisplayVal;
        }
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::ChangeNumberSign() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double dblDisplayValSign = -dblDisplayVal;
    ui->Display->setText(QString::number(dblDisplayValSign));
}

void Calculator::ClearScreen() {
    ui->Display->setText("0");
    calcVal = 0.0;
}

void Calculator::AddToMemory() {
    memoryVal += ui->Display->text().toDouble();
}

void Calculator::RemoveFromMemory() {
    memoryVal = 0.0;
}

void Calculator::GetFromMemory() {
    ui->Display->setText(QString::number(memoryVal));
}
