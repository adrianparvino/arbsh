
EXE='./stringmath'

if [ $# != "0" ]
then	EXE="valgrind $EXE"
fi


$EXE 666 777

$EXE 1234 1234

$EXE 987 987

$EXE 8792783258 3257823578

$EXE 8348746239087 2308235661094

$EXE 27238  23823

$EXE 576 999

$EXE 23423 98233790237235

$EXE 524387 22626272969

$EXE 23 8998980

$EXE 2 734734

$EXE 347 8

$EXE 232347623486 2309723480723

$EXE 22223523 2222

$EXE  999 777
 
$EXE  582738597  87234590275

$EXE  -924421  +12341213


$EXE -98767623 +28724387

$EXE -2348234897 +96796968349

$EXE -790879084594 23487234

$EXE +2398298 -9486098

$EXE +346437 988748

$EXE -823490 9034890835

$EXE 203984029384 -9999999999999

