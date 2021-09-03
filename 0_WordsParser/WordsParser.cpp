#include "WordsParser.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>


void WordsParser::LogInfo(std::string info) {
    if (this->useLogs) {
        std::cout << "INFO | " << info << std::endl;
    }
}

WordsParser::WordsParser(std::string inputFilename, std::string outputFilename, bool useLogs) {
    this->useLogs = useLogs;
    this->inputFilename = inputFilename;
    this->outputFilename = outputFilename;

    this->LogInfo("Create words parser");
    this->LogInfo("Set filename: " + inputFilename);
}

void WordsParser::AddWord(std::string word) {
    if (this->words.find(word) != this->words.end()) {
        this->LogInfo("Add word: " + word);
        this->words[word]++;
    }
    else {
        this->LogInfo("Add new word: " + word);
        this->words[word] = 1;
        this->orderedWords.push_back(word);
    }
    this->wordsCount++;
}

void WordsParser::AddFromLine(std::string rawStr) {
    int wordBegin = 0;
    int wordSize = 0;
    for (int i = 0; i < rawStr.size(); ++i) {
        if (isalpha(rawStr[i]) || isdigit(rawStr[i])) {
            wordSize++;
        }
        else {
            if (wordSize > 0) {
                std::string word = rawStr.substr(wordBegin, wordSize);
                this->AddWord(word);
            }
            wordSize = 0;
            wordBegin = i + 1;
        }
    }
    if (wordSize > 0) {
        std::string word = rawStr.substr(wordBegin, wordSize);
        this->AddWord(word);
    }
}

void WordsParser::ParseFile() {
    this->LogInfo("Parsing from file");

    std::ifstream file;
    file.open(this->inputFilename.c_str());

    while (true) {
        std::string line;
        std::getline(file, line);
        if( file.eof() ) break;
        this->AddFromLine(line);
    }

    this->SortWords();
}

bool WordsParser::CompareWordsByCount(std::string first, std::string second) {
    return ( this->words[first] > this->words[second] );
}

void WordsParser::WriteToCSV() {
    this->LogInfo("Writing to: " + this->outputFilename);
    std::ofstream file;
    file.open(this->outputFilename.c_str());

    file << "Word" << ',' << "Count" << ',' << "Percent" << std::endl;
    for (auto word: this->orderedWords) {
        float percent = 100.0 * this->words[word] / this->wordsCount;
        file << word << ',' << this->words[word] << ',' << percent << std::endl;
    }

}

void WordsParser::SortWords() {
    this->LogInfo("Sorting words by count");

    this->orderedWords.sort(std::bind(
        &WordsParser::CompareWordsByCount,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
}