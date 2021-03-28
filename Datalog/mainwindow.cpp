#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Search the serial port
    FindPortName();

    m_process_data = new Process_Data();

    port = new Serial_Service;

    m_portThread = new QThread;

    Init_interface();

    // The number of Readers in the current interface
    current_Datalog_index = 4;

    m_saveDirectory = QDir::currentPath();

    fileNameIndex = 0;

    recordAllData = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    m_portThread->quit();
    m_portThread->wait();
    delete m_portThread;
}

void MainWindow::Init_interface()
{
    // Add all Reader components to the component structure array, and then use the loop to initialize

    // CheckBox Enable

    Component_List[0].CheckBox_Enable = ui->checkBox_Reader1_Enable;
    Component_List[1].CheckBox_Enable = ui->checkBox_Reader2_Enable;
    Component_List[2].CheckBox_Enable = ui->checkBox_Reader3_Enable;
    Component_List[3].CheckBox_Enable = ui->checkBox_Reader4_Enable;

    // ComboBox Type

    Component_List[0].ComboBox_types = ui->comboBox_Reader1_DeviceType;
    Component_List[1].ComboBox_types = ui->comboBox_Reader2_DeviceType;
    Component_List[2].ComboBox_types = ui->comboBox_Reader3_DeviceType;
    Component_List[3].ComboBox_types = ui->comboBox_Reader4_DeviceType;

    // ComboBox ID

    Component_List[0].ComboBox_id = ui->comboBox_Reader1_DeviceID;
    Component_List[1].ComboBox_id = ui->comboBox_Reader2_DeviceID;
    Component_List[2].ComboBox_id = ui->comboBox_Reader3_DeviceID;
    Component_List[3].ComboBox_id = ui->comboBox_Reader4_DeviceID;

    // Read Button

    Component_List[0].Button_Read = ui->pushButton_Reader1_isRead;
    Component_List[1].Button_Read = ui->pushButton_Reader2_isRead;
    Component_List[2].Button_Read = ui->pushButton_Reader3_isRead;
    Component_List[3].Button_Read = ui->pushButton_Reader4_isRead;

    // Record Button

    Component_List[0].Button_Records = ui->pushButton_Reader1_isRecord;
    Component_List[1].Button_Records = ui->pushButton_Reader2_isRecord;
    Component_List[2].Button_Records = ui->pushButton_Reader3_isRecord;
    Component_List[3].Button_Records = ui->pushButton_Reader4_isRecord;

    // Zero Button

    Component_List[0].Button_Zero = ui->pushButton_Reader1_Zero;
    Component_List[1].Button_Zero = ui->pushButton_Reader2_Zero;
    Component_List[2].Button_Zero = ui->pushButton_Reader3_Zero;
    Component_List[3].Button_Zero = ui->pushButton_Reader4_Zero;

    // Data Display

    Component_List[0].Display_line = ui->lineEdit_Reader1;
    Component_List[1].Display_line = ui->lineEdit_Reader2;
    Component_List[2].Display_line = ui->lineEdit_Reader3;
    Component_List[3].Display_line = ui->lineEdit_Reader4;

    // Init Reader component
    for(uint i=0;i<4;i++)
    {
        Component_List[i].CheckBox_Enable->setEnabled(true);
        connect(Component_List[i].CheckBox_Enable,SIGNAL(clicked(bool)),this,SLOT(CheckBoxs_Enable_Click()));

        Component_List[i].ComboBox_types->setEnabled(false);
        Component_List[i].ComboBox_id->setEnabled(false);

        Component_List[i].Button_Records->setEnabled(false);
        connect(Component_List[i].Button_Records,SIGNAL(clicked(bool)),this,SLOT(Btn_Record_Click()));

        Component_List[i].Button_Read->setEnabled(false);
        connect(Component_List[i].Button_Read,SIGNAL(clicked(bool)),this,SLOT(Btn_Read_Click()));

        Component_List[i].Button_Zero->setEnabled(false);
        connect(Component_List[i].Button_Read,SIGNAL(clicked(bool)),this,SLOT(Btn_Zero_Click()));

        // The data column is only used for display, not for input
        Component_List[i].Display_line->setReadOnly(true);
    }


    // Initial settings of the remaining buttons
    ui->pushButton_SerialPort->setEnabled(true);
    ui->pushButton_Add_GroupBox->setEnabled(true);
    ui->pushButton_Browse->setEnabled(true);
    ui->pushButton_All_Read->setEnabled(false);
    ui->pushButton_All_Record->setEnabled(false);
    ui->pushButton_set_timer->setEnabled(false);
    ui->timerIntervalsTextBox->setEnabled(false);

    // Init Reader List
    for(int i=0;i<MAX_NUMBER_SENSORS;i++)
    {
        port->Reader_List[i].ID = 255;
        port->Reader_List[i].Type = 255;
        port->Reader_List[i].isRecord = false;
        port->Reader_List[i].isReading = false;
        port->Reader_List[i].setZero = false;
        port->Reader_List[i].fileName = "";
        port->Reader_List[i].saveDirectory = QDir::currentPath();
    }


    /*
     * connect() is an alternative to the callback technique: We use signals and slots. A signal is emitted when a particular event occurs.
     * We use this function to realize the response of the interface and the function calls between different classes
    */

    // Connect the click event of the open_port button and its response.
    connect(ui->pushButton_SerialPort, SIGNAL(clicked(bool)), this, SLOT(btn_Open_Port_Click()),Qt::UniqueConnection);

    // Connect the click event of the browse button and its response.
    connect(ui->pushButton_Browse,SIGNAL(clicked(bool)),this,SLOT(Btn_Browse_Click()),Qt::UniqueConnection);

    // Connect the click event of the all_read button and its response.
    connect(ui->pushButton_All_Read,SIGNAL(clicked(bool)),this,SLOT(Btn_All_Read_Click()),Qt::UniqueConnection);

    // Connect the click event of the all_record button and its response.
    connect(ui->pushButton_All_Record,SIGNAL(clicked(bool)),this,SLOT(Btn_All_Record_Click()),Qt::UniqueConnection);

    // Connect the click event of the add_more button and its response.
    connect(ui->pushButton_Add_GroupBox, SIGNAL(clicked(bool)), this, SLOT(Btn_Add_DatalogBox_Click()),Qt::UniqueConnection);

    // Connect the click event of the set_timer button and its response.
    connect(ui->pushButton_set_timer, SIGNAL(clicked(bool)), this, SLOT(Btn_SetTimer_Click()),Qt::UniqueConnection);

    // Connect the click event of the checkBox_Timer_Enable checkBox and its response.
    connect(ui->checkBox_Timer_Enable, SIGNAL(clicked(bool)), this, SLOT(TimerEnable_CheckChanged()),Qt::UniqueConnection);

    // Connect the click event of the rest button and its response.
    connect(ui->pushButton_Rest,SIGNAL(clicked(bool)),this,SLOT(Btn_Rest_Click()),Qt::UniqueConnection);

    // Connect the signal and the data processing
    connect(port, SIGNAL(Send_HCA_Data_to_Process(QByteArray,int)), m_process_data, SLOT(Process_HCA_Data(QByteArray,int)));
    connect(port, SIGNAL(Send_LVDT_Data_to_Process(QByteArray,int)), m_process_data, SLOT(Process_LVDT_Data(QByteArray,int)));
    connect(port, SIGNAL(Send_Torque_Data_to_Process(QByteArray,int)), m_process_data, SLOT(Process_Torque_Data(QByteArray,int)));

    // Connect the invalid data signal and its processing
    connect(port,SIGNAL(Send_to_Invalid_Reading(int)),this,SLOT(Handle_Invalid_Sending(int)));

    connect(port,SIGNAL(Send_to_Record_All_Data()),m_process_data,SLOT(Append_All_Data_To_File()));

    // Connecting the signal to the operation displayed in the LineEdit box of the Reader when the data process is finished
    connect(m_process_data,SIGNAL(Update_Displayed_Data(int)),this,SLOT(showData(int)));

    // Connecting the signal to the operation saved data as the file
    connect(m_process_data,SIGNAL(send_to_save_file(int)),m_process_data,SLOT(SaveSingleFile(int)));

    // Start Thread to send and receive
    connect(this,&MainWindow::start_portThread,port,&Serial_Service::loopSend);
    port->moveToThread(m_portThread);
    m_portThread->start();
}

void MainWindow::btn_Open_Port_Click(void)
{
    bool Button_Open_Serial = (ui->pushButton_SerialPort->text()==tr("Open Port"));
    int current_index = ui->comboBox_PortName->currentIndex();

    if(Button_Open_Serial)
    {
        if(current_index > 0)
        {
            port->Init(ui->comboBox_PortName->currentText(),9600);
            isOpen = port->Open_Port();

            // Open fail
            if(!isOpen)
            {
                QString dlgTitle=QString("Remind");
                QString strInfo=QString("Failed to open the port, please check if the port is occupied");
                if(show_Message_Box(dlgTitle,strInfo) == true)
                {
                     return;
                }
            }
            // Successfully opened
            else
            {
                ui->pushButton_SerialPort->setText(tr("Close Port"));
                ui->pushButton_All_Read->setEnabled(true);
                ui->pushButton_All_Record->setEnabled(true);
            }
        }
        else{
            // search the port name
            FindPortName();

            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Please select a port");

            if(show_Message_Box(dlgTitle,strInfo) == true)
            {
                return;
            }
        }
    }
    else
    {
        // Close the port, clear the data, initialize state
        ui->pushButton_SerialPort->setText(tr("Open Port"));
        ui->pushButton_All_Read->setEnabled(false);
        ui->pushButton_All_Record->setEnabled(false);

        for(int i=0;i<current_Datalog_index;i++)
        {
            if(port->Reader_List[i].isRecord)
            {
                m_process_data->closeSingleFile(i+1);
                Component_List[i].Button_Records->setText("Record");
                m_process_data->closeSingleFile(i);
                port->Reader_List[i].isRecord = false;
            }
            if(port->Reader_List[i].isReading)
            {
                Component_List[i].Button_Read->setText("Read");
                port->RemoveRequest(i+1);
                port->Reader_List[i].isReading = false;
            }
        }
        port->PauseRead();
        ui->pushButton_All_Read->setText("All Read");
        if(recordAllData)
        {
            recordAllData = false;
            ui->pushButton_All_Record->setText("All Record");
            port->Set_All_Record(false);
            m_process_data->closeFile_AllRecord();
        }
        port->ClosePort();
    }
}

void MainWindow::FindPortName()
{
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        // Automatically read the serial port number and add it to the ComboBox
        QSerialPort m_serial;
        m_serial.setPort(info);
        if(m_serial.open(QIODevice::ReadWrite))
        {
           ui->comboBox_PortName->addItem(info.portName());
           m_serial.close();
        }
    }
}

void MainWindow::CheckBoxs_Enable_Click()
{
    // Get the current index of Reader from the Enable CheckBox clicked
    int CheckBox_Index = 0;

    QCheckBox* cbox = qobject_cast<QCheckBox*>(sender());

    CheckBox_Index = Get_Reader_Index(cbox->objectName());

    // If Enable is not checked, the Read button, Type, ID, Record, Zero cannot respond
    if(Component_List[CheckBox_Index-1].CheckBox_Enable->isChecked())
    {
        Component_List[CheckBox_Index-1].Button_Read->setEnabled(true);
        Component_List[CheckBox_Index-1].ComboBox_types->setEnabled(true);
        Component_List[CheckBox_Index-1].ComboBox_id->setEnabled(true);
        Component_List[CheckBox_Index-1].Button_Records->setEnabled(true);
        Component_List[CheckBox_Index-1].Button_Zero->setEnabled(true);
    }else
    {
        Component_List[CheckBox_Index-1].Button_Read->setEnabled(false);
        Component_List[CheckBox_Index-1].ComboBox_types->setEnabled(false);
        Component_List[CheckBox_Index-1].ComboBox_id->setEnabled(false);
        Component_List[CheckBox_Index-1].Button_Records->setEnabled(false);
        Component_List[CheckBox_Index-1].Button_Zero->setEnabled(false);
        Component_List[CheckBox_Index-1].Display_line->clear();
    }
}

void MainWindow::Btn_Read_Click()
{
    // Get the current index of Reader from the Read button clicked
    int Button_Index = 0;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    Button_Index = Get_Reader_Index(btn->objectName());

    // First check if the port is open
    if(!isOpen)
    {
        QString dlgTitle=QString("Remind");
        QString strInfo=QString("Please select a port and open it");

        if(show_Message_Box(dlgTitle,strInfo) == true)
        {
            return;
        }
    }

    int Type_Index = Component_List[Button_Index-1].ComboBox_types->currentIndex();
    QString ID = Component_List[Button_Index-1].ComboBox_id->currentText();

    // if the Read button is clicked
    if(Component_List[Button_Index-1].Button_Read->text() == tr("Read"))
    {
        if(Type_Index != 0 && ID != "")
        {
            // The text of button changed from "Read" to "Stop"
            Component_List[Button_Index-1].Button_Read->setText("Stop");

            port->Reader_List[Button_Index-1].ID = ID.toInt();
            port->Reader_List[Button_Index-1].Type = Type_Index;
            port->Reader_List[Button_Index-1].isReading = true;

            // Add sent request
            port->SetRequest(Button_Index,Type_Index,ID.toInt());
        }
        // If the ID and type of sensor is not selected
        else if(Type_Index == 0 && ID == "")
        {
            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Please select sensor type and ID");

            if(show_Message_Box(dlgTitle,strInfo) == true)
            {
                return;
            }
        }
        // If the sensor type is not selected
        else if(Type_Index == 0 && ID !="")
        {
            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Please select sensor type");

            if(show_Message_Box(dlgTitle,strInfo))
            {
                return;
            }
        }
        // If the sensor ID is not selected
        else if(Type_Index !=0 && ID =="")
        {
            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Please select sensor ID");

            if(show_Message_Box(dlgTitle,strInfo))
            {
                return;
            }
        }
    }
    // Stop Reading
    else
    {
        // The text of button changed from "Stop" to "Read"
        Component_List[Button_Index-1].Button_Read->setText("Read");
        port->Reader_List[Button_Index-1].isReading = false;
        // Remove the send request of the Reader
        port->RemoveRequest(Button_Index);
    }
}

void MainWindow::Btn_Record_Click()
{
    // Get the current index of Reader from the Record button clicked
    int Record_Index = 0;
    QPushButton* btn = qobject_cast<QPushButton*>(sender());
    Record_Index = Get_Reader_Index(btn->objectName());

    port->Reader_List[Record_Index-1].saveDirectory = m_saveDirectory;

    if(Component_List[Record_Index-1].Button_Records->text()==tr("Record"))
    {
        // get the file name, according to the LineEdit
        port->Reader_List[Record_Index-1].fileName = QString(ui->lineEdit_File_Name->text() +"_Reader%1_Record").arg(Record_Index);

        // Avoid duplication of file names by adding fileNameIndex to the file name suffix
        while(QFile::exists(QString(port->Reader_List[Record_Index-1].saveDirectory + "/" + port->Reader_List[Record_Index-1].fileName + ".txt")))
        {
            fileNameIndex++;
            port->Reader_List[Record_Index-1].fileName = QString(ui->lineEdit_File_Name->text() +"_Reader%1_Record"+QString::number(fileNameIndex)).arg(Record_Index);
        }
        fileNameIndex = 0;

        // need to creative the file
        m_process_data->setCreateFile(Record_Index);
        port->Reader_List[Record_Index-1].isRecord = true;

        // The text of button changed from "All Record" to "Stop Record"
        Component_List[Record_Index-1].Button_Records->setText("Stop Record");
    }
    else
    {
        // The text of button changed from "Stop Record" to "All Record"
        Component_List[Record_Index-1].Button_Records->setText("Record");
        m_process_data->closeSingleFile(Record_Index);
        port->Reader_List[Record_Index-1].isRecord = false;
    }
}

void MainWindow::Btn_All_Read_Click()
{
    // Used to determine whether there is at least one Reader that has been configured with parameters(ID and Type)
    bool temp = false;

    // Click on the button of All Read
    if(ui->pushButton_All_Read->text() == tr("All Read"))
    {
        // Traverse the current list of all Readers
        for(int i=0;i<current_Datalog_index;i++)
        {
            // Get the state of Enable, ID, and Type
            bool is_Enable = Component_List[i].CheckBox_Enable->isChecked();
            int Type_Index = Component_List[i].ComboBox_types->currentIndex();
            QString ID = Component_List[i].ComboBox_id->currentText();

            // When Enable is selected, Type and ID are selected, and the button of Reader1 is not pressed
            if(is_Enable == true && Type_Index != 0 && ID != "")
            {
                /*
                 * Record that the Reader is in the state of being read.
                 * When it is used to record data, it can know which Readers are reading data.
                 */
                port->Reader_List[i].isReading = true;
                port->Reader_List[i].ID = ID.toInt();
                port->Reader_List[i].Type = Type_Index;
                qDebug()<<"reader_List:"<<port->Reader_List[i].Type;

                // There is at least one Reader that has been configured with parameters(ID and Type)
                temp = true;

                // If the current Reader has not started to read data
                if(Component_List[i].Button_Read->text() == tr("Read"))
                {
                    Component_List[i].Button_Read->setText("Stop");

                    port->SetRequest(i+1,Type_Index,ID.toInt());
                }
            }
            else
            {
                // Reader has not been enabled
                port->Reader_List[i].isReading = false;
                port->Reader_List[i].ID = 255;
                port->Reader_List[i].Type = 255;
            }
        }

        // No reader can read
        if(temp == false)
        {
            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Please set at least one Reader parameter");
            if(show_Message_Box(dlgTitle,strInfo) == true)
            {
                return;
            }
        }
        else
        {
            ui->pushButton_All_Read->setText("All Stop");
        }
    }
    // the button of "All Stop" is clicked
    else
    {
        ui->pushButton_All_Read->setText("All Read");
        for (int i=0;i<current_Datalog_index;i++) {
            // Update the Reader
            if(port->Reader_List[i].isReading)
            {
                Component_List[i].Button_Read->setText("Read");
                port->Reader_List[i].isReading = false;
            }
        }
        port->PauseRead();
    }
}

void MainWindow::Btn_Zero_Click(void)
{
    // Get the current index of Reader from the Zero button clicked
    int Btn_Zero_Index = 0;
    QPushButton* btn_zero = qobject_cast<QPushButton*>(sender());
    Btn_Zero_Index = Get_Reader_Index(btn_zero->objectName());

    // set the Reader's zero
    port->Reader_List[Btn_Zero_Index-1].setZero = true;
}

void MainWindow::Btn_Add_DatalogBox_Click(void)
{
    // the number of Reader increase
    current_Datalog_index++;
    if(current_Datalog_index>16){
        QString dlgTitle = QString("Remind");
        QString strInfo = QString("Could not add more Readers");
        show_Message_Box(dlgTitle,strInfo);
    }
    else
    {
        // creative the datalogBox for Reader
        Creative_DatalogBox();
    }
}

void MainWindow::Handle_Invalid_Sending(int Reader_Index)
{
    port->RemoveRequest(Reader_Index);
    port->Reader_List[Reader_Index-1].isReading = false;
    port->Reader_List[Reader_Index-1].isRecord = false;
    port->Reader_List[Reader_Index-1].Type = 255;
    port->Reader_List[Reader_Index-1].ID = 255;
    Component_List[Reader_Index-1].Button_Read->setText("Read");
    QString dlgTitle=QString("Invalid reading");
    QString strInfo=QString(tr("Please check if the ID and type of the Reader:%1 are correct").arg(Reader_Index));
    if(show_Message_Box(dlgTitle,strInfo) == true)
    {
        return;
    }
}

void MainWindow::Btn_SetTimer_Click()
{
    if(ui->pushButton_set_timer->text() == "Set Timer")
    {
        bool ok;
        ui->checkBox_Timer_Enable->setCheckState(Qt::Unchecked);
        ui->pushButton_set_timer->setEnabled(false);
        ui->timerIntervalsTextBox->setEnabled(false);
        unsigned long get_Interval = ui->timerIntervalsTextBox->text().toULong(&ok);

        // If the inpute is not a number
        if(!ok)
        {
            QString dlgTitle=QString("Remind");
            QString strInfo=QString("Unvalid character! Insert a Number!");

            bool result;
            result = show_Message_Box(dlgTitle,strInfo);
            if(result == true)
            {
                return;
            }
        }
        else
        {
            port->SetReadInterval(get_Interval);
        }
    }
}


void MainWindow::TimerEnable_CheckChanged()
{
    if(ui->checkBox_Timer_Enable->isChecked())
    {
//        recordAllData = false;
        ui->pushButton_set_timer->setEnabled(true);
        ui->timerIntervalsTextBox->setEnabled(true);
    }
    else
    {
        ui->pushButton_set_timer->setEnabled(false);
        ui->timerIntervalsTextBox->setEnabled(false);
    }
}


// Wait for the signal from Update_Displayed_Data(int Reader_Index) function to update the data
void MainWindow::showData(int Reader_Index)
{
    // According to the type of sensors, update the data
    if(port->Reader_List[Reader_Index-1].Type == HCA726S)
    {
        Component_List[Reader_Index-1].Display_line->setText(tr("x:%1, y:%2").arg(port->Reader_List[Reader_Index-1].data[0]).arg(port->Reader_List[Reader_Index-1].data[1]));
    }
    else
    {
        Component_List[Reader_Index-1].Display_line->setText(tr("%1").arg(port->Reader_List[Reader_Index-1].data[0]));
    }
}


void MainWindow::Btn_All_Record_Click()
{
    if(ui->pushButton_All_Record->text() == tr("All Record"))
    {
        m_fileName = QString(ui->lineEdit_File_Name->text() +"_AllReader_Record");
        // Calculate the file name of the saved file, and make the file name not conflict with other file names
        while(QFile::exists(QString(m_saveDirectory + "/" + m_fileName + ".txt")))
        {
            fileNameIndex++;
            m_fileName = QString(ui->lineEdit_File_Name->text() +"_AllReader_Record"+QString::number(fileNameIndex));
        }
        // reset the fileNameIndex
        fileNameIndex = 0;
        recordAllData = true;
        m_process_data->setCreateFile_AllRecord(m_saveDirectory,m_fileName);
        port->Set_All_Record(true);

        ui->pushButton_All_Record->setText("Stop All Record");
    }
    else
    {
        recordAllData = false;
        ui->pushButton_All_Record->setText("All Record");
        port->Set_All_Record(false);
        m_process_data->closeFile_AllRecord();
    }

}


void MainWindow::Btn_Browse_Click()
{
    QString current_path = QDir::currentPath();

    QString tempPath = QFileDialog::getExistingDirectory(this, QString("Save path"), current_path);

    if(!tempPath.isEmpty())
    {
        //update the save directory and show it
        m_saveDirectory = tempPath;
        ui->label_FilePath->setText(m_saveDirectory);
    }
    else
    {
        m_saveDirectory = current_path;
        return;
    }
}

void MainWindow::Btn_Rest_Click()
{
    //Restart the application
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::Creative_DatalogBox()
{
    QGroupBox* gridGroupBox = new QGroupBox(tr("Reader %1").arg(current_Datalog_index));

    QGridLayout *grid_layout = new QGridLayout;

    Component_List[current_Datalog_index-1].CheckBox_Enable = new QCheckBox("Enable");

    grid_layout->addWidget(Component_List[current_Datalog_index-1].CheckBox_Enable,0,0);

    /* Initialize the CheckBox of Enable
     * And connect the clicked event to the CheckBoxs_Enable_Click() function to facilitate subsequent calls and responses
    */
    connect(Component_List[current_Datalog_index-1].CheckBox_Enable,SIGNAL(clicked(bool)), this, SLOT(CheckBoxs_Enable_Click()));

    // Set name for CheckBox_type
    QString Name_CheckBox_Enable = tr("checkBox_Reader%1_Enable").arg(current_Datalog_index);

    Component_List[current_Datalog_index-1].CheckBox_Enable->setObjectName(Name_CheckBox_Enable);

    /* 0,1 Type
     * the GroupBox of Reader is based on the grid layout, which is rasterized matrix with 3 rows and 3 columns.
     * We initialize the components in the order of the rows
     * Now, it is 0 rows and 1 column
    */
    QHBoxLayout *Horizontal_Types_layout = new QHBoxLayout;

    QLabel* label_types = new QLabel("Types:");

    Component_List[current_Datalog_index-1].ComboBox_types = new QComboBox();

    QStringList Info_Sensors_Types = {"","HCA726S","LVDT Sensors","Torque Sensors"};

    //Add sensor type to the ComboBox
    for(int i=0;i<4;i++)
    {
        Component_List[current_Datalog_index-1].ComboBox_types->addItem(Info_Sensors_Types[i]);
    }

    Horizontal_Types_layout->addWidget(label_types, 0);

    Horizontal_Types_layout->addWidget(Component_List[current_Datalog_index-1].ComboBox_types,1);

    Horizontal_Types_layout->addStretch();

    grid_layout->addLayout(Horizontal_Types_layout,0,1);

    // Initialize the ComboBox of Type, which is not available initially, wait for Enable to be checked
    Component_List[current_Datalog_index-1].ComboBox_types->setEnabled(false);

    // Set name for ComboBoxs_type
    QString Name_comboBox_Type = tr("comboBox_Reader%1_DeviceType").arg(current_Datalog_index-1);

    Component_List[current_Datalog_index-1].ComboBox_types->setObjectName(Name_comboBox_Type);

    gridGroupBox->setLayout(grid_layout);


    /* 0,2 ID
     * Now, it is 0 rows and 2 column
    */
    QHBoxLayout *Horizontal_ID_layout = new QHBoxLayout;

    QLabel* label_ID = new QLabel("ID:");

    Component_List[current_Datalog_index-1].ComboBox_id = new QComboBox();

    QStringList Info_Sensors_ID = {"","0","1","2","3","4","5","6","7","8"};

    // Add the ID of Sensors
    for(int i=0;i<10;i++)
    {
        Component_List[current_Datalog_index-1].ComboBox_id->addItem(Info_Sensors_ID[i]);
    }

    Horizontal_ID_layout->addWidget(label_ID, 0);

    Horizontal_ID_layout->addWidget(Component_List[current_Datalog_index-1].ComboBox_id,1);

    Horizontal_ID_layout->addStretch();

    grid_layout->addLayout(Horizontal_ID_layout,0,2);

    // Initialize the ComboBox of ID, which is not available initially, wait for Enable to be checked
    Component_List[current_Datalog_index-1].ComboBox_id->setEnabled(false);

    // Set name for ComboBoxs_id
    QString Name_comboBox_ID = tr("comboBox_Reader%1_DeviceID").arg(current_Datalog_index);

    Component_List[current_Datalog_index-1].ComboBox_id->setObjectName(Name_comboBox_ID);

    gridGroupBox->setLayout(grid_layout);



    /* 1,0 Record
     * Now, it is 1 rows and 0 column
    */
    Component_List[current_Datalog_index-1].Button_Records = new QPushButton();

    Component_List[current_Datalog_index-1].Button_Records->setText("Record");

    // Initialize the Button of Record, which is not available initially, wait for Enable to be checked
    Component_List[current_Datalog_index-1].Button_Records->setEnabled(false);

    // Set name for Buttons_Records
    QString Name_btn_Record = tr("pushButton_Reader%1_isRecord").arg(current_Datalog_index);

    Component_List[current_Datalog_index-1].Button_Records->setObjectName(Name_btn_Record);

    // connect the clicked event to the Btn_Record_Click() function to facilitate subsequent calls and responses
    connect(Component_List[current_Datalog_index-1].Button_Records,SIGNAL(clicked(bool)),this,SLOT(Btn_Record_Click()));

    grid_layout->addWidget(Component_List[current_Datalog_index-1].Button_Records,1,0);



    /* 1,1 Read
     * Now, it is 1 rows and 1 column
    */
    Component_List[current_Datalog_index-1].Button_Read = new QPushButton();

    Component_List[current_Datalog_index-1].Button_Read->setText("Read");

    // Set name for buttons_read.
    // On this way, we can use the Get_Reader_Index(QString Components_Name) function to know
    QString Name_btn_read = tr("pushButton_Reader%1_isRead").arg(current_Datalog_index);

    Component_List[current_Datalog_index-1].Button_Read->setObjectName(Name_btn_read);

    /* Initialize the button of Read, which is not available initially, wait for Enable to be checked
     * And connect the control object to the control array of this class to facilitate subsequent calls and responses
    */
    Component_List[current_Datalog_index-1].Button_Read->setEnabled(false);

    connect(Component_List[current_Datalog_index-1].Button_Read,SIGNAL(clicked(bool)), this, SLOT(Btn_Read_Click()));

    grid_layout->addWidget(Component_List[current_Datalog_index-1].Button_Read,1,1);



    /* 1,2 Zero
     * Now, it is 1 rows and 1 column
    */
    Component_List[current_Datalog_index-1].Button_Zero = new QPushButton();

    Component_List[current_Datalog_index-1].Button_Zero->setText("Zero");

    // Initialize the button of Zero, which is not available initially, wait for Enable to be checked
    Component_List[current_Datalog_index-1].Button_Zero->setEnabled(false);

    // Set name for pushButton_Reader_Zero
    QString Name_btn_zero = tr("pushButton_Reader%1_Zero").arg(current_Datalog_index);

    Component_List[current_Datalog_index-1].Button_Zero->setObjectName(Name_btn_zero);

    connect(Component_List[current_Datalog_index-1].Button_Zero, SIGNAL(clicked(bool)), this, SLOT(Btn_Zero_Click()));

    grid_layout->addWidget(Component_List[current_Datalog_index-1].Button_Zero,1,2);

    /* 1,2 Line
    * Now, it is 3 rows
   */
    Component_List[current_Datalog_index-1].Display_line = new QLineEdit();

    Component_List[current_Datalog_index-1].Display_line->setReadOnly(true);

    Component_List[current_Datalog_index-1].Display_line->clear();

    grid_layout->addWidget(Component_List[current_Datalog_index-1].Display_line,2,0,2,3);

    port->Reader_List[current_Datalog_index-1].ID = 255;
    port->Reader_List[current_Datalog_index-1].Type = 255;
    port->Reader_List[current_Datalog_index-1].isRecord = false;
    port->Reader_List[current_Datalog_index-1].isReading = false;
    port->Reader_List[current_Datalog_index-1].setZero = false;
    port->Reader_List[current_Datalog_index-1].fileName = "";
    port->Reader_List[current_Datalog_index-1].saveDirectory = QDir::currentPath();


    if(current_Datalog_index == 5 || current_Datalog_index == 6)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,0,current_Datalog_index-3);
    }
    else if(current_Datalog_index == 7 || current_Datalog_index == 8)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,1,current_Datalog_index-5);
    }
    else if(current_Datalog_index == 9 || current_Datalog_index == 10)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,2, current_Datalog_index-9);
    }
    else if(current_Datalog_index == 11 || current_Datalog_index == 12)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,3,current_Datalog_index-11);
    }
    else if(current_Datalog_index == 13 || current_Datalog_index == 14)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,2, current_Datalog_index-11);
    }
    else if(current_Datalog_index == 15 || current_Datalog_index == 16)
    {
        ui->gridLayout_Reader->addWidget(gridGroupBox,3,current_Datalog_index-13);
    }
}


int MainWindow::Get_Reader_Index(QString Components_Name)
{
    QString Str_index;
    for(int j = 0; j < Components_Name.length(); j++)
    {
        if(Components_Name[j] > '0' && Components_Name[j] < '9')
        {
            Str_index.append(Components_Name[j]);
        }
    }
    return Str_index.toInt();
}

// A reminder window pops up
bool MainWindow::show_Message_Box(QString dlgTitle, QString strInfo)
{
    bool on_button_ok = false;
    QMessageBox::StandardButton result;
    result = QMessageBox::information(this,dlgTitle,strInfo,QMessageBox::Ok);

    if(result == QMessageBox::Ok)
    {
        on_button_ok = true;
    }
    return on_button_ok;
}
