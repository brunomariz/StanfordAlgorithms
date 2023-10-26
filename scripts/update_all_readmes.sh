#! /bin/bash

dirs=$(find . -type f -name 'Makefile' -not -path "./c_structures/*" | sed -r 's|/[^/]+$|/|' |sort |uniq)

for dir in $dirs; do
    echo "--> Running action on $dir"
    sh scripts/compile_run_update_readme.sh $dir
done

