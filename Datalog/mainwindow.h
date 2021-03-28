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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPortInfo>
#include "QSerialPortInfo" //Serial port information access
#include <QtWidgets>
#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QGroupBox>
#include <QLabel>
#include <QThread>
#include "serial_service.h"
#include "process_data.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//Components that make up Reader
typedef struct {
    QCheckBox *CheckBox_Enable;

    QGroupBox   gridGroupBox;
    QLineEdit   *Display_line;
    QComboBox   *ComboBox_types;
    QComboBox   *ComboBox_id;
    QPushButton *Button_Records;
    QPushButton *Button_Read;
    QPushButton *Button_Zero;
    QLabel      *label_types;
    QLabel      *label_ID;
} Reader_Component;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*
     * Initialize interface button
    */
    void Init_interface();

    /* Remind users of their use through a message box
     *
     * @param: dlgTitle: The title of the message
     * @param: strInfo: The content of the message
     */
    bool show_Message_Box(QString dlgTitle, QString strInfo);

    /* Get the Index of Reader from the Components Name
    */
    int Get_Reader_Index(QString Components_Name);

    /* Add more Readers in the interface for more devices to read
     * If you do not plan to make changes to the Reader interface,
     * I strongly recommend that you do not modify this function.
     **/
    void Creative_DatalogBox();

    /* Automatically Search for readable and writable ports and add it to the ComboBox
     */
    void FindPortName();

signals:
    // Send the signal to the class of Serial_Service to start the thread
    void start_portThread();

public slots:

    // (Open Port) Button response
    void btn_Open_Port_Click(void);

    // (All Read) Button response
    void Btn_All_Read_Click(void);

    /* (Add more) Button response
     * Add more Reader components to the interface
    */
    void Btn_Add_DatalogBox_Click(void);

    // (All Record) Button response
    void Btn_All_Record_Click();

    // (Rest) Button Response
    void Btn_Rest_Click();


    // Reader
    /* (Enable) CheckBoxs Response
     *
     * Function:Enable other buttons of Reader(Type, ID, Record, Read, Zero)
    */
    void CheckBoxs_Enable_Click(void);

    /* (Record) Button response for each Reader
     *
     * function: Make the data of each Reader be saved in the form of a single file
    */
    void Btn_Record_Click(void);

    /* (Read) Button response for each Reader
     *
     * function: Open the operation of read data
    */
    void Btn_Read_Click(void);

    // (Zero) Button response for each Reader
    void Btn_Zero_Click(void);


    // Timer
    // (Set) Button response
    void Btn_SetTimer_Click();

    // (Timer Enable) CheckBoxs Response
    void TimerEnable_CheckChanged();


    // Display the value of the current sensor in the line
    void showData(int Reader_Index);

    /* If the reader type and ID are incorrect,
     * a message box will be displayed to perform the operation again.
    */
    void Handle_Invalid_Sending(int Reader_Index);

    /* (Browse) Button Response
     * Choose the direction to save the file
    */
    void Btn_Browse_Click();

private:
    Ui::MainWindow *ui;

    Reader_Component Component_List[MAX_NUMBER_SENSORS];

    /*
     * This class contains functions such as opening the serial port,
     *  generating sending commands according to the sensor type and ID,
     *  reading and writing operations of the serial port, etc.
    */
    Serial_Service *port;


    /*
     * 用于判断是否打开了端口
     * Determine whether the port is opened
    */
    bool isOpen;

    /*
     * This class contains functions such as data parsing processing,
     *  writing file processing, etc.
    */
    Process_Data *m_process_data;

    // The number of Readers currently available
    int current_Datalog_index;

    /*
     * If it is need to save the data into file and the file name is exist, then this variable to be added to the file name.
    */
    int fileNameIndex;

    QString m_saveDirectory;
    QString m_fileName;

    // Recording all data from each Reader to the file or not
    bool recordAllData;

    // Thread
    QThread *m_portThread;
};
#endif // MAINWINDOW_H
