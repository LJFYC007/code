for i in {1..5}; do
    ./gen 100 0 > Subtask1/sky$i.in
    time ./sky < Subtask1/sky$i.in > Subtask1/sky$i.out
done

for i in {1..5}; do
    ./gen 1000 0 > Subtask2/sky$i.in
    time ./sky < Subtask2/sky$i.in > Subtask2/sky$i.out
done

for i in {1..5}; do
    ./gen 100000 1 > Subtask3/sky$i.in
    time ./sky < Subtask3/sky$i.in > Subtask3/sky$i.out
done

for i in {1..5}; do
    ./gen 100000 2 > Subtask4/sky$i.in
    time ./sky < Subtask4/sky$i.in > Subtask4/sky$i.out
done

for i in {1..5}; do
    ./gen 5000 0 > Subtask5/sky$i.in
    time ./sky < Subtask5/sky$i.in > Subtask5/sky$i.out
done

for i in {1..5}; do
    ./gen 100000 0 > Subtask6/sky$i.in
    time ./sky < Subtask6/sky$i.in > Subtask6/sky$i.out
done
