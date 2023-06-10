#ifndef CUECARDCOLLECTION
#define CUECARDCOLLECTION

#include "CueCard.h"

#include <vector>

class CueCardCollection
{
public:
    const std::vector<CueCard> mCueCards;
    const std::string mTitle;

    CueCardCollection(const std::string& title, const std::vector<CueCard>& cueCards);
};

#endif /* CUECARDCOLLECTION */
