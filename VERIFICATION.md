# Verifying order 15,896

Run `make verify` in the root of an extracted copy. It needs GNU Make, a C++17 GCC or Clang compiler, gzip, shasum and standard shell tools. Compilation and verification work offline. The two executables share neither implementation code nor intermediate data. Run `make paper` separately to rebuild the paper using pdfLaTeX.

| Certificate | Bytes | SHA-256 |
|---|---:|---|
| Archived gzip file | 5,643,936 | `6133dd9a10a5f7f7ee7dcd60f1645eedc0b4e49cb03b4ff341c0c185b68b7be3` |
| Uncompressed sign matrix | 31,585,352 | `93ba6e82b4e8a137a00b2e6898fa03466cd1cb5eb82bca245cefde5eafc77dcf` |

The archived stream was created with `gzip -n -9`. Each row occupies 1,987 bytes. Read each byte from its most significant bit to its least significant bit, taking 0 as +1 and 1 as −1. Rebuilding compares the uncompressed bytes directly. The manifest records the hash of each shipped source.

## Construction

The builder uses the field of 661² elements obtained by adjoining a square root of 2 and takes the generator to be 2 plus that root. It checks its multiplicative order and constructs Turyn's four sign circulants of order 331. Their symmetry and commutation give amicability, and checking every cyclic shift verifies the summed row Gram. The builder verifies the formal coefficient identities of the order-12 design and the parity condition in each of its 36 tiles. The substituted matrix of order 3,972 has 3,944,196 two-by-two Hadamard tiles. It checks the Paley conference core over the field of 1,987 elements by exact cyclic correlations, then writes all sign rows of order 15,896. A second implementation in the preparatory study produced the same packed bytes.

## Reconstruction from the manuscript

A fresh reader received only the revised manuscript (PDF and equivalent TeX source). Using Section 2 and Appendix A, the reader wrote a standalone C++17 program and generated all 31,585,352 bytes. A separate comparison with the decompressed certificate matched byte for byte, including the raw SHA-256 above. The reader used no repository code, certificate, external source, or clarification of the construction.

## Direct certificate check

The verifier consumes raw bytes on standard input. It requires exactly 15,896 complete rows and EOF. It compares every unordered pair using XOR and population count. Every row pair differed in 7,948 entries, giving inner product zero. The fixed sign alphabet and row length give diagonal 15,896. On the verification machine, Apple Clang 21.0.0 on x86-64, the separate verifier read the archived certificate and completed in 24.07 seconds elapsed. The builder also reproduced the payload in 0.54 CPU seconds. The first independent check ran at default scheduling priority because the environment rejected a priority change. A second pair check at nice 19 passed in 26.31 CPU seconds.

```text
PASS order=15896 bytes=31585352 diagonal_entries=15896 diagonal=15896 pairs=126333460 distance=7948
```

Removing one byte, appending one byte and replacing the payload by zero bytes of the correct length each caused a rejection. Flipping only the most significant bit of the first byte changed the distance between rows 1 and 2 to 7,949 and also caused a rejection. The independent verifier takes no design parameters or mathematical tables. It directly establishes the order-15,896 result. The other three orders follow from the proof.

## Reading copy

The document build uses pdfTeX 1.40.22 (TeX Live 2021), the default Computer Modern fonts and two compilation passes. The paper's source and the commands in the Makefile allow regeneration.

The final PDF SHA-256 is `a1deaa1990c122b620e36a83991cac7da738f8827016892b68d7826398f2be7b`. All five pages were inspected. The PDF uses embedded Type 1 fonts, and its text layer preserves the author's name, ligatures and accented reference names. GitHub's Markdown renderer recognized all 17 inline math spans in the README.
