for i in $(seq 1 100000);do 
    ./gen 
	./slayer
	./bf 
	if diff slayer.out slayer1.out ;then 
		echo $i "AC ~ HAHAHA ~" 
	else 
		echo $i "WA ~ WA ~" 
		exit 0 
	fi 
done
