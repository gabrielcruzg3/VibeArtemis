#pragma once

#include <QObject>
#include <QTimer>
#include <QString>
#include <QClipboard>
#include <QGuiApplication>
#include <atomic>
#include <cstdint>

class NvHTTP;

namespace vibeartemis {

class ClipboardSyncManager : public QObject {
    Q_OBJECT

public:
    explicit ClipboardSyncManager(QObject* parent = nullptr);
    ~ClipboardSyncManager() override;

    void setHttp(NvHTTP* http);
    void startSync(int pollIntervalMs = 1500);
    void stopSync();
    bool isSyncing() const;

    void triggerPushClipboard();
    void triggerFetchClipboard();

signals:
    void clipboardSyncNotification(const QString& message);

private slots:
    void onPollTimer();
    void onLocalClipboardChanged(QClipboard::Mode mode);

private:
    static uint64_t hashString(const QString& str);

    NvHTTP* m_Http{nullptr};
    QTimer m_PollTimer;
    std::atomic<bool> m_IsSyncing{false};
    uint64_t m_LastLocalHash{0};
    uint64_t m_LastRemoteHash{0};
    bool m_SuppressLocalUpdate{false};
};

} // namespace vibeartemis
