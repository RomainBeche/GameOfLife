cmake_minimum_required(VERSION 3.16)
project(GameOfLife)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)

# Fetch SFML 3.0 (latest version)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.0
)
FetchContent_MakeAvailable(SFML)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Main exectuable
add_executable(GameOfLife 
    main.cpp
    gameOfLife.cpp
    grid.cpp
    cell.cpp
    display.h
    consoleDisplay.cpp
    graphicalDisplay.cpp
    cellState.h
    aliveState.cpp
    deadState.cpp
    ruleSet.h
    conwayRuleSet.cpp
    file.cpp
)
target_link_libraries(GameOfLife PRIVATE sfml-graphics sfml-window sfml-system)

# Separate executable for grid testing
add_executable(GridTests 
    test.cpp
    gridTester.cpp
    grid.cpp
    cell.cpp
    aliveState.cpp
    deadState.cpp
    conwayRuleSet.cpp
    file.cpp
)
target_link_libraries(GridTests PRIVATE sfml-graphics sfml-window sfml-system)