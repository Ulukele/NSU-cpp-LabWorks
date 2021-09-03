#include "WordsParser.h"
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
    this->outputFilename = outputFilename + ".csv";

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

void WordsParser::ParseFile() {
    this->LogInfo("Parsing from file");

    std::ifstream file;
    file.open(this->inputFilename.c_str());

    while (true) {
        std::string word;
        std::getline(file, word);
        if( file.eof() ) break;
        this->AddWord(word);
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

    std::sort( this->orderedWords.begin(), this->orderedWords.end(), std::bind(
        &WordsParser::CompareWordsByCount,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ) );
}