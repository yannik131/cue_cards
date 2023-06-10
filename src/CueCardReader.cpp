#include "CueCardReader.h"

#include <fstream>
#include <string>
#include <filesystem>

CueCardCollection CueCardReader::getCueCardsFromFile(const std::string& path) const
{
    std::ifstream input(path);
    if(!input.is_open()) {
        throw FileNotFound(path);
    }

    std::vector<CueCard> cueCards;
    std::string frontText, backText;

    while(std::getline(input, frontText) && std::getline(input, backText))
    {
        frontText = removeTrailingCR(frontText);
        backText = removeTrailingCR(backText);

        CueCard cueCard(frontText, backText);
        cueCards.push_back(cueCard);

        frontText = backText = "";
    }

    if(cueCards.size() == 0) {
        throw FileEmpty(path);
    }

    if(frontText.empty() != backText.empty())
    {
        throw UnevenNumberOfLines(path);
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
