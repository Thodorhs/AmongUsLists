cd src
if [ "$1" == "-c" ]
    then make clean
elif [ "$1" == "-h" ]
    then
    echo "formats to run:"
    echo "-h for help"
    echo "-c for clean"
    echo "your.txt to run."
elif [ $# -eq 1 ]
    then
    if [ -f "AmongUs.out" ]
        then ./AmongUs.out ../tests/$1
    else
        make
        ./AmongUs.out ../tests/$1
    fi
else
  echo "try -h for help"
fi