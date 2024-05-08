#include "arduino_equipment.h"
#include "mainwindow.h"

int arduino_equipment::connect_arduino() {
    serial = new QSerialPort();

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if (serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()) {
            if (serialPortInfo.vendorIdentifier() == arduino_uno_vendor_id && serialPortInfo.productIdentifier() == arduino_uno_product_id) {
                arduino_port_name = serialPortInfo.portName();
                arduino_is_available = true;
                qDebug() << "port is available! ";
            }
        }
    }
    qDebug() << arduino_port_name;

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            qDebug() << "Serial port opened successfully";
            return 0;
        } else {
            qDebug() << "Failed to open serial port" << serial->errorString();
        }
    }
    return 1;
}


 QByteArray arduino_equipment::read_from_arduino(){

   if(serial->isReadable()){
        data = serial->readAll() ;
        return data ;
   }
   return data ;
 }

 int arduino_equipment::close_arduino(){
    if(serial->isOpen()){
        serial->close() ;
        return 0 ;
    }
    return 1 ;
}

 int arduino_equipment::write_to_arduino(QByteArray d ){
    if(serial->isWritable()){
        serial->write(d) ;
        return 0 ;
    }
    return 1 ;
 }

 QSerialPort *arduino_equipment::getserial()
 {
    return serial;
 }
<<<<<<<< HEAD:projet_final/Project_Walhazi final/arduino_equipment.cpp

 int arduino_equipment::serial_close() {
    serial->close() ;
    return 0 ;
 }
========
>>>>>>>> b910a0edda1592e1abd8a5899d3b4463a39139ea:projet walhazi 0.0.9/Project_Walhazi 0.0.7/arduino_equipment.cpp
