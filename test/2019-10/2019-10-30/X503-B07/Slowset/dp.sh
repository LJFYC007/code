for i in $(seq 1 100000);do
	./gen
	./Slowset
	./std
	if diff Slowset.out Slowset1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done

