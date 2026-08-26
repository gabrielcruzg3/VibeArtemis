/****************************************************************************
** Meta object code from reading C++ file 'systemproperties.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.10.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../backend/systemproperties.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'systemproperties.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.10.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN16SystemPropertiesE_t {};
} // unnamed namespace

template <> constexpr inline auto SystemProperties::qt_create_metaobjectdata<qt_meta_tag_ZN16SystemPropertiesE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "SystemProperties",
        "unmappedGamepadsChanged",
        "",
        "hasHardwareAccelerationChanged",
        "rendererAlwaysFullScreenChanged",
        "maximumResolutionChanged",
        "supportsHdrChanged",
        "updateDecoderProperties",
        "hasHardwareAcceleration",
        "rendererAlwaysFullScreen",
        "QSize",
        "maximumResolution",
        "supportsHdr",
        "getNativeResolution",
        "QRect",
        "displayIndex",
        "getSafeAreaResolution",
        "getRefreshRate",
        "startAsyncLoad",
        "waitForAsyncLoad",
        "refreshDisplays",
        "isRunningWayland",
        "isRunningXWayland",
        "isWow64",
        "isDarwin",
        "friendlyNativeArchName",
        "hasDesktopEnvironment",
        "hasBrowser",
        "hasDiscordIntegration",
        "usesMaterial3Theme",
        "versionString",
        "unmappedGamepads"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'unmappedGamepadsChanged'
        QtMocHelpers::SignalData<void()>(1, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'hasHardwareAccelerationChanged'
        QtMocHelpers::SignalData<void()>(3, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'rendererAlwaysFullScreenChanged'
        QtMocHelpers::SignalData<void()>(4, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'maximumResolutionChanged'
        QtMocHelpers::SignalData<void()>(5, 2, QMC::AccessPublic, QMetaType::Void),
        // Signal 'supportsHdrChanged'
        QtMocHelpers::SignalData<void()>(6, 2, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateDecoderProperties'
        QtMocHelpers::SlotData<void(bool, bool, QSize, bool)>(7, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Bool, 8 }, { QMetaType::Bool, 9 }, { 0x80000000 | 10, 11 }, { QMetaType::Bool, 12 },
        }}),
        // Method 'getNativeResolution'
        QtMocHelpers::MethodData<QRect(int)>(13, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 15 },
        }}),
        // Method 'getSafeAreaResolution'
        QtMocHelpers::MethodData<QRect(int)>(16, 2, QMC::AccessPublic, 0x80000000 | 14, {{
            { QMetaType::Int, 15 },
        }}),
        // Method 'getRefreshRate'
        QtMocHelpers::MethodData<int(int)>(17, 2, QMC::AccessPublic, QMetaType::Int, {{
            { QMetaType::Int, 15 },
        }}),
        // Method 'startAsyncLoad'
        QtMocHelpers::MethodData<void()>(18, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'waitForAsyncLoad'
        QtMocHelpers::MethodData<void()>(19, 2, QMC::AccessPublic, QMetaType::Void),
        // Method 'refreshDisplays'
        QtMocHelpers::MethodData<void()>(20, 2, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
        // property 'isRunningWayland'
        QtMocHelpers::PropertyData<bool>(21, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'isRunningXWayland'
        QtMocHelpers::PropertyData<bool>(22, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'isWow64'
        QtMocHelpers::PropertyData<bool>(23, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'isDarwin'
        QtMocHelpers::PropertyData<bool>(24, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'friendlyNativeArchName'
        QtMocHelpers::PropertyData<QString>(25, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'hasDesktopEnvironment'
        QtMocHelpers::PropertyData<bool>(26, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'hasBrowser'
        QtMocHelpers::PropertyData<bool>(27, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'hasDiscordIntegration'
        QtMocHelpers::PropertyData<bool>(28, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'usesMaterial3Theme'
        QtMocHelpers::PropertyData<bool>(29, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'versionString'
        QtMocHelpers::PropertyData<QString>(30, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Constant),
        // property 'hasHardwareAcceleration'
        QtMocHelpers::PropertyData<bool>(8, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable, 1),
        // property 'rendererAlwaysFullScreen'
        QtMocHelpers::PropertyData<bool>(9, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable, 2),
        // property 'unmappedGamepads'
        QtMocHelpers::PropertyData<QString>(31, QMetaType::QString, QMC::DefaultPropertyFlags | QMC::Writable, 0),
        // property 'maximumResolution'
        QtMocHelpers::PropertyData<QSize>(11, 0x80000000 | 10, QMC::DefaultPropertyFlags | QMC::Writable | QMC::EnumOrFlag, 3),
        // property 'supportsHdr'
        QtMocHelpers::PropertyData<bool>(12, QMetaType::Bool, QMC::DefaultPropertyFlags | QMC::Writable, 4),
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<SystemProperties, qt_meta_tag_ZN16SystemPropertiesE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject SystemProperties::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16SystemPropertiesE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16SystemPropertiesE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN16SystemPropertiesE_t>.metaTypes,
    nullptr
} };

void SystemProperties::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<SystemProperties *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->unmappedGamepadsChanged(); break;
        case 1: _t->hasHardwareAccelerationChanged(); break;
        case 2: _t->rendererAlwaysFullScreenChanged(); break;
        case 3: _t->maximumResolutionChanged(); break;
        case 4: _t->supportsHdrChanged(); break;
        case 5: _t->updateDecoderProperties((*reinterpret_cast<std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[2])),(*reinterpret_cast<std::add_pointer_t<QSize>>(_a[3])),(*reinterpret_cast<std::add_pointer_t<bool>>(_a[4]))); break;
        case 6: { QRect _r = _t->getNativeResolution((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QRect*>(_a[0]) = std::move(_r); }  break;
        case 7: { QRect _r = _t->getSafeAreaResolution((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<QRect*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->getRefreshRate((*reinterpret_cast<std::add_pointer_t<int>>(_a[1])));
            if (_a[0]) *reinterpret_cast<int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->startAsyncLoad(); break;
        case 10: _t->waitForAsyncLoad(); break;
        case 11: _t->refreshDisplays(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (SystemProperties::*)()>(_a, &SystemProperties::unmappedGamepadsChanged, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (SystemProperties::*)()>(_a, &SystemProperties::hasHardwareAccelerationChanged, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (SystemProperties::*)()>(_a, &SystemProperties::rendererAlwaysFullScreenChanged, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (SystemProperties::*)()>(_a, &SystemProperties::maximumResolutionChanged, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (SystemProperties::*)()>(_a, &SystemProperties::supportsHdrChanged, 4))
            return;
    }
    if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast<bool*>(_v) = _t->isRunningWayland; break;
        case 1: *reinterpret_cast<bool*>(_v) = _t->isRunningXWayland; break;
        case 2: *reinterpret_cast<bool*>(_v) = _t->isWow64; break;
        case 3: *reinterpret_cast<bool*>(_v) = _t->isDarwin; break;
        case 4: *reinterpret_cast<QString*>(_v) = _t->friendlyNativeArchName; break;
        case 5: *reinterpret_cast<bool*>(_v) = _t->hasDesktopEnvironment; break;
        case 6: *reinterpret_cast<bool*>(_v) = _t->hasBrowser; break;
        case 7: *reinterpret_cast<bool*>(_v) = _t->hasDiscordIntegration; break;
        case 8: *reinterpret_cast<bool*>(_v) = _t->usesMaterial3Theme; break;
        case 9: *reinterpret_cast<QString*>(_v) = _t->versionString; break;
        case 10: *reinterpret_cast<bool*>(_v) = _t->hasHardwareAcceleration; break;
        case 11: *reinterpret_cast<bool*>(_v) = _t->rendererAlwaysFullScreen; break;
        case 12: *reinterpret_cast<QString*>(_v) = _t->unmappedGamepads; break;
        case 13: *reinterpret_cast<QSize*>(_v) = _t->maximumResolution; break;
        case 14: *reinterpret_cast<bool*>(_v) = _t->supportsHdr; break;
        default: break;
        }
    }
    if (_c == QMetaObject::WriteProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 10:
            if (QtMocHelpers::setProperty(_t->hasHardwareAcceleration, *reinterpret_cast<bool*>(_v)))
                Q_EMIT _t->hasHardwareAccelerationChanged();
            break;
        case 11:
            if (QtMocHelpers::setProperty(_t->rendererAlwaysFullScreen, *reinterpret_cast<bool*>(_v)))
                Q_EMIT _t->rendererAlwaysFullScreenChanged();
            break;
        case 12:
            if (QtMocHelpers::setProperty(_t->unmappedGamepads, *reinterpret_cast<QString*>(_v)))
                Q_EMIT _t->unmappedGamepadsChanged();
            break;
        case 13:
            if (QtMocHelpers::setProperty(_t->maximumResolution, *reinterpret_cast<QSize*>(_v)))
                Q_EMIT _t->maximumResolutionChanged();
            break;
        case 14:
            if (QtMocHelpers::setProperty(_t->supportsHdr, *reinterpret_cast<bool*>(_v)))
                Q_EMIT _t->supportsHdrChanged();
            break;
        default: break;
        }
    }
}

const QMetaObject *SystemProperties::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SystemProperties::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN16SystemPropertiesE_t>.strings))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int SystemProperties::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::BindableProperty
            || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void SystemProperties::unmappedGamepadsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void SystemProperties::hasHardwareAccelerationChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void SystemProperties::rendererAlwaysFullScreenChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void SystemProperties::maximumResolutionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void SystemProperties::supportsHdrChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
