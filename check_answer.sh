#!/bin/bash

for i in {1..50}
do
   echo "Running test $i"
   echo $i | ./PA3_test.exe > temp.txt
   diff -w temp.txt output/output$i.txt > diff.txt
   if [ -s diff.txt ]
   then
       echo "Test $i FAILED"
       cat diff.txt
   else
       echo "Test $i PASSED"
   fi
done

rm temp.txt diff.txt