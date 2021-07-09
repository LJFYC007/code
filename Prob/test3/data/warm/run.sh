g++ std.cpp -o std -O2 -std=c++17
g++ gen.cpp -o gen -O2 -std=c++17
for i in {13..20};
do
	echo "#$i is running!"
	./gen>warm$i.in
	time ./std<warm$i.in>warm$i.out
done
