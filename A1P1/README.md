# Read Me for Map files

## Map Formats

Maps are located at the [website](http://www.windowsgames.co.uk/conquest_maps.html).

The maps have the format **.map**. They have three main parts to them, **Map**, **Continents**, and **Territories**. We are only interested in the **Continents** and **Territories** portion of the map. The **Continents** contain a name and the number of territories in that continient:

**ContinentName**=**numberOfTerritories**

The **Territory** portion of the file contains the name of the territory, x and y corrdinates (which we are not interested in), and the remaining adjacent connected territories:

**TerritoryName**,**X**,**Y**,**ConnectedTerritoryX**,**ConnectedTerritoryY**,**ConnectedTerritoryZ**...
