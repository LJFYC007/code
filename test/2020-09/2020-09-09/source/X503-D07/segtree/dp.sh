i=0
while true; do
	./gen
	./segtree
	./bf
    i=$(($i+1))
	if diff segtree.out segtree1.out ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
