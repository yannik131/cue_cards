#include "CueCardCollection.h"

#include <filesystem>

CueCardCollection::CueCardCollection(const std::string& title, 
    const std::vector<CueCard>& cueCards) :
        mTitle(title),
        mCueCards(cueCards)
{
}