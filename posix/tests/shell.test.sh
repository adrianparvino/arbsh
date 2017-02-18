
sh -c "ijkijk&&ls|wc&&ls" > file1 
./shell "ijkijk&&ls|wc&&ls" > file2 
diff file1 file2
echo bottom of diff one


sh -c "ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls" > file1 
./shell "ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls" > file2 
diff file1 file2
echo bottom of diff two

sh -c "ls&&ss&&ls||ls|wc&&ls&&ls&&ls" > file1 
./shell "ls&&ss&&ls||ls|wc&&ls&&ls&&ls" > file2 
diff file1 file2
echo bottom of diff three

sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas" > file1
./shell "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas" > file2
diff file1 file2
echo bottom of diff four

sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file1

./shell "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file2 
diff file1 file2
echo bottom of diff five

sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file1

./shell  "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file2

diff file1 file2
echo bottom of diff six

sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ds&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file1

./shell  "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ds&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls" > file2

diff file1 file2
echo bottom of diff seven

./shell "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc;ls||ls||ls;asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd " >file1

sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc;ls||ls||ls;asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd " > file2
diff file1 file2
echo bottom of diff eight

sh -c "ls&&ls&&ls|wc&&asas||ss" > file1
./shell "ls&&ls&&ls|wc&&asas||ss" > file2
diff file1 file2
echo bottom of diff nine

sh -c "ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss" > file1
./shell "ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss&&ls&&ls&&ls|wc&&asas||ss" > file2
diff file1 file2
echo bottom of diff ten

rm file1 file2

time sh -c "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc;ls||ls||ls;asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd " > file2

echo sh time

time ./shell  "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc;ls||ls||ls;asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd " > file1

echo shell time

time bash -c  "ijkijk&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd||ss||ls||ls||ls||asas&&asas&&ijkijk&&ls|wc;ls||ls||ls;asas&&asas&&ijkijk&&lsasdasdasd||ls|wc&&asas&&ls&&ls||ijkijk&&ls|wc&&ls&&asdasd&&asdasd " > file3

echo bash time
