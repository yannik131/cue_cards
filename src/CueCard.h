#ifndef CUECARD
#define CUECARD

#include <string>

class CueCard
{
public:
    const std::string mFrontText;
    const std::string mBackText;
    
    CueCard(const std::string& frontText, const std::string& backText);
};


#endif /* CUECARD */
