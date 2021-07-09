for i in $(seq 1 100000);do
	./gen
	./ljf
    ./lty
	if diff fake1.out fake2.out ;then
        echo $i "AC ~ HAHAHA ~"
	else
		exit 0
	fi
done
