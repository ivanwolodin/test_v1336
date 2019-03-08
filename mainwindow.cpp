#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple text processing");
    converter_obj = new converter();       // instantiation of processing object
    connect(ui->processed_button,          // who is calling signal
            SIGNAL(clicked(bool)),         // signal itself
            this,                          // who udergoes
            SLOT(outputProcessedText()));  // what to do, calling slot

    connect(ui->actionAbout_the_program,
            SIGNAL(triggered(bool)),
            SLOT(aboutTheProgram()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::outputProcessedText()
{
    QString raw_string = ui->raw_text->toPlainText();
    raw_string = raw_string.remove(QRegExp("[«»^]"));
    int case_to_act = dataValidation(raw_string);
//    qDebug()<<case_to_act;
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

void MainWindow::aboutTheProgram()
{
    QMessageBox::information(0,"About program","Program: Simple text processor\n"
                                                       "Version: 2.0\n"
                                                       "Author: Ivan Volodin\n"
                                                       "");
}

int dataValidation(QString raw_data)
{   /*
     * primitive data validation
     * the most primitive validation
     *
     * */
    if (raw_data == ""){
        return -1;
    }
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