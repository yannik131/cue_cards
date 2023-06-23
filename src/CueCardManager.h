#ifndef CUECARDMANAGER
#define CUECARDMANAGER

#include "CueCardCollection.h"

#include <stdexcept>

class NoCardsLeft : public std::runtime_error { using std::runtime_error::runtime_error; };
class StillCardsLeft : public std::runtime_error { using std::runtime_error::runtime_error; };

class CueCardManager {
private:
    const CueCardCollection mCardCollection;

    //The last entry is the most current card.
    //A std::stack was not used because shuffling stacks is not supported.
    std::vector<const CueCard*> mCurrentCards;
    std::vector<const CueCard*> mCorrectCards;
    std::vector<const CueCard*> mIncorrectCards;

    void fillCurrentCards();
public:
    CueCardManager(const CueCardCollection& CueCardCollection);

    void shuffleCards();

    const std::vector<const CueCard*> getCurrentCards() const;
    const std::vector<const CueCard*> getCorrectCards() const;
    const std::vector<const CueCard*> getIncorrectCards() const;

    void studentKnewTheCard();
    void studentDidntKnowTheCard();
    void continueWithIncorrectCards();
    bool allCardsLearned() const;
    void reset();
};

#endif /* CUECARDMANAGER */
