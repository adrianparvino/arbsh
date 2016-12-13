#!/bin/sh

# A series of post installation commands for self
# bootstrapping targets.

mkdir -p /newtoolchain/

mount /dev/sdc /newtoolchain/

mkdir -p /newtoolchain/src/

mount /dev/sdb /newtoolchain/src/

cp -r /toolchain/* /newtoolchain/

chown -R liveuser /newtoolchain

chmod 777 /tmp

su - liveuser

cd /newtoolchain/

export PATH=/usr/local/bin:/usr/bin:/bin/:sbin

export CC=gcc

make > logfile 2>&1 &

