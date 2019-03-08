#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QTextCodec>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->processed_text->setEnabled(true);
    this->setWindowTitle("Simple text processing");
    converter_obj = new converter();       // instantiation of processing object
    connect(ui->processed_button,          // who is calling signal
            SIGNAL(clicked(bool)),         // signal itself
            this,                          // who udergoes
            SLOT(outputProcessedText()));  // what to do, calling slot

    connect(ui->actionAbout_the_program,
            SIGNAL(triggered(bool)),
            SLOT(aboutTheProgram()));

    connect(ui->actionSave_to_file,
            SIGNAL(triggered(bool)),
            SLOT(writeInfoToFile())
            );
    connect(ui->actionRead_from_file,
            SIGNAL(triggered(bool)),
            SLOT(readInfoFromFile()));

    connect(ui->output_button,
            SIGNAL(clicked(bool)),
            SLOT(writeInfoToFile()));
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

void MainWindow::writeInfoToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Data"), "",
            tr("Data (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::WriteOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }
       QString info = ui->processed_text->toPlainText();
       //qDebug()<<info;

       info.replace("\n","\r\n");
       QTextStream out(&file);
               //out.setVersion(QDataStream::Qt_5_12);
               out << info.toUtf8();
           }

}

void MainWindow::readInfoFromFile()
{
    QString raw_text;
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Save Data"), "",
            tr("Data (*.txt);;All Files (*)"));
    if (fileName.isEmpty())
           return;
       else {
           QFile file(fileName);
           if (!file.open(QIODevice::ReadOnly)) {
               QMessageBox::information(this, tr("Unable to open file"),
                   file.errorString());
               return;
           }

    QTextStream in(&file);
            //out.setVersion(QDataStream::Qt_5_12);
           raw_text = in.readAll() ;
    }
    ui->raw_text->setText(raw_text);
    //qDebug()<<raw_text;
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
