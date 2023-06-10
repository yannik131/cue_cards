#ifndef CUECARDMANAGER
#define CUECARDMANAGER

#include "CueCardCollection.h"

#include <stdexcept>
#include <memory>

class NoCardsLeft : public std::exception { };
class StillCardsLeft : public std::exception { };

class CueCardManager {
private:
    const CueCardCollection mCardCollection;

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
