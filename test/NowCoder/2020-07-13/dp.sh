i=0
while true; do
	./gen
	./C
    ./check
    i=$(($i+1))
    echo $i
done
