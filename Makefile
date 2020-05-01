FLAGS = -pedantic-errors -std=c++11

card.o: classes/card.cpp classes/card.h
	g++ $(FLAGS) -c $<	

creature.o: classes/creature.cpp classes/creature.h
	g++ $(FLAGS) -c $<

battle.o: cpp/battle.cpp hfiles/battle.h
	g++ $(FLAGS) -c $<

printbattle.o: cpp/printbattle.cpp hfiles/battle.h
	g++ $(FLAGS) -c $<

test.o: cpp/test.cpp hfiles/battle.h
	g++ $(FLAGS) -c $<

movement.o: cpp/movement.cpp hfiles/movement.h
	g++ $(FLAGS) -c $<

titleScreen.o: cpp/titleScreen.cpp hfiles/titleScreen.h
	g++ $(FLAGS) -c $<

tutorial.o: cpp/tutorial.cpp hfiles/tutorial.h
	g++ $(FLAGS) -c $<

test: test.o battle.o printbattle.o creature.o card.o titleScreen.o tutorial.o movement.o
	g++ $(FLAGS) $^ -o $@
	mv test.o ofiles
	mv battle.o ofiles
	mv printbattle.o ofiles
	mv creature.o ofiles
	mv card.o ofiles
	mv titleScreen.o ofiles
	mv tutorial.o ofiles
	mv movement.o ofiles
