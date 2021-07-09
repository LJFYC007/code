g++ gen.cpp -o gen -O2 -std=c++17
g++ std.cpp -o std -O2 -std=c++17
for i in {15..20};
do
	echo "#$i is running"
	./gen>easy$i.in
	time ./std<easy$i.in>east$i.out
done
