FLAGS = -pedantic-errors -std=c++11

ofiles/card.o: classes/card.cpp classes/card.h
	g++ $(FLAGS) -c $<
	mv card.o ofiles

ofiles/creature.o: classes/creature.cpp classes/creature.h
	g++ $(FLAGS) -c $<
	mv creature.o ofiles

ofiles/battle.o: battle.cpp battle.h
	g++ $(FLAGS) -c $<
	mv battle.o ofiles

ofiles/printbattle.o: printbattle.cpp battle.h
	g++ $(FLAGS) -c $<
	mv printbattle.o ofiles

ofiles/test.o: test.cpp battle.h
	g++ $(FLAGS) -c $<
	mv test.o ofiles

test: ofiles/test.o ofiles/battle.o ofiles/printbattle.o ofiles/creature.o ofiles/card.o
	g++ $(FLAGS) $^ -o $@
