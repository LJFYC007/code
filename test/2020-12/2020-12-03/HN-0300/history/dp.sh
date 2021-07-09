i=0
while true; do
	./gen
	./history
	./1
    i=$(($i+1))
	if diff history.out history1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
