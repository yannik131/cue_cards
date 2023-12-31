#include <catch2/catch_test_macros.hpp>

#include "../CueCardReader.h"
#include "../CueCardCollection.h"

TEST_CASE("Cue cards can be read from text files", "[reading]") {
    CueCardReader reader;

    SECTION("Reading a correct file") {
        CueCardCollection cards = reader.getCueCardsFromFile("./resources/cards.txt");

        REQUIRE( cards.mCueCards.size() == 2 );
        REQUIRE( cards.mTitle == "cards" );
        REQUIRE( cards.mCueCards[1].mFrontText == "Phonon");
        REQUIRE( cards.mCueCards[1].mBackText == "Häufige Ber");
    }

    SECTION("Uneven number of lines throws Exception") {
        REQUIRE_THROWS_AS(
            reader.getCueCardsFromFile("./resources/cards_uneven.txt"),
            UnevenNumberOfLines
        );
    }

    SECTION("Empty file throws exception") {
        REQUIRE_THROWS_AS(
            reader.getCueCardsFromFile("./resources/empty_file.txt"),
            FileEmpty
        );
    }

    SECTION("File not found") {
        REQUIRE_THROWS_AS(
            reader.getCueCardsFromFile("asdf.doesNotExist"),
            FileNotFound
        );
    }
}
