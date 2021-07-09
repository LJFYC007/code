i=0
while true; do
	./gen
    ./average > output.txt
    ./bf > output1.txt
#	g++ average.cpp grader.cpp -o average -std=c++11 && ./average > output.txt
#	g++ bf.cpp grader.cpp -o bf -std=c++11 && ./bf > output1.txt
    i=$(($i+1))
	if diff output.txt output1.txt ;then
		echo $i "AC ~ HAHAHA ~"
	else
		echo $i "WA ~ WA ~"
		exit 0
	fi
done
