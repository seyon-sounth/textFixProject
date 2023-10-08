//
// Created by Tushar Raval - 40124664
//

#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * The following free functions are meant to trim whitespace from strings.
 */

/**
 * Checks if a string is whitespace.
*/
bool isWhitespace(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isspace);
}

/**
 * Trims whitespace and "\r" from a string.
*/
void trimString(std::string& str) {
    // Remove leading whitespace and '\r' characters
    str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](int ch) {
        return !std::isspace(ch) && ch != '\r';
    }));

    // Remove trailing whitespace and '\r' characters
    str.erase(std::find_if(str.rbegin(), str.rend(), [](int ch) {
        return !std::isspace(ch) && ch != '\r';
    }).base(), str.end());
}

/**
 * The following functions are for the Map class.
 */

/**
 * Default constructor for Map class.
 * @return Map object.
 */
Map::Map()
{
    this->name = "none";
}

/**
 * Constructor for Map class.
 * @param name Map name.
 * @return Map object.
 */
Map::Map(string name)
{
    this->name = name;
}

/**
 * Sets the name of the map.
 * @param name Map name.
 */
void Map::setName(string name)
{
    this->name = name;
}

/**
 * Adds a territory to the map.
 * @param territory Territory object.
 */
void Map::addTerritory(Territory *territory)
{
    this->territories.push_back(territory);
}

/**
 * Adds a continent to the map.
 * @param continent Continent object.
 */
void Map::addContinent(Continent *continent)
{
    this->continents.push_back(continent);
}

/**
 * Gets the name of the map.
 * @return Map name.
 */
string Map::getName()
{
    return this->name;
}

/**
 * Gets the territories in the map.
 * @return Vector of territories.
 */
vector<Territory *> Map::getTerritories()
{
    return this->territories;
}

/**
 * Gets the continents in the map.
 * @return Vector of continents.
 */
vector<Continent *> Map::getContinents()
{
    return this->continents;
}

/**
 * Gets a territory by name.
 * @param name Territory name.
 * @return Territory object.
 */
Territory *Map::getTerritory(string name)
{
    trimString(name);
    for (auto territory : this->territories)
    {
        if (territory->getName() == name)
        {
            return territory;
        }
    }

    return nullptr;
}

/**
 * Gets a territory by id.
 * @param id Territory id.
 * @return Territory object.
 */
Territory *Map::getTerritory(int id)
{
    for (auto territory : this->territories)
    {
        if (territory->getId() == id)
        {
            return territory;
        }
    }

    return nullptr;
}

/**
 * Gets a continent by id.
 * @param id Continent id.
 * @return Continent object.
 */
Continent *Map::getContinentById(int id)
{
    for (auto continent : this->continents)
    {
        if (continent->getId() == id)
        {
            return continent;
        }
    }

    return nullptr;
}

/**
 * Validates the map.
 * @return True if the map is valid, false otherwise.
 */
bool Map::validate()
{
    // Check if the map is empty.
    if (this->territories.empty() || this->continents.empty())
    {
        return false;
    }

    // Check if the map is connected.
    vector<Territory *> visitedTerritory;
    vector<Continent *> visitedContinent;
    dfs(this->territories[0], visitedTerritory, visitedContinent);

    if (visitedTerritory.size() != this->territories.size())
    {
        return false;
    }

    if (visitedContinent.size() != this->continents.size()){
        return false;
    }

    return true;
}

/**
 * Depth-first search algorithm.
 * @param territory Territory object.
 * @param visited Vector of visited territories.
 */
void Map::dfs(Territory *territory, vector<Territory *> &visited, vector<Continent *> &visited2)
{
    // Add the territory to the visited vector.
    visited.push_back(territory);

    // Get the continent from the current territory.
    Continent* tempContinent = this->getContinentById(territory->getContinentId());

    // Add the continent to the visited vector if it is not already there.
    if(find(visited2.begin(), visited2.end(), tempContinent) == visited2.end()){
        visited2.push_back(tempContinent);
    }

    // Iterate through the adjacent neighbours of the territory.
    for (auto neighbour : territory->getAdjNeighbours())
    {
        // Get the territory pointer from the neighbour using the name.
        Territory *foundNeighbour = getTerritory(neighbour);

        // If the neighbour is not visited, call dfs on it.
        if (foundNeighbour && find(visited.begin(), visited.end(), foundNeighbour) == visited.end())
        {
            dfs(foundNeighbour, visited, visited2);
        }
    }
}

/**
 * Copy constructor for Map class.
 * @param map Map object.
 * @return Map object.
 */
Map::Map(const Map &map)
{
    this->name = map.name;
    this->territories = map.territories;
    this->continents = map.continents;
}

/**
 * Overloaded == operator for Map class.
 * @param map Map object.
 * @return True if the maps are equal, false otherwise.
 */
bool Map::operator==(const Map &map)
{
    return this->name == map.name;
}

/**
 * Overloaded << operator for Map class.
 * @param out Output stream.
 * @param map Map object.
 * @return Output stream.
 */
ostream &operator<<(ostream &out, const Map &map)
{
    out << "Map: " << map.name << endl;
    out << "Continents: " << endl;

    for (auto continent : map.continents)
    {
        out << *continent;
    }

    return out;
}

/**
 * The following functions are for the MapLoader class.
 */

/**
 * Default constructor for MapLoader class.
 */
MapLoader::MapLoader()
{
    this->map = new Map();
}

/**
 * Constructor for MapLoader class.
 * This file loads the map from a file and creates a 
 * Map object with Territories and Continents.
 * @param path Path to the map file.
 */
MapLoader::MapLoader(string path)
{
    // Open the file.
    ifstream mapFile(path);
    
    string line;
    
    // Check if the file is open.
    if (mapFile.is_open())
    {
        // Create a new map.
        this->map = new Map();

        int conId = 1;
        int terId = 1;
        int count = 0;
        
        // Read the file line by line.
        while (getline(mapFile, line))
        {
            
            // Trim the line of whitespace.
            trimString(line);

            if (line == "[Map]")
            {
                continue;
            }
            else if (line == "[Continents]")
            {
                // Read the continents line by line
                while (getline(mapFile, line))
                {
                    if (isWhitespace(line)) break;
                    string name = line.substr(0, line.find("="));
                    auto *continent = new Continent(conId++, name);
                    this->map->addContinent(continent);
                }
            }
            else if (line =="[Territories]")
            {
                vector<vector<string>> neighbours;

                // Read the territories line by line.
                while (getline(mapFile, line))
                {
                    vector<string> temp;
                    string line2;

                    /*
                        * If the line is empty, increment the count.
                        * If the count is equal to the number of continents,
                        * break out of the loop. This is to read all of the 
                        * territories in the file.
                    */
                    if (isWhitespace(line))
                    {
                        count++;
                        if (count == this->map->getContinents().size())
                        {
                            count = 0;
                            break;
                        }
                        continue;
                    }

                    // Split the line by commas.
                    stringstream ss(line);

                    // Push the split line into a vector.
                    while (getline(ss, line2, ','))
                    {
                        temp.push_back(line2);
                    }

                    string name = temp[0];
                    int continentId = getContinentId(temp[3]);

                    if (continentId == -1)
                    {
                        cout << "Invalid continent." << endl;
                        exit(-1);
                    }

                    Territory *territory = new Territory(terId++, continentId, name);

                    for (int i = 4; i < temp.size(); i++)
                    {
                        territory->addNeighbour(temp[i]);
                    }

                    this->map->getContinentById(continentId)->addTerritory(territory);
                    this->map->addTerritory(territory);
                }
            }
        }
    }
    else
    {
        cout << "Unable to open file." << endl;
    }
}

/**
 * Gets the continent id.
 * @param continent Continent name.
 * @return Continent id.
 */
int MapLoader::getContinentId(string continent)
{
    for (auto continentObj : this->map->getContinents())
    {
        if (continentObj->getName() == continent)
        {
            return continentObj->getId();
        }
    }

    return -1;
}

/**
 * Gets the map.
 */
Map *MapLoader::getMap()
{
    return this->map;
}

/**
 * Copy constructor for MapLoader class.
 * @param mapLoader MapLoader object.
 * @return MapLoader object.
 */
MapLoader::MapLoader(const MapLoader &mapLoader)
{
    this->map = mapLoader.map;
}

/**
 * Overloaded == operator for MapLoader class.
 * @param mapLoader MapLoader object.
 * @return True if the map loaders are equal, false otherwise.
 */
bool MapLoader::operator==(const MapLoader &mapLoader)
{
    return this->map == mapLoader.map;
}

/**
 * Overloaded << operator for MapLoader class.
 * @param out Output stream.
 * @param mapLoader MapLoader object.
 * @return Output stream.
 */
ostream &operator<<(ostream &out, const MapLoader &mapLoader)
{
    out << "Map: " << mapLoader.map->getName() << endl;
    out << "Continents: " << endl;

    for (auto continent : mapLoader.map->getContinents())
    {
        out << *continent;
    }

    out << "Territories: " << endl;

    for (auto territory : mapLoader.map->getTerritories())
    {
        out << *territory;
    }

    return out;
}

/**
 * The following functions are for the Territory class.
 */

/**
 * Default constructor for Territory class.
 * @return Territory object.
 */
Territory::Territory()
{
    this->id = 0;
    this->army = 0;
    this->continentId = 0;
    this->owner = "none";
}

/**
 * Constructor for Territory class.
 * @param id Territory id.
 * @param continentId Continent id.
 * @param name Territory name.
 * @return Territory object.
 */
Territory::Territory(int id, int continentId, string name)
{
    this->id = id;
    this->army = 0;
    this->continentId = continentId;
    this->owner = "No Owner Yet";
    this->name = name;
}

/**
 * Copy constructor for Territory class.
 * @param territory Territory object.
 * @return Territory object.
 */
Territory::Territory(const Territory &territory)
{
    this->id = territory.id;
    this->army = territory.army;
    this->continentId = territory.continentId;
    this->owner = territory.owner;
    this->name = territory.name;
    this->adjNeighbours = territory.adjNeighbours;
}

/**
 * Overloaded == operator for Territory class.
 * @param territory Territory object.
 * @return True if the territories are equal, false otherwise.
 */
bool Territory::operator==(const Territory &territory)
{
    return this->id == territory.id;
}

/**
 * Overloaded << operator for Territory class.
 * @param out Output stream.
 * @param territory Territory object.
 * @return Output stream.
 */
ostream &operator<<(ostream &out, const Territory &territory)
{
    out << "Territory: " << territory.name << endl;
    out << "Owner: " << territory.owner << endl;
    out << "Armies: " << territory.army << endl;
    out << "Continent: " << territory.continentId << endl;
    out << "Neighbours: \n";

    for (auto neighbour : territory.adjNeighbours)
    {
        trimString(neighbour);
        out << neighbour << ", ";
    }
    out << endl;

    return out;
}

/**
 * Sets the name of the territory.
 * @param name Territory name.
 */
void Territory::setOwner(string owner)
{
    this->owner = owner;
}

/**
 * Sets the name of the territory.
 * @param name Territory name.
 */
void Territory::setName(string name)
{
    this->name = name;
}

/**
 * Sets the number of armies on the territory.
 * @param army Number of armies.
 */
void Territory::setArmy(int army)
{
    this->army = army;
}

/**
 * Adds a neighbour to the territory.
 * @param neighbour Territory object.
 */
void Territory::addNeighbour(string neighbour)
{
    this->adjNeighbours.push_back(neighbour);
}

/**
 * Sets the continent id of the territory.
 * @param continentId Continent id.
 */
void Territory::setContinentId(int continentId)
{
    this->continentId = continentId;
}

/**
 * Gets the id of the territory.
 * @return Territory id.
 */
int Territory::getId()
{
    return this->id;
}

/**
 * Gets the number of armies on the territory.
 * @return Number of armies.
 */
int Territory::getArmy()
{
    return this->army;
}

/**
 * Gets the continent id of the territory.
 * @return Continent id.
 */
int Territory::getContinentId()
{
    return this->continentId;
}

/**
 * Gets the owner of the territory.
 * @return Owner name.
 */
string Territory::getOwner()
{
    return this->owner;
}

/**
 * Gets the name of the territory.
 * @return Territory name.
 */
string Territory::getName()
{
    return this->name;
}

/**
 * Gets the adjacent neighbours of the territory.
 * @return Vector of adjacent neighbours.
 */
vector<string> Territory::getAdjNeighbours()
{
    return this->adjNeighbours;
}

/**
 * The following functions are for the Continent class.
 */

/**
 * Default constructor for Continent class.
 *  @return Continent object.
 */
Continent::Continent()
{
    this->id = 0;
    this->name = "none";
}

/**
 * Constructor for Continent class.
 * @param id Continent id.
 * @param name Continent name.
 * @param numTerritories Number of territories in the continent.
 * @return Continent object.
 */
Continent::Continent(int id, string name)
{
    this->id = id;
    this->name = name;
}

/**
 * Copy constructor for Continent class.
 * @param continent Continent object.
 * @return Continent object.
 */
Continent::Continent(const Continent &continent)
{
    this->id = continent.id;
    this->name = continent.name;
    this->territories = continent.territories;
}

/**
 * Overloaded == operator for Continent class.
 * @param continent Continent object.
 * @return True if the continents are equal, false otherwise.
 */
bool Continent::operator==(const Continent &continent)
{
    return this->id == continent.id;
}

/**
 * Overloaded << operator for Continent class.
 * @param out Output stream.
 * @param continent Continent object.
 * @return Output stream.
 */
ostream &operator<<(ostream &out, const Continent &continent)
{
    out << "Continent: " << continent.name << endl;
    out << "Territories: " << continent.territories.size() << endl;

    for (auto territory : continent.territories)
    {
        out << territory->getName() << ", ";
    }
    out << endl;

    return out;
}

/**
 * Sets the id of the continent.
 * @param id Continent id.
 */
void Continent::setId(int id)
{
    this->id = id;
}

/**
 * Adds a territory to the continent.
 * @param territory Territory object.
 */
void Continent::addTerritory(Territory *territory)
{
    this->territories.push_back(territory);
}

/**
 * Gets the id of the continent.
 * @return Continent id.
 */
int Continent::getId()
{
    return this->id;
}

/**
 * Gets the name of the continent.
 * @return Continent name.
 */
string Continent::getName()
{
    return this->name;
}

/**
 * Gets the territories in the continent.
 * @return Vector of territories.
 */
vector<Territory *> Continent::getTerritories()
{
    return this->territories;
}

/**
 * Gets the number of territories in the continent.
 * @return Number of territories.
 */
int Continent::getNumTerritories()
{
    return this->territories.size();
}
