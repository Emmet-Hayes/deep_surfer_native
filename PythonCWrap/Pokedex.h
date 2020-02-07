//
//  main.c
//  PokemonC
//
//  Created by Emmet Hayes on 7/28/19.
//  Copyright © 2019 Emmet Hayes. All rights reserved.
//
/* The C Language is fun, but it sure isn't 


*/
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/* global pokemon constants */
#define MAX_NAME_LENGTH 20 //Maximum length of move, item, ability, nature, and pokemon names
#define MAX_DESC_LENGTH 150 //Maximum length of move, item, ability, nature, and pokemon descriptions
#define USER_INPUT_LIMIT 6 //Maximum length of user input during mainPokemonMenu
#define DEX_SIZE 145 //Size of preloaded pokemon stockpile

/* pseudoclass Type: determines move effectiveness, each pokemon has up to two types. */
enum TYPE {
  NONE, NORMAL, FIRE, WATER, GRASS, ELECTRIC, ICE, POISON, GROUND, FLYING, PSYCHIC, BUG,
  ROCK, FIGHTING, GHOST, DRAGON, DARK, STEEL, FAIRY
}; typedef enum TYPE Type;
const char * typeToString(Type); //returns the type as a Camel Case string

/* Gender doesn't affect anything really it's just for flair. */
enum GENDER {
  MALE, FEMALE, GENDERLESS
}; typedef enum GENDER Gender;

/* Movecat is a specialized enumerator to signify what kind of damage a move does. */
enum MOVECAT {
  PHYSICAL, SPECIAL, STATUS
}; typedef enum MOVECAT Movecat;

/* Abilities are inherent boons each pokemon has that affect battles in various ways. */
struct ABILITY {
  char name[MAX_NAME_LENGTH], desc[MAX_DESC_LENGTH];
}; typedef struct ABILITY Ability;
Ability makeAbility(const char *);

/* Items are useful tools each pokemon can hold one that affects the battle. */
struct ITEM {
  char name[MAX_NAME_LENGTH], desc[MAX_DESC_LENGTH];
}; typedef struct ITEM Item;
Item makeItem(const char *);

/* Each pokemon has four moves which will enact various effects in battle or do damage. */
struct MOVE {
  char name[MAX_NAME_LENGTH], desc[MAX_DESC_LENGTH];
  Type type;
  Movecat movecat;
  unsigned char power, acc, pp;
}; typedef struct MOVE Move;
Move initMove(const char*, const char*, Type, Movecat, unsigned char, unsigned char, unsigned char);
Move makeMove(const char *);

/* Each pokemon has a nature which affects its final stats. */
struct NATURE {
  char name[MAX_NAME_LENGTH];
  float atkmod, defmod, spamod, spdmod, spemod;
}; typedef struct NATURE Nature;
Nature makeNature(const char *);

/* Each pokemon has stat values of various kinds, base, IVs, EVs, etc. */
struct STATS {
	unsigned short hp, atk, def, spa, spd, spe;
}; typedef struct STATS Stats;

/*The struct that holds the entire Pokemon with stats, ability, moves, items, natures, etc..*/
struct POKEMON {
  char name[MAX_NAME_LENGTH];
  char desc[MAX_DESC_LENGTH];
  unsigned char level, happiness;
  Gender gender;
  bool shiny;
  Type type[2];
  Item item;
  Ability ability;
  Move move[4];
  Stats base; //hp atk def spa spd spe
  Stats evs;
  Stats ivs;
  Stats stats;
  Nature nature;
}; typedef struct POKEMON Pokemon;
Pokemon initPokemon(const char*, const char*, unsigned char, unsigned char, Gender, bool, Type, Type, Item, Ability,
	Move, Move, Move, Move, Stats, Stats, Stats, Nature);
Pokemon makePokemon(const char*); //Initializes a premade pokemon by its name(c-string)
Stats getFullStats(Pokemon); //calculates the Pokemon's active stats
float modCalculator(Move, Pokemon, Pokemon); //mod factors pokemon type, STAB bonus, crit, and random(0.85-1.00)
void printPokemon(Pokemon); //prints the pokemon passed as an argument's data 
unsigned short damageCalculator(Pokemon, Move, Pokemon, float); //factors attacker's type and move, defender's type and mod 
int testAllPokemon(); //tests the entire pokemon database
int buildTeam(); //builds a team of six pokemon
int displayDex(); //displays the entire pokemon database
int playPokemonMatch(); //allows user to pick attacking and defending pokemon and run damage calculations
int mainPokemonMenu(); //displays a pokemon database main menu