i=0
while true; do
	./gen
	./dag
	./bf
    i=$(($i+1))
	if diff dag.out dag1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
