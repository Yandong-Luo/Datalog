/* Datalog is a multi-sensor data collection system base on Qt development.
 * And the verson of Qt is Qt 5.9.9 MSVC2017 64bit. These sensors
 * are base on RS485 Modbus. We connect them to a 16-port RS485 hub / Repeater.
 * These sensors including the tilt sensors (HCA726S, from Shenzhen
 * Ruifen Technology Co., Ltd.)，the motion detector sensors (LVDT HQH8B-10A-M2-C8P,
 * from Shenzhen Haoquan Technology Co., Ltd.), and the Torque Sensors(ZNNT-2000NM,
 * from Bengbu Transducer Sensor Technology Co., Ltd.).
 *
 * In this program, we mainly use three threads. The main thread is responsible
 * for the response and interaction of the UI interface. And we put
 * sending requests and receiving data in one thread. In addition, processing
 * and saving the received data in the third thread.
 *
 * - The application program can support up to 16 sensors to read data.
 *   Through the add more button, you can add more Reader to read.
 *
 * - The data read by each sensor can be saved to a single file, or all
 *   the data can be saved to a specific file.
 *
 * - When reading for the first time, it will check the correctness of
 *   the data sent, and judge whether the sensor type and ID match.
 *
 * - When reading, the received data fails, it will be saved with a value
 *   of 255, and the request will be sent again.
 *
 * - The user can customize the reading interval. If the total time for
 *   sending and reading of all sensors is less than this interval, wait
 *   for a sufficient interval before sending and reading. Otherwise, the
 *   serial port will continue to send and read data at a high frequency
 *   without any pause. To operate the serial port too frequently can easily
 *   cause write timeout errors.
 *
 * - The user can customize the path and the name of the saved file.
 *
 *  If you need more information, please feel free to contact me by email:
 *  dongdashu.aa@gmail.com
 *  dong_dashu@yeah.net
 *
**/

#ifndef PROCESS_DATA_H
#define PROCESS_DATA_H

#include <QObject>
#include "serial_service.h"
#include <QFile>
#include <qmath.h>

class Process_Data: public QObject
{
    Q_OBJECT
public:
    explicit Process_Data(QObject *parent = nullptr);
    ~Process_Data();

    /* Set the flag to set the data to zero*/
    void DataSetZero(int Reader_Index);

    /* Set the flag to creative file or not*/
    void setCreateFile(int Reader_Index);

    /* Set the flag to creative file for all data*/
    void setCreateFile_AllRecord(QString saveDirection, QString fileName);

    /* Close the file, which used to save all data*/
    void closeFile_AllRecord();

    /* Close the file, which used to save the data for Reader*/
    void closeSingleFile(int Reader_Index);

signals:
    /* Send the signal to update the data on the interface
     * you can find them in the constructor of the
     * mainwindow(the connect() function)
    */
    void Update_Displayed_Data(int Reader_Index);

    void send_to_save_file(int Reader_Index);

public slots:
    /* This function will be call when the data need to process.*/
    void Process_HCA_Data(QByteArray data, int Reader_Index);
    void Process_LVDT_Data(QByteArray Data, int Reader_Index);
    void Process_Torque_Data(QByteArray Data, int Reader_Index);

    /* This function will be call when the data need to save as a single file or a total file.*/
    void SaveSingleFile(int);
    void Append_All_Data_To_File();

private:

    // Record which reader needs to create a file for saving the data from a Reader
    bool Reader_createFile[MAX_NUMBER_SENSORS];

    // Multiple file objects for saving Reader data as a single file
    QFile *All_file[MAX_NUMBER_SENSORS];

    // This file object for saving all data as a file
    QFile *file;

    // The content Reader output to the file
    QString readerOutput[MAX_NUMBER_SENSORS];

    // Record whether need to create a file for saving all data
    bool CreateFile_AllRecord;

    // the file name for saving all data
    QString m_FileName_All;

    // the save directory for saving all data
    QString m_saveDirection_All;

    // Record which reader needs to set current data as zero
    bool SetZero[MAX_NUMBER_SENSORS];

    // we need to declare the class to get the static varible (Reader_List)
    Serial_Service *port;
};

#endif // PROCESS_DATA_H
