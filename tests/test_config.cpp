#include "src/core/config.h"
#include <iostream>
#include <cassert>
#include <filesystem>

void testDefaultConfig() {
    std::cout << "[TEST] Running testDefaultConfig..." << std::endl;
    auto config = vibeartemis::ConfigManager::instance().getConfig();
    assert(config.video.width == 1920);
    assert(config.video.height == 1080);
    assert(config.video.fps == 60);
    assert(config.video.bitrateKbps == 20000);
    assert(config.video.scaleMode == vibeartemis::ScaleMode::Fit);
    assert(config.apollo.smartClipboardSync == true);
    assert(config.apollo.enableServerCommands == true);
    std::cout << "  ✓ Default configuration verified" << std::endl;
}

void testConfigSerializationRoundtrip() {
    std::cout << "[TEST] Running testConfigSerializationRoundtrip..." << std::endl;
    std::filesystem::path testPath = std::filesystem::temp_directory_path() / "vibeartemis_test_config.json";

    auto& mgr = vibeartemis::ConfigManager::instance();
    auto config = mgr.getConfig();
    config.video.width = 3440;
    config.video.height = 1440;
    config.video.fps = 144;
    config.video.bitrateKbps = 80000;
    config.video.scaleMode = vibeartemis::ScaleMode::Fill;
    config.video.scaleFactor = 1.25f;
    config.apollo.customRefreshRate = 144;

    mgr.setConfig(config);
    bool saved = mgr.save(testPath);
    assert(saved);

    // Reset and reload
    mgr.setConfig(vibeartemis::ClientConfig{});
    bool loaded = mgr.load(testPath);
    assert(loaded);

    auto loadedConfig = mgr.getConfig();
    assert(loadedConfig.video.width == 3440);
    assert(loadedConfig.video.height == 1440);
    assert(loadedConfig.video.fps == 144);
    assert(loadedConfig.video.bitrateKbps == 80000);
    assert(loadedConfig.video.scaleMode == vibeartemis::ScaleMode::Fill);
    assert(std::abs(loadedConfig.video.scaleFactor - 1.25f) < 0.01f);
    assert(loadedConfig.apollo.customRefreshRate == 144);

    std::filesystem::remove(testPath);
    std::cout << "  ✓ Config JSON save/load roundtrip verified" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  VibeArtemis: Config Manager Tests     " << std::endl;
    std::cout << "========================================" << std::endl;

    testDefaultConfig();
    testConfigSerializationRoundtrip();

    std::cout << "\n>>> ALL CONFIG TESTS PASSED! <<<\n" << std::endl;
    return 0;
}
