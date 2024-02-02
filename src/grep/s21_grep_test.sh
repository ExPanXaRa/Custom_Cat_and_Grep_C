#!/bin/bash

COUNT_SUCCESS=0
COUNT_FAIL=0
DIFF_RES=""
TEST_CHAR1="sda"
TEST_CHAR2="sdA"
TEST_CHAR3="World"
TEST_CHAR4="a"
TEST_FILE1="t.txt"
TEST_FILE2="t2.txt"
TEST_FILE3="t3.txt"
TEST_FILE4="t4.txt"
TEST_FILE5="t5.txt"
TEST_FILE_L="retwtyrtgd"

for var in -i -v -c -l -n -h -o
do
  for TTES in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
  do
    for TCHAR in $TEST_CHAR1 $TEST_CHAR2 $TEST_CHAR3 $TEST_CHAR4
    do
      TEST="$var $TCHAR $TTES"
      $VAL ./s21_grep $TEST > s21_grep.txt
      grep $TEST > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
        then
          echo "SUCCESS: $TEST"
          COUNT_SUCCESS=$((COUNT_SUCCESS+1))
        else
          echo "FAIL: $TEST"
          COUNT_FAIL=$((COUNT_FAIL+1))
      fi
      rm s21_grep.txt grep.txt
    done
  done
done

for var in -i -v -c -l -n -h -o
do
  for TCHAR in $TEST_CHAR1 $TEST_CHAR2 $TEST_CHAR3 $TEST_CHAR4
  do
      TEST="$var $TCHAR $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4"
      ./s21_grep $TEST > s21_grep.txt
      grep $TEST > grep.txt
      DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
      if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
        then
          echo "SUCCESS: $TEST"
          COUNT_SUCCESS=$((COUNT_SUCCESS+1))
        else
          echo "FAIL: $TEST"
          COUNT_FAIL=$((COUNT_FAIL+1))
      fi
      rm s21_grep.txt grep.txt
  done
done

for TTES in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
  TEST="-f $TTES $TEST_FILE1"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
    then
      echo "SUCCESS: $TEST"
      COUNT_SUCCESS=$((COUNT_SUCCESS+1))
    else
      echo "FAIL: $TEST"
      COUNT_FAIL=$((COUNT_FAIL+1))
  fi
  rm s21_grep.txt grep.txt
done

for TTES in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
  TEST="-f $TTES $TEST_FILE1 $TEST_FILE2 $TEST_FILE3"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
    then
      echo "SUCCESS: $TEST"
      COUNT_SUCCESS=$((COUNT_SUCCESS+1))
    else
      echo "FAIL: $TEST"
      COUNT_FAIL=$((COUNT_FAIL+1))
  fi
  rm s21_grep.txt grep.txt
done

for TTES in $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4
do
  TEST="-e s -e d -e a $TTES"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
    then
      echo "SUCCESS: $TEST"
      COUNT_SUCCESS=$((COUNT_SUCCESS+1))
    else
      echo "FAIL: $TEST"
      COUNT_FAIL=$((COUNT_FAIL+1))
  fi
  rm s21_grep.txt grep.txt
done

TEST="-e s -e d -e a $TEST_FILE5 $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4"
./s21_grep $TEST > s21_grep.txt
grep $TEST > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
  then
    echo "SUCCESS: $TEST"
    COUNT_SUCCESS=$((COUNT_SUCCESS+1))
  else
    echo "FAIL: $TEST"
    COUNT_FAIL=$((COUNT_FAIL+1))
fi
rm s21_grep.txt grep.txt

TEST="-s sda lol"
./s21_grep $TEST > s21_grep.txt
grep $TEST > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
  then
    echo "SUCCESS: $TEST"
    COUNT_SUCCESS=$((COUNT_SUCCESS+1))
  else
    echo "FAIL: $TEST"
    COUNT_FAIL=$((COUNT_FAIL+1))
fi
rm s21_grep.txt grep.txt

TEST="-s sda $TEST_FILE1 $TEST_FILE2 lol $TEST_FILE3 $TEST_FILE4"
./s21_grep $TEST > s21_grep.txt
grep $TEST > grep.txt
DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
  then
    echo "SUCCESS: $TEST"
    COUNT_SUCCESS=$((COUNT_SUCCESS+1))
  else
    echo "FAIL: $TEST"
    COUNT_FAIL=$((COUNT_FAIL+1))
fi
rm s21_grep.txt grep.txt

for TCHAR in $TEST_CHAR1 $TEST_CHAR2 $TEST_CHAR3 $TEST_CHAR4
do
  TEST="$TCHAR $TEST_FILE1"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
    then
      echo "SUCCESS: $TEST"
      COUNT_SUCCESS=$((COUNT_SUCCESS+1))
    else
      echo "FAIL: $TEST"
      COUNT_FAIL=$((COUNT_FAIL+1))
  fi
  rm s21_grep.txt grep.txt
done

for TCHAR in $TEST_CHAR1 $TEST_CHAR2 $TEST_CHAR3 $TEST_CHAR4
do
  TEST="$TCHAR $TEST_FILE1 $TEST_FILE2 $TEST_FILE3 $TEST_FILE4"
  ./s21_grep $TEST > s21_grep.txt
  grep $TEST > grep.txt
  DIFF_RES="$(diff -s s21_grep.txt grep.txt)"
  if [ "$DIFF_RES" = "Files s21_grep.txt and grep.txt are identical" ]
    then
      echo "SUCCESS: $TEST"
      COUNT_SUCCESS=$((COUNT_SUCCESS+1))
    else
      echo "FAIL: $TEST"
      COUNT_FAIL=$((COUNT_FAIL+1))
  fi
  rm s21_grep.txt grep.txt
done



echo "SUCCESS: $COUNT_SUCCESS"
echo "FAIL: $COUNT_FAIL"