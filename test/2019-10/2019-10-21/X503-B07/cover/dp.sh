for i in $(seq 1 100000);do
	./gen
	./cover
	if diff cover.out cover.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
