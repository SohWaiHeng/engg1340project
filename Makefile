FLAGS = -pedantic-errors -std=c++11

ofiles/card.o: classes/card.cpp classes/card.h
	g++ $(FLAGS) -c $<
	mv card.o ofiles

ofiles/creature.o: classes/creature.cpp classes/creature.h
	g++ $(FLAGS) -c $<
	mv creature.o ofiles

ofiles/test.o: classes/test.cpp classes/creature.h
	g++ $(FLAGS) -c $<
	mv test.o ofiles

test: ofiles/test.o ofiles/creature.o ofiles/card.o
	g++ $(FLAGS) $^ -o $@
