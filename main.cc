#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

struct Row{char row[9];};

void menu();
void calculate(string str);
void set_display();
void create();
void change_dif();
void display();
void instructions();
void win();
string X, DIF;
int COUNT;
Row COLUMN[9];
Row SEC_COL[9];

int main(){
    // set up display
    set_display();

    // set up information
    srand(time(NULL));
    DIF = "Easy";

    // start game
    menu();
}

void menu(){
    system("clear");
    cout << " -- MINESWEEPER --\n" << endl;
    cout << " 1) Play Game\n";
    cout << " 2) How To Play\n";
    cout << " 3) Change Difficulty (Current: " << DIF << ")\n";
    cout << " 4) Exit Game\n" << endl;
    cout << " -> ";
    cin >> X;
    if (X == "1"){set_display(); create(); display();}
    else if (X == "2"){instructions();}
    else if (X == "3"){change_dif();}
    else if (X == "4"){
        system("clear");
        cout << "Thank you for playing!\n";
        exit(0);
    }
    else{menu();}
}

void set_display(){
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            COLUMN[i].row[j] = '-';
        }
    }
}

void instructions(){
    system("clear");
    cout << " -- HOW TO PLAY --\n" << endl;
    cout << " 1. Select a space (Example: A1, C9, etc)\n";
    cout << " 2. A number represents how many mines are around the space\n";
    cout << " 3. You can flag a space where you think a mine is\n";
    cout << " 4. To flag, type F after the space name (Example: A1F, G4F, etc)\n";
    cout << " 5. You win when every space is revealed or flagged\n" << endl;
    cout << " 1) Back To Menu\n" << " -> ";
    cin >> X;
    menu();
}

void change_dif(){
    system("clear");
    cout << " -- CHANGE DIFFICULTY --\n" << endl;
    cout << "Current Difficulty: " << DIF << endl;
    cout << " 1) Easy\n";
    cout << " 2) Challenging\n";
    cout << " 3) Extreme\n";
    cout << " 4) Back To Menu\n" << endl;
    cout << " -> ";
    cin >> X;
    if (X == "1"){
        DIF = "Easy";
        change_dif();
    }
    else if (X == "2"){
        DIF = "Challenging";
        change_dif();
    }
    else if (X == "3"){
        DIF = "Extreme";
        change_dif();
    }
    else if (X == "4"){menu();}
    else{change_dif();}
}

void display(){
    system("clear");
    cout << " | A  B  C  D  E  F  G  H  I\n";
    cout << "—|———————————————————————————\n";
    for (int i = 0; i < 9; i++){
        cout << (i + 1) << "| ";
        for (int j = 0; j < 9; j++){
            cout << COLUMN[i].row[j] << "  ";
        }
        cout << endl;
    }
    cout << endl;
    cout << " Enter tile location (A1 or A1F) [q: quit to menu]\n";
    cout << " -> ";
    cin >> X;
    if (X == "q" || X == "Q"){
        menu();
    }
    else{
        calculate(X);
    }
}

void create(){
    // set bomb spawn chance based on difficulty
    int dif;
    if (DIF == "Easy"){dif = 3;} // 20% chance
    else if (DIF == "Challenging"){dif = 4;} // 25% chance
    else{dif = 5;} // 33% chance

    // spawn bombs
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (rand() % dif < 1){SEC_COL[i].row[j] = 'X';}
            else{SEC_COL[i].row[j] = '-';}
        }
    }

    //remove illegal bombs
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(i == 0){ //first row
                if(j == 0){ //first element
                    if(SEC_COL[0].row[1] == 'X' && SEC_COL[1].row[0] == 'X' && SEC_COL[1].row[1] == 'X'){
                        SEC_COL[0].row[0] = '*';
                    }
                }
                else if(j == 8){ //last element
                    if(SEC_COL[0].row[7] == 'X' && SEC_COL[1].row[7] == 'X' && SEC_COL[1].row[8] == 'X'){
                        SEC_COL[0].row[8] = '*';
                    }
                }
                else{ //middle elements
                    if(SEC_COL[1].row[j-1] == 'X' && SEC_COL[1].row[j] == 'X' && SEC_COL[1].row[j+1] == 'X'){
                        if(SEC_COL[0].row[j-1] == 'X' && SEC_COL[0].row[j+1] == 'X'){
                            SEC_COL[0].row[j] = '*';
                        }
                    }
                }
            }
            else if(i == 8){ //last row
                if(j == 0){ //first element
                    if(SEC_COL[8].row[1] == 'X' && SEC_COL[7].row[0] == 'X' && SEC_COL[7].row[1] == 'X'){
                        SEC_COL[8].row[0] = '*';
                    }
                }
                else if(j == 8){ //last element
                    if(SEC_COL[8].row[7] == 'X' && SEC_COL[7].row[7] == 'X' && SEC_COL[7].row[8] == 'X'){
                        SEC_COL[8].row[8] = '*';
                    }
                }
                else{ //middle elements
                    if(SEC_COL[7].row[j-1] == 'X' && SEC_COL[7].row[j] == 'X' && SEC_COL[7].row[j+1] == 'X'){
                        if(SEC_COL[8].row[j-1] == 'X' && SEC_COL[8].row[j+1] == 'X'){
                            SEC_COL[8].row[j] = '*';
                        }
                    }
                }
            }
            else{ //middle rows
                if(j == 0){ //first element
                    if(SEC_COL[i].row[1] == 'X' && SEC_COL[i-1].row[0] == 'X' && SEC_COL[i-1].row[1] == 'X'){
                        if(SEC_COL[i+1].row[0] == 'X' && SEC_COL[i+1].row[1] == 'X'){
                            SEC_COL[i].row[j] = '*';
                        }
                    }
                }
                else if(j == 8){ //last element
                    if(SEC_COL[i].row[7] == 'X' && SEC_COL[i-1].row[7] == 'X' && SEC_COL[i-1].row[8] == 'X'){
                        if(SEC_COL[i+1].row[7] == 'X' && SEC_COL[i+1].row[8] == 'X'){
                            SEC_COL[i].row[j] = '*';
                        }
                    }
                }
                else{ //middle elements
                    if(SEC_COL[i-1].row[j-1] == 'X' && SEC_COL[i-1].row[j] == 'X' && SEC_COL[i-1].row[j+1] == 'X'){
                        if(SEC_COL[i+1].row[j-1] == 'X' && SEC_COL[i+1].row[j] == 'X' && SEC_COL[i+1].row[j+1] == 'X'){
                            if(SEC_COL[i].row[j-1] == 'X' && SEC_COL[i].row[j+1] == 'X'){
                                SEC_COL[i].row[j] = '*';
                            }
                        }
                    }
                }
            }
        }
    }

    // create numbers
    int num;
    for(int i = 0; i < 9; i++){
         for(int j = 0; j < 9; j++){
            if(SEC_COL[i].row[j] != 'X'){
                num = 0;
                if(i == 0){ //first row
                    if(j == 0){ //first element
                        if(SEC_COL[0].row[1] == 'X'){num++;}
                        if(SEC_COL[1].row[0] == 'X'){num++;}
                        if(SEC_COL[1].row[1] == 'X'){num++;}
                    }
                    else if(j == 8){ //last element
                        if(SEC_COL[0].row[7] == 'X'){num++;}
                        if(SEC_COL[1].row[7] == 'X'){num++;}
                        if(SEC_COL[1].row[8] == 'X'){num++;}
                    }
                    else{ //middle elements
                        if(SEC_COL[0].row[j-1] == 'X'){num++;}
                        if(SEC_COL[0].row[j+1] == 'X'){num++;}
                        if(SEC_COL[1].row[j-1] == 'X'){num++;}
                        if(SEC_COL[1].row[j] == 'X'){num++;}
                        if(SEC_COL[1].row[j+1] == 'X'){num++;}
                    }
                }
                else if(i == 8){ //last row
                    if(j == 0){ //first element
                        if(SEC_COL[8].row[1] == 'X'){num++;}
                        if(SEC_COL[7].row[0] == 'X'){num++;}
                        if(SEC_COL[7].row[1] == 'X'){num++;}
                    }
                    else if(j == 8){ //last element
                        if(SEC_COL[8].row[7] == 'X'){num++;}
                        if(SEC_COL[7].row[7] == 'X'){num++;}
                        if(SEC_COL[7].row[8] == 'X'){num++;}
                    }
                    else{ //middle elements
                        if(SEC_COL[8].row[j-1] == 'X'){num++;}
                        if(SEC_COL[8].row[j+1] == 'X'){num++;}
                        if(SEC_COL[7].row[j-1] == 'X'){num++;}
                        if(SEC_COL[7].row[j] == 'X'){num++;}
                        if(SEC_COL[7].row[j+1] == 'X'){num++;}
                    }
                }
                else{ //middle rows
                    if(j == 0){ //first element
                        if(SEC_COL[i-1].row[0] == 'X'){num++;}
                        if(SEC_COL[i-1].row[1] == 'X'){num++;}
                        if(SEC_COL[i].row[1] == 'X'){num++;}
                        if(SEC_COL[i+1].row[0] == 'X'){num++;}
                        if(SEC_COL[i+1].row[1] == 'X'){num++;}
                    }
                    else if(j == 8){ //last element
                        if(SEC_COL[i-1].row[7] == 'X'){num++;}
                        if(SEC_COL[i-1].row[8] == 'X'){num++;}
                        if(SEC_COL[i].row[7] == 'X'){num++;}
                        if(SEC_COL[i+1].row[7] == 'X'){num++;}
                        if(SEC_COL[i+1].row[8] == 'X'){num++;}
                    }
                    else{ //middle elements
                        if(SEC_COL[i-1].row[j-1] == 'X'){num++;}
                        if(SEC_COL[i-1].row[j] == 'X'){num++;}
                        if(SEC_COL[i-1].row[j+1] == 'X'){num++;}
                        if(SEC_COL[i].row[j-1] == 'X'){num++;}
                        if(SEC_COL[i].row[j+1] == 'X'){num++;}
                        if(SEC_COL[i+1].row[j-1] == 'X'){num++;}
                        if(SEC_COL[i+1].row[j] == 'X'){num++;}
                        if(SEC_COL[i+1].row[j+1] == 'X'){num++;}
                    }
                }
                SEC_COL[i].row[j] = to_string(num).at(0);
            }
        }
    }

    //reveal based on difficulty
    int rev = (rand() % 6) + 1;
    if(dif == 3){
        COUNT = 11;
        COLUMN[rev].row[rev] = SEC_COL[rev].row[rev];
        COLUMN[rev + 1].row[rev] = SEC_COL[rev + 1].row[rev];
        COLUMN[rev - 1].row[rev] = SEC_COL[rev - 1].row[rev];
        COLUMN[rev].row[rev + 1] = SEC_COL[rev].row[rev + 1];
        COLUMN[rev].row[rev - 1] = SEC_COL[rev].row[rev - 1];
        COLUMN[rev + 1].row[rev - 1] = SEC_COL[rev + 1].row[rev - 1];
        COLUMN[rev - 1].row[rev + 1] = SEC_COL[rev - 1].row[rev + 1];
        COLUMN[rev - 1].row[rev - 1] = SEC_COL[rev - 1].row[rev - 1];
        COLUMN[rev + 1].row[rev + 1] = SEC_COL[rev + 1].row[rev + 1];
        COLUMN[rev + 2].row[rev] = SEC_COL[rev + 2].row[rev];
        COLUMN[rev].row[rev + 2] = SEC_COL[rev].row[rev + 2];
    }
    else if(dif == 4){
        COUNT = 8;
        COLUMN[rev].row[rev] = SEC_COL[rev].row[rev];
        COLUMN[rev + 1].row[rev] = SEC_COL[rev + 1].row[rev];
        COLUMN[rev - 1].row[rev] = SEC_COL[rev - 1].row[rev];
        COLUMN[rev].row[rev + 1] = SEC_COL[rev].row[rev + 1];
        COLUMN[rev].row[rev - 1] = SEC_COL[rev].row[rev - 1];
        COLUMN[rev + 1].row[rev - 1] = SEC_COL[rev + 1].row[rev - 1];
        COLUMN[rev - 1].row[rev + 1] = SEC_COL[rev - 1].row[rev + 1];
        COLUMN[rev - 1].row[rev - 1] = SEC_COL[rev - 1].row[rev - 1];
    }
    else{
        COUNT = 5;
        COLUMN[rev].row[rev] = SEC_COL[rev].row[rev];
        COLUMN[rev + 1].row[rev] = SEC_COL[rev + 1].row[rev];
        COLUMN[rev].row[rev + 1] = SEC_COL[rev].row[rev + 1];
        COLUMN[rev].row[rev - 1] = SEC_COL[rev].row[rev - 1];
        COLUMN[rev - 1].row[rev] = SEC_COL[rev - 1].row[rev];
    }
}

void calculate(string str){
    int row, column;
    if(str.length() < 2 || str.length() > 3){
        display();
    }
    else{
        if(tolower(str.at(1)) == '1'){column = 0;}
        else if(tolower(str.at(1)) == '2'){column = 1;}
        else if(tolower(str.at(1)) == '3'){column = 2;}
        else if(tolower(str.at(1)) == '4'){column = 3;}
        else if(tolower(str.at(1)) == '5'){column = 4;}
        else if(tolower(str.at(1)) == '6'){column = 5;}
        else if(tolower(str.at(1)) == '7'){column = 6;}
        else if(tolower(str.at(1)) == '8'){column = 7;}
        else{column = 8;}

        if(tolower(str.at(0)) == 'a'){row = 0;}
        else if(tolower(str.at(0)) == 'b'){row = 1;}
        else if(tolower(str.at(0)) == 'c'){row = 2;}
        else if(tolower(str.at(0)) == 'd'){row = 3;}
        else if(tolower(str.at(0)) == 'e'){row = 4;}
        else if(tolower(str.at(0)) == 'f'){row = 5;}
        else if(tolower(str.at(0)) == 'g'){row = 6;}
        else if(tolower(str.at(0)) == 'h'){row = 7;}
        else{row = 8;}

        if(str.length() == 3){ //flagging
            if(SEC_COL[column].row[row] == 'X'){
                COLUMN[column].row[row] = 'X';
                COUNT++;
                if(COUNT == 81){win();}
                display();
            }
            else{
                system("clear");
                COLUMN[column].row[row] = '+';
                cout << " | A  B  C  D  E  F  G  H  I\n";
                cout << "—|———————————————————————————\n";
                for (int i = 0; i < 9; i++){
                    cout << (i + 1) << "| ";
                    for (int j = 0; j < 9; j++){
                        cout << COLUMN[i].row[j] << "  ";
                    }
                    cout << endl;
                }
                cout << endl << "INCORRECT FLAG\n";
                cout << "GAME OVER\n" << endl;
                cout << " 1) Play Again\n";
                cout << " 2) Back To Menu\n";
                cout << " 3) Exit Game\n";
                cin >> X;
                if(X == "1"){set_display(); create(); display();}
                else if(X == "2"){menu();}
                else{system("clear"); cout << "Thank you for playing!\n"; exit(0);}
            }
        }
        else{
            if(SEC_COL[column].row[row] == 'X'){
                system("clear");
                COLUMN[column].row[row] = '+';
                cout << " | A  B  C  D  E  F  G  H  I\n";
                cout << "—|———————————————————————————\n";
                for (int i = 0; i < 9; i++){
                    cout << (i + 1) << "| ";
                    for (int j = 0; j < 9; j++){
                        cout << COLUMN[i].row[j] << "  ";
                    }
                    cout << endl;
                }
                cout << endl << "YOU HIT A BOMB\n";
                cout << "GAME OVER\n" << endl;
                cout << " 1) Play Again\n";
                cout << " 2) Back To Menu\n";
                cout << " 3) Exit Game\n";
                cin >> X;
                if(X == "1"){set_display(); create(); display();}
                else if(X == "2"){menu();}
                else{system("clear"); cout << "Thank you for playing!\n"; exit(0);}
            }
            else{
                COLUMN[column].row[row] = SEC_COL[column].row[row];
                COUNT++;
                if(COUNT == 81){win();}
                display();
            }
        }
        
    }
}

void win(){
    system("clear");
    cout << " | A  B  C  D  E  F  G  H  I\n";
    cout << "—|———————————————————————————\n";
    for (int i = 0; i < 9; i++){
        cout << (i + 1) << "| ";
        for (int j = 0; j < 9; j++){
            cout << COLUMN[i].row[j] << "  ";
        }
        cout << endl;
    }
    cout << endl << "CONGRATULATIONS! YOU FOUND ALL THE MINES!\n";
    cout << " 1) Play Again\n";
    cout << " 2) Back To Menu\n";
    cout << " 3) Exit Game\n";
    cin >> X;
    if(X == "1"){set_display(); create(); display();}
    else if(X == "2"){menu();}
    else{exit(0);}
}
