FLAGS = -pedantic-errors -std=c++11

card.o: classes/card.cpp classes/card.h
	g++ $(FLAGS) -c $<	

creature.o: classes/creature.cpp classes/creature.h
	g++ $(FLAGS) -c $<

avatar.o: classes/avatar.cpp classes/avatar.h
	g++ $(FLAGS) -c $<

battle.o: cpp/battle.cpp hfiles/battle.h hfiles/colours.h hfiles/menu.h
	g++ $(FLAGS) -c $<

main.o: cpp/main.cpp hfiles/titleScreen.h hfiles/battle.h hfiles/tutorial.h hfiles/menu.h hfiles/movement.h hfiles/colours.h classes/creature.h classes/avatar.h classes/currency.h
	g++ $(FLAGS) -c $<

menu.o: cpp/menu.cpp hfiles/menu.h hfiles/movement.h hfiles/titleScreen.h hfiles/colours.h hfiles/battle.h classes/avatar.h classes/creature.h classes/currency.h
	g++ $(FLAGS) -c $<

movement.o: cpp/movement.cpp hfiles/movement.h hfiles/colours.h
	g++ $(FLAGS) -c $<

opponent.o: cpp/opponent.cpp hfiles/battle.h
	g++ $(FLAGS) -c $<

printbattle.o: cpp/printbattle.cpp hfiles/battle.h hfiles/colours.h
	g++ $(FLAGS) -c $<

titleScreen.o: cpp/titleScreen.cpp hfiles/titleScreen.h hfiles/menu.h
	g++ $(FLAGS) -c $<

tutorial.o: cpp/tutorial.cpp hfiles/tutorial.h hfiles/colours.h hfiles/movement.h hfiles/battle.h
	g++ $(FLAGS) -c $<

cardmaster: card.o creature.o avatar.o battle.o main.o menu.o movement.o opponent.o printbattle.o titleScreen.o tutorial.o
	g++ $(FLAGS) $^ -o $@
	mv card.o ofiles
	mv creature.o ofiles
	mv avatar.o ofiles
	mv battle.o ofiles
	mv main.o ofiles
	mv menu.o ofiles
	mv movement.o ofiles
	mv opponent.o ofiles
	mv printbattle.o ofiles
	mv titleScreen.o ofiles
	mv tutorial.o ofiles
