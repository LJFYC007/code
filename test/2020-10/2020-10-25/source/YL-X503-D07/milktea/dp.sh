i=0
while true; do
	./gen
	./milktea
	./bf
    i=$(($i+1))
	if diff milktea.out milktea1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
