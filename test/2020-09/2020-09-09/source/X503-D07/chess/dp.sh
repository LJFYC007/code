i=0
while true; do
	./gen
	./chess
	./bf
    i=$(($i+1))
	if diff chess.out chess1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
