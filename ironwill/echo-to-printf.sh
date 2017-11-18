#!/bin/sh

sed -i 's|echo|printf "%s\\n"|g' $1
