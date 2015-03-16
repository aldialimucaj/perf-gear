#!/bin/sh
# 
# File:   valgrind-tests.sh
# Author: Aldi Alimucaj
#
# Created on Mar 15, 2015, 8:22:52 PM
#

VALGRIND="valgrind --leak-check=full --error-exitcode=1 "
exes="$(find build/ -type f -executable)"

RESULT=0
for test in $exes; do
    echo "<<<< $test >>>>"
    res="$($VALGRIND $test)"
    rc=$?
    RESULT=$((RESULT+rc))
done

return $RESULT