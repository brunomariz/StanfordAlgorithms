#! /bin/bash

dirs=$(find . -type f -name 'Makefile' | sed -r 's|/[^/]+$|/|' |sort |uniq)

for dir in $dirs; do
    echo "--> Running action on $dir"
    sh actions/compile_run_update_readme.sh $dir
done

