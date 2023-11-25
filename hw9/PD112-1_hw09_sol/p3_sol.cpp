#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define TOTAL_PUNCTUATION 9
#define MAX_WORD_COUNT    10000
const char punctuation[TOTAL_PUNCTUATION] = {' ', ',', '.', '\'', '\"', '!', '?', ';', ':'};

bool isPunctuation(char character) {
    for (int i=0; i<TOTAL_PUNCTUATION; i++) {
        if (character == punctuation[i]) {
            return true;
        }
    }
    return false;
}

int splitWord(string article, string* wordArray) {
    /* -----------------------------------
        this function splits a string into 
        words, convert them to lowercase,
        and store to a string array.
    -----------------------------------*/
    int headIdx = 0, tailIdx = -1;
    string word;
    int wordIdx = 0;
    for (int i=0; i<article.length(); i++) {
        if (isPunctuation(article[i]) || (i == article.length()-1)) {
            tailIdx = i;
            if (isPunctuation(article[i]))
                tailIdx--;
            if (tailIdx >= headIdx) {
                word = article.substr(headIdx, tailIdx - headIdx + 1);
                for (int j=0; j<word.length(); j++) {
                    word[j] = tolower(word[j]);
                }
                wordArray[wordIdx++] = word;
            }
            headIdx = i+1;
        }
    }
    return wordIdx;
}

int countExistingVocab(string* wordArray, int totalWord, string* dictArray, int dictSize) {    
    int count = 0;
    // compare each word to every vocab,
    // increment the count if the 2 strings
    // are identical.
    for (int i = 0; i < totalWord; i++) {
        for (int j = 0; j < dictSize; j++) {
            if (wordArray[i] == dictArray[j]) {
                count++;
                break;
            }
        }
    }
    return count;
}


int main() {
    string articleName, dictName;
	cin >> articleName >> dictName;

    /* ------------------------------
        read data from article file
       ------------------------------*/
    string article, lineReader;
    ifstream txtfile(articleName);
	while (getline(txtfile, lineReader))
	{
        article = lineReader;
	}
	txtfile.close();

    /* ------------------------------
        read data from dictionary file
       ------------------------------*/
    int dictSize;
	ifstream dictFile(dictName);
    dictFile >> dictSize;
    string* dictArray = new string[dictSize];
	for (int i=0; i<dictSize; i++) {
        dictFile >> lineReader;
        // due to case-insensitive searching, 
        // convert the vocab to lower case.
        for (int j=0; j<lineReader.length(); j++) {
            lineReader[j] = tolower(lineReader[j]);
        } 
        dictArray[i] = lineReader;
	}
	dictFile.close();

    /* ---------------------------
        allocate a dynamic array 
            to store words
       ---------------------------*/
    string* wordArray = new string[MAX_WORD_COUNT];
    for (int i=0; i<MAX_WORD_COUNT; i++) {
        wordArray[i] = "";
    }

    /* ------------------------------------
        split and process the article string 
        to obtain all the complete and 
        independent words.
       ------------------------------------*/
    int totalWord = splitWord(article, wordArray);

    /* ------------------------------------
        calculate the total number of dictionary
        vocab that existed in the word array.
       ------------------------------------*/
    int totalVocabExist = countExistingVocab(wordArray, totalWord, dictArray, dictSize);

    /* --------------------
        output the answer
       -------------------*/
    cout << totalVocabExist;

    /* ------------------------------
        free the allocated memories
       -----------------------------*/
    delete[] dictArray;
    delete[] wordArray;

    return 0;
}