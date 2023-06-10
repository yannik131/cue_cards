#include <catch2/catch_test_macros.hpp>

#include "../CueCardManager.h"
#include "../CueCard.h"
#include "../CueCardReader.h"

#include <iostream>

TEST_CASE("Working with cue cards", "[learning]") {
    CueCardReader reader;
    CueCardCollection cueCardCollection = reader.getCueCardsFromFile("./resources/cards.txt");
    CueCardManager manager(cueCardCollection);
    
    manager.shuffleCards();

    REQUIRE(manager.getCurrentCards().size() == 2 );

    const CueCard* topCard = manager.getCurrentCards().back();
    manager.studentKnewTheCard();

    REQUIRE( manager.getCurrentCards().back() != topCard );
    REQUIRE( manager.getCorrectCards().back() == topCard );
    REQUIRE_THROWS_AS( manager.continueWithIncorrectCards(), StillCardsLeft );

    topCard = manager.getCurrentCards().back();
    manager.studentDidntKnowTheCard();

    REQUIRE( manager.getIncorrectCards().back() == topCard );
    REQUIRE( manager.getCurrentCards().empty() );

    manager.continueWithIncorrectCards();

    REQUIRE( manager.getCurrentCards().size() == 1 );
    REQUIRE( manager.getIncorrectCards().empty() );
    REQUIRE( manager.getCurrentCards().back() == topCard );

    manager.studentKnewTheCard();

    REQUIRE( manager.getCurrentCards().empty() );

    REQUIRE_THROWS_AS( manager.studentKnewTheCard(), NoCardsLeft );
    REQUIRE_THROWS_AS( manager.studentDidntKnowTheCard(), NoCardsLeft );
    REQUIRE_THROWS_AS( manager.continueWithIncorrectCards(), NoCardsLeft );
    REQUIRE_THROWS_AS( manager.shuffleCards(), NoCardsLeft );

    REQUIRE( manager.allCardsLearned() );

    manager.reset();

    REQUIRE( manager.getCurrentCards().size() == 2 );
    REQUIRE( (manager.getCorrectCards().empty() && manager.getIncorrectCards().empty()) );
}
