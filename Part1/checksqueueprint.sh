#This script checks that your print function works correctly.
#This script is already called from check.sh but you can also run it alone if you want
#How to run: ./checksqueueprint.sh <executable_name> (e.g. ./checksqueueprint.sh squeue)

#!/bin/bash

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly WARNING="\e[33;1mWARNING:\x1b[0m"
readonly SUCCESS="\e[92msuccess!\x1b[0m"

output="$(./$1)"
expected=$'squeue is:\n\tHola\n\taaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!\n\tMundo!\nsqueue is:\n\tHola\n\taaaaaaaaaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbbb!\n\tMundo!'
echo "Output:"
echo "$output"
echo "Expected Output:"
echo "$expected"
if [ "$output" == "$expected" ]; then
    echo -e $SUCCESS "The output of the print function is correct!"
else
    echo -e $ERROR "The output of the print function is NOT correct!"
    exit 1
fi
