/****************************************************************************
** Meta object code from reading C++ file 'FileExplorer.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/FileExplorer.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FileExplorer.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_FileExplorer_t {
    uint offsetsAndSizes[36];
    char stringdata0[13];
    char stringdata1[18];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[13];
    char stringdata5[20];
    char stringdata6[12];
    char stringdata7[6];
    char stringdata8[14];
    char stringdata9[29];
    char stringdata10[4];
    char stringdata11[13];
    char stringdata12[14];
    char stringdata13[16];
    char stringdata14[11];
    char stringdata15[11];
    char stringdata16[9];
    char stringdata17[15];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_FileExplorer_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_FileExplorer_t qt_meta_stringdata_FileExplorer = {
    {
        QT_MOC_LITERAL(0, 12),  // "FileExplorer"
        QT_MOC_LITERAL(13, 17),  // "fileDoubleClicked"
        QT_MOC_LITERAL(31, 0),  // ""
        QT_MOC_LITERAL(32, 8),  // "filePath"
        QT_MOC_LITERAL(41, 12),  // "fileSelected"
        QT_MOC_LITERAL(54, 19),  // "onItemDoubleClicked"
        QT_MOC_LITERAL(74, 11),  // "QModelIndex"
        QT_MOC_LITERAL(86, 5),  // "index"
        QT_MOC_LITERAL(92, 13),  // "onItemClicked"
        QT_MOC_LITERAL(106, 28),  // "onCustomContextMenuRequested"
        QT_MOC_LITERAL(135, 3),  // "pos"
        QT_MOC_LITERAL(139, 12),  // "browseFolder"
        QT_MOC_LITERAL(152, 13),  // "createNewFile"
        QT_MOC_LITERAL(166, 15),  // "createNewFolder"
        QT_MOC_LITERAL(182, 10),  // "deleteItem"
        QT_MOC_LITERAL(193, 10),  // "renameItem"
        QT_MOC_LITERAL(204, 8),  // "copyPath"
        QT_MOC_LITERAL(213, 14)   // "revealInSystem"
    },
    "FileExplorer",
    "fileDoubleClicked",
    "",
    "filePath",
    "fileSelected",
    "onItemDoubleClicked",
    "QModelIndex",
    "index",
    "onItemClicked",
    "onCustomContextMenuRequested",
    "pos",
    "browseFolder",
    "createNewFile",
    "createNewFolder",
    "deleteItem",
    "renameItem",
    "copyPath",
    "revealInSystem"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_FileExplorer[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   86,    2, 0x06,    1 /* Public */,
       4,    1,   89,    2, 0x06,    3 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       5,    1,   92,    2, 0x08,    5 /* Private */,
       8,    1,   95,    2, 0x08,    7 /* Private */,
       9,    1,   98,    2, 0x08,    9 /* Private */,
      11,    0,  101,    2, 0x08,   11 /* Private */,
      12,    0,  102,    2, 0x08,   12 /* Private */,
      13,    0,  103,    2, 0x08,   13 /* Private */,
      14,    0,  104,    2, 0x08,   14 /* Private */,
      15,    0,  105,    2, 0x08,   15 /* Private */,
      16,    0,  106,    2, 0x08,   16 /* Private */,
      17,    0,  107,    2, 0x08,   17 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QPoint,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject FileExplorer::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FileExplorer.offsetsAndSizes,
    qt_meta_data_FileExplorer,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_FileExplorer_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<FileExplorer, std::true_type>,
        // method 'fileDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'fileSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onItemDoubleClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'onItemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>,
        // method 'onCustomContextMenuRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'browseFolder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createNewFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createNewFolder'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'deleteItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'renameItem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'copyPath'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'revealInSystem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void FileExplorer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileExplorer *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->fileDoubleClicked((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 1: _t->fileSelected((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->onItemDoubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 3: _t->onItemClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 4: _t->onCustomContextMenuRequested((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 5: _t->browseFolder(); break;
        case 6: _t->createNewFile(); break;
        case 7: _t->createNewFolder(); break;
        case 8: _t->deleteItem(); break;
        case 9: _t->renameItem(); break;
        case 10: _t->copyPath(); break;
        case 11: _t->revealInSystem(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileExplorer::*)(const QString & );
            if (_t _q_method = &FileExplorer::fileDoubleClicked; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileExplorer::*)(const QString & );
            if (_t _q_method = &FileExplorer::fileSelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject *FileExplorer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileExplorer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileExplorer.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FileExplorer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void FileExplorer::fileDoubleClicked(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileExplorer::fileSelected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
