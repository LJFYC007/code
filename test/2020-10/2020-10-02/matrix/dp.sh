i=0
while true; do
	./gen
	./matrix
	./bf
    i=$(($i+1))
	if diff matrix.out matrix1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
