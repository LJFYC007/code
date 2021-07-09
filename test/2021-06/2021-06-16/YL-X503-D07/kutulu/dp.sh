i=0
while true; do
	./gen
	./kutulu
	./2
    i=$(($i+1))
	if diff kutulu.out kutulu1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
