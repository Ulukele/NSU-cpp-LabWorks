#include "WordsParser.h"

using namespace std;

int main() {

    WordsParser* wp = new WordsParser("words.txt");
    wp->ParseFile();
    wp->WriteToCSV();
}