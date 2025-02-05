/****************************************************************************
** Meta object code from reading C++ file 'FocusTrackKCM.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FocusTrackKCM.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FocusTrackKCM.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FocusTrackKCM_t {
    QByteArrayData data[5];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FocusTrackKCM_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FocusTrackKCM_t qt_meta_stringdata_FocusTrackKCM = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FocusTrackKCM"
QT_MOC_LITERAL(1, 14, 8), // "defaults"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "load"
QT_MOC_LITERAL(4, 29, 4) // "save"

    },
    "FocusTrackKCM\0defaults\0\0load\0save"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FocusTrackKCM[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x0a /* Public */,
       3,    0,   30,    2, 0x0a /* Public */,
       4,    0,   31,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FocusTrackKCM::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FocusTrackKCM *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->defaults(); break;
        case 1: _t->load(); break;
        case 2: _t->save(); break;
        default: ;
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject FocusTrackKCM::staticMetaObject = { {
    QMetaObject::SuperData::link<KCModule::staticMetaObject>(),
    qt_meta_stringdata_FocusTrackKCM.data,
    qt_meta_data_FocusTrackKCM,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FocusTrackKCM::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FocusTrackKCM::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FocusTrackKCM.stringdata0))
        return static_cast<void*>(this);
    return KCModule::qt_metacast(_clname);
}

int FocusTrackKCM::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = KCModule::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
