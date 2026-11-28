# Release record

Current verdict: ADMITTED

Version 0.1.0 of *An infinite family of paired Hadamard matrices from Williamson-type matrices* was archived and admitted on November 28, 2026 (UTC). Admission records the project's release decision. Independent expert peer review and external correctness certification remain outstanding. [Research standard](https://jeff-kline.github.io/posts/research-program/index.html) · [Version DOI](https://doi.org/10.5281/zenodo.24615122) · [All versions](https://doi.org/10.5281/zenodo.24615121)

| Gate | Result | Evidence |
|---|---|---|
| P1 · Attribution and priority | PASS | The November 27 search found no earlier construction at 15,896, 18,008, 18,296 or 23,096 in the sources searched. It identified earlier Miyamoto constructions at two other proposed orders and credited Kumar's earlier construction of 5,912. [Prior art](audit/PRIOR-ART.md) · [Final comparison](audit/FINAL-PRIOR-ART.md) |
| A1 · Claims and verification | PASS | The proof covers all four orders. A reader reconstructed the order-15,896 matrix from the manuscript alone, and a separate verifier checked all 126,333,460 distinct row pairs in the archived matrix. [Paper](paper/main.pdf) · [Verification](VERIFICATION.md) · [Review ledger](audit/LEDGER.md) |
| R1 · Reproduction and archive | PASS | The annotated tag `v0.1.0` (object `9fcbbeaad2729eed8ea3c22bdd2b8f569bbaf735`) fixes commit `d55b226457835f97f4a3f872513665ee5e5d47e5`. Zenodo's public archive matches both pre-release GitHub downloads byte for byte, with all 20 manifest entries verified. [GitHub Release](https://github.com/jeff-kline/hadamard-order-15896/releases/tag/v0.1.0) · [Archive verification](VERIFICATION.md#archive-verification) |

The permanent archive preserves the manuscript and release-candidate wording as tagged. The repository's reading copy adds the version DOI to the title page. An earlier construction implicit in an unexamined theorem could change the priority assessment. The archived computational certificate covers order 15,896. [Correction policy](CORRECTIONS.md)
