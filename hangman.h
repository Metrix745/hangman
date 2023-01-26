#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

const string TARGET_FILE = "food.csv";
const int ALPHABET = 26;
const string VALID = "qwertyuiopasdfghjklzxcvbnm";
class Hangman;
class Tester;

class Node
{
    public:
    friend class Hangman;
    friend class Tester;
    Node(char l){
        m_letter = l;
        m_end = false;
        m_next = vector<Node*>(ALPHABET, nullptr);
    }

    ~Node(){
        for(int i=0; i<int(m_next.size()); i++){
            if(m_next.at(i)){
                delete m_next.at(i);
            }
        }
        m_next.clear();
    }
    private:
    char m_letter;
    bool m_end;
    vector<Node*> m_next;
};

class Hangman{
    public:
        friend class Tester;
        Hangman();
        ~Hangman();
        bool validString(string s);
        void insert(string s);
        bool search(string s);
        bool isInString(string s, char c);
        void display();

        int getWrong();
        void incWrong();

        bool loadWords(string data);
        void pickWord();

        char getInput();
        void addToGuessed(char c);
        void displayGuessed();

        bool playGame();
        void reset();

    private:
        Node* m_root;
        int m_wrong;
        vector<string> m_words;
        vector<char> m_guessed;
        string m_secret;
        string m_progress;
};

