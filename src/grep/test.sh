#!/bin/bash
RED='\033[0;31m'
GRN='\033[0;32m'
YEL='\033[0;33m'
NC='\033[0m'
echo "start test script"
file_in=grep/test_file/grep_test.txt
file_in2=grep/test_file/grep_test_2.txt
args="-v -c -l -n -h -s -o -i -vc -vl -vn -vi -ln -nc -in -inc"
pattern=aa

for arg in $args
do
echo "testing s21_grep ${YEL}$arg${NC} $file_in..."
./grep/s21_grep $arg $pattern $file_in > grep/s21_result.txt
grep $arg $pattern $file_in > grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail $arg argument!${NC}"
fi
done

for arg in $args
do
echo "testing s21_grep ${YEL}$arg${NC} $file_in $file_in2..."
./grep/s21_grep $arg $pattern $file_in $file_in2> grep/s21_result.txt
grep $arg $pattern $file_in $file_in2> grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail $arg argument!${NC}"
fi
done

for arg in $args
do
echo "testing s21_grep ${YEL}-e A -e b $arg${NC} $file_in..."
./grep/s21_grep -e A -e b $arg $file_in > grep/s21_result.txt
grep -e A -e b $arg $file_in > grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail $arg argument!${NC}"
fi
done

for arg in $args
do
echo "testing s21_grep ${YEL}-f pattern.txt $arg${NC} $file_in..."
./grep/s21_grep $arg -f grep/test_file/pattern.txt $file_in > grep/s21_result.txt
grep $arg -f grep/test_file/pattern.txt $file_in > grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail $arg argument!${NC}"
fi
done

echo "testing s21_grep ${YEL}$pattern${NC} $file_in..."
./grep/s21_grep $pattern file.txt > grep/s21_result.txt
grep -f $pattern file.txt > grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail!${NC}"
fi

echo "testing s21_grep ${YEL}$pattern -W ${NC} $file_in..."
./grep/s21_grep -W $pattern $file_in > grep/s21_result.txt
grep -W $pattern $file_in > grep/orig_result.txt
if diff grep/s21_result.txt grep/orig_result.txt
then
echo "${GRN}success${NC}"
else
echo "${RED}fail -W argument!${NC}"
fi
