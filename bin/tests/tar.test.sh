dd if=/dev/urandom of=somefile bs=1M count=1000

./tar -cf somefile.tar somefile

mv somefile bak

./tar -xf somefile.tar

diff somefile bak

echo end of diff 1


dd if=/dev/urandom of=somefile bs=1M count=3000

./tar -cf somefile.tar somefile

mv somefile bak

./tar -xf somefile.tar

diff somefile bak

echo end of diff 2

./tar -cf usr.tar /usr

./tar -xf usr.tar

diff usr /usr

rm -rf usr usr.tar somefile somefile.tar bak



