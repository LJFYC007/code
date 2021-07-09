cd /home/huhao/Documents/problemset/1/data/score
g++ gen.cpp -o gen -O2 -std=c++17
for i in {1..20};
do
	touch score_4_$i.out
	./gen>score_4_$i.in
done
