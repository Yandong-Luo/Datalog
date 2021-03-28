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

#ifndef SERIAL_SERVICE_H
#define SERIAL_SERVICE_H

#include <QtSerialPort/QSerialPort>
#include <QDebug>
#include <QThread>
#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QApplication>
#include <QElapsedTimer>
#include <QtConcurrent>

#define MAX_NUMBER_SENSORS 16

/*
 * The type of the sensors
*/
#define HCA726S 1
#define LVDT_SENSORS 2
#define TORQUE_SENSORS 3

// Record the content of each Reader
typedef struct {
    int Reader_Index;
    int Type;
    int ID;
    QList<double> data;
    bool isRecord;
    bool isReading;
    bool setZero;
    QString saveDirectory;
    QString fileName;
} Reader;

class Serial_Service:public QObject
{
    Q_OBJECT

public:
    explicit Serial_Service(QObject *parent = nullptr);
    ~Serial_Service();

    // Initialize the serial port configuration
    void Init(QString PortName, long baud);

//    void Init_Port();

    /*
     * Function: Open the port and then return the result
    */
    bool Open_Port();

    /* According to the agreement of the torque sensor,
     * we need to perform XOR verification calculation on the content sent.
     *
     * Function: return the result of XOR veritification calculation
     * @param: data: the data that needs to be XOR verification calculation
    */
    char XORcheckSum(const QByteArray &data);

    /* According to the sensor type and ID, generate corresponding sending request
     *
     * Function: return the byte array to send
     *
     * @param: Type_Index: the type of sensor
     * @param: ID: the ID of sensor
    */
    QByteArray Update_Send_Data(int Type_Index, int ID);

    /* Remove the sending request from the List*/
    void RemoveRequest(int Reader_Index);

    /* According the Type and ID to calculaye the sending request and add them to the list
     *
     * Function: Add the sending request to the List
     *
     * @param: Reader_Index: Current Reader's index
     * @param: Type_Index: the type of sensor
     * @param: ID: the ID of sensor
    */
    void SetRequest(int Reader_Index, int Type_Index, int ID);

    /* Pause the sending and reading
     *
     * Function: pause the thread and clear all the sending request
    */
    void PauseRead();

    /* set the flag to control whether to save all data to a file
     *
     * @param: temp: all record button is clicked ? true or false
    */
    void Set_All_Record(bool temp);

    /* This function is executed in a separate thread to avoid jams and blocking of the GUI interface.
     * When the function is executed for the first time, the sent request will be verified to determine
     * whether the ID and type of the reader correspond to the sensor. When reading, some sensors may rarely
     * fail to read. If it does, we set the value to 255 for the next reading. We use the method of sending a
     * request and reading the data once, so as to ensure the stability of data reception.
     *
     * Function: Send and receive data regularly by the timer.
     */
    void loopSend();

    /* In this function, we will check the start of Fram for each sensor and check whether the data is complete.
     * If the data is not comlete, this function will return a null QByteArray and wait for the data.
     *
     * Function: check the data
     *
     * @param: buffer: the data read from buffer area
     * @param: startOfFrame: the start of frame
     * @param: len: the expected length of data
    */
    QByteArray HandleReceive(QByteArray &buffer, QByteArray startOfFrame,int len);

    // Record the content of each Reader
    static Reader Reader_List[MAX_NUMBER_SENSORS];

    /* If the data is correct and complete, use this function to open another thread to analyze and process
     * the data to get the value of each sensor.
     *
     * Function: send the data to different threads to process them
     *
     * @param: data: the correct and complete data
     * @param: Reader_Index: the Index of Reader
    */
    void Send_Data_to_Process(QByteArray data, int Reader_Index);

    /* This function will be called when the Set button is clicked.
     *
     * Function: Set the interval for timer
     *
     * @param: Interval_value: the value of interval. This value is from your input on the LineEdit.
    */
    void SetReadInterval(unsigned long Interval_value);

    /*close the serial port*/
    void ClosePort(void);

    /* Listen the thread and return the result of whether the data of all sensors have been collected*/
    bool Listen_Loop(void);

signals:
    /* the signals to call the corresponding function. you can find them in the constructor of the
     * mainwindow(the connect() function)
    */
    void Send_HCA_Data_to_Process(QByteArray Data,int Reader_Index);
    void Send_LVDT_Data_to_Process(QByteArray Data,int Reader_Index);
    void Send_Torque_Data_to_Process(QByteArray Data,int Reader_Index);
    void Send_to_Invalid_Reading(int Reader_Index);
    void Send_to_Record_All_Data();

public slots:

    /* This function will be call when the data is coming. In the Init() function, we connect the
     * signal of ReadyRead() function to this function. ReadyRead() function will send a signal,
     * when the serial port detects that data arrives. It should be noted that the existence of
     * data that can be read does not mean that the data is complete.
    */
    void RecieveData();

    // Actually I didn't use these two function in my program. You can ignore them.
    void handleBytesWritten(qint64 bytes);
    void handleError(QSerialPort::SerialPortError error);


private:

    // The serial port class provided by qt
    QSerialPort *port;

    // the name of serial port
    QString m_port;

    // baud rate
    long m_baud_rate;

    /* using a mapping list to access the request that needs to be sent.
     * the key of the mapping list is the index of Reader.
     * the value of the mapping list is the request of the sensor
    */
    QMap<int, QByteArray> m_writeData;

    /* the timer to call the loopsend() function
     * Complete timing request sending through this timer.
    */
    QTimer  *m_timer;

    // Actually I didn't use this variable in my program. You can ignore it.
    qint64  m_bytesWritten;

    // This timer is used to calculate the time required for all current sensors to send and receive
    QElapsedTimer Elapsed_timer;

    /* After sending the request, we opened a loop block and waited for the response from the sensor.
     * Then the timer is used to calculate the time to wait for a response. If the waiting time expires,
     * it is considered that the data reception has failed. If this happens in the first transmission,
     * it means that the ID and type of the sensor may not match, and a prompt window will pop up
    */
    QElapsedTimer waiting_time;

    // To control whether to record all data to a file
    bool m_all_record;

    // Used to determine which Reader the currently received data comes from
    int current_Reader;

    /* It is used to judge that the current data of all sensors have arrived, and this round of reading
     * data is completed
    */
    bool is_dataComplete;

    /* Record the interval time between every time to send the request*/
    qint64 Interval;

    /*Used to judge whether the transmission is the first time.
     * If it is true, then the programe will detect the type and ID is correct or not
    */
    bool check_Send;

    /*Thread lock, used to control the suspension and start of threads*/
    QMutex m_lock;

    /* Used to record whether the current thread is locked or not*/
    bool is_locking;
};

#endif // SERIAL_SERVICE_H
