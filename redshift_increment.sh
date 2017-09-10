#!/bin/bash

if [ "$1" == "+" ]; then
	# We're increasing...
	temp=$(<temp.txt)
	temp="$((temp + 150))" 
else
	# We're decreasing
	temp=$(<temp.txt)
	temp="$((temp - 10))" 
fi

redshift -O $temp
echo $temp > temp.txt
