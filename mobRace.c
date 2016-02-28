#include <stdio.h>
#include <stdlib.h>

char* displayMobNames (enum RacesEnum){
    switch(RacesEnum)
    {
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
