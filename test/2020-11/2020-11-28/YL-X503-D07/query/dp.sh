i=0
while true; do
	./gen
	./bf
	./query
    i=$(($i+1))
	if diff query.out query1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
