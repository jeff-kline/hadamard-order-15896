# Prior-art checks on 27 November 2026

**Two of the six proposed orders have an earlier construction.** Zaitsev published the two required quaternary inputs. Paley supplies both skew conference matrices, and Miyamoto's Theorem 7 then gives the real orders. Four candidates survive the searches below. [Zaitsev, updated 23 November](https://www.cs.uleth.ca/~zaitsevv/quaternary.html) · [Miyamoto, 1991](https://doi.org/10.1016/0097-3165(91)90008-5)

| n | 8n | m at Kumar pin | Quaternary order n−1 | Evidence and inference |
|---:|---:|---:|---:|---|
| 1567 | 12536 | 5 | 1566 | Public file, exact Gram verified. KNOWN. |
| 1783 | 14264 | 4 | 1782 | Public file, exact Gram verified. KNOWN. |
| 1987 | 15896 | 4 | 1986 | Explicitly on Zaitsev's unknown list. LIKELY NEW in this screen. |
| 2251 | 18008 | 4 | 2250 | Beyond the BH list. No earlier route located. LIKELY NEW in this screen. |
| 2287 | 18296 | 4 | 2286 | Beyond the BH list. No earlier route located. LIKELY NEW in this screen. |
| 2887 | 23096 | 5 | 2886 | Beyond the BH list. A previous release gives 16n. No earlier route to 8n located. LIKELY NEW in this screen. |

### Source checks

1. **Kumar.** `git ls-remote https://github.com/vatskishan03/Hadamard.git HEAD` returned `d885022144ba6bf4efa8315e14871a3736947527`. The checkout used for full-tree searches had this same HEAD. The updated Table 4 paragraph of FRONTIER.md, lines 58–62, identifies the 28 possible odd parts within its range. For each of the six orders in the table above we ran a literal digit search of all tracked text. In order, the file counts were 5, 1, 0, 0, 3, 3. All matches are within longer digit strings in search data or logs under search/eightp, search/negaskew or search/propus3. A digit-delimited search across all six found no occurrence. The quaternary certificate index in complex-hadamard/README.md supplies no further target input. [Pin](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/FRONTIER.md#L58-L62) · [Quaternary index](https://github.com/vatskishan03/Hadamard/tree/d885022144ba6bf4efa8315e14871a3736947527/complex-hadamard)
2. **Earlier releases.** The above-10,000 release constructs 25,072 and 46,192 at odd parts 1,567 and 2,887. Halving a Hadamard order does not follow from doubling. The order-4792 paper supplies the paired-block transfer and the repeated-member length-13 pairing. It precedes this work. [Larger orders](https://doi.org/10.5281/zenodo.24517277) · [Order 4792](https://doi.org/10.5281/zenodo.24597897)
3. **Survey.** Read the 3 November revision of Egan, Kotsireas, London and Ó Catháin, especially Tables 3–5 and the quaternary section. Its order list stops at 10,000. It provides methods and inputs, with no direct verdict for the six real orders. The earlier Cati–Pasechnik Table 4 covers these odd parts and supplies the baseline for Kumar's update. [2026 survey v2](https://arxiv.org/abs/2610.27175v2) · [Cati–Pasechnik v2](https://arxiv.org/abs/2411.18897v2)
4. **Zaitsev and earlier BH routes.** Downloaded the table, SHA-256 `c0e883fee90179b5bc7cd217a10c4ab98c1d3c5eebc083d126c454673a713896`. The two linked files have SHA-256 `e4fe3858ceaca0b40832a107feb67b0962164682059ed174a35d3039d12e3bc9` and `5bf483d00ee1223d5da0a5aba5b23f0dabbdc91019ec6fdd1e7e0806ef9e39ae`. After mapping the stated alphabet to fourth roots, our verifier checked lengths, entries and all 1,225,395 and 1,586,871 respective off-diagonal Hermitian inner products. Its integer computation uses the two sign planes of each row scaled by 1+i. Both Grams passed. [QH1566](https://www.cs.uleth.ca/~zaitsevv/matrices/QH1566.txt) · [QH1782](https://www.cs.uleth.ca/~zaitsevv/matrices/QH1782.txt) · [Verifier](../evidence/check-published-bh.cpp)

   Zaitsev's stated order-18m construction requires 2m−1 a prime power congruent to 1 modulo 4. For the first two inputs it is 173 and 197. Of the remaining four inputs only 2250 and 2286 are divisible by 18, and their parameters are 249 = 3·83 and 253 = 11·23. For the standard quaternary Paley route the values 2n−3 are 3971 = 11·19², 4499 = 11·409, 4571 = 7·653 and 5771 = 29·199. Seberry–Yamada Table A.1 lists the four half-inputs 993, 1125, 1143 and 1443 with exponent 3 and key wn. Its legend identifies these as WT at twice the listed odd order. Thus those entries do not supply the WT of odd order required by the classical WT-to-quaternary construction. Their complex Table 11.2 is blank at 993 and ends at 999. This checks named routes, without ruling out other BH constructions. [1992 survey, section 11.3 and Appendix A.2](https://documents.uow.edu.au/~jennie/WEBPDF/175_1992.pdf) · [Quaternary Paley construction](https://github.com/vatskishan03/Hadamard/blob/d885022144ba6bf4efa8315e14871a3736947527/complex-hadamard/PALEY.md)

### Query log

Every query below was made on **2026-11-27**. In the following templates, the six (n,N) substitutions are exactly the six rows above, with N = 8n.

| Service | Queries actually sent | Result |
|---|---|---|
| GitHub CLI | For each (n,N), both `gh search code` and `gh search repos` on `Hadamard N` and `Hadamard "8 x n"`, limit 30. An initial `Hadamard 15896` used limit 20 on each endpoint. | All 24 main calls completed with zero returned rows. Global code search uses GitHub's legacy index. |
| Kumar repository | At the pinned commit, `git grep --threads=1 -l -F N HEAD` for each N and `git grep -I -l -E '(^\|[^0-9])(12536\|14264\|15896\|18008\|18296\|23096)([^0-9]\|$)' HEAD` on all six. Also read the pinned frontier and complex-hadamard index. | Counts and interpretation above. |
| Zenodo REST | At /api/records, `q=hadamard AND N`, size 25, for each N. Positive control `q=hadamard AND 4792` and direct GET /api/records/24597897. | Zero records for each candidate. The control returned the published order-4792 record. |
| Zenodo broader queries | `hadamard AND (15896 OR 1987)`, size 3 (53 total, sampled titles unrelated). `title:hadamard`, sort=mostrecent, size 25 (179 total, 25 inspected). | No further target construction identified among inspected records. |
| arXiv Atom API | `(ti:hadamard OR abs:"Hadamard matrices") AND submittedDate:[202611030000 TO 202611272359]`, max 100; second query added `abs:"Hadamard matrix"`, requested lastUpdatedDate with the same interval, max 200. | 17 and 19 entries. The second response echoed submittedDate, so it supplies broader submission coverage only. Inspected titles and relevant abstracts. Switching, power projections, and k-ary Legendre pairs yielded no target construction. A third query used the same three terms without a date filter, sortBy=lastUpdatedDate descending, max_results=100. The first page reached September 30 and contained 40 listings updated since November 3, including survey v2. No additional target construction surfaced. |
| Targeted web search | `Hadamard "12536" "1567" construction Hadamard matrix November 2026`; `Hadamard matrices 14264 15896 18008 18296 23096 known order quaternion Williamson type quaternary Hadamard matrix`; for each surviving row, `Hadamard matrix "N" OR "N-with-comma" OR "BH(n−1" quaternary construction n` with actual numerals. | No additional primary-source construction. |
| Skew conference check | `Đoković Seberry 749 skew Hadamard matrices 4v 749 2996 undecided table census small orders 2500 May 2025`. | The census lists v=749 as undecided for skew H(2996), relevant to the WT(499) frontier preimage. |

Failed variants, recorded **NOT PERFORMED**: Zenodo's six compound `metadata.title:hadamard AND ("N" OR "BH(n−1,4)" OR "8 x n")` queries (size 100, DNS failure followed by HTTP 400 on retry), and its `title:hadamard` queries at size 40 with sort=mostrecent or sort=-publication_date (HTTP 400). Direct web-preview requests for the two BH files missed the web cache, then direct HTTPS downloads succeeded. [GitHub CLI semantics](https://cli.github.com/manual/gh_search_code) · [Zenodo records](https://zenodo.org/api/records) · [arXiv API](https://export.arxiv.org/api/query) · [Skew census](https://us.ticmeet.com/assets/archivos/d6f1d9b8-d39f-4888-925a-7eb81c4905cc/jenni-paper.pdf)

“Likely new” records a positive construction and a negative result in this dated search. Online indices can miss a construction published only as a general theorem or described with other parameters. Three of the four surviving orders have no coverage from Zaitsev's finite list.

The per-query GitHub and Zenodo results and the 19 arXiv submission titles are in [queries.tsv](queries.tsv).

The release-preparation search on the same date also queried GitHub code for `Miyamoto Hadamard 15896` and `Williamson 15896`, and GitHub repositories for `Hadamard open problems orders`. Each returned zero rows. The pinned frontier list, the quaternary table and the arXiv survey were rechecked. A fresh search is due before making the repository public.

To repeat the two earlier-order checks, download the two linked QH files above, confirm the listed SHA-256 digests, and run the following from the release root with the text files in the current directory.

```sh
mkdir -p build
c++ -std=c++17 -O3 evidence/check-published-bh.cpp -o build/check-published-bh
build/check-published-bh 1566 QH1566.txt
build/check-published-bh 1782 QH1782.txt
```

The order-4792 paper identifies the earlier eight-block construction of Seberry and Yamada (Lemma 8.12) used in its proof of the conference transfer and credits Craigen for the signed-group formulation of paired blocks. The present application uses that published transfer as a theorem. [Seberry and Yamada](https://documents.uow.edu.au/~jennie/WEBPDF/175_1992.pdf) · [Craigen](https://doi.org/10.1016/0097-3165(95)90002-0) · [Order-4792 paper](https://doi.org/10.5281/zenodo.24597897)
