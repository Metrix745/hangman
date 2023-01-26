//create a hangman game using tries made of nodes to store the words and have user input to play the game

#include "hangman.h"

//default constructor
Hangman::Hangman(){
    m_wrong = 0;
    m_secret = "";
    m_progress = "";
    m_root = new Node(' ');
}

//deconstructor
Hangman::~Hangman(){
    delete m_root;
}

bool Hangman::validString(string s){
    for(int i=0; i<int(s.size()); i++){
        char input = s[i];
        if(!isInString(VALID, input)){
            return false;
        }
    }
    return true;
}

//inserts word into the trie
void Hangman::insert(string s){
    if(!validString(s)){
        return;
    }
    Node* curr = m_root;
    for (int i = 0; i < int(s.length()); i++){
        if (curr->m_next[s[i] - 'a'] == nullptr){
            curr->m_next[s[i] - 'a'] = new Node(s[i]);
        }
        curr = curr->m_next[s[i] - 'a'];
    }
    curr->m_end = true;
}

//checks if word is in the trie
bool Hangman::search(string s){
    if(!validString(s)){
        return false;
    }
    Node* curr = m_root;
    for (int i = 0; i < int(s.length()); i++){
        if (curr->m_next[s[i] - 'a'] == nullptr){
            return false;
        }
        curr = curr->m_next[s[i] - 'a'];
    }
    return curr->m_end;
}

//function to check if a character is in a string
bool Hangman::isInString(string s, char c){
    for (int i = 0; i < int(s.length()); i++){
        if (s[i] == c){
            return true;
        }
    }
    return false;
}

//function to display hangman
void Hangman::display(){
    //draw a picture
    switch(m_wrong){
        case 0:
            cout << " _______" << endl;
            cout << " |/\n |\n |\n |\n |" << endl;
            break;
        case 1:
            cout << " _______" << endl;
            cout << " |/   | \n |\n |\n |\n |" << endl;
            break;
        case 2:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |\n |\n |" << endl;
            break;
        case 3:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |    |\n |\n |" << endl;
            break;
        case 4:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |   /|\n |\n |" << endl;
            break;
        case 5:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |   /|\\\n |\n |" << endl;
            break;
        case 6:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |   /|\\\n |   /\n |" << endl;
            break;
        case 7:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |   /|\\\n |   / \\\n |" << endl;
            break;
        default:
            cout << " _______" << endl;
            cout << " |/   | \n |   ( )\n |   /|\\\n |   / \\\n |" << endl;
    }
    //display progress and letters guessed
    cout << m_progress << endl;
    if(m_guessed.size() > 0){
        displayGuessed();
    }
}

//get the number of wrong guesses
int Hangman::getWrong(){
    return m_wrong;
}

//increment the number of wrong guesses
void Hangman::incWrong(){
    m_wrong++;
}

//load words from a text file into the trie
bool Hangman::loadWords(string data){
    ifstream inputStream(data);
    string target;
    while(inputStream){
        getline(inputStream, target, ',');
        insert(target);
        m_words.push_back(target);
    }
    inputStream.close();
    //if no words were loaded, make sure the program doesn't run
    if(m_words.size()==0){
        return false;
    }
    return true;
}

//pick a random word that exists in the trie
void Hangman::pickWord(){
    string randWord;
    do{
        int randIndex = rand() % m_words.size();
        randWord = m_words[randIndex];
    }while(!search(randWord));
    m_secret = randWord;

    //create a string of underscores the same length as the chosen word
    for (int i = 0; i < int(m_secret.length()); i++){
        m_progress += "_";
    }
}

//gather user input, only gets the first character
char Hangman::getInput(){
    string c;
    cout << "Guess a letter: ";
    cin >> c;
    string input = "";
    for(int i=0; i<int(c.size()); i++){
        input+=tolower(c[i]);
    }
    cout<<"Your input was: "<<input[0]<<endl;
    addToGuessed(input[0]);
    return input[0];
}

//add characters to the guessed vector for the user to refer back to
void Hangman::addToGuessed(char c){
    for(int i=0; i<int(m_guessed.size()); i++){
        if(m_guessed.at(i)==c){
            return;
        }
    }
    m_guessed.push_back(c);
}

//display all the characters that the player has guessed this round
void Hangman::displayGuessed(){
    cout << "You have guessed: " << m_guessed.at(0);
    for(int i=1; i<int(m_guessed.size());i++){
        cout <<", "<< m_guessed.at(i);
    }
    cout<<endl;
}

//runs the game
bool Hangman::playGame(){
    //picks a random word to be the next target
    pickWord();
    //start the game
    while (getWrong() < 7){
        //display hangman and progress
        display();

        //get user input
        char input = getInput();

        //check if the letter is in the word
        if (isInString(m_secret, input)){
            //update progress
            for (int i = 0; i < int(m_secret.length()); i++){
                if (m_secret[i] == input){
                    m_progress[i] = input;
                }
            }
        }else{
            //incorrect guess
            incWrong();
        }

        //check if the word has been guessed
        if (m_progress == m_secret){
            cout << "You win!" << endl;
            break;
        }
    }
    //if the player used all their guesses
    if (getWrong() == 7){
        display();
        cout << "You lose!" << endl;
    }

    cout << "The word was: "<< m_secret << endl;

    reset();

    cout << "Would you like to play again? (y/n) ";
    string playAgain;
    cin >> playAgain;
    if(playAgain[0] == 'Y' || playAgain[0] == 'y'){
        return true;
    }
    return false;
}

//reset the members for the next game
void Hangman::reset(){
    m_wrong=0;
    m_secret = "";
    m_progress = "";
    m_guessed.erase(m_guessed.begin(), m_guessed.end());
}