method=$1
if [ -z "$1" ]
  then
    echo "Use default"
    method="2"
fi

echo "Use method$method.c"
gcc -std=c99 -o 12392 12392.c "method$method.c" util.c