#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->processed_button,SIGNAL(clicked(bool)),this, SLOT(close()));
//    connect(ui->processed_button,
//            ui->processed_button->clicked(),
//            this,
//            this->close())
}

Widget::~Widget()
{
    delete ui;
}
