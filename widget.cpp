#include "widget.h"
#include "ui_widget.h"
#include <converter.h>
#include "qdebug.h"
#include <QDebug>
#include <QString>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    converter_obj = new converter(); // instantiation of processing object
    connect(ui->processed_button,    // who is calling signal
            SIGNAL(clicked(bool)),   // signal itself
            this,                    // who udergoes
            SLOT(outputProcessedText()));  // what to do, calling slot

}

Widget::~Widget()
{
    delete ui;
}

void Widget::outputProcessedText()
{
    QString raw_string = ui->raw_text->toPlainText();
    raw_string = raw_string.remove(QRegExp("[«»^]"));
    int case_to_act = dataValidation(raw_string);
    qDebug()<<case_to_act;
    switch ( case_to_act ) {
     case 1:
       ui->processed_text->setText(converter_obj->toBinary(raw_string.toInt()));
       break;
     case 2:
       ui->processed_text->setText(converter_obj->sortingByPetrolStations(raw_string));
       break;
     case 3:
       ui->processed_text->setText(converter_obj->sortingDebtorsByFloor(raw_string));
       break;
    case -1:
      ui->processed_text->setText("Invalid input data");
      break;
     }
}

int dataValidation(QString raw_data)
{   /*
     * primitive data validation
     * the most primitive validation
     *
     * */
    QStringList myStringList = raw_data.split('\n'); // got all string devided by '\n'
    myStringList.removeAll(QString(""));
    if (myStringList.length() == 1){
        return 1;
    }
    QStringList parsed = myStringList[1].split(QRegExp("\\s+"), QString::SkipEmptyParts);
    if (parsed.length() == 5){
        return 2;
    }
    else if (parsed.length() == 3) {
        return 3;
    }
    else {
        return -1;
    }
}
