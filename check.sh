#!/bin/bash

#This script checks for the following:
#   - you have a ReadMe file
#   - you have the necessary files in each part (See PART1_FILES and PART2_FILES below to see what we check for)
#   - your Makefile has the clean target
#   - your Makefile creates the right executable in each part
#   - your code compiles with no warnings or errors
#   - The script will also tell you if valgrind detects any memory leaks
#   - the script checks the format of the output of your print functions to make sure they adhere to the assignment requirements
#   - the script also checks if all the required files have been committed and pushed to github (problems reported as Warnings, but please remember that we can't mark it if it is not on Github!)
# You MUST run this script on the lab machines!

readonly ERROR="\e[31;1mERROR:\x1b[0m"
readonly WARNING="\e[33;1mWARNING:\x1b[0m"
readonly SUCCESS="\e[92msuccess!\x1b[0m"

readonly PART1_FILES=("squeue.h" "squeue.c" "squeue_client.c" "Makefile")
readonly PART2_FILES=("bucketstack.h" "bucketstack.c" "bucketstack_client.c" "Makefile")


# Check for README
if [ ! -f README ] && [ ! -f ReadMe ] && [ ! -f README.md ] && [ ! -f ReadMe.md ]
then
    echo -e $ERROR "Could not find README (or any acceptable variations of it)"
fi

error_p1=0
echo "Checking Part 1....."
cd "Part1"

#Check if the files from part 1 exist
for i in "${PART1_FILES[@]}"
do
    if [ ! -f "$i" ]; then
        echo -e $ERROR "Could not find file $i of Part 1."
        error_p1=1
    fi
done

#Check if clean target exists
clean_output="$(make clean 2>&1)"
if echo "$clean_output" | grep -q "No rule to make target"; then
    echo -e $ERROR "Your makefile for Part 1 does not contain a clean target."
    error_p1=1
fi

#Check that part 1 code compiles with no warnings or errors
output="$(make 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Your squeue program compiles with warnings. Please fix before submitting."
    error_p1=1
fi
	    
if [ $make_result != 0 ]; then
    echo -e $ERROR "make failed. Your squeue program does not compile correctly."
    error_p1=1
fi

#Check that squeue executable exists
if [ ! -x "squeue" ]; then
    echo -e $ERROR "squeue is not executable or does not exist. Cannot run program for Part 1."
    error_p1=1
else
    # run program to ensure all asserts passed
    ./squeue
    run_result=$?
    if [ $run_result != 0 ]; then
        echo -e $ERROR "Running your program failed. Either one of the asserts failed or a segmentation fault occurred. Check the error message above to see what happened"
        error_p1=1
    else
        #if program runs correctly, check memory leaks
        if ! type "valgrind" &> /dev/null; then
            echo -e $WARNING "valgrind is not found on this machine. Cannot check for memory leaks in part 1. Are you sure you are running this on the lab machine?!"
            error_p1=1
        else
            valgrind --error-exitcode=1 --leak-check=yes ./squeue > temp 2>&1
            if [ $? -eq 1 ]; then
                echo -e $ERROR "Valgrind reported errors in part 1! Remember that you loose marks for memory leaks. Exiting script."
                error_p1=1
            else
                echo -e $SUCCESS "No errors reported by valgrind in part 1"
            fi
        rm -f temp
        fi
    fi
fi

#check printing format
./checksqueueprint.sh squeue
print_result=$?
if [ $print_result != 0 ]; then
   error_p1=1
fi

if [ $error_p1 != 0 ]; then
    echo -e $ERROR "The checks run for Part 1 have failed. Please check above messages"
fi
   
cd .. #get out of part1 dir

error_p2=0
echo "Checking Part 2....."
cd "Part2"
    
for i in "${PART2_FILES[@]}"
do
    if [ ! -f "$i" ]; then
	echo -e $ERROR "Could not find file $i of Part 2."
        error_p2=1
    fi
done

clean_output="$(make clean 2>&1)"
if echo "$clean_output" | grep -q "No rule to make target"; then
    echo -e $ERROR "Your makefile for Part 2 does not contain a clean target."
    error_p2=1
fi

output="$(make 2>&1)"
make_result=$?

if grep "warning:" <<<"${output}"; then
    echo -e $ERROR "Part 2 compiles with warnings. Please fix before submitting."
    error_p2=1
fi
	    
if [ $make_result != 0 ]; then
    echo -e $ERROR "make failed. Your bucketstack program in part 2 does not compile correctly."
    exit 1
fi

if [ ! -x "bucketstack" ]; then
    echo -e $ERROR "bucketstack is not executable or does not exist. Cannot run program in part 2"
    error_p2=1
else
    if ! type "valgrind" &> /dev/null; then
        echo -e $WARNING "valgrind is not found on this machine. Cannot check for memory leaks in part 2. Are you sure you are running this on the lab machine?!"
        error_p2=1
    else
        valgrind --error-exitcode=1 --leak-check=yes ./bucketstack > temp 2>&1
        if [ $? -eq 1 ]; then
            echo -e $ERROR "Valgrind reported errors in part 2! Remember that you loose marks for memory leaks. Exiting script"
	        error_p2=1
        else
            echo -e $SUCCESS  "No errors reported by valgrind in part 2"
        fi
	rm -f temp
    fi  
fi
        


./checkbucketstackprint.sh bucketstack
print_result=$?
if [ $print_result != 0 ]; then
   error_p2=1
fi

if [ $error_p2 != 0 ]; then
echo -e $ERROR "The checks run for Part 2 have failed. Please check above messages"
fi

cd ..

# Checking tracking of files in git (only done locally(

if [ -f /.dockerenv ]; then
    echo "Running inside docker.. skipping git checks for Travis CI Build";
else

    # Check existence of every file of part 1 in repo...
    for file in ${PART1_FILES[@]}
    do

        git ls-files Part1/ --error-unmatch "Part1/$file" > /dev/null 2>&1
        if [ $? -ne 0 ]
        then
            echo -e $WARNING "$file not tracked by git"
        fi
    done

    # Check existence of every file of part 2 in repo...
    for file in ${PART2_FILES[@]}
    do
        git ls-files Part2/ --error-unmatch "Part2/$file" > /dev/null 2>&1
        if [ $? -ne 0 ]
        then
            echo -e $WARNING "$file not tracked by git"
        fi
    done

    # Check for new files that haven't been committed
    git diff --cached --exit-code > /dev/null
    new_files=$?

    # Check that there are no uncommitted changes
    git diff --exit-code > /dev/null
    changed_files=$?

    if [ $new_files -ne 0 ] || [ $changed_files -ne 0 ]
    then
        echo -e $WARNING "there are uncommitted changes"
    fi

    # Check for unpushed changes
    git diff --exit-code origin/main..HEAD > /dev/null
    if [ $? -ne 0 ]
    then
        echo -e $WARNING "there are unpushed commits"
    fi
fi

if [ $error_p1 != 0 ] || [ $error_p2 != 0 ]
then
    echo -e $ERROR "The checks for the assignment have failed. Please check above messages and fix them to avoid getting 0 on the assignment."
    exit 1
else
    echo -e $SUCCESS "Good job! All the checks for both parts of the assignment have passed. It is still your repsonsibiility to carefully test your assignment and make sure it adheres to the assignment requirements."
fi
