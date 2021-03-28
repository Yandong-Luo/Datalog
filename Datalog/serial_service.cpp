#include "serial_service.h"

Reader Serial_Service::Reader_List[MAX_NUMBER_SENSORS];

// Initialize variables
Serial_Service::Serial_Service(QObject *parent):QObject(parent)
{
    // The default interval for sending requests is 1000ms
    Interval = 1000;

    m_timer = new QTimer(this);

    m_timer->setInterval(0);

    m_timer->start();

    is_dataComplete = false;

    m_writeData.clear();

    check_Send = true;

    m_all_record = false;

    const QMutexLocker locker(&m_lock);
}

Serial_Service::~Serial_Service()
{
    port->close();
    port->deleteLater();
    delete m_timer;
}

void Serial_Service::Init(QString PortName, long baud)
{
    m_port = PortName;
    m_baud_rate = baud;

    port = new QSerialPort;

    // connect the signal of readyRead to the operation of RecieveData()
    connect(port, &QSerialPort::readyRead, this, &Serial_Service::RecieveData);

    // // Actually I didn't use these two function in my program. You can ignore them.
    connect(port, &QSerialPort::bytesWritten, this, &Serial_Service::handleBytesWritten);
    connect(port, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),this, &Serial_Service::handleError);

    // Connect timers and threads
    connect(m_timer, &QTimer::timeout, this, &Serial_Service::loopSend);
}

bool Serial_Service::Open_Port()
{
    bool isOpen = false;
    port->setPortName(m_port);                         // set the port name
    port->setBaudRate(m_baud_rate);                    // set the baud rate
    port->setDataBits(QSerialPort::Data8);             // set the Data bit
    port->setStopBits(QSerialPort::OneStop);           // set the stop bit
    port->setParity(QSerialPort::NoParity);            // No parity check required
    port->setFlowControl(QSerialPort::NoFlowControl);  // set the flow control

    // open the port
    if (port->open(QIODevice::ReadWrite))
    {
        qDebug() << "Port have been opened";
        port->setDataTerminalReady(true);
        isOpen = true;
    }
    else
    {
       qDebug() << "open it failed";
       isOpen = false;
    }

    // return the result
    return isOpen;
}

void Serial_Service::handleBytesWritten(qint64 bytes)
{
      m_bytesWritten += bytes;
      if (m_bytesWritten == m_writeData.size()) {
          m_bytesWritten = 0;
          qDebug() << QObject::tr("Data successfully sent to port %1").arg(port->portName()) << endl;
      }
}

void Serial_Service::handleError(QSerialPort::SerialPortError serialPortError)
{
      if (serialPortError == QSerialPort::WriteError) {
          qDebug() << QObject::tr("An I/O error occurred while writing the data to port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
      }
}

void Serial_Service::RecieveData()
{
    QByteArray startOfFrame;
    int len = 0;

    static QByteArray Rx_buffer;

    Rx_buffer.append(port->readAll());

    qDebug()<<"current_reader_type:"<<Reader_List[current_Reader-1].Type;

    // According to the type of sensor, set different start of frame
    switch (Reader_List[current_Reader-1].Type) {
        case HCA726S:
        {
            startOfFrame = "\x68";
            len = 16;
            break;
        }
        case LVDT_SENSORS:
        {
            startOfFrame = "\x01\x04";
            len = 9;
            break;
        }
        case TORQUE_SENSORS:
        {
            startOfFrame = "\xBB\xBB\xBB";
            len = 10;
            break;
        }
    }
    /* Check the integrity and correctness of the data.
     * If the check fails, an empty byte array will be obtained*/
    QByteArray data = HandleReceive(Rx_buffer,startOfFrame,len);
    if(!data.isEmpty())
    {
        // Data complete identifier
        is_dataComplete = true;
        // Send data to process
        Send_Data_to_Process(data,current_Reader);
    }
}

QByteArray Serial_Service::HandleReceive(QByteArray &buffer, QByteArray startOfFrame,int len)
{
    QByteArray data;

    // Determine whether the data contains the start of frame
    if(buffer.contains(startOfFrame))
    {
        const int pos = buffer.indexOf(startOfFrame);

        if(pos<0){
            return QByteArray();
        }
        // Determine whether the data is complete
        if(buffer.length()-pos < len)
        {
            return QByteArray();
        }
        // Get the data from buffer
        data.clear();
        data = buffer.mid(pos,len);
        buffer.remove(pos,len);
    }
    if(!data.isEmpty())
    {
        qDebug()<<"data:"<<data.toHex()<<"length:"<<data.length();
    }
    return data;
}

void Serial_Service::loopSend()
{
    // Ensure thread safety when reading and writing serial ports
    m_lock.lock();

    // Determine whether there is data to send
    if(!m_writeData.isEmpty())
    {
        // Start timing, calculate the time required for each read and write for multi-sensor
        Elapsed_timer.restart();

        // Start sending in order according to the mapping list
        QMap<int,QByteArray>::Iterator it=m_writeData.begin();

        while(it != m_writeData.end())
        {
            is_dataComplete = false;
            // Send data asynchronously
            qint64 bytesWritten = port->write(it.value());
            qDebug()<<"write data:"<<it.value().toHex();

            // Get the index of the reader currently being sent
            current_Reader = it.key();
            if (bytesWritten == -1) {
                      qDebug() << QObject::tr("Failed to write the data to port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
                  } else if (bytesWritten != it.value().length()) {
                      qDebug() << QObject::tr("Failed to write all the data to port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
                  }
            else if (!port->waitForBytesWritten(5000)) {
                qDebug() << QObject::tr("Operation timed out or an error occurred for port %1, error: %2").arg(port->portName()).arg(port->errorString()) << endl;
            }

            // Start calculating the time needed to wait for the data to arrive
            waiting_time.start();
            while(!is_dataComplete)
            {
                // Determine whether the first sending and reading is successful
                if(waiting_time.elapsed()>1000 && check_Send)
                {
                    // Sensor type and ID may not match, please check
                    qDebug()<<"remove remove";
                    emit Send_to_Invalid_Reading(it.key());
                    break;
                }
                //Prevent blockage caused by the sensor not responding after sending data
                else if(waiting_time.elapsed() > 1000 && !check_Send){
                    QByteArray data;
                    Send_Data_to_Process(data,it.key());
                    break;
                }
                /* Asynchronous blocking loop*/
                QCoreApplication::processEvents();
            }
            it++;
        }
        check_Send = false;

        // Determine whether you need to save all data to a file
        if(m_all_record)
        {
            QFuture<void> future = QtConcurrent::run([=]() {
                // Code in this block will run in another thread
                emit Send_to_Record_All_Data();
            });
        }

        /* Determine the time required for each round of data transmission and reading for all sensors.
         * If the required time exceeds the interval time, it will not sleep and continue to send at the highest speed.
         * Otherwise, sleep until the interval time is reached
         */
        qDebug()<<"the send and receive took:" << Elapsed_timer.elapsed()<<"ms";
        if(Elapsed_timer.elapsed() > Interval)
        {
            QThread::msleep(0);
        }
        else
        {
            QThread::msleep((unsigned long)(Interval-Elapsed_timer.elapsed()));
        }

        qDebug()<<"timer:"<<QString(QDateTime::currentDateTime().toString("hh:mm:ss.zzz"));
    }
    // Check whether the timer is on or not
    if (!m_timer->isActive())
    {
        m_timer->start();
    }
    m_lock.unlock();
}

void Serial_Service::Send_Data_to_Process(QByteArray data, int Reader_Index)
{
    switch (Reader_List[current_Reader-1].Type) {
        case HCA726S:
        {
//            emit Send_HCA_Data_to_Process(data,Reader_Index);
            QFuture<void> future_HCA_Process = QtConcurrent::run([=]() {
                // Code in this block will run in another thread
                emit Send_HCA_Data_to_Process(data,Reader_Index);
            });
            break;
        }
        case LVDT_SENSORS:
        {
//            emit Send_LVDT_Data_to_Process(data, Reader_Index);
            QFuture<void> future_LVDT_Process = QtConcurrent::run([=]() {
                // Code in this block will run in another thread
                emit Send_LVDT_Data_to_Process(data, Reader_Index);
            });
            break;
        }
        case TORQUE_SENSORS:
        {
//            emit Send_Torque_Data_to_Process(data,Reader_Index);
            QFuture<void> future_Torque_Process = QtConcurrent::run([=]() {
                // Code in this block will run in another thread
                emit Send_Torque_Data_to_Process(data,Reader_Index);
            });
            break;
        }
    }
}


QByteArray Serial_Service::Update_Send_Data(int Type_Index, int ID)
{
    static char HCA726S_Data[] = {
        0x68,0x04,0x00,0x04,0x08
    };

    static const char LVDT_Data[] = {
        0x01,0x04,0x00,0x04,0x00,0x02,0x30,0x0A
    };

    static const unsigned char TORQUE_Data[] = {
        0xAA,0xAA,0xAA,0x02,0xB1,0x00,0x00
    };

    QByteArray Send_Data;
    switch (Type_Index) {
        case HCA726S:{
            // The third bit is the address bit, and different corresponding commands need to be set according to different IDs
            Send_Data = QByteArray::fromRawData(HCA726S_Data, sizeof(HCA726S_Data));
            Send_Data[2] = static_cast <char>(ID);
            Send_Data[4] = Send_Data[1]+Send_Data[2]+Send_Data[3];
            break;
        }
        case LVDT_SENSORS:
        {
            // The first bit is the address bit, and different corresponding commands need to be set according to different IDs
            Send_Data = QByteArray::fromRawData(LVDT_Data, sizeof(LVDT_Data));
            Send_Data[0] = static_cast<char>(ID);
            break;
        }
        case TORQUE_SENSORS:
        {
            // The fourth bit is the address bit, and different corresponding commands need to be set according to different IDs
            Send_Data = QByteArray((const char*)TORQUE_Data, sizeof(TORQUE_Data));
            Send_Data[3] = static_cast<char>(ID);
            // XOR check calculation is required
            Send_Data.append(XORcheckSum(Send_Data));
        }
    }
    return Send_Data;
}

void Serial_Service::SetRequest(int Reader_Index, int Type_Index, int ID)
{
    // get the command and append it to the mapping list
    QByteArray request = Update_Send_Data(Type_Index, ID);

    m_writeData.insert(Reader_Index,request);

    check_Send = true;

    // If the thread is locked, unlock
    if(is_locking == true)
    {
        m_lock.unlock();
        is_locking = false;
    }
    qDebug()<<"m_write_length:"<<m_writeData.size();
}

void Serial_Service::RemoveRequest(int Reader_Index)
{
    m_writeData.remove(Reader_Index);
}

bool Serial_Service::Listen_Loop()
{
    return is_dataComplete;
}

void Serial_Service::PauseRead()
{
    qDebug()<<"pause";
    // Pause the thread
    is_locking = true;
    m_lock.lock();
    m_writeData.clear();
}

void Serial_Service::Set_All_Record(bool temp)
{
    m_all_record = temp;
}

void Serial_Service::SetReadInterval(unsigned long Interval_value)
{
    Interval = Interval_value;
}

// XOR check calculation
char Serial_Service::XORcheckSum(const QByteArray &data)
{
   char sum = 0x00;
   for (char c : data) {
       sum ^= c;
   }
   return sum;
}

void Serial_Service::ClosePort()
{
    port->clear();
    port->close();
    port->deleteLater();
}
