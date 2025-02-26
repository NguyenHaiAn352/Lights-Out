# Lights-Out
 A simple game where your one and only objective is to put out all the light. The gist is simple, but do you think you are up for the task?

 GAMEPLAY CORE:
 The game will represent a nxn grid blocks, some with light on or off. Clicking on a block will cause its adjacent blocks to switch their state. The goal
 is to put out all the light.

 CODING CORE:
 There will be 3 built-in mode to play (3x3, 4x4, 5x5), player can choose which one to play by clicking on either of the options. Once done, renderer
 will switch scene to grid stage and the game will begins. There can be an ingame timer for players to track how much time has passed, or a move counter to
 track how many time the player has clicked. The game will randomized a certain amount of blocks to be clicked beforehand. Throughout the game, system will
 track the state of each block (either clicked or not clicked, 2 clicks = not clicked) through a matrix of n*n size. The game will end once the matrix only
 have unclicked blocks (which is equivalent to turning all the light off). Clicking any key afterwards will end the renderer and terminate the program.
