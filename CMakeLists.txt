cmake_minimum_required(VERSION 3.26)
project(testFixProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(testFixProject main.cpp
        A1P1/MapDriver.cpp
        A1P1/Map.cpp
        A1P2/Player.cpp
        A1P2/PlayerDriver.cpp
        A1P3/Orders.cpp
        A1P3/OrdersDriver.cpp
        A1P4/Cards.cpp
        A1P4/CardsDriver.cpp
        A1P5/GameEngine.cpp
        A1P5/GameEngineDriver.cpp)
