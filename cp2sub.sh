#!/usr/bin/env bash
set -euo pipefail
shopt -s nullglob

if [[ $# -ne 1 ]]; then
  echo "usage: $0 DEST_DIR" >&2
  exit 1
fi

dest="$1"
mkdir -p "$dest"

dirs=(ex*/)
if [[ ${#dirs[@]} -eq 0 ]]; then
echo "No directories starting with 'ex' found." >&2
  exit 1
fi

for d in "${dirs[@]}"; do
  base="${d%/}"
  echo "sync: $base -> $dest/"
  rsync -a --prune-empty-dirs \
    --include='*/' \
    --include='Makefile' \
    --include='*.cpp' \
    --include='*.hpp' \
    --exclude='*' \
    "$base" "$dest/"
  # 既存の不要ファイルも宛先から消したい場合は上に --delete --delete-excluded を追加
done
