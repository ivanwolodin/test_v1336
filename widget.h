#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <converter.h>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    converter *converter_obj;
public slots:
    void output_processed_text();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
