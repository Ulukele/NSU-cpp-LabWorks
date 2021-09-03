#include <string>
#include <map>
#include <list>

#pragma once

class WordsParser {

    std::string inputFilename;
    std::string outputFilename;
    int wordsCount;
    std::map<std::string, int> words;
    std::list<std::string> orderedWords;
    bool useLogs;

    void SortWords();
    bool CompareWordsByCount(std::string first, std::string second);
    void AddFromLine(std::string rawStr);
    void AddWord(std::string word);
    void LogInfo(std::string info);


    public:

    WordsParser(std::string inputFilename, std::string outputFilename="parsed-data.csv", bool useLogs=true);
    void ParseFile();
    void WriteToCSV();
};