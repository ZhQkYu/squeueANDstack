#This script checks that your print function works correctly.
#How to run: ./checkbucketstack.sh <executable_name> (e.g. ./checkbucketstackprint.sh bucketstack)
#!/bin/bash

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly WARNING="\e[33;1mWARNING:\x1b[0m"
readonly SUCCESS="\e[92msuccess!\x1b[0m"

output="$(./$1)"
expected=$'stack is:\n\thola\n\thola\n\thola\n\tuno\n\tdos\nstack is:\n\tmundo!\n\tmundo!\n\tmundo!\n\ttres'
echo "Output: "
echo "$output"
echo "Expected Output: "
echo "$expected"
if [ "$output" == "$expected" ]; then
    echo -e $SUCCESS "The output of the print function is correct!"
else
    echo -e $ERROR "The output of the print function is NOT correct!"
    exit 1
fi
