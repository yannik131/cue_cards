cmake_minimum_required(VERSION 3.5)

project(cue_cards VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(cue_cards_l CueCard.cpp CueCardCollection.cpp CueCardReader.cpp CueCardManager.cpp)

add_executable(cue_cards main.cpp)
target_link_libraries(cue_cards cue_cards_l)

#Catch2 integration

find_package(Catch2 3 REQUIRED)
add_executable(tests test/CueCardReaderTest.cpp test/CueCardManagerTest.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cue_cards_l)