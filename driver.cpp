#include "hangman.h"
using namespace std;

int main(){
    //create trie and add words to it
    Hangman t;
    if(!t.loadWords(TARGET_FILE)){
        cout << "No words were loaded."<<endl;
        return -1;
    }

    //repeatedly play until the user quits
    bool playAgain = true;
    while(playAgain){
        playAgain = t.playGame();
    }
    
    return 0;
}