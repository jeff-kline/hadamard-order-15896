// Check the complex row Gram exactly for Zaitsev's text encoding.
// In (1+i) times a row, store both sign planes as bitsets.
#include <cstdint>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
using Word = std::uint64_t;
struct Row { std::vector<Word> real, imag; };
int distance(const std::vector<Word>& a, const std::vector<Word>& b) {
    int d = 0;
    for (std::size_t k = 0; k < a.size(); ++k)
        d += __builtin_popcountll(a[k] ^ b[k]);
    return d;
}
int main(int argc, char** argv) {
    if (argc != 3) return 2;
    const int n = std::stoi(argv[1]);
    if (n <= 0 || n > 10000) return 2;
    std::ifstream input(argv[2]);
    std::vector<Row> rows;
    std::string s;
    while (input >> s) {
        if (s.size() != static_cast<std::size_t>(n) || rows.size() >= s.size()) return 1;
        Row r;
        r.real.resize((n+63)/64);
        r.imag.resize((n+63)/64);
        for (int k = 0; k < n; ++k) {
            const char ch = s[k];
            if (ch != '1' && ch != '-' && ch != 'i' && ch != 'j') return 1;
            const Word bit = Word(1) << (k%64);
            if (ch == '-' || ch == 'i') r.real[k/64] |= bit;
            if (ch == '-' || ch == 'j') r.imag[k/64] |= bit;
        }
        for (const auto& u : rows) {
            if (distance(r.real, u.real) + distance(r.imag, u.imag) != n ||
                distance(r.imag, u.real) != distance(r.real, u.imag)) return 1;
        }
        rows.push_back(std::move(r));
    }
    if (rows.size() != static_cast<std::size_t>(n) || !input.eof()) return 1;
    std::cout << "BH(" << n << ",4) full Hermitian Gram PASS, "
              << n*(n-1)/2 << " distinct row pairs\n";
}
