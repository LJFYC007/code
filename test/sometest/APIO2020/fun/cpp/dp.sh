i=0
while true; do
	./gen
	bash compile_cpp.sh
    i=$(($i+1))
	echo $i
done
