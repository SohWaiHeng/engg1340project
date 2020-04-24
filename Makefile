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

ofiles/battle.o: battle.cpp battle.h
	g++ $(FLAGS) -c $<
	mv battle.o ofiles

ofiles/battletest.o: battletest.cpp battle.h
	g++ $(FLAGS) -c $<
	mv battletest.o ofiles

classes/test: ofiles/test.o ofiles/creature.o ofiles/card.o
	g++ $(FLAGS) $^ -o $@
	mv test classes

battletest: ofiles/battletest.o ofiles/battle.o ofiles/creature.o ofiles/card.o
	g++ $(FLAGS) $^ -o $@
