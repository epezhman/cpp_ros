/****************************************************************************
** Meta object code from reading C++ file 'RenderPaint.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "RenderPaint.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderPaint.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_RenderPaint_t {
    QByteArrayData data[21];
    char stringdata[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_RenderPaint_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_RenderPaint_t qt_meta_stringdata_RenderPaint = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 9),
QT_MOC_LITERAL(2, 22, 0),
QT_MOC_LITERAL(3, 23, 10),
QT_MOC_LITERAL(4, 34, 10),
QT_MOC_LITERAL(5, 45, 12),
QT_MOC_LITERAL(6, 58, 13),
QT_MOC_LITERAL(7, 72, 14),
QT_MOC_LITERAL(8, 87, 16),
QT_MOC_LITERAL(9, 104, 17),
QT_MOC_LITERAL(10, 122, 7),
QT_MOC_LITERAL(11, 130, 9),
QT_MOC_LITERAL(12, 140, 9),
QT_MOC_LITERAL(13, 150, 10),
QT_MOC_LITERAL(14, 161, 8),
QT_MOC_LITERAL(15, 170, 8),
QT_MOC_LITERAL(16, 179, 8),
QT_MOC_LITERAL(17, 188, 11),
QT_MOC_LITERAL(18, 200, 10),
QT_MOC_LITERAL(19, 211, 10),
QT_MOC_LITERAL(20, 222, 11)
    },
    "RenderPaint\0RGBValues\0\0RenderLoad\0"
    "RenderSave\0RenderZoomIn\0RenderZoomOut\0"
    "RenderPenSetUp\0RenderPenSetUpOn\0"
    "RenderPenSetUpOff\0Drawing\0LoadImage\0"
    "SaveImage\0updateDist\0updaten1\0updaten2\0"
    "updaten3\0updateParam\0updateIMin\0"
    "updateIMax\0updateAngle\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RenderPaint[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,  109,    2, 0x06,

 // slots: name, argc, parameters, tag, flags
       3,    0,  122,    2, 0x0a,
       4,    0,  123,    2, 0x0a,
       5,    0,  124,    2, 0x0a,
       6,    0,  125,    2, 0x0a,
       7,    0,  126,    2, 0x0a,
       8,    0,  127,    2, 0x0a,
       9,    0,  128,    2, 0x0a,
      10,    0,  129,    2, 0x0a,
      11,    0,  130,    2, 0x0a,
      12,    0,  131,    2, 0x0a,
      13,    1,  132,    2, 0x0a,
      14,    1,  135,    2, 0x0a,
      15,    1,  138,    2, 0x0a,
      16,    1,  141,    2, 0x0a,
      17,    0,  144,    2, 0x0a,
      18,    1,  145,    2, 0x0a,
      19,    1,  148,    2, 0x0a,
      20,    1,  151,    2, 0x0a,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,    2,    2,    2,

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
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,
    QMetaType::Void, QMetaType::Double,    2,

       0        // eod
};

void RenderPaint::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        RenderPaint *_t = static_cast<RenderPaint *>(_o);
        switch (_id) {
        case 0: _t->RGBValues((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6]))); break;
        case 1: _t->RenderLoad(); break;
        case 2: _t->RenderSave(); break;
        case 3: _t->RenderZoomIn(); break;
        case 4: _t->RenderZoomOut(); break;
        case 5: _t->RenderPenSetUp(); break;
        case 6: _t->RenderPenSetUpOn(); break;
        case 7: _t->RenderPenSetUpOff(); break;
        case 8: _t->Drawing(); break;
        case 9: _t->LoadImage(); break;
        case 10: _t->SaveImage(); break;
        case 11: _t->updateDist((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->updaten1((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->updaten2((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->updaten3((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 15: _t->updateParam(); break;
        case 16: _t->updateIMin((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 17: _t->updateIMax((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 18: _t->updateAngle((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (RenderPaint::*_t)(int , int , int , int , int , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&RenderPaint::RGBValues)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject RenderPaint::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_RenderPaint.data,
      qt_meta_data_RenderPaint,  qt_static_metacall, 0, 0}
};


const QMetaObject *RenderPaint::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RenderPaint::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderPaint.stringdata))
        return static_cast<void*>(const_cast< RenderPaint*>(this));
    return QWidget::qt_metacast(_clname);
}

int RenderPaint::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void RenderPaint::RGBValues(int _t1, int _t2, int _t3, int _t4, int _t5, int _t6)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
