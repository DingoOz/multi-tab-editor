/****************************************************************************
** Meta object code from reading C++ file 'TabWidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/TabWidget.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TabWidget.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_TabWidget_t {
    uint offsetsAndSizes[28];
    char stringdata0[10];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[6];
    char stringdata4[21];
    char stringdata5[12];
    char stringdata6[7];
    char stringdata7[19];
    char stringdata8[15];
    char stringdata9[17];
    char stringdata10[22];
    char stringdata11[16];
    char stringdata12[15];
    char stringdata13[20];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_TabWidget_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_TabWidget_t qt_meta_stringdata_TabWidget = {
    {
        QT_MOC_LITERAL(0, 9),  // "TabWidget"
        QT_MOC_LITERAL(10, 17),  // "tabCloseRequested"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 5),  // "index"
        QT_MOC_LITERAL(35, 20),  // "currentEditorChanged"
        QT_MOC_LITERAL(56, 11),  // "TextEditor*"
        QT_MOC_LITERAL(68, 6),  // "editor"
        QT_MOC_LITERAL(75, 18),  // "onDocumentModified"
        QT_MOC_LITERAL(94, 14),  // "updateTabTitle"
        QT_MOC_LITERAL(109, 16),  // "onCurrentChanged"
        QT_MOC_LITERAL(126, 21),  // "onTabBarDoubleClicked"
        QT_MOC_LITERAL(148, 15),  // "closeCurrentTab"
        QT_MOC_LITERAL(164, 14),  // "closeOtherTabs"
        QT_MOC_LITERAL(179, 19)   // "closeTabsToTheRight"
    },
    "TabWidget",
    "tabCloseRequested",
    "",
    "index",
    "currentEditorChanged",
    "TextEditor*",
    "editor",
    "onDocumentModified",
    "updateTabTitle",
    "onCurrentChanged",
    "onTabBarDoubleClicked",
    "closeCurrentTab",
    "closeOtherTabs",
    "closeTabsToTheRight"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_TabWidget[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   68,    2, 0x06,    1 /* Public */,
       4,    1,   71,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       7,    0,   74,    2, 0x0a,    5 /* Public */,
       8,    1,   75,    2, 0x0a,    6 /* Public */,
       9,    1,   78,    2, 0x08,    8 /* Private */,
      10,    1,   81,    2, 0x08,   10 /* Private */,
      11,    0,   84,    2, 0x08,   12 /* Private */,
      12,    0,   85,    2, 0x08,   13 /* Private */,
      13,    0,   86,    2, 0x08,   14 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject TabWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QTabWidget::staticMetaObject>(),
    qt_meta_stringdata_TabWidget.offsetsAndSizes,
    qt_meta_data_TabWidget,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_TabWidget_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<TabWidget, std::true_type>,
        // method 'tabCloseRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'currentEditorChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<TextEditor *, std::false_type>,
        // method 'onDocumentModified'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'updateTabTitle'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onCurrentChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onTabBarDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'closeCurrentTab'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeOtherTabs'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'closeTabsToTheRight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void TabWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TabWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tabCloseRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->currentEditorChanged((*reinterpret_cast< std::add_pointer_t<TextEditor*>>(_a[1]))); break;
        case 2: _t->onDocumentModified(); break;
        case 3: _t->updateTabTitle((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 4: _t->onCurrentChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->onTabBarDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->closeCurrentTab(); break;
        case 7: _t->closeOtherTabs(); break;
        case 8: _t->closeTabsToTheRight(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TabWidget::*)(int );
            if (_t _q_method = &TabWidget::tabCloseRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TabWidget::*)(TextEditor * );
            if (_t _q_method = &TabWidget::currentEditorChanged; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *TabWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TabWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TabWidget.stringdata0))
        return static_cast<void*>(this);
    return QTabWidget::qt_metacast(_clname);
}

int TabWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTabWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void TabWidget::tabCloseRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TabWidget::currentEditorChanged(TextEditor * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
