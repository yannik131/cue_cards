#include "CueCardManager.h"

#include <algorithm>

CueCardManager::CueCardManager(const CueCardCollection& cueCardCollection) : 
    mCardCollection(cueCardCollection) {
    fillCurrentCards();
}

void CueCardManager::fillCurrentCards() {
    for(int i = 0; i < mCardCollection.mCueCards.size(); ++i) {
        mCurrentCards.push_back(&mCardCollection.mCueCards[i]);
    }
}

void CueCardManager::shuffleCards() {
    if(mCurrentCards.empty()) {
        throw NoCardsLeft();
    }

    std::random_shuffle(mCurrentCards.begin(), mCurrentCards.end());
}

const std::vector<const CueCard*> CueCardManager::getCurrentCards() const { 
    return mCurrentCards; 
}

const std::vector<const CueCard*> CueCardManager::getCorrectCards() const { 
    return mCorrectCards; 
}

const std::vector<const CueCard*> CueCardManager::getIncorrectCards() const { 
    return mIncorrectCards; 
}

void CueCardManager::studentKnewTheCard() {
    if(mCurrentCards.empty()) {
        throw NoCardsLeft();
    }

    mCorrectCards.push_back(mCurrentCards.back());
    mCurrentCards.pop_back();
}

void CueCardManager::studentDidntKnowTheCard() {
    if(mCurrentCards.empty()) {
        throw NoCardsLeft();
    }

    mIncorrectCards.push_back(mCurrentCards.back());
    mCurrentCards.pop_back();
}

void CueCardManager::continueWithIncorrectCards() {
    if(!mCurrentCards.empty()) {
        throw StillCardsLeft();
    }

    if(mIncorrectCards.empty()) {
        throw NoCardsLeft();
    }

    mIncorrectCards.swap(mCurrentCards);
}

bool CueCardManager::allCardsLearned() const {
    return mCurrentCards.empty() && 
        ((mIncorrectCards.size() + mCorrectCards.size()) == mCardCollection.mCueCards.size());
}

void CueCardManager::reset() {
    mCurrentCards.clear();
    mIncorrectCards.clear();
    mCorrectCards.clear();

    fillCurrentCards();
}