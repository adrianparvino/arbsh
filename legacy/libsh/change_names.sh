#!/bin/sh

DEFAULT_NAME="cmgraff"
DEFAULT_ADDR="cm0graff@gmail.com"

set_git()
{
	git config --global user.name "$1"
	git config --global user.email "$2"
	git commit --amend --reset-author
	git pull
}
  

if [ $# != 2 ]
then	printf -- "%s\n" "pls supply 2 args"
	exit
fi

if [ $1 = "self" ]
then	set_git $DEFAULT_NAME $DEFAULT_ADDR
	exit
fi

set_git $1 $2

