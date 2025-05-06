# Lights-Out
 A simple game where your one and only objective is to put out all the light. The gist is simple, but do you think you are up for the task?

 GAMEPLAY CORE:
 The game will represent a 3x3 grid blocks, some with light on or off. Clicking on a block will cause its adjacent blocks to switch their state. The goal
 is to put out all the light.

 CODING CORE:
 There will be 2 built-in modes to play (Normal Mode and Hard Mode), player can choose which one to play by clicking on either of the options. Once done, renderer
 will switch scene to grid stage and the game will begins. There can be an ingame timer for players to track how much time has passed, or a move counter to
 track how many time the player has clicked. The game will randomized a certain amount of blocks to be clicked beforehand. Throughout the game, system will
 track the state of each block (either clicked or not clicked, 2 clicks = not clicked) through a matrix of n*n size. The game will end once the matrix only
 have unclicked blocks (which is equivalent to turning all the light off). Clicking any key afterwards will end the renderer and terminate the program.
    + Normal Gamemode: Comes with 3 hints and no timer. Player can take as much time as they need to beat the game.
    + Hard Gamemode: There is no more hints. And now you must beat the game within a certain time limit to win.

SOURCES AND CREDITS:
    - Sprites and/or Images:
        + Blocks: LTNC.docx's Tic-tac-toe.
    - Audios and/or Sound Effects:
        + Title: Safe Space - ThatOneMTFGuy.
        + Normal Gamemode: Sundowner - Key After Key
        + Hard Gamemode: Eternal Hope, Eternal Fight - Exedious.
        + Clock Tick: https://www.youtube.com/watch?v=G5NyXL47S74 & Creative Common Licenses.
    - Codes:
        + Bases of graphics.h, logic.h and a part of main.cpp: LTNC.docx.
        + Timer logic: LazyFoo's SDL Tutorial.
    - Font:
        + DK Cool Crayon: David Kerchoff - Hanoded Fonts License & FAQ.
