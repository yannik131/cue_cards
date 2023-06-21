#include "CueCardReader.h"

#include <fstream>
#include <string>
#include <filesystem>

CueCardCollection CueCardReader::getCueCardsFromFile(const std::string& path) const
{
    std::ifstream input(path);
    if(!input.is_open()) {
        throw FileNotFound("File not found: " + path);
    }

    std::vector<CueCard> cueCards;
    std::string frontText, backText;

    unsigned lineCount = 1;
    while(std::getline(input, frontText) && std::getline(input, backText))
    {
        frontText = removeTrailingCR(frontText);
        backText = removeTrailingCR(backText);

        if(frontText.empty() || backText.empty()) {
            throw EmptyLineEncountered("Empty line encountered: " + path + ", lines " + std::to_string(lineCount-1) + "-" + 
            std::to_string(lineCount));
        }

        CueCard cueCard(frontText, backText);
        cueCards.push_back(cueCard);

        frontText = backText = "";
        lineCount += 2;
    }

    if(cueCards.size() == 0) {
        throw FileEmpty("File is empty: " + path);
    }

    if(frontText.empty() != backText.empty())
    {
        throw UnevenNumberOfLines("Uneven number of lines: " + path);
    }

    std::string title = std::filesystem::path(path).stem().string();

    return CueCardCollection(title, cueCards);
}

std::string removeTrailingCR(const std::string& str)
{
    if(str.back() == '\r') {
        return str.substr(0, str.size()-1);
    }

    return str;
}
