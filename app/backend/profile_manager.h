#pragma once

#include <QObject>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

namespace vibeartemis {

struct StreamProfile {
    QString name;
    int width{1920};
    int height{1080};
    int fps{60};
    int bitrateKbps{20000};
    bool useVirtualDisplay{true};
    int resolutionScaleFactor{100};
    bool enableHdr{false};
    bool ultraLowLatency{false};
};

class ProfileManager : public QObject {
    Q_OBJECT

public:
    static ProfileManager* instance();

    Q_INVOKABLE QStringList getProfileNames() const;
    Q_INVOKABLE QVariantMap getProfile(const QString& name) const;
    Q_INVOKABLE bool applyProfile(const QString& name);
    Q_INVOKABLE bool saveProfile(const QString& name, int width, int height, int fps, int bitrateKbps, bool useVirtualDisplay = true, int scaleFactor = 100, bool enableHdr = false);
    Q_INVOKABLE bool deleteProfile(const QString& name);
    Q_INVOKABLE void setCustomResolution(int width, int height, int fps);

signals:
    void profilesChanged();
    void profileApplied(const QString& name);

private:
    explicit ProfileManager(QObject* parent = nullptr);
    void loadProfiles();
    void saveProfiles();
    void initDefaultProfiles();
    QString getProfilesFilePath() const;

    QMap<QString, StreamProfile> m_Profiles;
    QString m_ActiveProfileName{"Default (1080p 60 FPS)"};
};

} // namespace vibeartemis
