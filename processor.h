#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <QWidget>
#include <QMap>
#include <QString>
#include <QVector>
#include <cmath>
int GetFloorByFlat(int flat);
class processor : public QWidget
{
    Q_OBJECT
public:
    explicit processor(QWidget *parent = nullptr);


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
#endif // PROCESSOR_H

