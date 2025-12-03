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

add_executable(GameOfLife 
    main.cpp
    gameOfLife.cpp
    gameOfLife.h
    grid.cpp
    grid.h
    cell.cpp
    cell.h
    display.h
    consoleDisplay.cpp
    consoleDisplay.h
    graphicalDisplay.cpp
    graphicalDisplay.h
    cellState.h
    aliveState.cpp
    aliveState.h
    deadState.cpp
    deadState.h
    ruleSet.h
    conwayRuleSet.cpp
    conwayRuleSet.h
    file.cpp
    file.h
)

target_link_libraries(GameOfLife PRIVATE sfml-graphics sfml-window sfml-system)