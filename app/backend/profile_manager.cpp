#include "backend/profile_manager.h"
#include "settings/streamingpreferences.h"
#include <QDebug>

namespace vibeartemis {

static ProfileManager* s_ProfileManager = nullptr;

ProfileManager* ProfileManager::instance() {
    if (!s_ProfileManager) {
        s_ProfileManager = new ProfileManager();
    }
    return s_ProfileManager;
}

ProfileManager::ProfileManager(QObject* parent)
    : QObject(parent)
{
    loadProfiles();
}

QString ProfileManager::getProfilesFilePath() const {
    QString configDir = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(configDir);
    return configDir + "/profiles.json";
}

void ProfileManager::initDefaultProfiles() {
    m_Profiles.clear();

    StreamProfile p1{"Default (1080p 60 FPS)", 1920, 1080, 60, 20000, true, 100, false, false};
    StreamProfile p2{"Ultrawide 21:9 (3440x1440 144 FPS)", 3440, 1440, 144, 45000, true, 100, true, true};
    StreamProfile p3{"Super Ultrawide 32:9 (5120x1440 120 FPS)", 5120, 1440, 120, 50000, true, 100, true, true};
    StreamProfile p4{"16:10 Laptop / Deck (2560x1600 120 FPS)", 2560, 1600, 120, 35000, true, 100, false, false};
    StreamProfile p5{"4K HDR Cinema (3840x2160 60 FPS)", 3840, 2160, 60, 60000, true, 100, true, false};
    StreamProfile p6{"Esports High Refresh (1920x1080 240 FPS)", 1920, 1080, 240, 35000, true, 100, false, true};

    m_Profiles[p1.name] = p1;
    m_Profiles[p2.name] = p2;
    m_Profiles[p3.name] = p3;
    m_Profiles[p4.name] = p4;
    m_Profiles[p5.name] = p5;
    m_Profiles[p6.name] = p6;
}

void ProfileManager::loadProfiles() {
    QFile file(getProfilesFilePath());
    if (!file.exists() || !file.open(QIODevice::ReadOnly)) {
        initDefaultProfiles();
        saveProfiles();
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (!doc.isObject()) {
        initDefaultProfiles();
        return;
    }

    QJsonObject root = doc.object();
    m_ActiveProfileName = root.value("activeProfile").toString("Default (1080p 60 FPS)");
    QJsonArray array = root.value("profiles").toArray();

    if (array.isEmpty()) {
        initDefaultProfiles();
        return;
    }

    m_Profiles.clear();
    for (const auto& item : array) {
        QJsonObject obj = item.toObject();
        StreamProfile p;
        p.name = obj.value("name").toString();
        p.width = obj.value("width").toInt(1920);
        p.height = obj.value("height").toInt(1080);
        p.fps = obj.value("fps").toInt(60);
        p.bitrateKbps = obj.value("bitrateKbps").toInt(20000);
        p.useVirtualDisplay = obj.value("useVirtualDisplay").toBool(true);
        p.resolutionScaleFactor = obj.value("resolutionScaleFactor").toInt(100);
        p.enableHdr = obj.value("enableHdr").toBool(false);
        p.ultraLowLatency = obj.value("ultraLowLatency").toBool(false);

        if (!p.name.isEmpty()) {
            m_Profiles[p.name] = p;
        }
    }
}

void ProfileManager::saveProfiles() {
    QJsonObject root;
    root["activeProfile"] = m_ActiveProfileName;

    QJsonArray array;
    for (const auto& p : m_Profiles) {
        QJsonObject obj;
        obj["name"] = p.name;
        obj["width"] = p.width;
        obj["height"] = p.height;
        obj["fps"] = p.fps;
        obj["bitrateKbps"] = p.bitrateKbps;
        obj["useVirtualDisplay"] = p.useVirtualDisplay;
        obj["resolutionScaleFactor"] = p.resolutionScaleFactor;
        obj["enableHdr"] = p.enableHdr;
        obj["ultraLowLatency"] = p.ultraLowLatency;
        array.append(obj);
    }
    root["profiles"] = array;

    QFile file(getProfilesFilePath());
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
        file.close();
    }
}

QStringList ProfileManager::getProfileNames() const {
    return m_Profiles.keys();
}

QVariantMap ProfileManager::getProfile(const QString& name) const {
    QVariantMap map;
    if (m_Profiles.contains(name)) {
        const auto& p = m_Profiles[name];
        map["name"] = p.name;
        map["width"] = p.width;
        map["height"] = p.height;
        map["fps"] = p.fps;
        map["bitrateKbps"] = p.bitrateKbps;
        map["useVirtualDisplay"] = p.useVirtualDisplay;
        map["resolutionScaleFactor"] = p.resolutionScaleFactor;
        map["enableHdr"] = p.enableHdr;
        map["ultraLowLatency"] = p.ultraLowLatency;
    }
    return map;
}

bool ProfileManager::applyProfile(const QString& name) {
    if (!m_Profiles.contains(name)) {
        return false;
    }

    const auto& p = m_Profiles[name];
    m_ActiveProfileName = name;

    StreamingPreferences* prefs = StreamingPreferences::get();
    if (prefs) {
        prefs->width = p.width;
        prefs->height = p.height;
        prefs->fps = p.fps;
        prefs->bitrateKbps = p.bitrateKbps;
        prefs->useVirtualDisplay = p.useVirtualDisplay;
        prefs->resolutionScaleFactor = p.resolutionScaleFactor;
        prefs->enableHdr = p.enableHdr;
        prefs->ultraLowLatency = p.ultraLowLatency;
        prefs->save();

        emit prefs->displayModeChanged();
        emit prefs->bitrateChanged();
        emit prefs->useVirtualDisplayChanged();
        emit prefs->resolutionScaleFactorChanged();
        emit prefs->enableHdrChanged();
        emit prefs->ultraLowLatencyChanged();
    }

    saveProfiles();
    emit profileApplied(name);
    emit activeProfileIndexChanged();
    return true;
}

QString ProfileManager::getActiveProfileName() const {
    return m_ActiveProfileName;
}

void ProfileManager::setActiveProfileName(const QString& name) {
    if (m_ActiveProfileName != name) {
        applyProfile(name);
    }
}

int ProfileManager::getActiveProfileIndex() const {
    QStringList names = getProfileNames();
    int idx = names.indexOf(m_ActiveProfileName);
    return (idx >= 0) ? idx : 0;
}

void ProfileManager::setActiveProfileIndex(int index) {
    QStringList names = getProfileNames();
    if (index >= 0 && index < names.size()) {
        applyProfile(names.at(index));
    }
}

bool ProfileManager::applyProfileIndex(int index) {
    QStringList names = getProfileNames();
    if (index >= 0 && index < names.size()) {
        return applyProfile(names.at(index));
    }
    return false;
}

bool ProfileManager::saveProfile(const QString& name, int width, int height, int fps, int bitrateKbps, bool useVirtualDisplay, int scaleFactor, bool enableHdr) {
    if (name.trimmed().isEmpty()) {
        return false;
    }

    StreamProfile p;
    p.name = name.trimmed();
    p.width = (width > 0) ? width : 1920;
    p.height = (height > 0) ? height : 1080;
    p.fps = (fps > 0) ? fps : 60;
    p.bitrateKbps = (bitrateKbps > 0) ? bitrateKbps : 20000;
    p.useVirtualDisplay = useVirtualDisplay;
    p.resolutionScaleFactor = scaleFactor;
    p.enableHdr = enableHdr;
    p.ultraLowLatency = false;

    m_Profiles[p.name] = p;
    m_ActiveProfileName = p.name;
    saveProfiles();
    emit profilesChanged();
    return true;
}

bool ProfileManager::deleteProfile(const QString& name) {
    if (m_Profiles.contains(name) && m_Profiles.size() > 1) {
        m_Profiles.remove(name);
        if (m_ActiveProfileName == name) {
            m_ActiveProfileName = m_Profiles.firstKey();
            applyProfile(m_ActiveProfileName);
        }
        saveProfiles();
        emit profilesChanged();
        return true;
    }
    return false;
}

void ProfileManager::setCustomResolution(int width, int height, int fps) {
    StreamingPreferences* prefs = StreamingPreferences::get();
    if (prefs) {
        if (width > 0) prefs->width = width;
        if (height > 0) prefs->height = height;
        if (fps > 0) prefs->fps = fps;
        prefs->save();
        emit prefs->displayModeChanged();
    }
}

} // namespace vibeartemis
