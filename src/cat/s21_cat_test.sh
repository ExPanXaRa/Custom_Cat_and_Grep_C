#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
DIFF_RES=""
TEST_FILE1="test.txt"
TEST_FILE2="test-2.txt"

for var in -b -e -n -s -t ""
do
          TEST="$var $TEST_FILE1"
          ./s21_cat $TEST > s21_cat.txt
          cat $TEST > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" = "Files s21_cat.txt and cat.txt are identical" ]
            then
              echo "SUCCESS: $TEST"
              COUNT_SUCCESS=$((COUNT_SUCCESS+1))
            else
              echo "FAIL: $TEST"
              COUNT_FAIL=$((COUNT_FAIL+1))
          fi
          rm s21_cat.txt cat.txt
done

for var in -b -e -n -s -t ""
do
          TEST="$var $TEST_FILE1 $TEST_FILE2"
          ./s21_cat $TEST > s21_cat.txt
          cat $TEST > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" = "Files s21_cat.txt and cat.txt are identical" ]
            then
              echo "SUCCESS: $TEST"
              COUNT_SUCCESS=$((COUNT_SUCCESS+1))
            else
              echo "FAIL: $TEST"
              COUNT_FAIL=$((COUNT_FAIL+1))
          fi
          rm s21_cat.txt cat.txt
done

echo "SUCCESS: $COUNT_SUCCESS"
echo "FAIL: $COUNT_FAIL"