#include "WordsParser.h"
#include <string.h>
#include <iostream>
#include <fstream>
#include <functional>


void WordsParser::LogInfo(std::string info) {
    if (useLogs) {
        std::cout << "INFO | " << info << std::endl;
    }
}

WordsParser::WordsParser(std::string& inputFilename, std::string& outputFilename, bool useLogs) {
    this->useLogs = useLogs;
    this->inputFilename = inputFilename;
    this->outputFilename = outputFilename;
    wordsCount = 0;

    LogInfo("Create words parser");
    LogInfo("Set filename: " + inputFilename);
}

void WordsParser::AddWord(std::string& word) {
    if (words.find(word) != words.end()) {
        LogInfo("Add word: " + word);
        words[word]++;
    }
    else {
        LogInfo("Add new word: " + word);
        words[word] = 1;
        orderedWords.push_back(word);
    }
    wordsCount++;
}

void WordsParser::AddFromLine(std::string& rawStr) {
    int wordBegin = 0;
    int wordSize = 0;
    for (int i = 0; i < rawStr.size(); ++i) {
        if (isalpha(rawStr[i]) || isdigit(rawStr[i])) {
            wordSize++;
        }
        else {
            if (wordSize > 0) {
                std::string word = rawStr.substr(wordBegin, wordSize);
                AddWord(word);
            }
            wordSize = 0;
            wordBegin = i + 1;
        }
    }
    if (wordSize > 0) {
        std::string word = rawStr.substr(wordBegin, wordSize);
        AddWord(word);
    }
}

void WordsParser::ParseFile() {
    LogInfo("Parsing from file");

    std::ifstream file;
    file.open(inputFilename.c_str());

    while ( !file.eof() ) {
        std::string line;
        std::getline(file, line);
        AddFromLine(line);
    }
    file.close();
    
    SortWords();
}

bool WordsParser::CompareWordsByCount(std::string& first, std::string& second) {
    return ( words[first] > words[second] );
}

void WordsParser::WriteToCSV() {
    LogInfo("Writing to: " + outputFilename);
    std::ofstream file;
    file.open(outputFilename.c_str());

    file << "Word" << ',' << "Count" << ',' << "Percent" << std::endl;
    for (auto word: orderedWords) {
        float percent = 100.0 * words[word] / wordsCount;
        file << word << ',' << words[word] << ',' << percent << std::endl;
    }
    file.close();
}

void WordsParser::SortWords() {
    LogInfo("Sorting words by count");

    orderedWords.sort(std::bind(
        &WordsParser::CompareWordsByCount,
        this,
        std::placeholders::_1,
        std::placeholders::_2
    ));
}