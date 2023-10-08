//
// Created by Krishnna Shanmugam.
//
#include "GameEngine.h"
#include <iostream>

// Test function to simulate user input and game state transitions.
void testGameStates() {
    // Create a game engine instance.
    GameEngine engine;

    // Define game states.
    State start("Start");
    State map_loaded("Map_loaded");
    State map_validated("Map_Validated");
    State players_added("Players_Added");
    State assign_reinforcement("Assign_Reinforcement");
    State issue_orders("Issure_Orders");
    State execute_orders("Execute_Orders");
    State win("Win");
    State end_state("End_State");


    // Define commands.
    Command loadmap("loadmap");
    Command validatemap("validatemap");
    Command addplayer("addplayer");
    Command assigncountries("assigncountries");
    Command issueorder("issueorder");
    Command endissueorders("endissueorders");
    Command execorder("execorder");
    Command endexecorders("endexecorders");
    Command Win("win");
    Command end("end");
    Command play("play");


    // Associate commands with states.
    start.addCommand(play);
    playing.addCommand(pause);
    playing.addCommand(exit);
    paused.addCommand(resume);

    // Add states to the game engine.
    engine.addState(start);
    engine.addState(map_loaded);
    engine.addState(map_validated);
    engine.addState(players_added);
    engine.addState(assign_reinforcement);
    engine.addState(issue_orders);
    engine.addState(execute_orders);
    engine.addState(win);
    engine.addState(end_state);

    // Define and add transitions between states.
    Transition t1("loadmap", &start, &map_loaded);
    Transition t2("loadmap", &map_loaded, &map_loaded);
    Transition t3("validatemap", &map_loaded, &map_validated);
    Transition t4("addplayer", &map_validated, &players_added);
    Transition t5("addplayer", &players_added, &players_added);
    Transition t6("assigncountries", &players_added, &assign_reinforcement);
    Transition t7("issueorder", &assign_reinforcement, &issue_orders);
    Transition t8("issueorder", &issue_orders, &issue_orders);
    Transition t9("endissueorders", &issue_orders, &execute_orders);
    Transition t10("execorder", &execute_orders, &execute_orders);
    Transition t11("endexecorders", &execute_orders, &assign_reinforcement);
    Transition t12("Win", &execute_orders, &win);
    Transition t13("play", &win, &start);
    Transition t14("end", &win, &end_state);

    engine.addTransition(t1);
    engine.addTransition(t2);
    engine.addTransition(t3);
    engine.addTransition(t4);
    engine.addTransition(t5);
    engine.addTransition(t6);
    engine.addTransition(t7);
    engine.addTransition(t8);
    engine.addTransition(t9);
    engine.addTransition(t10);
    engine.addTransition(t11);
    engine.addTransition(t12);
    engine.addTransition(t13);
    engine.addTransition(t14);

    // Set the initial state.
    engine.setCurrentState("Start");

    std::string command;
    while (true) {
        std::cout << "Current State: " << gameEngine.getCurrentState()->getName() << std::endl;
        std::cout << "Enter a command: ";
        std::cin >> command;

        if (command == "exit") break;

        // Handles user commands and potentially transitions to a new state.
        gameEngine.getCurrentState()->handleCommand(command);
    }
}

int main() {
    testGameStates();
    return 0;
}
