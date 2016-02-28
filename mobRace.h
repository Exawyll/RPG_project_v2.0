#ifndef MOBRACE_H_INCLUDED
#define MOBRACE_H_INCLUDED

// Races of mobs are enumerated.
typedef enum RacesEnum  {
    GOBELIN,
    SKELETON,
    ORC,
    ZOMBIE,
    URUKAI,
    TROLL,
    DRAGON
} races;

char* setMobNames (int races);

#endif // MOBRACE_H_INCLUDED
