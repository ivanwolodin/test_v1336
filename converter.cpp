#include "converter.h"
#include "qdebug.h"
#include <QString>
#include <string>
#include <sstream>
#include <QVector>
#include <cmath>

converter::converter(QWidget *parent) : QWidget(parent)
{

}

void converter::NumberAsBinary(char* _result,
                               int _number)
{
    /* initial task declaration.
     *
     * do not yet know how to handle it
     *
     * */
    int arr[64]; //узнать длину результата
    int i=0, r;

    while(_number!=0){
        r = _number%2;
        arr[i++] = r;
        _number /= 2;
    }

    for(int j=i-1;j>=0;j--){
        qDebug()<<arr[j];
    }
}

QString converter::toBinary(int n)
{
    /* function which convert int to binary
     *
     * */
    QString r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

QString converter::sortingByPetrolStations(QString raw_data)
{
    /* function which sort petrol station by streets
     *
     * assuming that every single line ends with '\n'
     * there is primitive checks for data consistency
     * function is not optimised at all
     *
     * */
    QString response;
    int petrol_type, petrol_price;
    QString street, company_name;
    QMap<QString, QVector<QString> > company_by_street;
    QMap<QString, QVector<int> > petrol_by_company;
    QStringList myStringList = raw_data.split('\n'); // got all string devided by '\n'

    for(int i=1; i<myStringList.length(); i++){//zero-element contains number
        QStringList parsed = myStringList[i].split(QRegExp("\\s+"), QString::SkipEmptyParts);

        petrol_price = parsed[0].toInt();
        street = parsed[2];
        petrol_type = parsed[3].toInt();
        company_name = parsed[4];

        if (petrol_price<2000 or petrol_price>3000){
            return "Inconsistency data with petrol price";
        }

        if (petrol_type!=92 and petrol_type!=95 and petrol_type != 98){
            return "Inconsistency data with petrol type";
        }

          // but example data contains inconsistency with formal task number two!
//        if (!company_by_street[street].contains(company_name)){
//            company_by_street[street].push_back(company_name);
//        }
        company_by_street[street].push_back(company_name);
        if (!petrol_by_company[company_name].contains(petrol_type)){
            petrol_by_company[company_name].push_back(petrol_type);
        }
    }
    //qDebug()<<petrol_by_company<<company_by_street;
    for(auto street: company_by_street.keys()){
        for (int i=0;i<company_by_street[street].length();i++){
            if( petrol_by_company[company_by_street[street][i]].length() ==3){
                response += street;
                response += " ";
                response += company_by_street[street][i];
                response += "\n";
            }
        }
    }
    if (response == "") return "нет";
    return response;
}

QString converter::sortingDebtorsByFloor(QString raw_data)
{
    /* function which sort debtors by floor in desc. order
     * must be somehow optimized
     *
    */
    QString response;
    int flat_number(0);
    float debt;
    QString family;
    QStringList myStringList = raw_data.split('\n'); // got all string devided by '\n'

    QMap<int, int > flat_by_floor;
    QMap<int, QString > debtor_by_flat;
    QMap<int, float > debt_by_flat;
    QMap<int, QVector<int> > flats_by_floor;

    QMap<float, int> flat_by_debt;
    QMap<float, int>::iterator iterator_map=flat_by_debt.end();

    for(int i=1; i<myStringList.length(); i++){//zero-element contains irrelevant for this alg. number

        QStringList parsed = myStringList[i].split(QRegExp("\\s+"), QString::SkipEmptyParts);
        family = parsed[0];
        flat_number = parsed[1].toInt();
        debt = (parsed[2].toFloat());

        flats_by_floor[getFloorByFlat(flat_number)].push_back(flat_number);

        debt_by_flat[flat_number] = debt;
        debtor_by_flat[flat_number] = family;
    }

    float least_debt;
    for (auto floor: flats_by_floor.keys()){
        least_debt = debt_by_flat[flats_by_floor[floor][0]];
        flat_by_floor[floor] = flats_by_floor[floor][0];

        for (int i=0; i<flats_by_floor[floor].length(); i++){
            flat_number = flats_by_floor[floor][i];
            debt = debt_by_flat[flat_number];
            if (debt<least_debt){//collision by the way, if they are equal, not explained in task paper how to resolve it
                flat_by_floor[floor] = flat_number;
                least_debt = debt;
            }
        }
        flat_by_debt[least_debt] = flat_number;

    }

    for (auto floor: flats_by_floor.keys()){
        flat_by_debt[
                debt_by_flat[flat_by_floor[floor]] //get debt
                ] = flat_by_floor[floor];
    }
    qDebug()<<flat_by_debt;
    for(;iterator_map != flat_by_debt.begin();){
        --iterator_map;
        response += QString::number(iterator_map.key()); response += " ";// debt // float to double // must be handled
        response += QString::number(getFloorByFlat(iterator_map.value())); response += " "; // floor
        response += QString::number(iterator_map.value()); response += " ";                 // flat number
        response += debtor_by_flat[iterator_map.value()]; response += " ";                  // family name
        response += "\n";
    }

    return response;
}


int getFloorByFlat(int flat){
        /*get floor by given flat
         *
         * */
        int doorway;
        float floor;
        if (flat>=1 and flat <=36){
            doorway = 1;
        }
        else if (flat>=37 and flat <=72) {
            doorway = 2;
        }
        else if (flat>=73 and flat <=108) {
            doorway = 3;
        }
        else if (flat>=109 and flat <=144) {
            doorway = 4;
        }
        else {
            //exception
            return -1;
        }
        floor = (flat - ((doorway-1)*36) );
        floor/=4;
        return std::ceil(floor); // int values
}

