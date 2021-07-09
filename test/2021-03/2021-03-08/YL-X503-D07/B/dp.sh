for i in $(seq 1 100000);do 
    ./gen 
	./B
	./bf 
	if diff output.txt output1.txt ;then 
		echo $i "AC ~ HAHAHA ~" 
	else 
		echo $i "WA ~ WA ~" 
		exit 0 
	fi 
done
