
FILE="$1"
PREF="g"
WORDS="\
free \
realloc \
malloc \
calloc \
"

for i in $WORDS
do	#echo "$i"
	sed -i "s|$i|${PREF}${i}|g" "$FILE"
done

