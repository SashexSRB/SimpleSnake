#!/bin/bash

#var init
message=""
do_add=false

#parse opts
while [[ $# -gt 0 ]]; do
	case "$1" in
		-a) 
			do_add=true
			shift
			;;
		-m)
			shift
			message="$1"
			shift
			;;
		-am|-ma)
			do_add=true
			shift
			message="$1"
			shift
			;;
		*)
			echo "Usage: $0 -m \"commit message\" [-a] or -am \"message\""
			exit 1
			;;
	esac 
done

#check if message was provided
if [ -z "$message" ]; then
	echo "ERR: Commit message is required"
	echo "Usage: $0 -m \"commit message\" [-a] or -am \"message\""
	exit 1
fi

if $do_add; then
	git add -A
fi
git commit -m "$message"
git push -u origin main

