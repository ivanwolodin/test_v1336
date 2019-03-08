#ifndef CONVERTER_H
#define CONVERTER_H

#include <QWidget>
#include <QMap>
int GetFloorByFlat(int flat);
class converter : public QWidget
{
    Q_OBJECT
public:
    explicit converter(QWidget *parent = nullptr);


signals:

public slots:
    void NumberAsBinary(char* _result,
                        int _number);

    QString toBinary(int n);
    QString sortingByPetrolStations(QString raw_data);
    QString sortingDebtorsByFloor(QString raw_data);
    //QString SortingByPetrolStations(QString raw_data);
};
int getFloorByFlat(int flat);
#endif // CONVERTER_H
