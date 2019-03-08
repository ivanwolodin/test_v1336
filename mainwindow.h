#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <converter.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    converter *converter_obj;
private:
    Ui::MainWindow *ui;
public slots:
    void outputProcessedText();
    void aboutTheProgram();
};
#endif // MAINWINDOW_H

int dataValidation(QString raw_data);
