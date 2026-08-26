#pragma once

#include <string>
#include <cstdint>

#ifdef QT_CORE_LIB
#include <QString>
#endif

namespace vibeartemis {

struct DisplayGeometry {
    int width{1920};
    int height{1080};
    int refreshRate{60};
    double aspectRatio{16.0 / 9.0};
    float scaleFactor{1.0f};
    bool isUltrawide{false};
};

class VirtualDisplayManager {
public:
    static DisplayGeometry calculateTargetResolution(int clientWidth, int clientHeight, int clientFps, float scaleFactor = 1.0f);
    static std::string buildLaunchQueryParametersStd(const DisplayGeometry& geom, bool enableVirtualDisplay = true, float scaleFactor = 1.0f);
    static bool isUltrawideAspectRatio(int width, int height);

#ifdef QT_CORE_LIB
    static QString buildLaunchQueryParameters(const DisplayGeometry& geom, bool enableVirtualDisplay = true, float scaleFactor = 1.0f) {
        return QString::fromStdString(buildLaunchQueryParametersStd(geom, enableVirtualDisplay, scaleFactor));
    }
#endif
};

} // namespace vibeartemis
