# Release record

Current verdict: NOT YET ADMITTED

Version 0.1.0 of *An infinite family of paired Hadamard matrices from Williamson-type matrices* is a private release candidate under Jeffery Kline's [public research standard](https://jeff-kline.github.io/posts/research-program/index.html).

| Gate | Evidence | Status and remaining work |
|---|---|---|
| P1 · Attribution and priority (PARTIAL) | The November 27 search found four orders without an earlier construction in the searched corpus. Two proposed orders had known Miyamoto inputs. [Prior-art record](audit/PRIOR-ART.md) | Repeat the dated comparison before public visibility. |
| A1 · Claims and verification (PASS) | The theorem proves four existence results. Order 15,896 has a separate, exhaustive verification of the shipped bytes. [Paper](paper/main.pdf) · [Verification](VERIFICATION.md) · [Review ledger](audit/LEDGER.md) | The local proof and certificate checks are documented in the review ledger. |
| R1 · Reproduction and archive (PARTIAL) | The local package contains code, a certificate, exact reproduction commands and citation metadata. [Verification](VERIFICATION.md) · [Correction policy](CORRECTIONS.md) | Public repository, tag, provider metadata, DOI and archive byte comparison are pending. |

## Publication plan

The private repository is `jeff-kline/hadamard-order-15896` and the planned tag is `v0.1.0`. Local preparation and verification are delegated. The author controls remote repository creation and visibility, all pushes and tags, the GitHub Release, the Zenodo integration and any public-site listing.

The planned archive uses the Zenodo GitHub integration. Enable it before creating the GitHub Release. Before the release, retrieve the GitHub API tag zipball twice and compare the bytes. After archival, compare the public Zenodo download with the pinned GitHub zipball, inspect the record metadata, resolve the version DOI, and verify the internal manifest. Record the active DOI and version in living metadata after these checks.
