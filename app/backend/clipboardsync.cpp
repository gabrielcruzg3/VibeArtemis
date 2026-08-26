#include "app/backend/clipboardsync.h"
#include "app/backend/nvhttp.h"
#include <QDebug>

namespace vibeartemis {

uint64_t ClipboardSyncManager::hashString(const QString& str) {
    uint64_t hash = 14695981039346656037ULL;
    QByteArray bytes = str.toUtf8();
    for (char c : bytes) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ULL;
    }
    return hash;
}

ClipboardSyncManager::ClipboardSyncManager(QObject* parent) : QObject(parent) {
    connect(&m_PollTimer, &QTimer::timeout, this, &ClipboardSyncManager::onPollTimer);
    QClipboard* cb = QGuiApplication::clipboard();
    if (cb) {
        connect(cb, &QClipboard::changed, this, &ClipboardSyncManager::onLocalClipboardChanged);
    }
}

ClipboardSyncManager::~ClipboardSyncManager() {
    stopSync();
}

void ClipboardSyncManager::setHttp(NvHTTP* http) {
    m_Http = http;
}

void ClipboardSyncManager::startSync(int pollIntervalMs) {
    if (m_IsSyncing.load()) return;
    m_IsSyncing.store(true);
    m_PollTimer.start(pollIntervalMs);
    qInfo() << "[ClipboardSync] Started bidirectional clipboard synchronization (Interval:" << pollIntervalMs << "ms)";
}

void ClipboardSyncManager::stopSync() {
    if (!m_IsSyncing.load()) return;
    m_PollTimer.stop();
    m_IsSyncing.store(false);
    qInfo() << "[ClipboardSync] Stopped clipboard synchronization";
}

bool ClipboardSyncManager::isSyncing() const {
    return m_IsSyncing.load();
}

void ClipboardSyncManager::onPollTimer() {
    if (!m_IsSyncing.load() || !m_Http) return;
    triggerFetchClipboard();
}

void ClipboardSyncManager::onLocalClipboardChanged(QClipboard::Mode mode) {
    if (mode != QClipboard::Clipboard || !m_IsSyncing.load() || !m_Http) return;
    if (m_SuppressLocalUpdate) {
        m_SuppressLocalUpdate = false;
        return;
    }
    triggerPushClipboard();
}

void ClipboardSyncManager::triggerPushClipboard() {
    if (!m_Http) return;
    QClipboard* cb = QGuiApplication::clipboard();
    if (!cb) return;

    QString text = cb->text(QClipboard::Clipboard);
    if (text.isEmpty()) return;

    uint64_t hash = hashString(text);
    if (hash == m_LastLocalHash || hash == m_LastRemoteHash) return;

    m_LastLocalHash = hash;
    try {
        m_Http->uploadClipboard(text);
        emit clipboardSyncNotification(QString("Uploaded clipboard to host (%1 chars)").arg(text.length()));
    } catch (...) {
        // Host might not be Apollo or endpoint not available
    }
}

void ClipboardSyncManager::triggerFetchClipboard() {
    if (!m_Http) return;
    try {
        QString text = m_Http->fetchClipboard();
        if (text.isEmpty()) return;

        uint64_t hash = hashString(text);
        if (hash == m_LastRemoteHash || hash == m_LastLocalHash) return;

        m_LastRemoteHash = hash;
        QClipboard* cb = QGuiApplication::clipboard();
        if (cb) {
            m_SuppressLocalUpdate = true;
            cb->setText(text, QClipboard::Clipboard);
            emit clipboardSyncNotification(QString("Fetched clipboard from host (%1 chars)").arg(text.length()));
        }
    } catch (...) {
        // Ignored if host endpoint unsupported
    }
}

} // namespace vibeartemis
