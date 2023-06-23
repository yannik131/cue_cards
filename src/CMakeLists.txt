cmake_minimum_required(VERSION 3.5)

project(cue_cards VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Request the required wxWidgets libs
find_package(wxWidgets 3.3 COMPONENTS core base REQUIRED CONFIG)

# Include the wxWidgets use file to initialize various settings
if(wxWidgets_USE_FILE)
    include(${wxWidgets_USE_FILE})
endif()

add_library(cue_cards_l CueCard.cpp CueCardCollection.cpp CueCardReader.cpp CueCardManager.cpp)
add_library(gui App.cpp CueCardPanel.cpp MainFrame.cpp)
target_link_libraries(gui ${wxWidgets_LIBRARIES} cue_cards_l)

add_executable(cue_cards main.cpp)
target_link_libraries(cue_cards cue_cards_l gui)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -lpng -lz -ljpeg -lfltk_gl -lGLU -lGL -lfltk -lXrender -lXfixes -lXext -lXft -lfontconfig -lpthread -ldl -lm -lX11")

#Catch2 integration

find_package(Catch2 3 REQUIRED)
add_executable(tests test/CueCardReaderTest.cpp test/CueCardManagerTest.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain cue_cards_l)

