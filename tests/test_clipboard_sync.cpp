#include <iostream>
#include <cassert>
#include <string>
#include <cstdint>

uint64_t hashString(const std::string& str) {
    uint64_t hash = 14695981039346656037ULL;
    for (char c : str) {
        hash ^= static_cast<uint8_t>(c);
        hash *= 1099511628211ULL;
    }
    return hash;
}

void testHashComputation() {
    std::cout << "[TEST] Running testHashComputation..." << std::endl;
    std::string text1 = "Hello Apollo Host!";
    std::string text2 = "Hello Apollo Host!";
    std::string text3 = "Different Text";

    uint64_t h1 = hashString(text1);
    uint64_t h2 = hashString(text2);
    uint64_t h3 = hashString(text3);

    assert(h1 == h2);
    assert(h1 != h3);
    std::cout << "  ✓ FNV text hashing deterministic and distinct" << std::endl;
}

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << "  VibeArtemis: Clipboard Sync Tests     " << std::endl;
    std::cout << "========================================" << std::endl;

    testHashComputation();

    std::cout << "\n>>> ALL CLIPBOARD SYNC TESTS PASSED! <<<\n" << std::endl;
    return 0;
}
