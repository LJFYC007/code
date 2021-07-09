for i in {1..6}; do
    ./gen 1000 > number$i.in
    time ./std < number$i.in > number$i.out
done

for i in {7..12}; do
    ./gen 99991 > number$i.in
    time ./std < number$i.in > number$i.out
done

for i in {13..20}; do
    ./gen 200000 > number$i.in
    time ./std < number$i.in > number$i.out
done

