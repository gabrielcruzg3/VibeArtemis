#include "backend/vdisplay_manager.h"
#include <cmath>
#include <sstream>
#include <iomanip>

namespace vibeartemis {

bool VirtualDisplayManager::isUltrawideAspectRatio(int width, int height) {
    if (height <= 0) return false;
    double ratio = static_cast<double>(width) / static_cast<double>(height);
    return ratio > (16.0 / 9.0 + 0.1);
}

DisplayGeometry VirtualDisplayManager::calculateTargetResolution(int clientWidth, int clientHeight, int clientFps, float scaleFactor) {
    DisplayGeometry geom;
    if (clientWidth <= 0) clientWidth = 1920;
    if (clientHeight <= 0) clientHeight = 1080;
    if (clientFps <= 0) clientFps = 60;
    if (scaleFactor <= 0.1f) scaleFactor = 1.0f;

    int targetW = static_cast<int>(std::round(clientWidth * scaleFactor));
    int targetH = static_cast<int>(std::round(clientHeight * scaleFactor));

    // Align to 2-pixel boundaries for encoder compatibility
    if (targetW % 2 != 0) targetW += 1;
    if (targetH % 2 != 0) targetH += 1;

    geom.width = targetW;
    geom.height = targetH;
    geom.refreshRate = clientFps;
    geom.scaleFactor = scaleFactor;
    geom.aspectRatio = static_cast<double>(targetW) / static_cast<double>(targetH);
    geom.isUltrawide = isUltrawideAspectRatio(targetW, targetH);

    return geom;
}

std::string VirtualDisplayManager::buildLaunchQueryParametersStd(const DisplayGeometry& geom, bool enableVirtualDisplay, float scaleFactor) {
    if (!enableVirtualDisplay) {
        return "";
    }

    std::ostringstream ss;
    ss << "&vdisplay=1&vdisplay_res=" << geom.width << "x" << geom.height
       << "&vdisplay_fps=" << geom.refreshRate
       << "&vdisplay_scale=" << std::fixed << std::setprecision(2) << scaleFactor;
    return ss.str();
}

} // namespace vibeartemis
