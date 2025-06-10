/****************************************************************************
** Meta object code from reading C++ file 'FindReplacePanel.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/FindReplacePanel.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FindReplacePanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_FindReplacePanel_t {
    uint offsetsAndSizes[36];
    char stringdata0[17];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[5];
    char stringdata4[14];
    char stringdata5[11];
    char stringdata6[9];
    char stringdata7[17];
    char stringdata8[9];
    char stringdata9[12];
    char stringdata10[20];
    char stringdata11[9];
    char stringdata12[13];
    char stringdata13[8];
    char stringdata14[11];
    char stringdata15[18];
    char stringdata16[17];
    char stringdata17[21];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FindReplacePanel_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FindReplacePanel_t qt_meta_stringdata_FindReplacePanel = {
    {
        QT_MOC_LITERAL(0, 16),  // "FindReplacePanel"
        QT_MOC_LITERAL(17, 13),  // "findRequested"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 4),  // "text"
        QT_MOC_LITERAL(37, 13),  // "caseSensitive"
        QT_MOC_LITERAL(51, 10),  // "wholeWords"
        QT_MOC_LITERAL(62, 8),  // "useRegex"
        QT_MOC_LITERAL(71, 16),  // "replaceRequested"
        QT_MOC_LITERAL(88, 8),  // "findText"
        QT_MOC_LITERAL(97, 11),  // "replaceText"
        QT_MOC_LITERAL(109, 19),  // "replaceAllRequested"
        QT_MOC_LITERAL(129, 8),  // "findNext"
        QT_MOC_LITERAL(138, 12),  // "findPrevious"
        QT_MOC_LITERAL(151, 7),  // "replace"
        QT_MOC_LITERAL(159, 10),  // "replaceAll"
        QT_MOC_LITERAL(170, 17),  // "onFindTextChanged"
        QT_MOC_LITERAL(188, 16),  // "onOptionsChanged"
        QT_MOC_LITERAL(205, 20)   // "onCloseButtonClicked"
    },
    "FindReplacePanel",
    "findRequested",
    "",
    "text",
    "caseSensitive",
    "wholeWords",
    "useRegex",
    "replaceRequested",
    "findText",
    "replaceText",
    "replaceAllRequested",
    "findNext",
    "findPrevious",
    "replace",
    "replaceAll",
    "onFindTextChanged",
    "onOptionsChanged",
    "onCloseButtonClicked"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FindReplacePanel[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    4,   74,    2, 0x06,    1 /* Public */,
       7,    5,   83,    2, 0x06,    6 /* Public */,
      10,    5,   94,    2, 0x06,   12 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    0,  105,    2, 0x0a,   18 /* Public */,
      12,    0,  106,    2, 0x0a,   19 /* Public */,
      13,    0,  107,    2, 0x0a,   20 /* Public */,
      14,    0,  108,    2, 0x0a,   21 /* Public */,
      15,    0,  109,    2, 0x0a,   22 /* Public */,
      16,    0,  110,    2, 0x08,   23 /* Private */,
      17,    0,  111,    2, 0x08,   24 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    8,    9,    4,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    8,    9,    4,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FindReplacePanel::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FindReplacePanel.offsetsAndSizes,
    qt_meta_data_FindReplacePanel,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FindReplacePanel_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FindReplacePanel, std::true_type>,
        // method 'findRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'replaceRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'replaceAllRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'findNext'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'findPrevious'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replace'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'replaceAll'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onFindTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onOptionsChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onCloseButtonClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FindReplacePanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FindReplacePanel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->findRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4]))); break;
        case 1: _t->replaceRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 2: _t->replaceAllRequested((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[5]))); break;
        case 3: _t->findNext(); break;
        case 4: _t->findPrevious(); break;
        case 5: _t->replace(); break;
        case 6: _t->replaceAll(); break;
        case 7: _t->onFindTextChanged(); break;
        case 8: _t->onOptionsChanged(); break;
        case 9: _t->onCloseButtonClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FindReplacePanel::*)(const QString & , bool , bool , bool );
            if (_t _q_method = &FindReplacePanel::findRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FindReplacePanel::*)(const QString & , const QString & , bool , bool , bool );
            if (_t _q_method = &FindReplacePanel::replaceRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FindReplacePanel::*)(const QString & , const QString & , bool , bool , bool );
            if (_t _q_method = &FindReplacePanel::replaceAllRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *FindReplacePanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FindReplacePanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FindReplacePanel.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FindReplacePanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void FindReplacePanel::findRequested(const QString & _t1, bool _t2, bool _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FindReplacePanel::replaceRequested(const QString & _t1, const QString & _t2, bool _t3, bool _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FindReplacePanel::replaceAllRequested(const QString & _t1, const QString & _t2, bool _t3, bool _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
