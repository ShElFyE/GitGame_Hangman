#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ctime> 
using namespace std;

class Word {
private:
    string wordG;
    vector<bool> guessed_;
public:
    Word(string word) : wordG(word) {
        guessed_.resize(wordG.length(), false);
    }
    Word() = default;
    bool checkL(char letter) {
        bool found = false;
        for (int i = 0; i < wordG.length(); i++) {
            if (wordG[i] == letter) {
                guessed_[i] = true;
                found = true;
            }
        }
        return found;
    }
    bool guessed() const {
        for (bool b : guessed_) {
            if (!b) {
                return false;
            }
        }
        return true;
    }
    bool guessedAt(int i) const {
        return guessed_[i];
    }
    string getW() const {
        return wordG;
    }
};

class HangmanShow { 
public:
    HangmanShow() {}
    void gameViselits(int RemainAt) const {
        cout << " ___" << "\n";
        cout << "| |" << "\n";
        if (RemainAt <= 6) {
            cout << "| O" << "\n";
        }
        else {
            cout << "|" << "\n";
        }
        if (RemainAt <= 5) {
            if (RemainAt <= 4) {
                cout << "| /";
            }
            else {
                cout << "|  ";
            }
            if (RemainAt <= 3) {
                cout << "\\" << "\n";
            }
            else {
                cout << "|" << "\n";
            }
            if (RemainAt <= 2) {
                cout << "|  /";
            }
            else {
                cout << "|   ";
            }
            if (RemainAt == 1) {
                cout << "\\" << "\n";
            }
            else if (RemainAt == 0) {
                cout << "X" << "\n";
            }
            else {
                cout << "|" << "\n";
            }
        }
        cout << "=========" << "\n";
    }

    void Words(const Word& word) const {
        cout << "Slovo: ";
        for (int i = 0; i < word.getW().length(); i++) {
            if (word.guessedAt(i)) {
                cout << word.getW()[i] << " ";
            }
            else {
                cout << "_ ";
            }
        }
        cout << "\n";
    }
    void GuessedL(const vector<char>& guessedLetters) const {
        cout << "Bukv vsego zagadano: ";
        for (char letter : guessedLetters) {
            cout << letter << " ";
        }
        cout << "\n";
    }
};

class Hangman {
private:
    vector<string> words_;
    Word wordG;
    int RemainingAt;
    vector<char> GuesssedLet;
public:
    Hangman() : RemainingAt(6) {
        srand(time(NULL)); 
        ofstream file1("words.txt");
        if (file1.is_open()) {
            file1 << "kofein\n";
            file1 << "moloko\n";
            file1 << "sobaka\n";
            file1 << "serdse\n";
            file1 << "derevo\n";
            file1.close();
        }
        else {
            cerr << "Error creating file!\n";
            exit(1);
        }
        ifstream file("words.txt");
        if (!file.is_open()) {
            cerr << "Error!\n";
            exit(1);
        }
        string line;
        while (getline(file, line)) {
            words_.push_back(line);
        }
        file.close();
    }
    void play() {
        HangmanShow view;
        wordG = Word(words_[rand() % words_.size()]);
        GuesssedLet.clear();
        RemainingAt = 6;
        view.Words(wordG);
        view.gameViselits(RemainingAt);
        view.GuessedL(GuesssedLet);
        while (RemainingAt > 0 && !wordG.guessed()) {
            char letter;
            cout << "Vvedite bukvu: ";
            cin >> letter;
            if (find(GuesssedLet.begin(), GuesssedLet.end(), letter) != GuesssedLet.end()) {
                cout << "Bukva uje ispolzovana!" << "\n";
                continue;
            }
            GuesssedLet.push_back(letter);
            if (wordG.checkL(letter)) {
                cout << "Pravilno!" << "\n";
            }
            else {
                cout << "Ne pravilno!" << "\n";
                RemainingAt--;
                view.gameViselits(RemainingAt);
            }
            view.Words(wordG);
            view.GuessedL(GuesssedLet);
        }
        if (wordG.guessed()) {
            cout << "Pozdravlayu! Vi vigrali! Slovo bilo: " << wordG.getW() << "\n";
        }
        else {
            cout << "Ups, vi proigrali, slovo bilo: " << wordG.getW() << "\n";
        }
    }
};
int main() {
    Hangman game;
    game.play();
    return 0;
}