/****************************************************************************
** Meta object code from reading C++ file 'automaton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../KinectShopApp/automaton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'automaton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_automaton_t {
    QByteArrayData data[9];
    char stringdata[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_automaton_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_automaton_t qt_meta_stringdata_automaton = {
    {
QT_MOC_LITERAL(0, 0, 9), // "automaton"
QT_MOC_LITERAL(1, 10, 12), // "stateChanged"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "input"
QT_MOC_LITERAL(4, 30, 13), // "inputReceived"
QT_MOC_LITERAL(5, 44, 5), // "state"
QT_MOC_LITERAL(6, 50, 4), // "from"
QT_MOC_LITERAL(7, 55, 11), // "transitions"
QT_MOC_LITERAL(8, 67, 12) // "receiveInput"

    },
    "automaton\0stateChanged\0\0input\0"
    "inputReceived\0state\0from\0transitions\0"
    "receiveInput"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_automaton[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   42,    2, 0x0a /* Public */,
       8,    1,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    6,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void automaton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        automaton *_t = static_cast<automaton *>(_o);
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->inputReceived((*reinterpret_cast< state(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->transitions((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->receiveInput((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (automaton::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&automaton::stateChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (automaton::*_t)(state , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&automaton::inputReceived)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject automaton::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_automaton.data,
      qt_meta_data_automaton,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *automaton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *automaton::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_automaton.stringdata))
        return static_cast<void*>(const_cast< automaton*>(this));
    return QObject::qt_metacast(_clname);
}

int automaton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void automaton::stateChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void automaton::inputReceived(state _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
