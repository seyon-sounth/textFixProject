//
// Created by Krishnna Shanmugam on 2023-10-06.
//

#include "GameEngine.h"
#include <iostream>
using namespace std;


//copy constructor
GameEngine::GameEngine(const GameEngine& game_engine) {
    state = "start";
    numOfPlayers = game_engine.numOfPlayers;
}

// Initialize the game engine with no current state.
GameEngine::GameEngine() : currentState(nullptr) {}

// Add a state to the game engine.
void GameEngine::addState(const State& state) {
    states.push_back(state);
}

// Add a transition to the game engine.
void GameEngine::addTransition(const Transition& transition) {
    transitions.push_back(transition);
}

// Set the current state of the game engine by state name.
void GameEngine::setCurrentState(const std::string& stateName) {
    for (auto& state : states) {
        if (state.getName() == stateName) {
            currentState = &state;
            break;
        }
    }
}

// Sets up the game map using the MapLoader from MapDriver.cpp
void GameEngine::setupMap(const std::string& path) {

    MapLoader *mapLoader = new MapLoader(path);
    gameMap = *(mapLoader->getMap());

    if(mapLoader->getMap()->validate()){
        cout << "Map is valid" << endl;
    }else{
        cout << "Map is invalid" << endl;
    }
}

// Adds a player to the game's list of players.
void GameEngine::addPlayer(Player* player) {
    playersInGame.push_back(player);
}

// Allows a player to issue an order.
void GameEngine::issueOrder(Player* player, Order* order) {
    player->issueOrder();
    // Additional logic if needed.
}

// Allows a player to draw a card from the game's deck.
void GameEngine::drawCard(Player* player) {
    Card* drawnCard = gameDeck.draw();
    player->addCardToHand(drawnCard);
}

// Handle a user command.
// This function will first check if the command is valid for the current state.
// If valid, it will look for a transition triggered by the command and move to the target state.
void GameEngine::handleCommand(const std::string& cmdName) {
    if (!currentState->hasCommand(cmdName)) {
        std::cout << "Invalid command!" << std::endl;
        return;
    }

    for (auto& transition : transitions) {
        if (transition.isTriggeredBy(cmdName) && transition.getSourceState() == currentState) {
            currentState = transition.getTargetState();
            std::cout << "Transitioned to state: " << currentState->getName() << std::endl;
            return;
        }
    }

    std::cout << "Command executed but no state transition occurred." << std::endl;
}

// Initialize the state with a given name.
State::State(const std::string& name) : name(name) {}

// Add a valid command to the state.
void State::addCommand(const Command& cmd) {
    commands.push_back(cmd);
}

// Check if the state has a specific command.
bool State::hasCommand(const std::string& cmdName) const {
    for (const auto& cmd : commands) {
        if (cmd.getName() == cmdName) {
            return true;
        }
    }
    return false;
}

// Get the name of the state.
std::string State::getName() const {
    return name;
}

// Initialize the transition with a command, source state, and target state.
Transition::Transition(const std::string& cmdName, State* source, State* target)
        : commandName(cmdName), sourceState(source), targetState(target) {}

// Check if the transition is triggered by a specific command.
bool Transition::isTriggeredBy(const std::string& cmdName) const {
    return cmdName == commandName;
}

// Get the destination state of the transition.
State* Transition::getTargetState() const {
    return targetState;
}

// Get the starting state of the transition.
State* Transition::getSourceState() const {
    return sourceState;
}

// Initialize the command with a given name.
Command::Command(const std::string& name) : name(name) {}

// Get the name of the command.
std::string Command::getName() const {
    return name;
}
