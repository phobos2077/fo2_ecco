#!/bin/bash

set -xeu -o pipefail

echo Hello?

extra_dir="${extra_dir:-extra}"
extra_dir="$(realpath $extra_dir)"
bin_dir="$extra_dir/bin"
compile="$bin_dir/compile.exe"
dst="root/data/scripts"
mkdir -p "$dst"
dst="$(realpath $dst)"


mkdir -p $dst
cd scripts_src
for f in $(ls | grep "\.ssl$"); do
  int_name="$(echo $f | sed 's|\.ssl$|.int|')"
  echo $f = $dst/$int_name
#  $compile -l -O2 -p -s -q -n "$f" -o "$dst/$int_name"
done