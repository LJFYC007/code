for i in $(seq 1 100000);do
	./gen
	./lipschitz
	./bf
	if diff lipschitz1.out lipschitz.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
