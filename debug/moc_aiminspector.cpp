/****************************************************************************
** Meta object code from reading C++ file 'aiminspector.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.1.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/debug/aiminspector.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'aiminspector.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.1.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_AimInspector_t {
    QByteArrayData data[12];
    char stringdata[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_AimInspector_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_AimInspector_t qt_meta_stringdata_AimInspector = {
    {
QT_MOC_LITERAL(0, 0, 12),
QT_MOC_LITERAL(1, 13, 16),
QT_MOC_LITERAL(2, 30, 0),
QT_MOC_LITERAL(3, 31, 16),
QT_MOC_LITERAL(4, 48, 22),
QT_MOC_LITERAL(5, 71, 20),
QT_MOC_LITERAL(6, 92, 21),
QT_MOC_LITERAL(7, 114, 9),
QT_MOC_LITERAL(8, 124, 15),
QT_MOC_LITERAL(9, 140, 13),
QT_MOC_LITERAL(10, 154, 14),
QT_MOC_LITERAL(11, 169, 9)
    },
    "AimInspector\0cpuStatusChanged\0\0"
    "ledStatusChanged\0componentStatusChanged\0"
    "printerStatusChanged\0keyboardStatusChanged\0"
    "cpuStatus\0componentStatus\0printerStatus\0"
    "keyboardStatus\0ledStatus\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AimInspector[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       5,   44, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x05,
       3,    0,   40,    2, 0x05,
       4,    0,   41,    2, 0x05,
       5,    0,   42,    2, 0x05,
       6,    0,   43,    2, 0x05,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       7, QMetaType::QString, 0x00495003,
       8, QMetaType::QString, 0x00495003,
       9, QMetaType::QString, 0x00495003,
      10, QMetaType::QString, 0x00495003,
      11, QMetaType::QString, 0x00495003,

 // properties: notify_signal_id
       0,
       2,
       3,
       4,
       1,

       0        // eod
};

void AimInspector::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AimInspector *_t = static_cast<AimInspector *>(_o);
        switch (_id) {
        case 0: _t->cpuStatusChanged(); break;
        case 1: _t->ledStatusChanged(); break;
        case 2: _t->componentStatusChanged(); break;
        case 3: _t->printerStatusChanged(); break;
        case 4: _t->keyboardStatusChanged(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AimInspector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AimInspector::cpuStatusChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (AimInspector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AimInspector::ledStatusChanged)) {
                *result = 1;
            }
        }
        {
            typedef void (AimInspector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AimInspector::componentStatusChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (AimInspector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AimInspector::printerStatusChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (AimInspector::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AimInspector::keyboardStatusChanged)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject AimInspector::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AimInspector.data,
      qt_meta_data_AimInspector,  qt_static_metacall, 0, 0}
};


const QMetaObject *AimInspector::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AimInspector::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AimInspector.stringdata))
        return static_cast<void*>(const_cast< AimInspector*>(this));
    return QObject::qt_metacast(_clname);
}

int AimInspector::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = GetCpuStatus(); break;
        case 1: *reinterpret_cast< QString*>(_v) = GetComponentStatus(); break;
        case 2: *reinterpret_cast< QString*>(_v) = GetPrinterStatus(); break;
        case 3: *reinterpret_cast< QString*>(_v) = GetKeyboardStatus(); break;
        case 4: *reinterpret_cast< QString*>(_v) = GetLedStatus(); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: SetCpuStatus(*reinterpret_cast< QString*>(_v)); break;
        case 1: SetComponentStatus(*reinterpret_cast< QString*>(_v)); break;
        case 2: SetPrinterStatus(*reinterpret_cast< QString*>(_v)); break;
        case 3: SetKeyboardStatus(*reinterpret_cast< QString*>(_v)); break;
        case 4: SetLedStatus(*reinterpret_cast< QString*>(_v)); break;
        }
        _id -= 5;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 5;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 5;
    } else if (_c == QMetaObject::RegisterPropertyMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void AimInspector::cpuStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void AimInspector::ledStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}

// SIGNAL 2
void AimInspector::componentStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, 0);
}

// SIGNAL 3
void AimInspector::printerStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void AimInspector::keyboardStatusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, 0);
}
QT_END_MOC_NAMESPACE
