// Build H(15896) from Turyn WT(331), the paired Cooper-Wallis T(3) design,
// and the conference transfer of Theorem 1 in the order-4792 release.
//
// c++ -std=c++17 -O3 build.cpp -o build
// ./build H15896.packed
//
// Output: 15896 rows of 1987 bytes. The high bit comes first in each byte.
// A set bit encodes -1, and a clear bit encodes +1.

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace {

constexpr int q = 661;
constexpr int w = (q + 1) / 2;
constexpr int tile_order = 6 * w;
constexpr int m = tile_order + 1;
constexpr int n = (m - 1) / 2;
constexpr int order = 8 * m;
constexpr int h2[2][2]{{1, 1}, {1, -1}};
static_assert(order == 15896);

using Line = std::array<int, w>;
using Quadruple = std::array<Line, 4>;
using Design = std::array<std::array<int, 12>, 12>;
using Border = std::array<std::array<int, 8>, 8>;
using Tile = std::array<std::array<std::int8_t, 2>, 2>;

void require(bool condition, const char* message) {
    if (!condition) throw std::runtime_error(message);
}

int mod(int value, int modulus) {
    const int remainder = value % modulus;
    return remainder < 0 ? remainder + modulus : remainder;
}

bool is_prime(int value) {
    if (value < 2) return false;
    for (int d = 2; d <= value / d; ++d)
        if (value % d == 0) return false;
    return true;
}

// The quadratic field is F_q[x]/(x^2 - 2).
using FieldElement = std::array<int, 2>;

FieldElement multiply(FieldElement a, FieldElement b) {
    return {mod(a[0] * b[0] + 2 * a[1] * b[1], q),
            mod(a[0] * b[1] + a[1] * b[0], q)};
}

FieldElement power(FieldElement base, int exponent) {
    FieldElement result{1, 0};
    while (exponent != 0) {
        if (exponent % 2 != 0) result = multiply(result, base);
        base = multiply(base, base);
        exponent /= 2;
    }
    return result;
}

Quadruple turyn() {
    require(is_prime(q) && q % 4 == 1, "invalid Turyn prime");
    require(power({2, 0}, (q - 1) / 2) == FieldElement{q - 1, 0}, "2 must be a nonsquare");
    constexpr FieldElement generator{2, 1};
    constexpr FieldElement one{1, 0};
    constexpr int group_order = q * q - 1;
    static_assert(group_order == 8 * 3 * 5 * 11 * 331);
    require(power(generator, group_order) == one, "wrong generator group order");
    for (int prime : {2, 3, 5, 11, 331}) {
        require(is_prime(prime), "wrong prime divisor of the group order");
        require(power(generator, group_order / prime) != one, "generator is not primitive");
    }
    const FieldElement inverse_delta = power(generator, group_order - w);
    Line r{}, s{};
    for (int j = 0; j <= q; ++j) {
        // Character of the alternating form on (1, g^j), scaled by delta=g^w.
        const auto point = power(generator, j);
        const auto conjugate = power(point, q);
        const auto ratio = multiply({conjugate[0] - point[0], conjugate[1] - point[1]}, inverse_delta);
        require(ratio[1] == 0, "character argument outside the base field");
        const int character = ratio[0] == 0 ? 0 : (power(ratio, (q - 1) / 2) == one ? 1 : -1);
        (j % 2 == 0 ? r : s)[j / 2] = (j / 2 % 2 == 0 ? 1 : -1) * character;
    }

    // Recenter the odd orbit to make its circulant symmetric.
    int center = 0;
    for (; center < w; ++center) {
        bool symmetric = true;
        for (int k = 0; k < w; ++k)
            if (s[(center + k) % w] != s[mod(center - k, w)]) symmetric = false;
        if (symmetric) break;
    }
    require(center < w && r[0] == 0, "invalid Turyn circulant rows");
    std::rotate(s.begin(), s.begin() + center, s.end());
    Quadruple factors{s, s, r, r};
    factors[2][0] = 1;
    factors[3][0] = -1;

    // Circulants commute and symmetric circulants are therefore amicable.
    // Their summed Gram is circulant, so checking its first row suffices.
    for (int shift = 0; shift < w; ++shift) {
        int sum = 0;
        for (const auto& factor : factors) {
            require(std::abs(factor[shift]) == 1, "Williamson factor is not a sign matrix");
            require(factor[shift] == factor[mod(-shift, w)], "Williamson factor is not symmetric");
            for (int k = 0; k < w; ++k) sum += factor[k] * factor[(k + shift) % w];
        }
        require(sum == (shift == 0 ? 4 * w : 0), "Williamson summed Gram");
    }
    std::cout << "Turyn WT(" << w << "): q=" << q << ", center=" << center
              << ", symmetric sign circulants and exact summed Gram\n";
    return factors;
}

constexpr int row_pairs[6][2]{{0, 4}, {1, 10}, {2, 7}, {3, 5}, {6, 8}, {9, 11}};
constexpr int col_pairs[6][2]{{1, 10}, {3, 2}, {4, 7}, {6, 9}, {8, 0}, {11, 5}};

Design paired_design() {
    // The circulants A,B,C,D have first rows 100,010,001,000. A signed
    // block number encodes one input of the Goethals-Seidel array.
    constexpr int inputs[4][4]{{1, 2, 3, 4}, {2, -1, 4, -3},
                               {3, -4, -1, 2}, {4, 3, -2, -1}};
    constexpr int blocks[4][4]{{1, 2, 3, 4}, {-2, 1, -4, 3},
                               {-3, 4, 1, -2}, {-4, -3, 2, 1}};
    Design design{};
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            const int row_block = i / 3, col_block = j / 3;
            const int x = i % 3, y = j % 3;
            const int block = blocks[row_block][col_block];
            int offset = y - x;
            if (row_block != col_block) {
                // Right multiplication by the reversal, with transpose
                // for the off-diagonal blocks outside block row/column 0.
                offset = 2 - y - x;
                if (row_block != 0 && col_block != 0) offset = -offset;
            }
            for (int factor = 0; factor < 4; ++factor) {
                const int input = inputs[factor][std::abs(block) - 1];
                if (std::abs(input) - 1 != mod(offset, 3)) continue;
                require(design[i][j] == 0, "overlapping design supports");
                design[i][j] = (block * input < 0 ? -1 : 1) * (factor + 1);
            }
            require(design[i][j] != 0, "uncovered design coordinate");
        }
    }

    // Coefficients in the formal Gram of the design, with commuting variables.
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j <= i; ++j) {
            int coefficient[4][4]{};
            for (int k = 0; k < 12; ++k) {
                const int a = design[i][k], b = design[j][k];
                const int x = std::abs(a) - 1, y = std::abs(b) - 1;
                coefficient[std::min(x, y)][std::max(x, y)] += a * b < 0 ? -1 : 1;
            }
            for (int x = 0; x < 4; ++x)
                for (int y = x; y < 4; ++y)
                    require(coefficient[x][y] == (i == j && x == y ? 3 : 0), "design formal Gram");
        }
    }
    for (const auto* pairs : {row_pairs, col_pairs}) {
        int seen[12]{};
        for (int i = 0; i < 6; ++i)
            for (int j : pairs[i]) {
                require(j >= 0 && j < 12, "pair index outside the design");
                ++seen[j];
            }
        for (int count : seen) require(count == 1, "pairs must partition their axis");
    }
    for (const auto& rows : row_pairs) {
        for (const auto& columns : col_pairs) {
            int sign = 1, parity = 0;
            for (int i : rows) {
                for (int j : columns) {
                    const int label = design[i][j];
                    sign *= label < 0 ? -1 : 1;
                    parity ^= 1 << (std::abs(label) - 1);
                }
            }
            require(sign == -1 && parity == 0, "design tile sign or parity");
        }
    }
    std::cout << "T(3) design: formal Gram, pair partitions, and all 36 formal tiles verified\n";
    return design;
}

struct TransferTiles {
    std::vector<Tile> f, switched;
};

TransferTiles expand(const Design& design, const Quadruple& factors) {
    TransferTiles result{std::vector<Tile>(tile_order * tile_order),
                         std::vector<Tile>(tile_order * tile_order)};
    std::uint64_t reflection_count = 0;
    for (int x = 0; x < tile_order; ++x) {
        for (int y = 0; y < tile_order; ++y) {
            auto& tile = result.f[x * tile_order + y];
            auto& switched = result.switched[y * tile_order + x];
            const int shift = mod(y % w - x % w, w);
            int product = 1;
            for (int h = 0; h < 2; ++h) {
                for (int k = 0; k < 2; ++k) {
                    const int label = design[row_pairs[x / w][h]][col_pairs[y / w][k]];
                    const int value = (label < 0 ? -1 : 1) * factors[std::abs(label) - 1][shift];
                    tile[h][k] = static_cast<std::int8_t>(value);
                    product *= value;
                }
            }
            require(product == -1, "substituted sign tile");
            // P=T H2/2 has determinant the negative of det(T)/2.
            const int determinant = tile[0][0] * tile[1][1] - tile[0][1] * tile[1][0];
            if (determinant == 2) ++reflection_count;

            // F' = -(D F D / 2)^T, with D=I tensor H2. Swap both the tile
            // indices and the two scalar indices for the transpose.
            for (int h = 0; h < 2; ++h) {
                for (int k = 0; k < 2; ++k) {
                    int value = 0;
                    for (int a = 0; a < 2; ++a)
                        for (int b = 0; b < 2; ++b)
                            value -= h2[h][a] * tile[a][b] * h2[b][k];
                    require(std::abs(value) == 2, "switched tile is not a sign tile");
                    switched[k][h] = static_cast<std::int8_t>(value / 2);
                }
            }
        }
    }
    std::cout << "Paired H(" << 2 * tile_order << "): all " << tile_order * tile_order
              << " tiles have sign product -1, giving " << reflection_count
              << " reflections after right multiplication by H2/2\n";
    return result;
}

std::vector<std::int8_t> paley_core() {
    require(is_prime(m) && m % 4 == 3, "invalid skew Paley prime");
    std::array<int, m> chi{};
    chi.fill(-1);
    chi[0] = 0;
    for (int x = 1; x < m; ++x) chi[x * x % m] = 1;
    int sum = 0;
    for (int x = 0; x < m; ++x) sum += chi[x];
    require(sum == 0, "Paley core does not have zero row sum");
    // The bordered conference has off-diagonal Gram zero if each nonzero
    // periodic autocorrelation of chi is -1.
    for (int j = 0; j < m; ++j) {
        require(chi[j] == -chi[mod(-j, m)], "Paley core is not skew");
        int correlation = 0;
        for (int k = 0; k < m; ++k) correlation += chi[k] * chi[(k + j) % m];
        require(correlation == (j == 0 ? m - 1 : -1), "Paley conference Gram");
    }
    std::vector<int> points;
    for (int sign : {1, -1}) {
        for (int x = 1; x < m; ++x)
            if (chi[x] == sign) points.push_back(x);
        require(points.size() == (sign == 1 ? n : 2 * n), "Paley half size");
    }
    std::vector<std::int8_t> core(tile_order * tile_order);
    for (int x = 0; x < tile_order; ++x)
        for (int y = 0; y < tile_order; ++y)
            core[x * tile_order + y] = static_cast<std::int8_t>(chi[mod(points[y] - points[x], m)]);
    std::cout << "Paley C(" << m + 1 << "): skew and exact conference Gram verified\n";
    return core;
}

struct Borders {
    Border corner, top, left;
};

Borders make_borders(const std::vector<std::int8_t>& core) {
    int sums[2][2]{};
    for (int x = 0; x < tile_order; ++x) {
        for (int s = 0; s < 2; ++s) {
            int total = 0;
            for (int j = 0; j < n; ++j) total += core[x * tile_order + s * n + j];
            if (x % n == 0) sums[x / n][s] = total;
            require(total == sums[x / n][s], "nonconstant Paley half sum");
        }
    }

    Borders borders{};
    Border k{}, sigma{};
    // Strand index is 4*s + 2*h + c, where c labels the copy.
    for (int i = 0; i < 8; ++i) {
        const int s = i / 4, h = i / 2 % 2, c = i % 2;
        for (int j = 0; j < 8; ++j) {
            const int ss = j / 4, hh = j / 2 % 2, cc = j % 2;
            // The corrected border R, with row i interpreted as 4*u+a.
            borders.top[i][j] = h2[i / 4][hh] * (i % 4 == 2 * ss + cc ? -1 : 1);
            k[i][j] = h == hh ? h2[s][ss] * h2[c][cc] : 0;
            sigma[i][j] = c == cc ? sums[s][ss] * h2[h][hh] : 0;
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            for (int p = 0; p < 8; ++p) {
                borders.corner[i][j] += borders.top[i][p] * k[p][j];
                borders.left[i][j] -= sigma[i][p] * k[p][j];
            }
            require(std::abs(borders.corner[i][j]) == 2, "invalid corner sign");
            require(std::abs(borders.left[i][j]) == 1, "invalid left border sign");
            borders.corner[i][j] /= 2;
        }
    }
    return borders;
}

using Row = std::array<std::int8_t, order>;

void write_row(std::ofstream& file, const Row& row) {
    std::array<unsigned char, m> packed{};
    for (int j = 0; j < m; ++j) {
        unsigned int byte = 0;
        for (int b = 0; b < 8; ++b) {
            const int entry = row[8 * j + b];
            require(std::abs(entry) == 1, "non-sign entry in output row");
            byte = (byte << 1) | (entry < 0);
        }
        packed[j] = static_cast<unsigned char>(byte);
    }
    file.write(reinterpret_cast<const char*>(packed.data()), packed.size());
}

void transfer(const TransferTiles& tiles, const std::vector<std::int8_t>& core, const char* path) {
    const auto borders = make_borders(core);
    std::ofstream file(path, std::ios::binary);
    require(file.good(), "cannot open output file");
    Row row0{}, row1{};
    for (int i = 0; i < 8; ++i) {
        std::copy(borders.corner[i].begin(), borders.corner[i].end(), row0.begin());
        for (int strand = 0; strand < 8; ++strand)
            std::fill_n(row0.begin() + 8 + strand * 2 * n, 2 * n, borders.top[i][strand]);
        write_row(file, row0);
    }

    struct StrandIndex { int point, h, copy; };
    std::vector<StrandIndex> index;
    for (int s = 0; s < 2; ++s)
        for (int h = 0; h < 2; ++h)
            for (int copy = 0; copy < 2; ++copy)
                for (int t = 0; t < n; ++t) index.push_back({s * n + t, h, copy});

    for (int i = 0; i < 8 * n; ++i) {
        const auto [x, h, copy] = index[i];
        std::copy(borders.left[i / n].begin(), borders.left[i / n].end(), row0.begin());
        std::copy_n(row0.begin(), 8, row1.begin());
        for (int j = 0; j < 8 * n; ++j) {
            const auto [y, k, other_copy] = index[j];
            const int position = x * tile_order + y;
            // U and V have complementary supports. The final 2-by-2 cell
            // is either U*J2 (constant) or V*[[1,-1],[-1,1]].
            int diagonal;
            if (copy == other_copy) {
                diagonal = x == y ? h2[h][k] : core[position] * h2[h][k];
            } else {
                const auto& blocks = copy == 0 ? tiles.f : tiles.switched;
                diagonal = blocks[position][h][k];
            }
            const int crossed = copy == other_copy && x != y ? diagonal : -diagonal;
            row0[8 + 2 * j] = row1[9 + 2 * j] = static_cast<std::int8_t>(diagonal);
            row0[9 + 2 * j] = row1[8 + 2 * j] = static_cast<std::int8_t>(crossed);
        }
        write_row(file, row0);
        write_row(file, row1);
    }
    file.close();
    require(file.good(), "failed to write output file");
    std::cout << "H(" << order << "): wrote " << order * m << " packed bytes\n";
}

}  // namespace

int main(int argc, char** argv) {
    try {
        require(argc == 2, "usage: build H15896.packed");
        const auto factors = turyn();
        const auto design = paired_design();
        const auto tiles = expand(design, factors);
        const auto core = paley_core();
        transfer(tiles, core, argv[1]);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
