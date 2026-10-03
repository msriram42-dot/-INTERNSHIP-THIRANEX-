#include <iostream>
#include <limits>
#include <string>
using namespace std;

void displayBoard(const char b[]) {
    cout << '\n';
    for (int i=0; i<9; i+=3) {
        cout << ' ' << b[i] << " | " << b[i+1] << " | " << b[i+2] << '\n';
        if (i<6) cout << "---+---+---\n";
    }
    cout << '\n';
}
bool hasWon(const char b[], char p) {
    const int lines[8][3]={{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    for (const auto& l:lines)
        if (b[l[0]]==p && b[l[1]]==p && b[l[2]]==p) return true;
    return false;
}
int main() {
    cout << "TIC TAC TOE - TWO PLAYERS\n";
    string replay;
    do {
        char b[9]={'1','2','3','4','5','6','7','8','9'};
        char p='X'; int moves=0; bool won=false;
        displayBoard(b);
        while (moves<9) {
            int choice;
            cout << "Player " << p << ", choose a position (1-9): ";
            if (!(cin>>choice)) {
                if (cin.eof()) return 0;
                cin.clear(); cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout << "Please enter a number.\n"; continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if (choice<1 || choice>9) { cout << "Choose a position from 1 to 9.\n"; continue; }
            if (b[choice-1]=='X' || b[choice-1]=='O') { cout << "That position is occupied. Try again.\n"; continue; }
            b[choice-1]=p; ++moves; displayBoard(b);
            if (hasWon(b,p)) {
                cout << "Player " << p << " wins!\nPlayer " << (p=='X'?'O':'X') << " loses.\n";
                won=true; break;
            }
            p=(p=='X')?'O':'X';
        }
        if (!won) cout << "It is a draw!\n";
        while (true) {
            cout << "Play again? (y/n): ";
            if (!(cin>>replay)) return 0;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            if (replay=="y" || replay=="Y" || replay=="n" || replay=="N") break;
            cout << "Please enter y or n.\n";
        }
    } while (replay=="y" || replay=="Y");
    cout << "Thanks for playing!\n";
}
