#include <stdio.h>
#include <stdlib.h>

#include "mobRace.h"

//Give a name to the mob depending of the race
char* setMobNames(int races)
{
    switch(races)
    {
        case GOBELIN:
            return "Gobelin";
            break;
        case SKELETON:
            return "Skeleton";
            break;
        case ORC:
            return "Orc";
            break;
        case ZOMBIE:
            return "Zombie";
            break;
        case URUKAI:
            return "Urukai";
            break;
        case TROLL:
            return "Troll";
            break;
        case DRAGON:
            return "Dragon";
            break;
        default:
            break;
    }
}
