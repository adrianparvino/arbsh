#!/bin/sh

EXE="../bc -l"
#EXE="bc -l"

echo "scale=10;123981239.981273987 * 12983791827398.29836472638" | $EXE

echo "scale=100;759634576394.3946587934658364895 / 9834759834895386.36459364958346" | $EXE

echo "34895734986539489834759837489573498573.398475984759837485734987598345 + 9823749832749872384234872934.28347982374987239847982374" | $EXE

echo "a=123123123.987239874; b=123123123.239479823748; a+b" | $EXE

echo "20347023.23498723984 - 28934723874.234720384" | $EXE

echo "scale=100;a=739534985.895347284957;b=238746782364.2374623784; c = a / b; c+0" | $EXE
