#!/bin/bash

# Runs make on the directory passed as param $1, then runs the program a.out generated by the compilation, and inserts the output of the execution in the README.md in the same directory.

make -C $1
readme_path="${1}README.md"
program_output="## Program output

\`\`\`bash
$ make
$ ./a.out 
$(${1}a.out)
\`\`\`"
output_start_tag="<!-- gh-action-output -->"
output_end_tag="<!-- gh-action-output end -->"

# Test if readme exists
if test -f "$readme_path"; then
    echo "$FILE exists."
else
    echo "No README found. Creating README."
    echo "${output_start_tag}" >> ${readme_path}
    echo "${output_end_tag}" >> ${readme_path}
fi



# Test if gh-action output tags are in readme

if grep -Ewq "${output_start_tag}" ${readme_path}; then 
    echo
else 
    echo "\033[0;31mError: Missing start tag: ${output_start_tag}\033[0m"
    exit 1
fi

if grep -Ewq "${output_end_tag}" ${readme_path}; then 
    echo
else 
    echo "\033[0;31mError: Missing end tag: ${output_end_tag}\033[0m"
    exit 1
fi


# Replace with new output

# Delete previous content
output_start=$(grep -n "$output_start_tag" ${readme_path} | head -n 1 | cut -d: -f1)
output_content_start=$((${output_start}+1))

output_end=$(grep -n "$output_end_tag" ${readme_path} | head -n 1 | cut -d: -f1)
output_content_end=$((${output_end}-1))

if [ $output_content_end -ge $output_content_start ];
then
    sed -i.bkp "${output_content_start},${output_content_end}d" ${readme_path}
fi

# Add new content
IFS='
'
count=0
for line in $program_output
do
  count=$((count+1))
  sed -i '/gh-action-output end -/i '"${line}" ${readme_path}
done

