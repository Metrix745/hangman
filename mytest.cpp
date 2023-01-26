#include "hangman.h"

const string INVALID = "109357190387";

class Tester{
    public:
    bool construct();
    
    bool insertNorm(Hangman& t, vector<string>& words);
    bool insertError();

    bool searchNorm(Hangman& t, vector<string>& words);
    bool searchError(Hangman& t);
};

int main(){
    Tester test;
    Hangman t;
    vector<string> words;
    cout<<"test construct "<<test.construct() <<endl;
    cout<<"test insertNorm "<<test.insertNorm(t, words) <<endl;
    cout<<"test insertError "<<test.insertError()<<endl;
    cout<<"test searchNorm "<<test.searchNorm(t, words) <<endl;
    cout<<"test searchError "<<test.searchError(t)<<endl;
    return 0;
}

bool Tester::construct(){
    Hangman t;
    if (t.m_wrong != 0 || t.m_secret != "" || t.m_progress != "" || !t.m_root){
        return false;
    }
    return true;
}

bool Tester::insertNorm(Hangman& t, vector<string>& words){
    //load words into the trie
    ifstream inputStream(TARGET_FILE);
    string target;
    while(inputStream){
        getline(inputStream, target, ',');
        t.insert(target);
        words.push_back(target);
    }
    inputStream.close();

    //check that each word has a path
    string testString;
    Node* curr;
    for(int i=0; i<int(words.size()); i++){
        testString = words.at(i);
        curr = t.m_root;
        for(int j=0; j<int(testString.size()); j++){
            curr = curr->m_next[testString[j]-'a'];
            if(curr->m_letter != testString[j]){
                cout << testString << " : "<<testString[j-1]<< " : " << curr->m_letter <<endl;
                return false;
            }
            
        }
    }
    return true;
}

bool Tester::insertError(){
    Hangman t;
    t.insert(INVALID);
    if(t.search(INVALID)){
        return false;
    }
    return true;

}

bool Tester::searchNorm(Hangman& t, vector<string>& words){
    for(int i=0; i<int(words.size());i++){
        if(!t.search(words[i])){
            return false;
        }
    }
    return true;
}

bool Tester::searchError(Hangman& t){
    if(t.search(INVALID)){
        return false;
    }
    return true;
}