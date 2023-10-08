//
// Created by Tushar Raval - 40124664
//
#include "Map.h"
#include <iostream>

using namespace std;

vector<Map *> testLoadMaps(vector<string> paths)
{
    vector<Map *> maps;
    for (const auto &path : paths)
    {
        MapLoader *mapLoader = new MapLoader(path);
        
        mapLoader->getMap()->setName(path);
        
        maps.push_back(mapLoader->getMap());
        
        cout << *mapLoader->getMap() << endl;
        
        if(mapLoader->getMap()->validate()){
            cout << "*********** Map is valid *********** \n" << endl;
        }else{
            cout << "*********** Map is invalid *********** \n" << endl;
        }
    }
    return maps;
}

int main(int argc, char const *argv[])
{

    // Test MapLoader
    vector<string> paths;

    paths.push_back("../A1P1/Africa.map");
    paths.push_back("../A1P1/Canada.map");

    vector<Map *> maps = testLoadMaps(paths);


    return 0;
}