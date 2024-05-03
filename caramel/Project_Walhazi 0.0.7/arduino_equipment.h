#ifndef ARDUINO_EQUIPMENT_H
#define ARDUINO_EQUIPMENT_H


#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include<QString>
#include <QMainWindow>

class arduino_equipment
{
public:
    int connect_arduino() ;
    int close_arduino() ;
    int write_to_arduino(QByteArray) ;


    QByteArray read_from_arduino() ;
    QSerialPort * getserial() ;
    QString get_arduino_port_name()  ;
private :
    QSerialPort * serial ;
    static const quint16 arduino_uno_vendor_id = 9025 ;
    static const quint16 arduino_uno_product_id = 67 ;
    QString arduino_port_name = "" ;
    bool arduino_is_available ;
    QByteArray data ;

};

#endif // ARDUINO_EQUIPMENT_H
