#include <array>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

namespace {
constexpr std::size_t order = 15896;
constexpr std::size_t row_bytes = order / 8;
constexpr std::size_t row_words = (row_bytes + 7) / 8;
using Row = std::array<std::uint64_t, row_words>;
}

int main() {
    std::vector<Row> rows(order, Row{});
    std::array<unsigned char, row_bytes> packed{};
    for (std::size_t i = 0; i < order; ++i) {
        if (std::fread(packed.data(), 1, packed.size(), stdin) != packed.size()) {
            std::fprintf(stderr, "Short or unreadable input at row %zu\n", i + 1);
            return 1;
        }
        // A common permutation of bit positions preserves every XOR weight.
        // Copy bytes directly and leave the unused bits in the last word zero.
        std::memcpy(rows[i].data(), packed.data(), packed.size());
    }
    if (std::fgetc(stdin) != EOF || std::ferror(stdin)) {
        std::fputs("Trailing data or input error\n", stderr);
        return 1;
    }

    // Each of the order packed bits denotes one sign. Its square is 1,
    // so every diagonal entry of the row Gram matrix is order.
    std::uint64_t pairs = 0;
    for (std::size_t i = 0; i < order; ++i) {
        for (std::size_t j = 0; j < i; ++j) {
            unsigned distance = 0;
            for (std::size_t k = 0; k < row_words; ++k) {
                distance += __builtin_popcountll(rows[i][k] ^ rows[j][k]);
            }
            if (distance != order / 2) {
                std::fprintf(stderr,
                             "Rows %zu and %zu have distance %u, expected %zu\n",
                             j + 1, i + 1, distance, order / 2);
                return 1;
            }
            ++pairs;
        }
    }
    std::printf("PASS order=%zu bytes=%zu diagonal_entries=%zu diagonal=%zu "
                "pairs=%" PRIu64 " distance=%zu\n",
                order, order * row_bytes, order, order, pairs, order / 2);
}
