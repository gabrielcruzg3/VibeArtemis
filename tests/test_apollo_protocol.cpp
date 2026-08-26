#include <iostream>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <string>

extern "C" {
#include "Limelight.h"
}

void testServerCommandOpcode() {
    std::cout << "[TEST] Running testServerCommandOpcode..." << std::endl;
    // Verify Apollo Server Command function returns error gracefully when not connected rather than crashing
    int res = LiSendExecServerCmd(1);
    assert(res != 0);
    std::cout << "  ✓ LiSendExecServerCmd handled offline state cleanly (res = " << res << ")" << std::endl;
}

void testEmptyPayloadOpcode() {
    std::cout << "[TEST] Running testEmptyPayloadOpcode..." << std::endl;
    int res = LiSendEmptyPayload();
    assert(res != 0);
    std::cout << "  ✓ LiSendEmptyPayload handled offline state cleanly (res = " << res << ")" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  VibeArtemis: Apollo Protocol Tests    " << std::endl;
    std::cout << "========================================" << std::endl;

    testServerCommandOpcode();
    testEmptyPayloadOpcode();

    std::cout << "\n>>> ALL APOLLO PROTOCOL TESTS PASSED! <<<\n" << std::endl;
    return 0;
}
