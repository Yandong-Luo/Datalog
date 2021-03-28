/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Datalog/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[305];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 16), // "start_portThread"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 19), // "btn_Open_Port_Click"
QT_MOC_LITERAL(4, 49, 18), // "Btn_All_Read_Click"
QT_MOC_LITERAL(5, 68, 24), // "Btn_Add_DatalogBox_Click"
QT_MOC_LITERAL(6, 93, 20), // "Btn_All_Record_Click"
QT_MOC_LITERAL(7, 114, 14), // "Btn_Rest_Click"
QT_MOC_LITERAL(8, 129, 22), // "CheckBoxs_Enable_Click"
QT_MOC_LITERAL(9, 152, 16), // "Btn_Record_Click"
QT_MOC_LITERAL(10, 169, 14), // "Btn_Read_Click"
QT_MOC_LITERAL(11, 184, 14), // "Btn_Zero_Click"
QT_MOC_LITERAL(12, 199, 18), // "Btn_SetTimer_Click"
QT_MOC_LITERAL(13, 218, 24), // "TimerEnable_CheckChanged"
QT_MOC_LITERAL(14, 243, 8), // "showData"
QT_MOC_LITERAL(15, 252, 12), // "Reader_Index"
QT_MOC_LITERAL(16, 265, 22), // "Handle_Invalid_Sending"
QT_MOC_LITERAL(17, 288, 16) // "Btn_Browse_Click"

    },
    "MainWindow\0start_portThread\0\0"
    "btn_Open_Port_Click\0Btn_All_Read_Click\0"
    "Btn_Add_DatalogBox_Click\0Btn_All_Record_Click\0"
    "Btn_Rest_Click\0CheckBoxs_Enable_Click\0"
    "Btn_Record_Click\0Btn_Read_Click\0"
    "Btn_Zero_Click\0Btn_SetTimer_Click\0"
    "TimerEnable_CheckChanged\0showData\0"
    "Reader_Index\0Handle_Invalid_Sending\0"
    "Btn_Browse_Click"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   90,    2, 0x0a /* Public */,
       4,    0,   91,    2, 0x0a /* Public */,
       5,    0,   92,    2, 0x0a /* Public */,
       6,    0,   93,    2, 0x0a /* Public */,
       7,    0,   94,    2, 0x0a /* Public */,
       8,    0,   95,    2, 0x0a /* Public */,
       9,    0,   96,    2, 0x0a /* Public */,
      10,    0,   97,    2, 0x0a /* Public */,
      11,    0,   98,    2, 0x0a /* Public */,
      12,    0,   99,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    1,  101,    2, 0x0a /* Public */,
      16,    1,  104,    2, 0x0a /* Public */,
      17,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->start_portThread(); break;
        case 1: _t->btn_Open_Port_Click(); break;
        case 2: _t->Btn_All_Read_Click(); break;
        case 3: _t->Btn_Add_DatalogBox_Click(); break;
        case 4: _t->Btn_All_Record_Click(); break;
        case 5: _t->Btn_Rest_Click(); break;
        case 6: _t->CheckBoxs_Enable_Click(); break;
        case 7: _t->Btn_Record_Click(); break;
        case 8: _t->Btn_Read_Click(); break;
        case 9: _t->Btn_Zero_Click(); break;
        case 10: _t->Btn_SetTimer_Click(); break;
        case 11: _t->TimerEnable_CheckChanged(); break;
        case 12: _t->showData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->Handle_Invalid_Sending((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->Btn_Browse_Click(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::start_portThread)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::start_portThread()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
