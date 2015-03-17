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
    echo ""
    echo "<<<< $test >>>>"
    res="$($VALGRIND $test)"
    rc=$?
    RESULT=$((RESULT+rc))
done

echo ""

if [ "$RESULT" -eq 0 ]; then
    echo "*********************************************"
    echo "NO errors from Valgrind"
    echo "*********************************************"
else
    echo "*********************************************"
    >&2 echo "ERRORS reported from Valgrind. Check Log."
    echo "*********************************************"
fi

return $RESULT