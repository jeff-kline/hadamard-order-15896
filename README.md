# An infinite family of paired Hadamard matrices from Williamson-type matrices

Jeffery Kline

**Status: version 0.1.0 admitted November 28, 2026 (UTC).** [Tag v0.1.0](https://github.com/jeff-kline/hadamard-order-15896/tree/v0.1.0) · [Version DOI](https://doi.org/10.5281/zenodo.24615122) · [All versions](https://doi.org/10.5281/zenodo.24615121) · [Release record](ADMISSION.md)

Admission records the checks completed under Kline's research standard. Independent expert peer review remains outstanding. [Paper](paper/main.pdf) · [TeX source](paper/main.tex)

Every Williamson-type quadruple of positive odd order $w$ gives a Hadamard matrix of order $12w$ whose rows and columns can be paired into two-by-two Hadamard blocks. We give one pairing of the order-12 Cooper–Wallis design that works for every such quadruple. Turyn’s quadruples give infinitely many distinct paired orders. When a conference matrix of order $6w+2$ exists, the published paired-block construction gives a Hadamard matrix of order $8(6w+1)$. At $w=331$ we construct the matrix of order 15,896 and verify every pair of rows. The theorem also gives orders 18,008, 18,296 and 23,096. We found no earlier construction at these four orders in the sources searched through November 27, 2026.

## What is new

Cooper and Wallis supplied the design. The order-4792 paper showed how to turn a conference matrix and a suitably paired Hadamard matrix into a larger Hadamard matrix. It also gave an order-52 design pairing when two Williamson-type inputs coincide. [Cooper and Wallis](https://doi.org/10.1017/S0004972700045019) · [Order-4792 paper](https://doi.org/10.5281/zenodo.24597897)

- **Principal result.** A fixed pairing in the order-12 design works for every Williamson-type quadruple of positive odd order $w$, including noncirculant examples. Substitution gives a paired Hadamard matrix of order $12w$. A conference matrix of order $6w+2$ then gives a Hadamard matrix of order $8(6w+1)$.
- Turyn's and Spence's families supply four applications. At order 15,896 the release includes a packed sign matrix and a separate verifier that reads those bytes and checks every pair of rows. The other three orders follow from the theorem.

Priority is bounded to the dated literature and repository search. [Prior-art record](audit/PRIOR-ART.md)

## Earlier work

Miyamoto's theorem applies at real order $8n$ when there is a conference matrix of order $n+1$ and a quaternary Hadamard matrix of order $n-1$. Zaitsev supplies the needed quaternary matrices for real orders 12,536 and 14,264. His table lists the order-1,986 quaternary input for real order 15,896 as unknown. The quaternary inputs for the three larger orders lie beyond that table. All four applications here use the paired real input and a Paley conference matrix. [Miyamoto](https://doi.org/10.1016/0097-3165(91)90008-5) · [Zaitsev's table](https://www.cs.uleth.ca/~zaitsevv/quaternary.html) · [Kumar's pinned frontier](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md#L58-L62)

| Hadamard order | Williamson-type order | Source | Paley prime |
|---:|---:|---|---:|
| 15,896 | 331 | Turyn, $q=661$ | 1987 |
| 18,008 | 375 | Spence, $q=5$, $r=3$ | 2251 |
| 18,296 | 381 | Turyn, $q=761$ | 2287 |
| 23,096 | 481 | Turyn, $q=961$ | 2887 |

## Orders below 10,000

The documented inputs give 79 final orders below 10,000, all previously known. The Turyn/Spence and Paley conditions in the paper give 27 of them, and the scalar case adds 56. The full table lists the input and earlier evidence for each order. Order 5,912 overlaps Kumar's October 2026 discovery. His main-branch certificate is dated October 29, four weeks before this note. Order 8,696 was already obtainable by an older construction. [All 79 orders](audit/orders-below-10000.tsv) · [Recent and sporadic comparisons](audit/FINAL-PRIOR-ART.md#small-orders)

## Rebuild and verify

Appendix A of the paper specifies each entry of the order-15,896 matrix and its byte ordering. Run `make verify` here with GCC or Clang in C++17 mode, GNU Make, gzip and shasum. The default flags optimize for the local processor. Use `make verify CXXFLAGS=-O3` on compilers that do not accept `-march=native`. It rebuilds the matrix, compares it byte for byte with the archived certificate, and passes the shipped matrix to the independently written row-pair verifier. Run `make paper` with pdfLaTeX to typeset the note. [Builder](evidence/build.cpp) · [Verifier](evidence/verify.cpp) · [Packed matrix](evidence/H15896.packed.gz) · [Verification record](VERIFICATION.md)

## Role of AI

AI assisted the derivations, the computer verification, the literature search and the exposition under the author's direction. Process-separated AI reviews checked the proofs and certificates; they are not independent expert peer review, and no independent human expert has examined the proofs. The release repository records the sources, the reviews and their dispositions. [Attribution and review ledger](audit/LEDGER.md)

[Citation](CITATION.cff) · [Corrections](CORRECTIONS.md) · [License](LICENSE)
