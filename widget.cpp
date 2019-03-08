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
            SLOT(output_binary()));  // what to do, calling slot

}

Widget::~Widget()
{
    delete ui;
}

void Widget::output_binary()
{
    //int raw_int = ui->raw_text->toPlainText().toInt();
    QString raw_string = ui->raw_text->toPlainText();
    // implement exception processing

    //ui->processed_text->setText(converter_obj->toBinary(raw_int));
    ui->processed_text->setText(converter_obj->SortingByPetrolStations(raw_string));
}
