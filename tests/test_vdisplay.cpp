#include "app/backend/vdisplay_manager.h"
#include <iostream>
#include <cassert>
#include <cmath>

void testStandard1080p() {
    std::cout << "[TEST] Running testStandard1080p..." << std::endl;
    auto geom = vibeartemis::VirtualDisplayManager::calculateTargetResolution(1920, 1080, 60, 1.0f);
    assert(geom.width == 1920);
    assert(geom.height == 1080);
    assert(geom.refreshRate == 60);
    assert(!geom.isUltrawide);
    std::cout << "  ✓ 1080p 60Hz calculated: " << geom.width << "x" << geom.height << "@" << geom.refreshRate << std::endl;
}

void testHighRefreshRateScaleFactor() {
    std::cout << "[TEST] Running testHighRefreshRateScaleFactor..." << std::endl;
    auto geom = vibeartemis::VirtualDisplayManager::calculateTargetResolution(2560, 1440, 165, 1.2f);
    assert(geom.width == 3072);
    assert(geom.height == 1728);
    assert(geom.refreshRate == 165);
    std::cout << "  ✓ 1440p @ 1.2x scale calculated: " << geom.width << "x" << geom.height << "@" << geom.refreshRate << std::endl;
}

void testUltrawideDetection() {
    std::cout << "[TEST] Running testUltrawideDetection..." << std::endl;
    assert(vibeartemis::VirtualDisplayManager::isUltrawideAspectRatio(3440, 1440) == true);
    assert(vibeartemis::VirtualDisplayManager::isUltrawideAspectRatio(5120, 1440) == true);
    assert(vibeartemis::VirtualDisplayManager::isUltrawideAspectRatio(1920, 1080) == false);
    assert(vibeartemis::VirtualDisplayManager::isUltrawideAspectRatio(2560, 1600) == false);
    std::cout << "  ✓ Ultrawide aspect ratio detection verified" << std::endl;
}

void testLaunchQueryParameters() {
    std::cout << "[TEST] Running testLaunchQueryParameters..." << std::endl;
    vibeartemis::DisplayGeometry geom;
    geom.width = 2560;
    geom.height = 1440;
    geom.refreshRate = 144;
    geom.scaleFactor = 1.2f;

    std::string params = vibeartemis::VirtualDisplayManager::buildLaunchQueryParametersStd(geom, true, 1.2f);
    assert(params.find("&vdisplay=1") != std::string::npos);
    assert(params.find("&vdisplay_res=2560x1440") != std::string::npos);
    assert(params.find("&vdisplay_fps=144") != std::string::npos);
    assert(params.find("&vdisplay_scale=1.20") != std::string::npos);
    std::cout << "  ✓ Query params string generated: " << params << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  VibeArtemis: Virtual Display Tests    " << std::endl;
    std::cout << "========================================" << std::endl;

    testStandard1080p();
    testHighRefreshRateScaleFactor();
    testUltrawideDetection();
    testLaunchQueryParameters();

    std::cout << "\n>>> ALL VIRTUAL DISPLAY TESTS PASSED! <<<\n" << std::endl;
    return 0;
}
