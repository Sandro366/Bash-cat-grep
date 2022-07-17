#!/bin/bash
RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[0;33m'
NC='\033[0m'
echo "start test script"
file_in=cat/test_file/cat_test.txt
args="-n -e -b -nb -s -snb -t -e -et -etb -v -benstv"
for arg in $args
do
echo "testing s21_cat ${YEL}$arg${NC} $file_in..."

./cat/s21_cat $arg $file_in > cat/s21_result.txt
cat $arg $file_in > cat/orig_result.txt
if diff cat/s21_result.txt cat/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail $arg argument!${NC}"
fi
done

