/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata[457];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10),
QT_MOC_LITERAL(1, 11, 14),
QT_MOC_LITERAL(2, 26, 0),
QT_MOC_LITERAL(3, 27, 3),
QT_MOC_LITERAL(4, 31, 11),
QT_MOC_LITERAL(5, 43, 10),
QT_MOC_LITERAL(6, 54, 18),
QT_MOC_LITERAL(7, 73, 28),
QT_MOC_LITERAL(8, 102, 29),
QT_MOC_LITERAL(9, 132, 26),
QT_MOC_LITERAL(10, 159, 8),
QT_MOC_LITERAL(11, 168, 25),
QT_MOC_LITERAL(12, 194, 24),
QT_MOC_LITERAL(13, 219, 29),
QT_MOC_LITERAL(14, 249, 30),
QT_MOC_LITERAL(15, 280, 11),
QT_MOC_LITERAL(16, 292, 14),
QT_MOC_LITERAL(17, 307, 11),
QT_MOC_LITERAL(18, 319, 18),
QT_MOC_LITERAL(19, 338, 21),
QT_MOC_LITERAL(20, 360, 21),
QT_MOC_LITERAL(21, 382, 22),
QT_MOC_LITERAL(22, 405, 20),
QT_MOC_LITERAL(23, 426, 30)
    },
    "MainWindow\0updatePlayerUI\0\0img\0"
    "chooseVideo\0choosePath\0on_playBtn_clicked\0"
    "on_videoSlider_sliderPressed\0"
    "on_videoSlider_sliderReleased\0"
    "on_videoSlider_sliderMoved\0position\0"
    "on_backwardButton_clicked\0"
    "on_forwardButton_clicked\0"
    "on_quickforwardButton_clicked\0"
    "on_quickbackwardButton_clicked\0"
    "myMouseMove\0myMousePressed\0myMouseLeft\0"
    "myMouseMovePressed\0openInformationDialog\0"
    "openDeplacementDialog\0on_debutButton_clicked\0"
    "on_finButton_clicked\0"
    "on_trajectoirecheckBox_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      20,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  114,    2, 0x08 /* Private */,
       4,    0,  117,    2, 0x08 /* Private */,
       5,    0,  118,    2, 0x08 /* Private */,
       6,    0,  119,    2, 0x08 /* Private */,
       7,    0,  120,    2, 0x08 /* Private */,
       8,    0,  121,    2, 0x08 /* Private */,
       9,    1,  122,    2, 0x08 /* Private */,
      11,    0,  125,    2, 0x08 /* Private */,
      12,    0,  126,    2, 0x08 /* Private */,
      13,    0,  127,    2, 0x08 /* Private */,
      14,    0,  128,    2, 0x08 /* Private */,
      15,    2,  129,    2, 0x08 /* Private */,
      16,    2,  134,    2, 0x08 /* Private */,
      17,    2,  139,    2, 0x08 /* Private */,
      18,    2,  144,    2, 0x08 /* Private */,
      19,    0,  149,    2, 0x08 /* Private */,
      20,    0,  150,    2, 0x08 /* Private */,
      21,    0,  151,    2, 0x08 /* Private */,
      22,    0,  152,    2, 0x08 /* Private */,
      23,    0,  153,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::QImage,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->updatePlayerUI((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 1: _t->chooseVideo(); break;
        case 2: _t->choosePath(); break;
        case 3: _t->on_playBtn_clicked(); break;
        case 4: _t->on_videoSlider_sliderPressed(); break;
        case 5: _t->on_videoSlider_sliderReleased(); break;
        case 6: _t->on_videoSlider_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_backwardButton_clicked(); break;
        case 8: _t->on_forwardButton_clicked(); break;
        case 9: _t->on_quickforwardButton_clicked(); break;
        case 10: _t->on_quickbackwardButton_clicked(); break;
        case 11: _t->myMouseMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 12: _t->myMousePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 13: _t->myMouseLeft((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 14: _t->myMouseMovePressed((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->openInformationDialog(); break;
        case 16: _t->openDeplacementDialog(); break;
        case 17: _t->on_debutButton_clicked(); break;
        case 18: _t->on_finButton_clicked(); break;
        case 19: _t->on_trajectoirecheckBox_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 20)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 20;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 20)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 20;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
