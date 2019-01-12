This is a simple tic tac toe app coded in C++ from scratch as my finals for my introductory C++ class in college.

The computer plays against you by picking an open spot randomly, without knowing whether it not it should block you from winning the game.

In other words, there is no (un)supervised learning enforced on this script. The machine just chooses randomly if a spot is open.

Feel free to browse around it if you would like and maybe copy the source code to tamper with it as you may...

----------------------------------------------------------------------------------------------------------------------

How to run it
-------------

• Open your terminal

• Clone the Repository
git clone https://github.com/cartagenae/TicTacToe-CPP

• Log on to your directory
cd TicTacToe-CPP

• Compile the program
g++ tictactoe.cpp -o tictactoe

• Run it
./tictactoe

----------------------------------------------------------------------------------------------------------------------

** NOTE: You can also change the dimensions of the grid by adjusting the SIZE variable by #define. It is set at 3 by default but you can set it up 12 if you would like

e.g.
tictactoe.cpp
...
#define LETTER 0
#define NUMBER 1
#define SIZE 3    <-- Change and then recompile your program with g++
...

Thanks for visiting,

Eric Cartagena
