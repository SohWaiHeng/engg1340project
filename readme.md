# engg1340project

## GROUP 102 
1. Yew Fu Yen - 3035667168
2. Soh Wai Heng - 3035709502

# PROJECT TOPIC - THE CARDMASTER

## Game description:

Our group is planning to make a text-based game which combines the concept of both an RPG (role-playing game) and a trading card game.

The game follows a main story, and just like any RPGs, the player will be able to go around maps of different regions, to complete a variety of missions along with the progression of the storyline.
The main goal of the game is to complete the storyline.
There are three types of collectibles in the games, which are creatures, cards and in-game currencies. The player will collect these items along with the progression of the game.
The creatures are used to build a deck to be used by the player in battles. Cards can be added to creatures, and in-game currencies are used to level up creatures or buy items in game.
Along the journey, the player will be confronted with different opponents (computer AI) during mission tasks or at some locations in the map. The player will have to battle with these opponents in order to continue with the game.

These battles will be carried out in the form of a turn-based card game.The battle rules are implemented based on an old mobile card game named Card Wars Kingdom.
The players will deploy the creatures in his deck to the battlefield, then decide how he should use his creatures/cards based on the elixir he owns that round.
To win the battle, the player has to defeat all of opponent's creature deployed on the battlefield.
The in-depth battle rules are written in the section ```Rules in the battlefield``` below.

As the reward of winning the battle, the player will obtain new creatures/cards and in-game currencies to improve his inventories.
Battles are usually required for the player to complete a mission when progressing with the main story. There would be a number of missions designed for the player to complete in game.
All these missions also serve to prepare the player to face the last and biggest battle of our game, which is the "final boss". 
The game is completed when the player has successfully defeated the "final boss" and thus finishes the story.


## Features in game in relation to the coding requirements:

### 1. Generation of random game sets or events
	- There are several features in the game which can be randomly generated including:
	  1. Random locations in map where the player will be confronted with an opponent (with certain probabilities)
	  2. Random draw from the player's available card pool in battle (totally random)
	  3. Random moves by the the opponent's Computer AI
	  4. Random drops and rewards given to player after winning a battle (with certain probabilities)
	  5. Random draw of a creature given to player every time the player buys a treasure chest (with certain probabilities)

### 2. Data structures for storing game status
   	- Creatures' data like their names, stats and cards will be stored in structs
	- List of the player's creature will be stored in linked list / array of structs
	- Cards will be represented in a class, with member functions (function of the card) and member variables (name of card, stats of card, whom this card is played on)
	- Currencies will also be stored in structs, since there are different type of currencies
	- In the game there will be a menu page where the player can access all the creatures he has, check his stats and build his deck
	- We plan to represent the menu page in a class, for which its member functions are used to perform different functions available in the menu page (eg: build deck from creature list)

### 3. Dynamic memory management
	- Linked list is used to store the creatures the player owns. The linked list can be easily added with new creatures and thus memory can be easily allocated accordingly
	- Data needed during runtime in the game are only loaded from certain txt files during runtime if possible. We plan to use a series of dynamic arrays and variables to achieve this. After these data are used the memory will be cleaned after changes were output and saved in txt files.

### 4. File I/O
	- The game will include both save and load functions
	- The player can save the game at certain save points
	- Saving will take all the info of the creatures owned by the player, the player's amount of in-game currencies, and the part of storyline the player is in at the time of saving, and output them to a txt file (file name decided by player)
	- The player can continue his game by loading an available txt save file
	- Loading will take in some necessary info from txt file (when starting the game) and memory will be allocated to store these data
	- Some game data will also be stored in txt files and is loaded when needed. For example: maps, full list of creatures, full list of cards

### 5. Program codes in multiple files
	- We are going to split the whole code into multiple cpp, header and txt files.
	- Since our game is based on a storyline, we plan to split different events that will happen in the story into blocks of functions. These story function blocks will be written in different cpp files and be arranged in the main functions sequentially.
	- Some necessary functions like functions for the player to move around the map, functions for battling will also be written in different cpp files.
	- Multiple functions of the same category of usage (eg: for walking on map) can be declared in the sanme header file.
	- txt files are used to store data like maps, list of creatures etc.

## Rules in the battlefield:
TheThe concept of our card game will be based on an old game named Card Wars Kingdom. Before the battle commences, the player has to construct a deck of creature from all the creatures he owned before the battle begins. The deck can be constructed or changed anytime in the menu page. The player has to come up with an effective strategy and choose the most suitable creatures for the battle in order to increase his/her chances of winning.

a. Creatures:
        
	i. There will be many different creatures available in game, and they are there to assist the player in battling the opponents. These creatures are categorised into different rarities (eg: common, rare, legendary, etc.). This will be explained in the "types of creatures" section later.
	
	ii. Each creature will have six stats: hp (health), atk (attack damage), mgc (magic damage), crt (critical damage chance), elixir cost and level.
	
	iii. Hp is health, the creature dies in battle when the hp goes under 0. The player will not lose the creature permanently after the creature died in a battle.
	
	iv. Besides the four basic stats, each creature comes with a set of 5 cards.
	
	v. Each card has different functionalities, and the set of 5 cards is always fixed (they are not allowed to be removed, changed or swapped between creatures)
	
	vi. The creatures are started at level 1 when the player obtains them in chests.
	
	vii. The player can upgrade their creatures to a higher level by feeding them with cakes, which can be obtained from the battles, or feeding them with other creatures which are not needed by the player. (Feeding with creatures gives more XP than cakes)
	
	viii. Levelling up increases a creature's hp, atk, mgc. and crt.
	
	ix. The maximum level of a creature is 50.

b. Getting the creatures:

The player can own creatures by opening the treasure chests, and these chests can be earned from either the rewards of winning battles or paying in-game money. The creatures gotten by the player from the chest are completely random. However, there will be few different types of chests available, and the more expensive the chest is, the higher the chances of getting a rarer creature.

c. Basic rules of battle: 

    i. There will be a set amount of elixir given to the player in every single round. In round 1, the player will have one elixir, in round 2, the player will have 2 elixirs, and so on. (The maximum number of elixirs given is 10, so even if the game has exceeded 10 rounds, the player will only get 10 elixirs)
	
	ii. Elixir is used to perform actions in each round. Different action requires different amount of elixir.
	
	iii. The player or AI is randomly chosen to start the game.
	
	iv. At the start of the battle, 5 cards from the 25 available cards (5 creatures) are randomly drawn to the player's hand.
	
	v. At round 1, the battlefield will be empty, the starting player (AI or player) will have to choose a creature from his deck and be deployed on the battlefield. Deploying a creature costs one elixir.
	
	vi. To move to the next player's turn, the player should type 'next'.
	
	vii. The rules are the same for the second player. When the player has completed that round, he/she should type 'next' to move to the new round.
	
	viii. At round 2, the player can decide on how he wishes to use the 2 elixirs he/she has. He can either deploy two more creatures onto the field, use a card with elixir cost less than or equals to 2, etc.
	
	ix. The rules for all the remaining rounds are the same. 
	
	x. A player loses when all of his/her creatures deployed on the field died, even if he/she still has undeployed creatures in the deck.

d. Moves player can make in a battle:

	i. Attack: 
      	- by typing "<your_creature_name> attack <opponent_creature_name>"
		- opponent's creature will be attacked and its hp will decrease by the atk damage of the attacking creature
		- total elixir of current player decrease by the elixir cost of the attacking creature
		- a card is drawn from the 5 cards of the attacking creature
		- there is a probability of crt % that the attack will be a critical attack. Critical attack = attack + 35%
		
	ii. Deploy: 
      	- by typing "deploy <creature no.>"
		- adding the creature on battlefield
		- total elixir decrease by 1
		
	iii. Use Card: 
      	- by typing "use card <number> on <own_or_opponent's_creature>"
        
e. Cards

    i. The cards allow a lot of special effects to be used in battles and hence are able to increase the depth of the game.
    
	ii. Name and functions of cards:
	
		  1. magic attack: play magic attack card on the player's own creature to attack an opponent's creature using magic attack, the attacked creatured will lose mgc amount of hp, no cards drawn after magic attack
		  
		  2. heal: heal by x% hp
		  
		  3. add Elixir: play card to add elixir
        		eg: a card costs 3 elixirs, description: gain 2 elixirs per opponent's creature on the field
        		If the oppponent has three creatures on the field, the player can use 3 elixirs to gain 6 elixirs, which gives him/her a net gain 3 elixirs.
			
		  4. atk up: increase atk by x%
		  
		  5. atk down: decrease atk by x%
		  
		  6. poison: poison by x%, meaning after every round, the creature poisoned will automatically decrease x% hp
		  
		  7. direct damage: directly decrease x% hp
		  
		  8. haste: decrease attack elixir cost by 1 for n rounds
		  
		  9. shield: gain and shields to shield from any n number of attacks
		  
		  10. thorns: reflect damage to the attacker, not applicable to magic attack
		  
		  11. elixir sap: steal elixir away from opponent
        		eg: play 1 elixir sap card on creature a, and use creature a to attack opponent creature b, then the player's elixir + 1, and opponent's elixir - 1
			
		  12. silence: play silence card on creature, and no card can be played anymore on the creature for n rounds
		  
		  13. block card: prevents card to be drawn from the creature for n rounds
		  
		  14. heroic: can only play on own creature, eg: creature a, b and c are on the field, if the player plays heroic card on creature a, in opponent's turn, the opponent can only attack creature a
		  
		  15. defence up: damage received decrease by x%
		  
		  16. blind: the creature blinded will miss its next attack
		  
		  17. area effect: eg: creatures a, b and c are on the field, area heal played on b will heal a, b and c, area heal played on a will heal a and b, area effect affects the adjacent creatures.
		  
		  18. remove: remove effects like remove poison, remove shield, etc.
		  
	iii. A card can have multiple functions and criterias for the fucntions to activate:
	
		eg: - card A: 10% poison, if creature has thorns, attack down for 2 turns

f. Types of creatures: 

    i. Type 1: These creatures have very high atk value, low/average mgc value, cards found on them usually have functions like atk up, haste.
    
	ii. Type 2: These creatures have very high mgc value, low atk value, cards found on them usually have functions like magic attack, shield, elixir sap.
	
	iii. Type 3: These creatures have average atk and mgc, cards found on them usually have functions like poison, silence, block card, blind.
	
	iv. Type 4: These creatures have high hp, average atk and mgc, cards found on them usually have functions like thorns, defence up, heroic.
	
	v. Type 5: These creatures have low hp, low atk, high mgc, cards found usually have functions like heal, direct damage, remove.

g. Player avatar:

    i. The player can choose and change avatar for himself/herself in the game. Each avatar will have a set of five unique cards.
    
	ii. In a battle, whenever a card is played, the elixir costs used to play the cards will accumulate, and we will call this accumulation 'meter'.
	
	iii. When the meter is full, for example 25, the player will be able to draw a card from one of the avatar's cards.
	
	iv. These 5 cards usually provides insane values and can help the player to get an upper hand in the battle. (eg: 0 elixir cost, area 3 shields and area thorns for 3 turns)


h. Example of how the battlefield looks like:

 		 ____________________________________________________________________________
		|                                                                            |
		|               atk: 88          atk: 344          atk: 10                   |
		|               mgc: 888         mgc: 109          mgc: 9999                 |
		|               hp: - 11         hp: --- 156       hp: ----- 10              |
		|               v[ o w o ]v       "{ 0 _ o }"       |[ $ _ $ ]|              |
		|                 NyanCat            Shrek             Najib                 |
		|                                                                            |
		|_____                                                                       |
		|(*-*)| 3  These are                                                         |
		|_____|    undeployed                                                        |
		|_____     creatures                                                         |
		|[=3=]| 5                                                                    |
		|_____|            Baymax            Happy           CryingMan               |
		|               \[ 0 - 0 ]/       ~( ^ u ^ )~       ={ T w T }=              |
		|               cost: 4           cost: 2           cost: 3                  |
		|               hp: ----- 154     hp: ----- 176     hp: ----- 333            |
		|               atk: 165          atk: 175          atk: 86                  |
		|               mgc: 256          mgc: 300          mgc: 190                 |
		|           ________  ________  ________  ________  ________                 |
		|          |  (1)   ||  (2)   ||  (3)   ||  (4)   ||  (5)   |                |
		|          |0 elixir||2 elixir||5 elixir||3 elixir||8 elixir|                |
		|          |        ||        ||        ||        ||        |    ELIXIR:     |
		|          |ultimate|| other  ||        ||        ||        |       2        |
		|          |  wish  ||  names ||        ||        ||        |                |
		|          |________||________||________||________||________|                |
		|____________________________________________________________________________|



## Other functions/features in our game:

1. Title screen: 

Player will be given the choice of starting a new game or continue their previously saved game progress, which has been stored in other files.

2. Tutorial: 

If the player chooses to start a new game, a tutorial page will be prompted to teach the player on the rules of the game and different controls and keys used in the game at the beginning of the game. The player is given the choice to skip the tutorials. This tutorial page will be loaded from another file.

3. Map/player movement:

We will create a map and divide it into smaller blocks (25 x 65 characters) to be displayed on the screen terminal. The player can move his/her character around the map using the keys WASD via the paths set by us, and attempts to walk through the walls will lead to an error message. When the character has reached the sides of the map, another block of the map will be displayed to replace the existing one. The player is allowed to fast-forward their movement by entering the characters shown on different junctions.

An example of a single block of map is shown below:

                                65 columns

	OOOOOOOOOOO|    |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOO|    |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOO|    |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOO|  G                                    |OOOOOOOOOOOOO
	OOOOOOOOOOO|__________________________________  F  |OOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO|    |OOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO|    |OOOOOOOOOOOOO
	OOOOO|             |OOOOOOOOOOOOOOOOOOOOOOOOOO|    |OOOOOOOOOOOOO
	OOOOO|             |OOOOOOOOOOOOOOOOOOOOOOOOOO|    |OOOOOOOOOOOOO
	OOOOO|             |OOOOOOOOOOOOOOOOOOOOOOOOOO|    |OOOOOOOOOOOOO
	OOOOO|   LIBRARY   |OOOOOOOO|                   E  |OOOOOOOOOOOOO
	OOOOO|             |OOOOOOOO|  J   ________________|OOOOOOOOOOOOO
	OOOOO|             |OOOOOOOO|     |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO     25 rows
	OOOOO|_____   _____|OOOOOOOO|     |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOO| |OOOOOOOOOOOOOO|     |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO    
	(3.3)       A                  C  |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	_________________ B ______________|OOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOO|H_______________  I|OOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOO
	OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO| |OOOOOOOOOOOOOOOOOOOOOOOOOOO
