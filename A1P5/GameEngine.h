//
// Created by Krishnna Shanmugam.
//

#include <vector>
#include <string>
#include <functional>
#include "../A1P1/Map.h"
#include "../A1P2/Player.h"
#include "../A1P3/Orders.h"
#include "../A1P4/Cards.h"
using namespace std;

// Represents a game state.
// It contains a name and a list of valid commands that can be executed in that state.
class State;

// Represents a transition between states.
// Each transition has a command that triggers it, a source state, and a target state.
class Transition;

// Represents a user command.
// Each command has a name associated with it.
class Command;

// The main game engine class.
// It manages a list of states and transitions, and handles user commands to determine state transitions.
class GameEngine {
private:
    std::vector<State> states;         // List of game states.
    std::vector<Transition> transitions; // List of state transitions.
    State *currentState;              // Pointer to the current game state.

public:

    Deck gameDeck;

    int numOfPlayers;

    string state;

    Map gameMap;

    vector<Player*> playersInGame;

    GameEngine();

    GameEngine(const GameEngine &game_engine);

    GameEngine &operator=(const GameEngine &game_engine);

        // Draw a card in the game engine
        void drawCard(Player* player);

        // issuing orders to the game engine
        void issueOrder(Player* player, Order* order);

        //load map
        void setupMap(const std::string &path);

        //adding a player to the game engine
        void addPlayer(Player *player);

        // Add a state to the game engine.
        void addState(const State &state);

        // Add a transition to the game engine.
        void addTransition(const Transition &transition);

        // Set the current state of the game engine by state name.
        void setCurrentState(const std::string &stateName);

        // Handle a user command and determine if a state transition should occur.
        void handleCommand(const std::string &cmdName);
    };

// Represents a game state.
    class State {
    private:
        std::string name;               // Name of the state.
        std::vector<Command> commands;  // List of valid commands in this state.

    public:

        State(const std::string &name);

        // Add a valid command to this state.
        void addCommand(const Command &cmd);

        // Check if the state has a specific command.
        bool hasCommand(const std::string &cmdName) const;

        // Get the name of the state.
        std::string getName() const;
    };

// Represents a transition between states.
    class Transition {
    private:
        std::string commandName;  // The command that triggers this transition.
        State *sourceState;       // The starting state of the transition.
        State *targetState;       // The destination state of the transition.

    public:
        Transition(const std::string &cmdName, State *source, State *target);

        // Check if the transition is triggered by a specific command.
        bool isTriggeredBy(const std::string &cmdName) const;

        // Get the destination state of the transition.
        State *getTargetState() const;

        // Get the starting state of the transition.
        State *getSourceState() const;
    };

// Represents a user command.
    class Command {
    private:
        std::string name;  // Name of the command.

    public:
        Command(const std::string &name);

        // Get the name of the command.
        std::string getName() const;
    };
