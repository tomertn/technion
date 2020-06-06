#! /bin/bash

### less then 1 param: ###
if (($#<1)) ; then 
    echo "Not enough parameters"
    exit 1
fi
### Dir does not exists! ###
if [ ! -d  "$1" ] ; then
    echo "Directory does not exist"
    exit 1
fi

cd "$1"

find -type f > listOfFiles
res=0
while read line; do 
    temp= `cat "$line" | wc -l`
	res = res + temp;
done<listOfFiles
echo $res
rm listOfFiles
exit 0
