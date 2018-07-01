build:
		g++ -g -std=c++14 salbp1-simulated-annealing.cpp -o salbp1-sa

build_se:
		g++ -g -std=c++14 salbp1-simulated-annealing-se.cpp -o salbp1-sa-se

run:
	./salbp1-sa -c 54 -s 1530389452 -v < WEE-MAG.IN2

generate_gold:
	./salbp1-sa -c 54 -s 1530389452 -v < WEE-MAG.IN2
	mv outputs.txt gold_outputs.txt
