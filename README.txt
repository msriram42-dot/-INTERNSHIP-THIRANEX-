TIC TAC TOE - C++ MINI GAME

Extract the ZIP before running.
Windows: Double-click Run_Game.bat. Requires the MSYS2 GCC compiler already installed on your computer.
The launcher uses C:\msys64\ucrt64\bin automatically.

Two players share the keyboard. X starts. Enter positions 1-9.
Three matching marks in a row, column, or diagonal win.
A full board without a winner is a draw. Enter y to replay or n to exit.

PowerShell alternative (inside this folder):
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
g++ main.cpp -std=c++17 -o game.exe
.\game.exe

Includes loops, arrays, conditional logic, updated board display,
win/loss and draw detection, invalid move handling, and replay.
