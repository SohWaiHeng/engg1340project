FLAGS = -pedantic-errors -std=c++11

card.o: classes/card.cpp classes/card.h
	g++ $(FLAGS) -c $<	

creature.o: classes/creature.cpp classes/creature.h
	g++ $(FLAGS) -c $<

battle.o: battle.cpp battle.h
	g++ $(FLAGS) -c $<

printbattle.o: printbattle.cpp battle.h
	g++ $(FLAGS) -c $<

test.o: test.cpp battle.h
	g++ $(FLAGS) -c $<

test: test.o battle.o printbattle.o creature.o card.o
	g++ $(FLAGS) $^ -o $@
	mv test.o ofiles
	mv battle.o ofiles
	mv printbattle.o ofiles
	mv creature.o ofiles
	mv card.o ofiles
