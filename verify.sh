#!/bin/sh
set -eu
scratch=$(mktemp -d build/verify.XXXXXXXX)
trap 'rm -rf "$scratch"' EXIT
trap 'exit 1' HUP INT TERM
archive=evidence/H15896.packed.gz
raw="$scratch/certificate"
rebuilt="$scratch/rebuilt"
archive_sha=6133dd9a10a5f7f7ee7dcd60f1645eedc0b4e49cb03b4ff341c0c185b68b7be3
raw_sha=93ba6e82b4e8a137a00b2e6898fa03466cd1cb5eb82bca245cefde5eafc77dcf
printf '%s  %s\n' "$archive_sha" "$archive" | shasum -a 256 -c -
gzip -dc "$archive" > "$raw"
printf '%s  %s\n' "$raw_sha" "$raw" | shasum -a 256 -c -
build/construct "$rebuilt"
cmp "$rebuilt" "$raw"
echo "MATCH rebuilt and shipped matrix $raw_sha"
build/verify < "$raw" > "$scratch/gram"
cat "$scratch/gram"
grep -Fxq 'PASS order=15896 bytes=31585352 diagonal_entries=15896 diagonal=15896 pairs=126333460 distance=7948' "$scratch/gram"
echo 'MATCH exact row Gram'
