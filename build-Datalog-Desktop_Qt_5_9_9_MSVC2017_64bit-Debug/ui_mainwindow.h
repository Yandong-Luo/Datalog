/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit_File_Name;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_Browse;
    QLabel *label_FilePath;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_timer;
    QPushButton *pushButton_set_timer;
    QLabel *label_9;
    QLineEdit *timerIntervalsTextBox;
    QCheckBox *checkBox_Timer_Enable;
    QGroupBox *groupBox_6;
    QGridLayout *gridLayout_11;
    QPushButton *pushButton_Rest;
    QComboBox *comboBox_PortName;
    QPushButton *pushButton_All_Record;
    QPushButton *pushButton_Add_GroupBox;
    QPushButton *pushButton_SerialPort;
    QPushButton *pushButton_All_Read;
    QGridLayout *gridLayout_Reader;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox_Reader1_DeviceType;
    QCheckBox *checkBox_Reader1_Enable;
    QPushButton *pushButton_Reader1_isRecord;
    QPushButton *pushButton_Reader1_isRead;
    QLineEdit *lineEdit_Reader1;
    QPushButton *pushButton_Reader1_Zero;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *comboBox_Reader1_DeviceID;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_5;
    QCheckBox *checkBox_Reader4_Enable;
    QPushButton *pushButton_Reader4_isRead;
    QPushButton *pushButton_Reader4_Zero;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QComboBox *comboBox_Reader4_DeviceType;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_6;
    QComboBox *comboBox_Reader4_DeviceID;
    QPushButton *pushButton_Reader4_isRecord;
    QLineEdit *lineEdit_Reader4;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_4;
    QPushButton *pushButton_Reader3_isRead;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *comboBox_Reader3_DeviceType;
    QPushButton *pushButton_Reader3_Zero;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_4;
    QComboBox *comboBox_Reader3_DeviceID;
    QPushButton *pushButton_Reader3_isRecord;
    QCheckBox *checkBox_Reader3_Enable;
    QLineEdit *lineEdit_Reader3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_8;
    QGridLayout *gridLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_7;
    QComboBox *comboBox_Reader2_DeviceType;
    QPushButton *pushButton_Reader2_isRecord;
    QLineEdit *lineEdit_Reader2;
    QPushButton *pushButton_Reader2_Zero;
    QCheckBox *checkBox_Reader2_Enable;
    QPushButton *pushButton_Reader2_isRead;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_8;
    QComboBox *comboBox_Reader2_DeviceID;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuwdaw;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(702, 469);
        MainWindow->setMaximumSize(QSize(1076, 640));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_7 = new QGridLayout(centralwidget);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        groupBox_7 = new QGroupBox(centralwidget);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        verticalLayout = new QVBoxLayout(groupBox_7);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit_File_Name = new QLineEdit(groupBox_7);
        lineEdit_File_Name->setObjectName(QStringLiteral("lineEdit_File_Name"));

        verticalLayout->addWidget(lineEdit_File_Name);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        pushButton_Browse = new QPushButton(groupBox_7);
        pushButton_Browse->setObjectName(QStringLiteral("pushButton_Browse"));

        horizontalLayout_9->addWidget(pushButton_Browse);

        label_FilePath = new QLabel(groupBox_7);
        label_FilePath->setObjectName(QStringLiteral("label_FilePath"));

        horizontalLayout_9->addWidget(label_FilePath);


        verticalLayout->addLayout(horizontalLayout_9);


        verticalLayout_2->addWidget(groupBox_7);

        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayout = new QGridLayout(groupBox_5);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout_timer = new QGridLayout();
        gridLayout_timer->setObjectName(QStringLiteral("gridLayout_timer"));
        pushButton_set_timer = new QPushButton(groupBox_5);
        pushButton_set_timer->setObjectName(QStringLiteral("pushButton_set_timer"));

        gridLayout_timer->addWidget(pushButton_set_timer, 1, 0, 1, 1);

        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_timer->addWidget(label_9, 0, 1, 1, 1);

        timerIntervalsTextBox = new QLineEdit(groupBox_5);
        timerIntervalsTextBox->setObjectName(QStringLiteral("timerIntervalsTextBox"));

        gridLayout_timer->addWidget(timerIntervalsTextBox, 1, 1, 1, 1);

        checkBox_Timer_Enable = new QCheckBox(groupBox_5);
        checkBox_Timer_Enable->setObjectName(QStringLiteral("checkBox_Timer_Enable"));

        gridLayout_timer->addWidget(checkBox_Timer_Enable, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_timer, 0, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox_5);


        gridLayout_7->addLayout(verticalLayout_2, 0, 0, 1, 1);

        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        gridLayout_11 = new QGridLayout(groupBox_6);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        pushButton_Rest = new QPushButton(groupBox_6);
        pushButton_Rest->setObjectName(QStringLiteral("pushButton_Rest"));

        gridLayout_11->addWidget(pushButton_Rest, 0, 2, 1, 1);

        comboBox_PortName = new QComboBox(groupBox_6);
        comboBox_PortName->setObjectName(QStringLiteral("comboBox_PortName"));
        comboBox_PortName->setMaximumSize(QSize(80, 20));
        comboBox_PortName->setMouseTracking(true);

        gridLayout_11->addWidget(comboBox_PortName, 0, 0, 1, 1);

        pushButton_All_Record = new QPushButton(groupBox_6);
        pushButton_All_Record->setObjectName(QStringLiteral("pushButton_All_Record"));

        gridLayout_11->addWidget(pushButton_All_Record, 1, 1, 1, 1);

        pushButton_Add_GroupBox = new QPushButton(groupBox_6);
        pushButton_Add_GroupBox->setObjectName(QStringLiteral("pushButton_Add_GroupBox"));

        gridLayout_11->addWidget(pushButton_Add_GroupBox, 1, 2, 1, 1);

        pushButton_SerialPort = new QPushButton(groupBox_6);
        pushButton_SerialPort->setObjectName(QStringLiteral("pushButton_SerialPort"));

        gridLayout_11->addWidget(pushButton_SerialPort, 0, 1, 1, 1);

        pushButton_All_Read = new QPushButton(groupBox_6);
        pushButton_All_Read->setObjectName(QStringLiteral("pushButton_All_Read"));

        gridLayout_11->addWidget(pushButton_All_Read, 1, 0, 1, 1);


        gridLayout_7->addWidget(groupBox_6, 0, 2, 1, 1);

        gridLayout_Reader = new QGridLayout();
        gridLayout_Reader->setObjectName(QStringLiteral("gridLayout_Reader"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox_Reader1_DeviceType = new QComboBox(groupBox);
        comboBox_Reader1_DeviceType->setObjectName(QStringLiteral("comboBox_Reader1_DeviceType"));
        comboBox_Reader1_DeviceType->setMouseTracking(false);

        horizontalLayout->addWidget(comboBox_Reader1_DeviceType);


        gridLayout_3->addLayout(horizontalLayout, 0, 1, 1, 1);

        checkBox_Reader1_Enable = new QCheckBox(groupBox);
        checkBox_Reader1_Enable->setObjectName(QStringLiteral("checkBox_Reader1_Enable"));

        gridLayout_3->addWidget(checkBox_Reader1_Enable, 0, 0, 1, 1);

        pushButton_Reader1_isRecord = new QPushButton(groupBox);
        pushButton_Reader1_isRecord->setObjectName(QStringLiteral("pushButton_Reader1_isRecord"));

        gridLayout_3->addWidget(pushButton_Reader1_isRecord, 1, 0, 1, 1);

        pushButton_Reader1_isRead = new QPushButton(groupBox);
        pushButton_Reader1_isRead->setObjectName(QStringLiteral("pushButton_Reader1_isRead"));

        gridLayout_3->addWidget(pushButton_Reader1_isRead, 1, 1, 1, 1);

        lineEdit_Reader1 = new QLineEdit(groupBox);
        lineEdit_Reader1->setObjectName(QStringLiteral("lineEdit_Reader1"));

        gridLayout_3->addWidget(lineEdit_Reader1, 2, 0, 1, 3);

        pushButton_Reader1_Zero = new QPushButton(groupBox);
        pushButton_Reader1_Zero->setObjectName(QStringLiteral("pushButton_Reader1_Zero"));

        gridLayout_3->addWidget(pushButton_Reader1_Zero, 1, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        comboBox_Reader1_DeviceID = new QComboBox(groupBox);
        comboBox_Reader1_DeviceID->setObjectName(QStringLiteral("comboBox_Reader1_DeviceID"));

        horizontalLayout_2->addWidget(comboBox_Reader1_DeviceID);


        gridLayout_3->addLayout(horizontalLayout_2, 0, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_3, 0, 1, 1, 1);


        gridLayout_Reader->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_2 = new QGridLayout(groupBox_4);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        checkBox_Reader4_Enable = new QCheckBox(groupBox_4);
        checkBox_Reader4_Enable->setObjectName(QStringLiteral("checkBox_Reader4_Enable"));

        gridLayout_5->addWidget(checkBox_Reader4_Enable, 0, 0, 1, 1);

        pushButton_Reader4_isRead = new QPushButton(groupBox_4);
        pushButton_Reader4_isRead->setObjectName(QStringLiteral("pushButton_Reader4_isRead"));

        gridLayout_5->addWidget(pushButton_Reader4_isRead, 1, 1, 1, 1);

        pushButton_Reader4_Zero = new QPushButton(groupBox_4);
        pushButton_Reader4_Zero->setObjectName(QStringLiteral("pushButton_Reader4_Zero"));

        gridLayout_5->addWidget(pushButton_Reader4_Zero, 1, 2, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        comboBox_Reader4_DeviceType = new QComboBox(groupBox_4);
        comboBox_Reader4_DeviceType->setObjectName(QStringLiteral("comboBox_Reader4_DeviceType"));
        comboBox_Reader4_DeviceType->setMouseTracking(false);

        horizontalLayout_5->addWidget(comboBox_Reader4_DeviceType);


        gridLayout_5->addLayout(horizontalLayout_5, 0, 1, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_6->addWidget(label_6);

        comboBox_Reader4_DeviceID = new QComboBox(groupBox_4);
        comboBox_Reader4_DeviceID->setObjectName(QStringLiteral("comboBox_Reader4_DeviceID"));

        horizontalLayout_6->addWidget(comboBox_Reader4_DeviceID);


        gridLayout_5->addLayout(horizontalLayout_6, 0, 2, 1, 1);

        pushButton_Reader4_isRecord = new QPushButton(groupBox_4);
        pushButton_Reader4_isRecord->setObjectName(QStringLiteral("pushButton_Reader4_isRecord"));

        gridLayout_5->addWidget(pushButton_Reader4_isRecord, 1, 0, 1, 1);

        lineEdit_Reader4 = new QLineEdit(groupBox_4);
        lineEdit_Reader4->setObjectName(QStringLiteral("lineEdit_Reader4"));

        gridLayout_5->addWidget(lineEdit_Reader4, 2, 0, 1, 3);


        gridLayout_2->addLayout(gridLayout_5, 0, 0, 1, 1);


        gridLayout_Reader->addWidget(groupBox_4, 1, 1, 1, 1);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_9 = new QGridLayout(groupBox_3);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        pushButton_Reader3_isRead = new QPushButton(groupBox_3);
        pushButton_Reader3_isRead->setObjectName(QStringLiteral("pushButton_Reader3_isRead"));

        gridLayout_4->addWidget(pushButton_Reader3_isRead, 1, 1, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        comboBox_Reader3_DeviceType = new QComboBox(groupBox_3);
        comboBox_Reader3_DeviceType->setObjectName(QStringLiteral("comboBox_Reader3_DeviceType"));
        comboBox_Reader3_DeviceType->setMouseTracking(false);

        horizontalLayout_3->addWidget(comboBox_Reader3_DeviceType);


        gridLayout_4->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        pushButton_Reader3_Zero = new QPushButton(groupBox_3);
        pushButton_Reader3_Zero->setObjectName(QStringLiteral("pushButton_Reader3_Zero"));

        gridLayout_4->addWidget(pushButton_Reader3_Zero, 1, 2, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_4->addWidget(label_4);

        comboBox_Reader3_DeviceID = new QComboBox(groupBox_3);
        comboBox_Reader3_DeviceID->setObjectName(QStringLiteral("comboBox_Reader3_DeviceID"));

        horizontalLayout_4->addWidget(comboBox_Reader3_DeviceID);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 2, 1, 1);

        pushButton_Reader3_isRecord = new QPushButton(groupBox_3);
        pushButton_Reader3_isRecord->setObjectName(QStringLiteral("pushButton_Reader3_isRecord"));

        gridLayout_4->addWidget(pushButton_Reader3_isRecord, 1, 0, 1, 1);

        checkBox_Reader3_Enable = new QCheckBox(groupBox_3);
        checkBox_Reader3_Enable->setObjectName(QStringLiteral("checkBox_Reader3_Enable"));

        gridLayout_4->addWidget(checkBox_Reader3_Enable, 0, 0, 1, 1);


        gridLayout_9->addLayout(gridLayout_4, 0, 0, 1, 1);

        lineEdit_Reader3 = new QLineEdit(groupBox_3);
        lineEdit_Reader3->setObjectName(QStringLiteral("lineEdit_Reader3"));

        gridLayout_9->addWidget(lineEdit_Reader3, 1, 0, 1, 1);


        gridLayout_Reader->addWidget(groupBox_3, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_8 = new QGridLayout(groupBox_2);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_7->addWidget(label_7);

        comboBox_Reader2_DeviceType = new QComboBox(groupBox_2);
        comboBox_Reader2_DeviceType->setObjectName(QStringLiteral("comboBox_Reader2_DeviceType"));
        comboBox_Reader2_DeviceType->setMouseTracking(false);

        horizontalLayout_7->addWidget(comboBox_Reader2_DeviceType);


        gridLayout_6->addLayout(horizontalLayout_7, 0, 1, 1, 1);

        pushButton_Reader2_isRecord = new QPushButton(groupBox_2);
        pushButton_Reader2_isRecord->setObjectName(QStringLiteral("pushButton_Reader2_isRecord"));

        gridLayout_6->addWidget(pushButton_Reader2_isRecord, 1, 0, 1, 1);

        lineEdit_Reader2 = new QLineEdit(groupBox_2);
        lineEdit_Reader2->setObjectName(QStringLiteral("lineEdit_Reader2"));

        gridLayout_6->addWidget(lineEdit_Reader2, 2, 0, 1, 3);

        pushButton_Reader2_Zero = new QPushButton(groupBox_2);
        pushButton_Reader2_Zero->setObjectName(QStringLiteral("pushButton_Reader2_Zero"));

        gridLayout_6->addWidget(pushButton_Reader2_Zero, 1, 2, 1, 1);

        checkBox_Reader2_Enable = new QCheckBox(groupBox_2);
        checkBox_Reader2_Enable->setObjectName(QStringLiteral("checkBox_Reader2_Enable"));

        gridLayout_6->addWidget(checkBox_Reader2_Enable, 0, 0, 1, 1);

        pushButton_Reader2_isRead = new QPushButton(groupBox_2);
        pushButton_Reader2_isRead->setObjectName(QStringLiteral("pushButton_Reader2_isRead"));

        gridLayout_6->addWidget(pushButton_Reader2_isRead, 1, 1, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_8->addWidget(label_8);

        comboBox_Reader2_DeviceID = new QComboBox(groupBox_2);
        comboBox_Reader2_DeviceID->setObjectName(QStringLiteral("comboBox_Reader2_DeviceID"));

        horizontalLayout_8->addWidget(comboBox_Reader2_DeviceID);


        gridLayout_6->addLayout(horizontalLayout_8, 0, 2, 1, 1);


        gridLayout_8->addLayout(gridLayout_6, 0, 0, 1, 1);


        gridLayout_Reader->addWidget(groupBox_2, 0, 1, 1, 1);


        gridLayout_7->addLayout(gridLayout_Reader, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 702, 22));
        menuwdaw = new QMenu(menubar);
        menuwdaw->setObjectName(QStringLiteral("menuwdaw"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuwdaw->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Specimen ID", Q_NULLPTR));
        lineEdit_File_Name->setText(QApplication::translate("MainWindow", "Specimen", Q_NULLPTR));
        pushButton_Browse->setText(QApplication::translate("MainWindow", "Browse..", Q_NULLPTR));
        label_FilePath->setText(QApplication::translate("MainWindow", "Release\\", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Recording Timer", Q_NULLPTR));
        pushButton_set_timer->setText(QApplication::translate("MainWindow", "Set Timer", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Intervals (ms)", Q_NULLPTR));
        checkBox_Timer_Enable->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        groupBox_6->setTitle(QString());
        pushButton_Rest->setText(QApplication::translate("MainWindow", "Rest", Q_NULLPTR));
        comboBox_PortName->clear();
        comboBox_PortName->insertItems(0, QStringList()
         << QString()
        );
        pushButton_All_Record->setText(QApplication::translate("MainWindow", "All Record", Q_NULLPTR));
        pushButton_Add_GroupBox->setText(QApplication::translate("MainWindow", "Add more", Q_NULLPTR));
        pushButton_SerialPort->setText(QApplication::translate("MainWindow", "Open Port", Q_NULLPTR));
        pushButton_All_Read->setText(QApplication::translate("MainWindow", "All Read", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Reader 1", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Types:", Q_NULLPTR));
        comboBox_Reader1_DeviceType->clear();
        comboBox_Reader1_DeviceType->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "HCA726S", Q_NULLPTR)
         << QApplication::translate("MainWindow", "LVDT Sensors", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Torque Sensors", Q_NULLPTR)
        );
        checkBox_Reader1_Enable->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        pushButton_Reader1_isRecord->setText(QApplication::translate("MainWindow", "Record", Q_NULLPTR));
        pushButton_Reader1_isRead->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        pushButton_Reader1_Zero->setText(QApplication::translate("MainWindow", "Zero", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "ID:", Q_NULLPTR));
        comboBox_Reader1_DeviceID->clear();
        comboBox_Reader1_DeviceID->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Reader 4", Q_NULLPTR));
        checkBox_Reader4_Enable->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        pushButton_Reader4_isRead->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        pushButton_Reader4_Zero->setText(QApplication::translate("MainWindow", "Zero", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Types:", Q_NULLPTR));
        comboBox_Reader4_DeviceType->clear();
        comboBox_Reader4_DeviceType->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "HCA726S", Q_NULLPTR)
         << QApplication::translate("MainWindow", "LVDT Sensors", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Torque Sensors", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("MainWindow", "ID:", Q_NULLPTR));
        comboBox_Reader4_DeviceID->clear();
        comboBox_Reader4_DeviceID->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        pushButton_Reader4_isRecord->setText(QApplication::translate("MainWindow", "Record", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Reader 3", Q_NULLPTR));
        pushButton_Reader3_isRead->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Types:", Q_NULLPTR));
        comboBox_Reader3_DeviceType->clear();
        comboBox_Reader3_DeviceType->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "HCA726S", Q_NULLPTR)
         << QApplication::translate("MainWindow", "LVDT Sensors", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Torque Sensors", Q_NULLPTR)
        );
        pushButton_Reader3_Zero->setText(QApplication::translate("MainWindow", "Zero", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "ID:", Q_NULLPTR));
        comboBox_Reader3_DeviceID->clear();
        comboBox_Reader3_DeviceID->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        pushButton_Reader3_isRecord->setText(QApplication::translate("MainWindow", "Record", Q_NULLPTR));
        checkBox_Reader3_Enable->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Reader 2", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "Types:", Q_NULLPTR));
        comboBox_Reader2_DeviceType->clear();
        comboBox_Reader2_DeviceType->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "HCA726S", Q_NULLPTR)
         << QApplication::translate("MainWindow", "LVDT Sensors", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Torque Sensors", Q_NULLPTR)
        );
        pushButton_Reader2_isRecord->setText(QApplication::translate("MainWindow", "Record", Q_NULLPTR));
        pushButton_Reader2_Zero->setText(QApplication::translate("MainWindow", "Zero", Q_NULLPTR));
        checkBox_Reader2_Enable->setText(QApplication::translate("MainWindow", "Enable", Q_NULLPTR));
        pushButton_Reader2_isRead->setText(QApplication::translate("MainWindow", "Read", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "ID:", Q_NULLPTR));
        comboBox_Reader2_DeviceID->clear();
        comboBox_Reader2_DeviceID->insertItems(0, QStringList()
         << QString()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
         << QApplication::translate("MainWindow", "3", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "6", Q_NULLPTR)
         << QApplication::translate("MainWindow", "7", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8", Q_NULLPTR)
        );
        menuwdaw->setTitle(QApplication::translate("MainWindow", "Dataloger", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
