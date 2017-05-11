#!/bin/sh

if [ $# -gt 0 ]
then	EXE="./tests/arbprec-driver"
else	EXE="valgrind ./tests/arbprec-driver"
fi

$EXE 123124 123

$EXE 9999999 123123

$EXE 112398712312893 13123123

$EXE 82172387 23498

$EXE 66767688 987698412

$EXE 66767688 987698412123

$EXE -123124 -123

$EXE 9999999 -123123

$EXE -112398712312893 +13123123

$EXE +82172387 +23498

$EXE -66767688 -987698412

$EXE 66767688 -987698412123

$EXE 1231231 123

$EXE 1231231.0 123.0

$EXE 834038.3272 90598.3434834908

$EXE 5489237.32623 23.233

$EXE 1.34 7.4329823

$EXE 9982374.293487 7.7

$EXE 1. .2348

$EXE 1 2348

$EXE 1.0000 .2348

$EXE 1.000 2348.000000

$EXE -5489237.32623 -23.233

$EXE 1.34 -7.4329823

$EXE +9982374.293487 7.7

$EXE -1. -.2348

$EXE 1 -2348

$EXE 1.0000 -.2348

$EXE -1.000 2348.000000

$EXE 7.676786786786 9543.645645


