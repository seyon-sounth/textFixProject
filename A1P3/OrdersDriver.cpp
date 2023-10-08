#include <iostream>
#include "Orders.h"

int main()
{
    OrdersList Orders;
    Orders.add(Deploy());
    Orders.add(Advance());
    Orders.add(Bomb());
    Orders.add(Blockade());
    Orders.add(Airlift());
    Orders.add(Negotiate());
    Orders.move("negotiate", 0);
    Orders.iterate();
    return 0;
}
