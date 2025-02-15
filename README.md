# basic-snake-game
This is my project for Introduction To Programming course in C

Our project is to implement the famous game (Snake) but it has some differences from what we have seen before.
General description of the game:
Snake is one of the oldest and most popular computer games, and the logic of the game is very simple. The only rules in this game are not to hit the walls and the snake itself, and our snake game only needs to eat the food on the playing field to survive.
Our game is for two players. That is, there are two snakes on the board, each controlled by one of the participants. First, the name of each participant is taken from the console.
Game screen:
The game board includes 2 snakes, apples, bombs, and side walls Used to represent each character:
'@' for walls (borders)
'$' for apple (fruit)
'B' for bombs
'O' and 'o' for snake1 (for head and body)
'&' and '8' for snake2 (for head and body)
The game screen is updated after a while using the (sleep) function. We have 3 modes for game speed: slow, medium, and fast, which the user determines. The snake moves to the right with the arrow keys on the keyboard and the snake moves to the left with the keys d, a, and s.
The score of each snake is displayed instantly on the console screen.
Game logic:
When the game starts, the snakes start moving and whenever one of the snakes dies, the game ends. 
If one of the snakes eats the fruit, one unit is added to its score and length. Fruit appears randomly on the screen at each stage.
If one of the snakes hits the bomb, it dies and the game is over. The bomb appears randomly on the screen for the first time and its location does not change.
If one of the snakes hits the wall, it also dies and the game is over. All walls are on the border.
Every time a snake dies, the game ends and 4 points are added to the snake that did not die.
When the game is over, whichever snake has the most points is declared the winner.

The code for this game uses a functional programming approach and basic programming concepts such as conditions, loops, and structs in the C programming language.

