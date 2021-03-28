#include "process_data.h"

Process_Data::Process_Data(QObject *parent) : QObject(parent)
{
    port = new Serial_Service();

    memset(Reader_createFile,0,sizeof(Reader_createFile));

    CreateFile_AllRecord = false;

    memset(SetZero,false,sizeof (SetZero));
}

Process_Data::~Process_Data()
{
    file->close();
    file->deleteLater();
    for(int i=0;i<MAX_NUMBER_SENSORS;i++)
    {
        All_file[i]->close();
        All_file[i]->deleteLater();
    }
}

void Process_Data::Process_HCA_Data(QByteArray Data, int Reader_Index)
{
    if(Data.length() == 16)
    {
        QString Str_Data = QString(Data.toHex());
        // X 轴
        QString xAxis = Str_Data.mid(9,7);
        // Y 轴
        QString yAxis = Str_Data.mid(17,7);

        xAxis = xAxis.insert(3,'.');
        yAxis = yAxis.insert(3,'.');

        double x = xAxis.toDouble();
        double y = yAxis.toDouble();

        /* According to the communication protocol, the high bit of the first byte is the sign bit,
         * 0 is positive and 1 is negative. The low bit of the first byte and all the bits of the
         * second byte constitute an integer value, and the remaining two bytes represent the
         * decimal value.
        */
        if(Str_Data.mid(8,1) == "1")
        {
            x = x*-1;
        }
        if(Str_Data.mid(16,1) == "1")
        {
            y = y*-1;
        }

        // Determine whether the value needs to be set to 0
        if(port->Reader_List[Reader_Index-1].setZero)
        {
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(0.0);
            port->Reader_List[Reader_Index-1].data.append(0.0);
            port->Reader_List[Reader_Index-1].setZero = false;
        }
        else
        {
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(x);
            port->Reader_List[Reader_Index-1].data.append(y);
        }
    }
    // if the data is an invalid value or empty
    else
    {
        port->Reader_List[Reader_Index-1].data.clear();
        port->Reader_List[Reader_Index-1].data.append(255);
        port->Reader_List[Reader_Index-1].data.append(255);
    }
    // update the data to display
    emit Update_Displayed_Data(Reader_Index);

    // save data as a file or not?
    if(port->Reader_List[Reader_Index-1].isRecord)
    {
        emit send_to_save_file(Reader_Index);
    }
}

void Process_Data::Process_LVDT_Data(QByteArray Data, int Reader_Index)
{
    bool ok;

    if(Data.length() == 9)
    {
        QString Str_Data = QString(Data.toHex());

        // Integer part:
        int integer_part = Str_Data.mid(7,3).toInt(&ok,16);

        // decimal part:
        int decimal_part = Str_Data.mid(10,4).toInt(&ok,16);

        // Spliced into String and then converted to double
        QString temp_value = tr("%1.%2").arg(integer_part).arg(decimal_part);

        if(port->Reader_List[Reader_Index-1].setZero)
        {
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(0.0);
            port->Reader_List[Reader_Index-1].setZero = false;
        }
        else
        {
            //Displacement_value
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(temp_value.toDouble());
        }
    }
    // if the data is an invalid value or empty
    else
    {
        port->Reader_List[Reader_Index-1].data.clear();
        port->Reader_List[Reader_Index-1].data.append(255);
    }
    emit Update_Displayed_Data(Reader_Index);

    // save data as a file or not?
    if(port->Reader_List[Reader_Index-1].isRecord)
    {
        emit send_to_save_file(Reader_Index);
    }
}

void Process_Data::Process_Torque_Data(QByteArray Data, int Reader_Index)
{
    bool ok;

    QList<double> result;

    if(Data.length() == 10)
    {
        QByteArray value = Data.mid(5,2);

        QString Str_value = QString(value.toHex());

        // Decimal_point_position
        int Dpp = QString(Data.mid(7,1).toHex()).toInt(&ok,16);

        // uint of data
        int uint = QString(Data.mid(8,1).toHex()).toInt(&ok,16);

        double T_value = Str_value.toInt(&ok,16)*qPow(0.1,Dpp);

        // Take Mpa as the unit
        if(uint!=2)
        {
            T_value = T_value/10;
        }
        if(SetZero[Reader_Index-1])
        {
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(0.0);
            port->Reader_List[Reader_Index-1].setZero = false;
        }
        else
        {
            port->Reader_List[Reader_Index-1].data.clear();
            port->Reader_List[Reader_Index-1].data.append(T_value);
        }
    }
    // if the data is an invalid value or empty
    else
    {
        port->Reader_List[Reader_Index-1].data.clear();
        port->Reader_List[Reader_Index-1].data.append(255);
    }
    emit Update_Displayed_Data(Reader_Index);

    // save data as a file or not?
    if(port->Reader_List[Reader_Index-1].isRecord)
    {
        emit send_to_save_file(Reader_Index);
    }
}

//Save the data of Reader to a file separately
void Process_Data::SaveSingleFile(int Reader_Index)
{
    readerOutput[Reader_Index-1] = QString(QDateTime::currentDateTime().toString("hh:mm:ss.zzz")).leftJustified(30,' ');

    if(Reader_createFile[Reader_Index-1])
    {
        // The title bar of the file
        QString readerTitles = "Time (h.m.s.ms)";

        // Set the corresponding title according to the sensor type and ID
        if(port->Reader_List[Reader_Index-1].Type == HCA726S)
        {
            // the content of title
            QString HCA726_xAxis_title = tr("ID:%1 R%2 (X)").arg(port->Reader_List[Reader_Index-1].ID).arg(Reader_Index);
            QString HCA726_yAxis_title = tr("ID:%1 R%2 (Y)").arg(port->Reader_List[Reader_Index-1].ID).arg(Reader_Index);

            // Set each title to occupy 30 characters, if not enough, use spaces to fill in
            HCA726_xAxis_title = HCA726_xAxis_title.leftJustified(30,' ');
            HCA726_yAxis_title = HCA726_yAxis_title.leftJustified(30,' ');

            readerTitles.append(HCA726_xAxis_title);
            readerTitles.append(HCA726_yAxis_title);
        }
        else if(port->Reader_List[Reader_Index-1].Type == LVDT_SENSORS)
        {
            // the content of title
            QString LVDT_title = tr("R%1 D (cm)").arg(Reader_Index);

            // Set each title to occupy 30 characters, if not enough, use spaces to fill in
            LVDT_title = LVDT_title.leftJustified(30,' ');

            readerTitles.append(LVDT_title);
        }
        else if(port->Reader_List[Reader_Index-1].Type == TORQUE_SENSORS)
        {
            // the content of title
            QString Torque_title = tr("R%1 T (N'm),").arg(Reader_Index).toUtf8();

            // Set each title to occupy 30 characters, if not enough, use spaces to fill in
            Torque_title = Torque_title.leftJustified(30,' ');

            readerTitles.append(Torque_title);
        }

        All_file[Reader_Index-1] = new QFile;

        // Set the file name (including absolute path)
        All_file[Reader_Index-1]->setFileName(QString(port->Reader_List[Reader_Index-1].saveDirectory+"/"+port->Reader_List[Reader_Index-1].fileName+".txt"));

        // Determine whether the file exists
        if(!All_file[Reader_Index-1]->exists(QString(port->Reader_List[Reader_Index-1].saveDirectory+"/"+port->Reader_List[Reader_Index-1].fileName+".txt")))
        {
            // The file cannot be opened and created. The open() function contains the operation of creating a new file
            if(!All_file[Reader_Index-1]->open(QIODevice::QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug()<<"Error creating file! Choose another name!";
                return;
            }
            else
            {
                // Write title content to the file
                All_file[Reader_Index-1]->write(QString("%1 No Reader%2,  \n\n").arg(port->Reader_List[Reader_Index-1].fileName).arg(Reader_Index).toUtf8());
                All_file[Reader_Index-1]->write(QString(readerTitles+"\n").toUtf8());
                All_file[Reader_Index-1]->flush();

                // No more need to create files again
                Reader_createFile[Reader_Index-1] = false;
            }
        }
    }
    if(port->Reader_List[Reader_Index-1].Type == HCA726S && port->Reader_List[Reader_Index-1].data.length() == 2)
    {
        // Write the data to the file. Set each content to occupy 30 characters, if not enough, use spaces to fill in.
        readerOutput[Reader_Index-1].append(tr("%1").arg(QString::number(port->Reader_List[Reader_Index-1].data[0])).leftJustified(30,' '));
        readerOutput[Reader_Index-1].append(tr("%1").arg(QString::number(port->Reader_List[Reader_Index-1].data[1])).leftJustified(30,' '));
    }
    else if(port->Reader_List[Reader_Index-1].Type == LVDT_SENSORS && port->Reader_List[Reader_Index-1].data.length() == 1)
    {
        // Write the data to the file. Set each content to occupy 30 characters, if not enough, use spaces to fill in.
        readerOutput[Reader_Index-1].append(tr("%1").arg(port->Reader_List[Reader_Index-1].data[0]).leftJustified(30,' '));
    }
    else if(port->Reader_List[Reader_Index-1].Type == TORQUE_SENSORS && port->Reader_List[Reader_Index-1].data.length() == 1)
    {
        // Write the data to the file. Set each content to occupy 30 characters, if not enough, use spaces to fill in.
        readerOutput[Reader_Index-1].append(tr("%1").arg(port->Reader_List[Reader_Index-1].data[0]).leftJustified(30,' '));
    }
    All_file[Reader_Index-1]->write(QString(readerOutput[Reader_Index-1]+"\n").toUtf8());
    All_file[Reader_Index-1]->flush();
}

void Process_Data::Append_All_Data_To_File()
{
    QString All_Reader_Output = QString(QDateTime::currentDateTime().toString("hh:mm:ss.zzz").leftJustified(30,' '));

    if(CreateFile_AllRecord)
    {
        QString readerTitles = "Time (h.m.s.ms), ";

        readerTitles = readerTitles.leftJustified(30,' ');

         // Create the title in the txt file
        for(int i=0;i<MAX_NUMBER_SENSORS;i++)
        {
            if(port->Reader_List[i].isReading)
            {
                if(port->Reader_List[i].Type == HCA726S)
                {
                    // The content of title
                    QString HCA726_xAxis_title = tr("ID:%1 R%2 (X)").arg(port->Reader_List[i].ID).arg(i+1);
                    QString HCA726_yAxis_title = tr("ID:%1 R%2 (Y)").arg(port->Reader_List[i].ID).arg(i+1);

                    // Set the title to occupy 30 characters, if not enough, use spaces to fill in.
                    HCA726_xAxis_title = HCA726_xAxis_title.leftJustified(30,' ');
                    HCA726_yAxis_title = HCA726_yAxis_title.leftJustified(30,' ');

                    readerTitles.append(HCA726_xAxis_title);
                    readerTitles.append(HCA726_yAxis_title);
                }
                else if(port->Reader_List[i].Type == LVDT_SENSORS)
                {
                    // The content of title
                    QString LVDT_title = tr("R%1 D (cm)").arg(i+1);

                    // Set the title to occupy 30 characters, if not enough, use spaces to fill in.
                    LVDT_title = LVDT_title.leftJustified(30,' ');

                    readerTitles.append(LVDT_title);
                }
                else if(port->Reader_List[i].Type == TORQUE_SENSORS)
                {
                    // The content of title
                    QString Torque_title = tr("R%1 T (N·m),").arg(i+1);

                    // Set the title to occupy 30 characters, if not enough, use spaces to fill in.
                    Torque_title = Torque_title.leftJustified(30,' ');

                    readerTitles.append(Torque_title);
                }
            }
        }

        file = new QFile;

        // Set the file name (including absolute path)
        file->setFileName(QString(m_saveDirection_All+"/"+m_FileName_All+".txt"));

        // Determine whether the file exists
        if(!file->exists())
        {
            // The file cannot be opened and created. The open() function contains the operation of creating a new file
            if(!file->open(QIODevice::QIODevice::WriteOnly | QIODevice::Text))
            {
                qDebug()<<"Error creating file! Choose another name!";
                return;
            }
            else
            {
                // Write title content to the file
                file->write(QString("%1 No ,  \n\n").arg(m_FileName_All).toUtf8());
                file->write(QString(readerTitles+"\n").toUtf8());
                file->flush();
                CreateFile_AllRecord = false;
            }
        }
    }

    // Write the data to the file. Set each content to occupy 30 characters, if not enough, use spaces to fill in.
    for(int i=0;i<MAX_NUMBER_SENSORS;i++)
    {
        if(port->Reader_List[i].isReading)
        {
            if(port->Reader_List[i].Type == HCA726S)
            {
                double x_value = port->Reader_List[i].data[0];
                double y_value = port->Reader_List[i].data[1];
                All_Reader_Output.append(tr("%1").arg(QString::number(x_value)).leftJustified(30,' '));
                All_Reader_Output.append(tr("%1").arg(QString::number(y_value)).leftJustified(30,' '));
            }
            else if(port->Reader_List[i].Type == LVDT_SENSORS)
            {
                double D_value = port->Reader_List[i].data[0];
                All_Reader_Output.append(tr("%1").arg(D_value).leftJustified(30,' '));
            }
            else if(port->Reader_List[i].Type == TORQUE_SENSORS)
            {
                double T_value = port->Reader_List[i].data[0];
                All_Reader_Output.append(tr("%1").arg(T_value).leftJustified(30,' '));
            }
        }
    }
    file->write(QString(All_Reader_Output+"\n").toUtf8());
    file->flush();
}

void Process_Data::DataSetZero(int Reader_Index)
{
    port->Reader_List[Reader_Index-1].setZero = true;
}

void Process_Data::setCreateFile(int Reader_Index)
{
    Reader_createFile[Reader_Index-1] = true;
}

void Process_Data::setCreateFile_AllRecord(QString saveDirection, QString fileName)
{
    CreateFile_AllRecord = true;
    m_FileName_All = fileName;
    m_saveDirection_All = saveDirection;
}

void Process_Data::closeSingleFile(int Reader_Index)
{
//    file->close();
    All_file[Reader_Index-1]->close();
}
void Process_Data::closeFile_AllRecord()
{
    file->close();
}
