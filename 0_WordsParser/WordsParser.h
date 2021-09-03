#include <string>
#include <map>
#include <vector>

#pragma once

class WordsParser {

    std::string inputFilename;
    std::string outputFilename;
    int wordsCount;
    std::map<std::string, int> words;
    std::vector<std::string> orderedWords;
    bool useLogs;

    void SortWords();
    bool CompareWordsByCount(std::string first, std::string second);
    void AddWord(std::string word);
    void LogInfo(std::string info);


    public:

    WordsParser(std::string inputFilename, std::string outputFilename="parsed-data", bool useLogs=true);
    void ParseFile();
    void WriteToCSV();
};