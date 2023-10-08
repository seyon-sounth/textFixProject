//
// Created by Tushar Raval - 40124664
//

#ifndef UNTITLED_MAP_H
#define UNTITLED_MAP_H
using namespace std;
#include <string>
#include <vector>

class Territory
{
private:
    int id;
    int army;
    int continentId;
    string name;
    string owner;
    vector<string> adjNeighbours;

public:
    explicit Territory();
    explicit Territory(int id, int continentId, string name);
    Territory(const Territory &territory);
    bool operator==(const Territory &territory);
    friend ostream &operator<<(ostream &out, const Territory &territory);
    void setName(string name);
    void setOwner(string owner);
    void setArmy(int army);
    void addNeighbour(string neighbour);
    void setContinentId(int continentId);
    int getId();
    int getArmy();
    int getContinentId();
    string getOwner();
    string getName();
    vector<string> getAdjNeighbours();
};

class Continent
{
private:
    int id;
    string name;
    vector<Territory *> territories;

public:
    explicit Continent();
    explicit Continent(int id, string name);
    Continent(const Continent &continent);
    bool operator==(const Continent &continent);
    friend ostream &operator<<(ostream &out, const Continent &continent);
    void setId(int id);
    void addTerritory(Territory *territory);
    int getId();
    string getName();
    vector<Territory *> getTerritories();
    int getNumTerritories();
};
class Map
{
private:
    string name;
    vector<Territory *> territories;
    vector<Continent *> continents;
    void dfs(Territory *territory, vector<Territory *> &visited, vector<Continent *> &visited2);

public:
    explicit Map();
    explicit Map(string name);
    bool validate();
    void setName(string name);
    void addTerritory(Territory *territory);
    void addContinent(Continent *continent);
    string getName();
    vector<Territory *> getTerritories();
    vector<Continent *> getContinents();
    Territory *getTerritory(int id);
    Territory *getTerritory(string name);
    Continent *getContinentById(int id);
    Map(const Map &map);
    bool operator==(const Map &map);
    friend ostream &operator<<(ostream &out, const Map &map);
};

class MapLoader
{
private:
    Map *map;
    int getContinentId(string continent);

public:
    explicit MapLoader();
    explicit MapLoader(string path);
    Map *getMap();
    MapLoader(const MapLoader &mapLoader);
    bool operator==(const MapLoader &mapLoader);
    friend ostream &operator<<(ostream &out, const MapLoader &mapLoader);
};
#endif