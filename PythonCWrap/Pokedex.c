
//  Created by Emmet Hayes on 7/28/19.
//  Copyright © 2019 Emmet Hayes. All rights reserved.

#include "Pokedex.h"

const char* typeToString(const Type t) {
  switch (t) {
    case NONE: return "None";
    case NORMAL: return "Normal";
    case FIRE: return "Fire";
    case WATER: return "Water";
    case GRASS: return "Grass";
    case ELECTRIC: return "Electric";
    case ICE: return "Ice";
    case POISON: return "Poison";
    case GROUND: return "Ground";
    case FLYING: return "Flying";
    case PSYCHIC: return "Psychic";
    case BUG: return "Bug";
    case ROCK: return "Rock";
    case FIGHTING: return "Fighting";
    case GHOST: return "Ghost";
    case DRAGON: return "Dragon";
    case DARK: return "Dark";
    case STEEL: return "Steel";
    case FAIRY: return "Fairy";
    default: return "None";
  }
}

Ability makeAbility(const char* aName) {
  Ability a;
  strcpy(a.name, aName);
  strcpy(a.desc, "No Ability description");
  return a;
}

Item makeItem(const char* iName) {
  Item i;
  strcpy(i.name, iName);
  strcpy(i.desc, "No Item Description");
  return i;
}

Move initMove(const char* name, const char* desc, Type t, Movecat mc, unsigned char pwr, unsigned char acc, unsigned char pp) {
	Move m;
	strcpy(m.name, name);
	strcpy(m.desc, desc);
	m.type = t;
	m.movecat = mc;
	m.power = pwr;
	m.acc = acc;
	m.pp = pp;
	return m;
}

Move makeMove(const char* mName) {
  if (strcmp(mName, "Volt Tackle") == 0) { //pikachu
    return initMove("Volt Tackle", "Has 33% recoil. 10% chance to paralyze target.", ELECTRIC, PHYSICAL, 120, 100, 24);
  } else if (strcmp(mName, "Iron Tail") == 0) { //pikachu
    return initMove("Iron Tail", "30% chance to lower the target's Defense by 1.", STEEL, PHYSICAL, 100, 75, 24);
  } else if (strcmp(mName, "Brick Break") == 0) { //pikachu
    return initMove("Brick Break", "Destroys screens, unless the target is immune.", FIGHTING, PHYSICAL, 75, 100, 24);
  } else if (strcmp(mName, "Nuzzle") == 0) { //pikachu
    return initMove("Nuzzle", "100% chance to paralze target.", ELECTRIC, PHYSICAL, 20, 100, 24);
  } else if (strcmp(mName, "Sludge Bomb") == 0) { //lots
    return initMove("Sludge Bomb", "30% chance to poison target.", POISON, SPECIAL, 90, 100, 24);
  } else if (strcmp(mName, "Solar Beam") == 0) { //bulbasaur, ninetales, victreebel
    return initMove("Solar Beam", "Takes two turn to cast unless Sunny Day is active.", GRASS, SPECIAL, 120, 100, 16);
  } else if (strcmp(mName, "Synthesis") == 0) {
    return initMove("Synthesis", "Heal 50%", GRASS, STATUS, 0, 100, 8);
  } else if (strcmp(mName, "Leech Seed") == 0) { //venusaur, tangela
    return initMove("Leech Seed", "Heal 50%", GRASS, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Giga Drain") == 0) {
    return initMove("Giga Drain", "Heal 50%", GRASS, SPECIAL, 75, 100, 16);
  } else if (strcmp(mName, "Earthquake") == 0) {
    return initMove("Earthquake", "", GROUND, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Roost") == 0) {
    return initMove("Roost", "", FLYING, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Flare Blitz") == 0) {
    return initMove("Flare Blitz", "", FIRE, PHYSICAL, 120, 100, 24);
  } else if (strcmp(mName, "Outrage") == 0) {
    return initMove("Outrage", "", DRAGON, PHYSICAL, 120, 100, 24);
  } else if (strcmp(mName, "Rapid Spin") == 0) {
    return initMove("Rapid Spin", "", NORMAL, PHYSICAL, 20, 100, 64);
  } else if (strcmp(mName, "Hydro Pump") == 0) {
    return initMove("Hydro Pump", "", WATER, SPECIAL, 120, 100, 16);
  } else if (strcmp(mName, "Scald") == 0) {
    return initMove("Scald", "", WATER, SPECIAL, 80, 100, 24);
  } else if (strcmp(mName, "Aura Sphere") == 0) {
    return initMove("Aura Sphere", "", FIGHTING, SPECIAL, 80, 100, 32);
  } else if (strcmp(mName, "Sleep Powder") == 0) {
    return initMove("Sleep Powder", "", GRASS, PHYSICAL, 0, 100, 16);
  } else if (strcmp(mName, "Bug Buzz") == 0) {
    return initMove("Bug Buzz", "", BUG, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Air Slash") == 0) {
    return initMove("Air Slash", "", FLYING, PHYSICAL, 75, 95, 24);
  } else if (strcmp(mName, "Quiver Dance") == 0) {
    return initMove("Quiver Dance", "", BUG, PHYSICAL, 0, 100, 32);
  } else if (strcmp(mName, "U-turn") == 0) {
    return initMove("U-turn", "", BUG, PHYSICAL, 70, 100, 16);
  } else if (strcmp(mName, "Poison Jab") == 0) {
    return initMove("Poison Jab", "", POISON, PHYSICAL, 80, 100, 32);
  } else if (strcmp(mName, "Drill Run") == 0) {
    return initMove("Drill Run", "", GROUND, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Knock Off") == 0) {
    return initMove("Knock Off", "", DARK, PHYSICAL, 65, 100, 16);
  } else if (strcmp(mName, "Hurricane") == 0) {
    return initMove("Hurricane", "", FLYING, SPECIAL, 110, 70, 16);
  } else if (strcmp(mName, "Heat Wave") == 0) {
    return initMove("Heat Wave", "10% chance to burn the target.", FIRE, SPECIAL, 95, 90, 16);
  } else if (strcmp(mName, "Facade") == 0) {
    return initMove("Earthquake", "", NORMAL, PHYSICAL, 70, 100, 16);
  } else if (strcmp(mName, "Stomping Tantrum") == 0) {
    return initMove("Stomping Tantrum", "Power doubles if the user's last move failed.", GROUND, PHYSICAL, 75, 100, 16);
  } else if (strcmp(mName, "Sucker Punch") == 0) {
    return initMove("Sucker Punch", "", DARK, PHYSICAL, 70, 100, 8);
  } else if (strcmp(mName, "Drill Peck") == 0) {
    return initMove("Drill Peck", "", FLYING, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Frustration") == 0) {
    return initMove("Frustration", "", NORMAL, PHYSICAL, 102, 100, 16);
  } else if (strcmp(mName, "Coil") == 0) {
    return initMove("Coil", "", POISON, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Gunk Shot") == 0) {
    return initMove("Gunk Shot", "", POISON, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Thunderbolt") == 0) {
    return initMove("Thunderbolt", "", ELECTRIC, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Grass Knot") == 0) {
    return initMove("Grass Knot", "", GRASS, SPECIAL, 100, 100, 16);
  } else if (strcmp(mName, "Focus Blast") == 0) {
    return initMove("Focus Blast", "", FIGHTING, SPECIAL, 120, 170, 16);
  } else if (strcmp(mName, "Nasty Plot") == 0) {
    return initMove("Nasty Plot", "", DARK, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Stealth Rock") == 0) {
    return initMove("Stealth Rock", "", ROCK, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Toxic Spikes") == 0) {
    return initMove("Toxic Spikes", "", POISON, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Sludge Wave") == 0) {
    return initMove("Sludge Wave", "", POISON, SPECIAL, 95, 100, 16);
  } else if (strcmp(mName, "Earth Power") == 0) {
    return initMove("Earth Power", "", GROUND, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Flamethrower") == 0) {
    return initMove("Flamethrower", "", FIRE, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Overheat") == 0) {
    return initMove("Overheat", "", FIRE, SPECIAL, 130, 90, 16);
  } else if (strcmp(mName, "Fire Blast") == 0) {
    return initMove("Fire Blast", "", FIRE, SPECIAL, 110, 85, 16);
  } else if (strcmp(mName, "Hyper Voice") == 0) {
    return initMove("Hyper Voice", "", NORMAL, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Dazzling Gleam") == 0) {
    return initMove("Dazzling Gleam", "", FAIRY, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Brave Bird") == 0) {
    return initMove("Brave Bird", "", FLYING, PHYSICAL, 120, 100, 16);
  } else if (strcmp(mName, "Toxic") == 0) {
    return initMove("Toxic", "", POISON, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Strength Sap") == 0) {
    return initMove("Strength Sap", "", GRASS, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Spore") == 0) {
    return initMove("Spore", "", GRASS, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Leech Life") == 0) {
    return initMove("Leech Life", "", BUG, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Screech") == 0) {
    return initMove("Screech", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Substitute") == 0) {
    return initMove("Substitute", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Memento") == 0) {
    return initMove("Memento", "", GHOST, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Water Pulse") == 0) {
    return initMove("Water Pulse", "", WATER, SPECIAL, 60, 100, 16);
  } else if (strcmp(mName, "Rain Dance") == 0) {
    return initMove("Rain Dance", "", WATER, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Close Combat") == 0) {
    return initMove("Close Combat", "", FIGHTING, PHYSICAL, 120, 100, 16);
  } else if (strcmp(mName, "Stone Edge") == 0) {
    return initMove("Stone Edge", "", ROCK, PHYSICAL, 100, 80, 16);
  } else if (strcmp(mName, "Wild Charge") == 0) {
    return initMove("Wild Charge", "", ELECTRIC, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Extreme Speed") == 0) {
    return initMove("Extreme Speed", "", NORMAL, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Morning Sun") == 0) {
    return initMove("Morning Sun", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Vacuum Wave") == 0) {
    return initMove("Vacuum Wave", "", FIGHTING, SPECIAL, 40, 100, 16);
  } else if (strcmp(mName, "Psychic") == 0) {
    return initMove("Psychic", "", PSYCHIC, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Recover") == 0) {
    return initMove("Recover", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Shadow Ball") == 0) {
    return initMove("Shadow Ball", "", GHOST, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Bullet Punch") == 0) {
    return initMove("Bullet Punch", "", STEEL, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Weather Ball") == 0) {
    return initMove("Weather Ball", "", NORMAL, SPECIAL, 50, 100, 16);
  } else if (strcmp(mName, "Haze") == 0) {
    return initMove("Haze", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Explosion") == 0) {
    return initMove("Explosion", "", NORMAL, PHYSICAL, 250, 100, 16);
  } else if (strcmp(mName, "High Horsepower") == 0) {
    return initMove("High Horsepower", "", GROUND, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Psyshock") == 0) {
    return initMove("Psyshock", "", PSYCHIC, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Slack Off") == 0) {
    return initMove("Slack Off", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Flash Cannon") == 0) {
    return initMove("Flash Cannon", "", STEEL, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Volt Switch") == 0) {
    return initMove("Volt Switch", "", ELECTRIC, SPECIAL, 70, 100, 16);
  } else if (strcmp(mName, "First Impression") == 0) {
    return initMove("First Impression", "", NORMAL, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Leaf Blade") == 0) {
    return initMove("Leaf Blade", "", GRASS, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Swords Dance") == 0) {
    return initMove("Swords Dance", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Jump Kick") == 0) {
    return initMove("Jump Kick", "", FIGHTING, PHYSICAL, 110, 90, 16);
  } else if (strcmp(mName, "Return") == 0) {
    return initMove("Return", "", NORMAL, PHYSICAL, 102, 100, 16);
  } else if (strcmp(mName, "Whirlpool") == 0) {
    return initMove("Whirlpool", "", WATER, SPECIAL, 15, 75, 16);
  } else if (strcmp(mName, "Perish Song") == 0) {
    return initMove("Perish Song", "", NORMAL, STATUS, 0, 100, 16);
  }  else if (strcmp(mName, "Ice Beam") == 0) {
    return initMove("Ice Beam", "", ICE, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Rest") == 0) {
    return initMove("Rest", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Curse") == 0) {
    return initMove("Curse", "", GHOST, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Sleep Talk") == 0) {
    return initMove("Sleep Talk", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Shell Smash") == 0) {
    return initMove("Shell Smash", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Icicle Spear") == 0) {
    return initMove("Icicle Spear", "", ICE, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "Taunt") == 0) {
    return initMove("Taunt", "", DARK, STATUS, 10, 100, 16);
  } else if (strcmp(mName, "Rock Blast") == 0) {
    return initMove("Rock Blast", "", ROCK, PHYSICAL, 25, 100, 16);
  } else if (strcmp(mName, "Hypnosis") == 0) {
    return initMove("Hypnosis", "", PSYCHIC, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Belly Drum") == 0) {
    return initMove("Belly Drum", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Zen Headbutt") == 0) {
    return initMove("Earthquake", "", PSYCHIC, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Drain Punch") == 0) {
    return initMove("Drain Punch", "", FIGHTING, PHYSICAL, 75, 100, 16);
  } else if (strcmp(mName, "Liquidation") == 0) {
    return initMove("Liquidation", "", WATER, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "X-Scissor") == 0) {
    return initMove("X-Scissor", "", BUG, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Agility") == 0) {
    return initMove("Agility", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Reflect") == 0) {
    return initMove("Reflect", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Light Screen") == 0) {
    return initMove("Light Screen", "", PSYCHIC, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Trick Room") == 0) {
    return initMove("Trick Room", "", PSYCHIC, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Trick") == 0) {
    return initMove("Trick", "", PSYCHIC, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Leaf Storm") == 0) {
    return initMove("Leaf Storm", "", GRASS, SPECIAL, 130, 90, 16);
  } else if (strcmp(mName, "Bonemerang") == 0) {
    return initMove("Bonemerang", "", GROUND, PHYSICAL, 100, 95, 16);
  } else if (strcmp(mName, "Rock Slide") == 0) {
    return initMove("Rock Slide", "", ROCK, PHYSICAL, 75, 90, 16);
  } else if (strcmp(mName, "Fire Punch") == 0) {
    return initMove("Fire Punch", "", FIRE, PHYSICAL, 75, 100, 16);
  } else if (strcmp(mName, "Mach Punch") == 0) {
    return initMove("Mach Punch", "", FIGHTING, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Thunder Punch") == 0) {
    return initMove("Thunder Punch", "", ELECTRIC, PHYSICAL, 75, 100, 16);
  } else if (strcmp(mName, "Pain Split") == 0) {
    return initMove("Pain Split", "", NORMAL, PHYSICAL, 0, 100, 16);
  } else if (strcmp(mName, "Will-O-Wisp") == 0) {
    return initMove("Will-O-Wisp", "", FIRE, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Seismic Toss") == 0) {
    return initMove("Seismic Toss", "", FIGHTING, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Heal Bell") == 0) {
    return initMove("Heal Bell", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Soft-Boiled") == 0) {
    return initMove("Soft-Boiled", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Power-Up Punch") == 0) {
    return initMove("Power-Up Punch", "", FIGHTING, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Waterfall") == 0) {
    return initMove("Waterfall", "", WATER, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Megahorn") == 0) {
    return initMove("Megahorn", "", BUG, PHYSICAL, 120, 85, 16);
  } else if (strcmp(mName, "Aerial Ace") == 0) {
    return initMove("Aerial Ace", "", FLYING, PHYSICAL, 60, 100, 16);
  } else if (strcmp(mName, "Ice Punch") == 0) {
    return initMove("Ice Punch", "", ICE, PHYSICAL, 75, 100, 16);
  } else if (strcmp(mName, "Cross Chop") == 0) {
    return initMove("Cross Chop", "", FIGHTING, PHYSICAL, 100, 80, 16);
  } else if (strcmp(mName, "Clear Smog") == 0) {
    return initMove("Clear Smog", "", POISON, SPECIAL, 50, 100, 16);
  } else if (strcmp(mName, "Me First") == 0) {
    return initMove("Me First", "", NORMAL, PHYSICAL, 100, 100, 16);
  } else if (strcmp(mName, "Body Slam") == 0) {
    return initMove("Body Slam", "", NORMAL, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "Dragon Dance") == 0) {
    return initMove("Dragon Dance", "", DRAGON, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Bounce") == 0) {
    return initMove("Bounce", "", FLYING, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "Freeze-Dry") == 0) {
    return initMove("Freeze-Dry", "", ICE, PHYSICAL, 70, 100, 16);
  } else if (strcmp(mName, "Transform") == 0) {
    return initMove("Transform", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Baton Pass") == 0) {
    return initMove("Baton Pass", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Stored Power") == 0) {
    return initMove("Stored Power", "", PSYCHIC, SPECIAL, 20, 100, 16);
  } else if (strcmp(mName, "Last Resort") == 0) {
    return initMove("Last Resort", "", NORMAL, PHYSICAL, 140, 100, 16);
  } else if (strcmp(mName, "Wish") == 0) {
    return initMove("Wish", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Protect") == 0) {
    return initMove("Protect", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Superpower") == 0) {
    return initMove("Superpower", "", FIGHTING, PHYSICAL, 120, 100, 16);
  } else if (strcmp(mName, "Double-Edge") == 0) {
    return initMove("Double-Edge", "", NORMAL, PHYSICAL, 120, 100, 16);
  } else if (strcmp(mName, "Quick Attack") == 0) {
    return initMove("Quick Attack", "", NORMAL, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Tri Attack") == 0) {
    return initMove("Tri Attack", "", NORMAL, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Charge Beam") == 0) {
    return initMove("Charge Beam", "", ELECTRIC, SPECIAL, 50, 100, 16);
  } else if (strcmp(mName, "Shadow Ball") == 0) {
    return initMove("Shadow Ball", "", GHOST, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Signal Beam") == 0) {
    return initMove("Signal Beam", "", BUG, SPECIAL, 70, 100, 16);
  } else if (strcmp(mName, "Pursuit") == 0) {
    return initMove("Pursuit", "", DARK, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Discharge") == 0) {
    return initMove("Discharge", "", ELECTRIC, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Defog") == 0) {
    return initMove("Defog", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Fly") == 0) {
    return initMove("Fly", "", FLYING, PHYSICAL, 80, 100, 16);
  } else if (strcmp(mName, "Psystrike") == 0) {
    return initMove("Psystrike", "", PSYCHIC, SPECIAL, 100, 100, 16);
  } else if (strcmp(mName, "Aromatherapy") == 0) {
    return initMove("Aromatherapy", "", GRASS, SPECIAL, 100, 100, 16);
  } else if (strcmp(mName, "Eruption") == 0) {
    return initMove("Eruption", "", FIRE, SPECIAL, 150, 100, 16);
  } else if (strcmp(mName, "Work Up") == 0) {
    return initMove("Work Up", "", NORMAL, SPECIAL, 60, 90, 16);
  } else if (strcmp(mName, "Sticky Web") == 0) {
    return initMove("Sticky Web", "", BUG, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Dragon Pulse") == 0) {
    return initMove("Dragon Pulse", "", DRAGON, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Ancient Power") == 0) {
    return initMove("Ancient Power", "", ROCK, SPECIAL, 60, 100, 16);
  } else if (strcmp(mName, "Silver Wind") == 0) {
    return initMove("Silver Wind", "", DRAGON, SPECIAL, 60, 100, 16);
  } else if (strcmp(mName, "Night Shade") == 0) {
    return initMove("Night Shade", "", GHOST, SPECIAL, 0, 100, 16);
  } else if (strcmp(mName, "Moonblast") == 0) {
    return initMove("Dragon Tail", "", FAIRY, SPECIAL, 95, 100, 16);
  } else if (strcmp(mName, "Play Rough") == 0) {
    return initMove("Play Rough", "", FAIRY, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Aqua Jet") == 0) {
    return initMove("Aqua Jet", "", WATER, PHYSICAL, 40, 100, 16);
  } else if (strcmp(mName, "Head Smash") == 0) {
    return initMove("Head Smash", "", ROCK, PHYSICAL, 150, 100, 16);
  } else if (strcmp(mName, "Wood Hammer") == 0) {
    return initMove("Wood Hammer", "", GRASS, PHYSICAL, 120, 100, 16);
  } else if (strcmp(mName, "Acrobatics") == 0) {
    return initMove("Acrobatics", "", FLYING, PHYSICAL, 55, 100, 16);
  } else if (strcmp(mName, "Foul Play") == 0) {
    return initMove("Foul Play", "", DARK, PHYSICAL, 90, 100, 16);
  } else if (strcmp(mName, "Tail Slap") == 0) {
    return initMove("Play Rough", "", NORMAL, PHYSICAL, 25, 100, 16);
  } else if (strcmp(mName, "Thunder Wave") == 0) {
    return initMove("Thunder Wave", "", ELECTRIC, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Spikes") == 0) {
    return initMove("Spikes", "", GROUND, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Gyro Ball") == 0) {
    return initMove("Gyro Ball", "", STEEL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Encore") == 0) {
    return initMove("Encore", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Hex") == 0) {
    return initMove("Play Rough", "", GHOST, SPECIAL, 65, 100, 16);
  } else if (strcmp(mName, "Will-O-Wisp") == 0) {
    return initMove("Will-O-Wisp", "", FIRE, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Counter") == 0) {
    return initMove("Counter", "", FIGHTING, PHYSICAL, 0, 100, 16);
  } else if (strcmp(mName, "Mirror Coat") == 0) {
    return initMove("Mirror Coat", "", PSYCHIC, SPECIAL, 0, 100, 16);
  } else if (strcmp(mName, "Destiny Bond") == 0) {
    return initMove("Destiny Bond", "", GHOST, SPECIAL, 0, 100, 16);
  } else if (strcmp(mName, "Psychic Fangs") == 0) {
    return initMove("Psychic Fangs", "", PSYCHIC, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "Glare") == 0) {
    return initMove("Play Rough", "", DRAGON, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Headbutt") == 0) {
    return initMove("Play Rough", "", DRAGON, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Infestation") == 0) {
    return initMove("Infestation", "", BUG, SPECIAL, 20, 100, 16);
  } else if (strcmp(mName, "Bullet Seed") == 0) {
    return initMove("Bullet Seed", "", GRASS, SPECIAL, 20, 100, 16);
  } else if (strcmp(mName, "Icicle Crash") == 0) {
    return initMove("Icicle Crash", "", ICE, PHYSICAL, 85, 100, 16);
  } else if (strcmp(mName, "Yawn") == 0) {
    return initMove("Yawn", "", DRAGON, SPECIAL, 90, 100, 16);
  } else if (strcmp(mName, "Lava Plume") == 0) {
    return initMove("Lava Plume", "", FIRE, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Energy Ball") == 0) {
    return initMove("Energy Ball", "", GRASS, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Icy Wind") == 0) {
    return initMove("Icy Wind", "", ICE, SPECIAL, 55, 95, 16);
  } else if (strcmp(mName, "Whirlwind") == 0) {
    return initMove("Whirlwind", "", FLYING, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Dark Pulse") == 0) {
    return initMove("Dark Pulse", "", DARK, SPECIAL, 80, 100, 16);
  } else if (strcmp(mName, "Focus Energy") == 0) {
    return initMove("Focus Energy", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Draco Meteor") == 0) {
    return initMove("Draco Meteor", "", DRAGON, SPECIAL, 130, 90, 16);
  } else if (strcmp(mName, "Foresight") == 0) {
    return initMove("Foresight", "", FIGHTING, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Milk Drink") == 0) {
    return initMove("Milk Drink", "", NORMAL, STATUS, 0, 100, 16);
  } else if (strcmp(mName, "Sacred Fire") == 0) {
    return initMove("Sacred Fire", "", FIRE, PHYSICAL, 100, 95, 16);
  } else if (strcmp(mName, "Aeroblast") == 0) {
    return initMove("Aeroblast", "", FLYING, SPECIAL, 100, 95, 16);
  } else if (strncmp(mName, "Hidden Power", 12) == 0) { //if first 12 chars are "Hidden Power"
    char * p = (char *)mName;
    p += 13;
    Move t = initMove("Hidden Power", "", NORMAL, SPECIAL, 60, 100, 16);
    printf("Hidden power is %s\n", p);
    if (strcmp(p, "Ice") == 0) t.type = ICE;
    else if (strcmp(p, "Ghost") == 0) t.type = GHOST;
    else if (strcmp(p, "Grass") == 0) t.type = GRASS;
    else if (strcmp(p, "Fire") == 0) t.type = FIRE;
    else if (strcmp(p, "Fighting") == 0) t.type = FIGHTING;
    else if (strcmp(p, "Psychic") == 0) t.type = PSYCHIC;
  } return initMove("No Name", "No Move Description", NONE, 0, 0, 100, 24);
}

Nature makeNature(const char* nName) {
  Nature n = { "No Nature", 1.0f, 1.0f, 1.0f, 1.0f, 1.0f };
  strcpy(n.name, nName);
  if (strcmp(nName, "Modest") == 0) {
    n.atkmod = 0.9f; n.spamod = 1.1f;
  } else if (strcmp(nName, "Adamant") == 0) {
    n.atkmod = 1.1f; n.spamod = 0.9f;
  } else if (strcmp(nName, "Jolly") == 0) {
    n.spemod = 1.1f; n.spamod = 0.9f;
  } else if (strcmp(nName, "Timid") == 0) {
    n.spemod = 1.1f; n.atkmod = 0.9f;
  } else if (strcmp(nName, "Bold") == 0) {
    n.defmod = 1.1f; n.atkmod = 0.9f;
  } else if (strcmp(nName, "Brave") == 0) {
    n.atkmod = 1.1f; n.spemod = 0.9f;
  } else if (strcmp(nName, "Calm") == 0) {
    n.spdmod = 1.1f; n.atkmod = 0.9f;
  } else if (strcmp(nName, "Careful") == 0) {
    n.spdmod = 1.1f; n.spamod = 0.9f;
  } else if (strcmp(nName, "Gentle") == 0) {
    n.spdmod = 1.1f; n.defmod = 0.9f;
  } else if (strcmp(nName, "Hasty") == 0) {
    n.spemod = 1.1f; n.defmod = 0.9f;
  } else if (strcmp(nName, "Impish") == 0) {
    n.defmod = 1.1f; n.spamod = 0.9f;
  } else if (strcmp(nName, "Lax") == 0) {
    n.defmod = 1.1f; n.spdmod = 0.9f;
  } else if (strcmp(nName, "Lonely") == 0) {
    n.atkmod = 1.1f; n.defmod = 0.9f;
  } else if (strcmp(nName, "Mild") == 0) {
    n.spamod = 1.1f; n.defmod = 0.9f;
  } else if (strcmp(nName, "Naive") == 0) {
    n.spemod = 1.1f; n.spdmod = 0.9f;
  } else if (strcmp(nName, "Naughty") == 0) {
    n.atkmod = 1.1f; n.spdmod = 0.9f;
  } else if (strcmp(nName, "Quiet") == 0) {
    n.spamod = 1.1f; n.spemod = 0.9f;
  } else if (strcmp(nName, "Rash") == 0) {
    n.spamod = 1.1f; n.spdmod = 0.9f;
  } else if (strcmp(nName, "Relaxed") == 0) {
    n.defmod = 1.1f; n.spemod = 0.9f;
  } else if (strcmp(nName, "Sassy") == 0) {
    n.spdmod = 1.1f; n.spemod = 0.9f;
  }
  return n;
}

Stats getFullStats(Pokemon p) {
  Stats tStats;
  tStats.hp = (unsigned short)((((p.ivs.hp + 2 * p.base.hp + (p.evs.hp / 4)) * p.level) / 100) + 10);
  tStats.atk = (unsigned short)((((2*p.base.atk + (p.evs.atk/4) + p.ivs.atk)*p.level)/100 + 5) * p.nature.atkmod);
  tStats.def = (unsigned short)((((2*p.base.def + (p.evs.def/4) + p.ivs.def)*p.level)/100 + 5) * p.nature.defmod);
  tStats.spa = (unsigned short)((((2*p.base.spa + (p.evs.spa/4) + p.ivs.spa)*p.level)/100 + 5) * p.nature.spamod);
  tStats.spd = (unsigned short)((((2*p.base.spd + (p.evs.spd/4) + p.ivs.spd)*p.level)/100 + 5) * p.nature.spdmod);
  tStats.spe = (unsigned short)((((2*p.base.spe + (p.evs.spe/4) + p.ivs.spe)*p.level)/100 + 5) * p.nature.spemod);
  return tStats;
}

Pokemon initPokemon(const char* name, const char* desc, unsigned char lvl, unsigned char happy, Gender g, bool sh,
	Type type1, Type type2, Item item, Ability ability, Move move1, Move move2, Move move3, Move move4, 
	Stats base, Stats ivs, Stats evs, Nature nature) {
	Pokemon p;
	strcpy(p.name, name);
	strcpy(p.desc, desc);
	p.level = lvl;
	p.happiness = happy;
	p.gender = g;
	p.shiny = sh;
	p.type[0] = type1;
	p.type[1] = type2;
	p.item = item; 
	p.ability = ability; 
	p.move[0] = move1; 
	p.move[1] = move2;
	p.move[2] = move3;
	p.move[3] = move4;
	p.base = base;
	p.ivs = ivs;
	p.evs = evs;
	p.nature = nature;
	p.stats = getFullStats(p);
	return p;
}

Pokemon makePokemon(const char* pName) {
  if (strcmp(pName, "Bulbasaur") == 0) {
    return initPokemon("Bulbasaur", "", 100, 255, 0, 0, GRASS, POISON,
      makeItem("Life Orb"), makeAbility("Chlorophyll"),  makeMove("Sludge Bomb"),
        makeMove("Solar Beam"), makeMove("Sleep Powder"), makeMove("Giga Drain"),
      (Stats){45, 49, 49, 65, 65, 45}, (Stats){0, 0, 0, 252, 6, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Venusaur") == 0) {
    return initPokemon("Venusaur", "", 100, 255, 0, 0, GRASS, POISON,
      makeItem("Venusaurite"), makeAbility("Chlorophyll"), makeMove("Leech Seed"),
        makeMove("Sludge Bomb"), makeMove("Synthesis"), makeMove("Earthquake"),
      (Stats){80, 82, 83, 100, 100, 80}, (Stats){252, 0, 172, 0, 68, 16}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Serious"));
  } else if (strcmp(pName, "Charizard") == 0) {
    return initPokemon("Charizard", "", 100, 255, 0, 0, FIRE, FLYING,
      makeItem("Charizardite X"), makeAbility("Blaze"), makeMove("Roost"),
        makeMove("Flare Blitz"), makeMove("Outrage"), makeMove("Earthquake"),
		(Stats){78, 84, 78, 109, 85, 100}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Blastoise") == 0) {
    return initPokemon("Blastoise", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Blastoisinite"), makeAbility("Rain Dish"), makeMove("Rapid Spin"),
        makeMove("Ice Beam"), makeMove("Aura Sphere"), makeMove("Scald"),
		(Stats){79, 83, 100, 85, 105, 78}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Butterfree") == 0) {
    return initPokemon("Butterfree", "", 100, 255, 0, 0, BUG, FLYING,
      makeItem("Focus Sash"), makeAbility("Tinted Lens"), makeMove("Sleep Powder"),
        makeMove("Quiver Dance"), makeMove("Bug Buzz"), makeMove("Air Slash"),
		(Stats){60, 45, 50, 90, 80, 70}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Beedrill") == 0) {
    return initPokemon("Beedrill", "", 100, 255, 0, 0, BUG, POISON,
      makeItem("Beedrillite"), makeAbility("Swarm"), makeMove("U-turn"),
        makeMove("Poison Jab"), makeMove("Drill Run"), makeMove("Knock Off"),
		(Stats){60, 45, 50, 90, 80, 70}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Pidgeot") == 0) {
    return initPokemon("Pidgeot", "", 100, 255, 0, 0, NORMAL, FLYING,
      makeItem("Pidgeotite"), makeAbility("Big Pecks"), makeMove("Hurricane"),
        makeMove("Heat Wave"), makeMove("U-turn"), makeMove("Roost"),
		(Stats) {60, 45, 50, 90, 80, 70}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Raticate") == 0) {
    return initPokemon("Raticate", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Flame Orb"), makeAbility("Guts"), makeMove("Facade"),
        makeMove("Stomping Tantrum"), makeMove("Sucker Punch"), makeMove("U-turn"),
		(Stats){55, 81, 60, 50, 70, 97}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Fearow") == 0) {
    return initPokemon("Fearow", "", 100, 0, 0, 0, NORMAL, FLYING,
      makeItem("Scope Lens"), makeAbility("Sniper"), makeMove("Drill Peck"),
        makeMove("Frustration"), makeMove("Drill Run"), makeMove("U-turn"),
		(Stats){65, 90, 65, 61, 61, 100}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Arbok") == 0) {
    return initPokemon("Arbok", "", 100, 255, 0, 0, POISON, NONE,
      makeItem("Black Sludge"), makeAbility("Intimidate"), makeMove("Coil"),
        makeMove("Gunk Shot"), makeMove("Earthquake"), makeMove("Sucker Punch"),
		(Stats){60, 95, 69, 65, 79, 80}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Pikachu") == 0) {
    return initPokemon("Pikachu", "Physical Pikachu", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Light Ball"), makeAbility("Static"), makeMove("Volt Tackle"),
        makeMove("Iron Tail"), makeMove("Brick Break"), makeMove("Nuzzle"),
		(Stats){35, 55, 40, 50, 50, 90}, (Stats){0, 252, 0, 0, 6, 252}, (Stats) {31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Raichu") == 0) {
    return initPokemon("Raichu", "Special Raichu", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Life Orb"), makeAbility("Lightning Rod"), makeMove("Thunderbolt"),
        makeMove("Grass Knot"), makeMove("Focus Blast"), makeMove("Nasty Plot"),
		(Stats){60, 90, 55, 90, 80, 110}, (Stats){0, 252, 0, 0, 6, 252}, (Stats) {31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Sandslash") == 0) {
    return initPokemon("Sandslash", "Spiky Sandslash", 100, 255, 0, 0, GROUND, NONE,
      makeItem("Leftovers"), makeAbility("Sand Rush"), makeMove("Earthquake"),
        makeMove("Knock Off"), makeMove("Rapid Spin"), makeMove("Stealth Rock"),
		(Stats){75, 100, 110, 45, 55, 65}, (Stats){252, 4, 0, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Nidoqueen") == 0) {
    return initPokemon("Nidoqueen", "Protective Nidoqueen", 100, 255, 0, 0, POISON, GROUND,
      makeItem("Black Sludge"), makeAbility("Sheer Force"), makeMove("Toxic Spikes"),
        makeMove("Sludge Wave"), makeMove("Earth Power"), makeMove("Ice Beam"),
		(Stats){90, 92, 87, 75, 85, 76}, (Stats){252, 0, 108, 0, 72, 76}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));
  } else if (strcmp(pName, "Nidoking") == 0) {
    return initPokemon("Nidoqueen", "Angry Nidoking", 100, 255, 0, 0, POISON, GROUND,
      makeItem("Life Orb"), makeAbility("Sheer Force"), makeMove("Flamethrower"),
        makeMove("Sludge Wave"), makeMove("Earth Power"), makeMove("Ice Beam"),
		(Stats){81, 102, 77, 85, 75, 85}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Clefable") == 0) {
    return initPokemon("Clefable", "", 100, 255, 0, 0, FAIRY, NONE,
      makeItem("Leftovers"), makeAbility("Magic Guard"), makeMove("Moonblast"),
        makeMove("Soft-Boiled"), makeMove("Stealth Rock"), makeMove("Wish"),
		(Stats) {95, 70, 73, 95, 90, 60}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));
  } else if (strcmp(pName, "Ninetales") == 0) { //RU
    return initPokemon("Ninetales", "Sunny Specs Ninetales", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Choice Specs"), makeAbility("Drought"), makeMove("Overheat"),
        makeMove("Fire Blast"), makeMove("Solar Beam"), makeMove("Hidden Power Ice"),
		(Stats) {73, 76, 75, 81, 100, 100}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Wigglytuff") == 0) {
    return initPokemon("Wigglytuff", "Fluffy Wigglytuff", 100, 255, 0, 0, NORMAL, FAIRY,
      makeItem("Life Orb"), makeAbility("Competitive"), makeMove("Stealth Rock"),
        makeMove("Hyper Voice"), makeMove("Dazzling Gleam"), makeMove("Fire Blast"),
		(Stats) {140, 70, 45, 85, 50, 45}, (Stats){4, 0, 0, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Golbat") == 0) {
    return initPokemon("Golbat", "Cave Golbat", 100, 255, 0, 0, POISON, FLYING,
      makeItem("Eviolite"), makeAbility("Infiltrator"), makeMove("Brave Bird"),
        makeMove("Toxic"), makeMove("Defog"), makeMove("Roost"),
		(Stats) {75, 80, 70, 65, 75, 90}, (Stats){252, 0, 0, 0, 80, 176}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Oddish") == 0) {
    return initPokemon("Oddish", "Stinky Oddish", 100, 255, 0, 0, GRASS, POISON,
      makeItem("Eviolite"), makeAbility("Chlorophyll"), makeMove("Sleep Powder"),
        makeMove("Strength Sap"), makeMove("Sludge Bomb"), makeMove("Giga Drain"),
		(Stats) {45, 50, 55, 75, 65, 30}, (Stats){160, 0, 236, 0, 76, 36}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest")); //LC
  } else if (strcmp(pName, "Vileplume") == 0) {
    return initPokemon("Vileplume", "Shitty Venusaur Basically", 100, 255, 0, 0, GRASS, POISON,
      makeItem("Leftovers"), makeAbility("Chlorophyll"), makeMove("Sleep Powder"),
        makeMove("Strength Sap"), makeMove("Sludge Bomb"), makeMove("Giga Drain"),
		(Stats) {75, 80, 85, 110, 90, 50}, (Stats){160, 0, 236, 0, 76, 36}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//vileplume sucks NUBL
  } else if (strcmp(pName, "Parasect") == 0) {
    return initPokemon("Parasect", "Rare Cripple", 100, 255, 0, 0, BUG, GRASS,
      makeItem("Leftovers"), makeAbility("Dry Skin"), makeMove("Spore"),
        makeMove("Leech Life"), makeMove("Synthesis"), makeMove("Knock Off"),
		(Stats) {60, 95, 80, 60, 80, 30}, (Stats){248, 0, 8, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Careful"));
  } else if (strcmp(pName, "Venomoth") == 0) {
    return initPokemon("Venomoth", "", 100, 255, 0, 0, BUG, POISON,
      makeItem("Buginium Z"), makeAbility("Tinted Lens"), makeMove("Quiver Dance"),
        makeMove("Sleep Powder"), makeMove("Bug Buzz"), makeMove("Sludge Bomb"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Dugtrio") == 0) {
    return initPokemon("Dugtrio", "", 100, 255, 0, 0, GROUND, NONE,
      makeItem("Groundium Z"), makeAbility("Arena Trap"), makeMove("Earthquake"),
        makeMove("Screech"), makeMove("Substitute"), makeMove("Memento"),
		(Stats) {35, 100, 50, 50, 70, 120}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Persian") == 0) {
    return initPokemon("Persian", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Life Orb"), makeAbility("Technician"), makeMove("Nasty Plot"),
        makeMove("Hyper Voice"), makeMove("Hidden Power Ghost"), makeMove("Water Pulse"),
		(Stats) {65, 70, 60, 65, 65, 115}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Golduck") == 0) {
    return initPokemon("Golduck", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Life Orb"), makeAbility("Swift Swim"), makeMove("Rain Dance"),
        makeMove("Hydro Pump"), makeMove("Ice Beam"), makeMove("Hidden Power Grass"),
		(Stats) {80, 82, 78, 95, 80, 85}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Primeape") == 0) {
    return initPokemon("Primeape", "", 100, 255, 0, 0, FIGHTING, NONE,
      makeItem("Choice Scarf"), makeAbility("Defiant"), makeMove("Close Combat"),
        makeMove("U-turn"), makeMove("Stone Edge"), makeMove("Gunk Shot"),
		(Stats) {65, 105, 60, 60, 70, 95}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Arcanine") == 0) {
    return initPokemon("Arcanine", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Life Orb"), makeAbility("Flash Fire"), makeMove("Flare Blitz"),
        makeMove("Wild Charge"), makeMove("Extreme Speed"), makeMove("Morning Sun"),
		(Stats) {90, 110, 80, 100, 80, 95}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Poliwrath") == 0) {
    return initPokemon("Poliwrath", "", 100, 255, 0, 0, WATER, FIGHTING,
      makeItem("Leftovers"), makeAbility("Water Absorb"), makeMove("Scald"),
        makeMove("Focus Blast"), makeMove("Toxic"), makeMove("Vacuum Wave"),
		(Stats) {90, 95, 95, 70, 90, 70}, (Stats){252, 0, 0, 160, 0, 96}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Alakazam") == 0) {
    return initPokemon("Alakazam", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Alakazite"), makeAbility("Magic Guard"), makeMove("Psychic"),
        makeMove("Recover"), makeMove("Focus Blast"), makeMove("Shadow Ball"),
		(Stats) {55, 50, 45, 135, 95, 120}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Machamp") == 0) {
    return initPokemon("Machamp", "", 100, 255, 0, 0, FIGHTING, NONE,
      makeItem("Flame Orb"), makeAbility("Guts"), makeMove("Close Combat"),
        makeMove("Knock Off"), makeMove("Facade"), makeMove("Bullet Punch"),
		(Stats) {90, 130, 80, 65, 85, 55}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Victreebel") == 0) {
    return initPokemon("Victreebel", "", 100, 255, 0, 0, GRASS, POISON,
      makeItem("Life Orb"), makeAbility("Chlorophyll"), makeMove("Solar Beam"),
        makeMove("Sleep Powder"), makeMove("Weather Ball"), makeMove("Sludge Bomb"),
		(Stats) {80, 70, 65, 80, 120, 80}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Tentacruel") == 0) {
    return initPokemon("Tentacruel", "", 100, 255, 0, 0, WATER, POISON,
      makeItem("Black Sludge"), makeAbility("Clear Body"), makeMove("Scald"),
        makeMove("Rapid Spin"), makeMove("Haze"), makeMove("Sludge Bomb"),
		(Stats) {80, 70, 65, 80, 120, 100}, (Stats){252, 0, 112, 0, 0, 144}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Golem") == 0) {
    return initPokemon("Golem", "", 100, 255, 0, 0, GROUND, ROCK,
      makeItem("Weakness Policy"), makeAbility("Sturdy"), makeMove("Stealth Rock"),
        makeMove("Earthquake"), makeMove("Stone Edge"), makeMove("Explosion"),
		(Stats) {80, 120, 130, 55, 65, 45}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Rapidash") == 0) {
    return initPokemon("Rapidash", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Firium Z"), makeAbility("Flash Fire"), makeMove("Flare Blitz"),
        makeMove("Wild Charge"), makeMove("High Horsepower"), makeMove("Morning Sun"),
		(Stats) {65, 100, 70, 80, 80, 105}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Slowbro") == 0) {
    return initPokemon("Slowbro", "", 100, 255, 0, 0, WATER, PSYCHIC,
      makeItem("Leftovers"), makeAbility("Regenerator"), makeMove("Scald"),
        makeMove("Psyshock"), makeMove("Ice Beam"), makeMove("Slack Off"),
		(Stats) {95, 75, 110, 100, 80, 30}, (Stats){252, 0, 252, 4, 0, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//RU Uber OU UU
  } else if (strcmp(pName, "Magneton") == 0) {
    return initPokemon("Magneton", "", 100, 255, 0, 0, ELECTRIC, STEEL,
      makeItem("Choice Specs"), makeAbility("Magnet Pull"), makeMove("Thunderbolt"),
        makeMove("Flash Cannon"), makeMove("Volt Switch"), makeMove("Hidden Power Fire"),
		(Stats) {50, 60, 95, 120, 70, 70}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Farfetch'd") == 0) {
    return initPokemon("Farfetch'd", "", 100, 255, 0, 0, NORMAL, FLYING,
      makeItem("Stick"), makeAbility("Defiant"), makeMove("First Impression"),
        makeMove("Brave Bird"), makeMove("Leaf Blade"), makeMove("Knock Off"),
		(Stats) {52, 90, 55, 58, 62, 60}, (Stats){0, 252, 5, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Dodrio") == 0) {
    return initPokemon("Dodrio", "", 100, 255, 0, 0, NORMAL, FLYING,
      makeItem("Flyinium Z"), makeAbility("Early Bird"), makeMove("Swords Dance"),
        makeMove("Brave Bird"), makeMove("Jump Kick"), makeMove("Return"),
		(Stats) {60, 110, 70, 60, 60, 110}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Dewgong") == 0) {
    return initPokemon("Dewgong", "", 100, 255, 0, 0, WATER, ICE,
      makeItem("Leftovers"), makeAbility("Hydration"), makeMove("Whirlpool"),
        makeMove("Perish Song"), makeMove("Rain Dance"), makeMove("Rest"),
		(Stats) {90, 70, 80, 70, 95, 70}, (Stats){252, 0, 4, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));
  } else if (strcmp(pName, "Muk") == 0) {
    return initPokemon("Muk", "", 100, 255, 0, 0, POISON, NONE,
      makeItem("Black Sludge"), makeAbility("Sticky Hold"), makeMove("Curse"),
        makeMove("Poison Jab"), makeMove("Rest"), makeMove("Sleep Talk"),
		(Stats) {105, 105, 75, 65, 100, 50}, (Stats){252, 4, 0, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Careful"));//PU
  } else if (strcmp(pName, "Cloyster") == 0) {
    return initPokemon("Cloyster", "", 100, 255, 0, 0, WATER, ICE,
      makeItem("Focus Sash"), makeAbility("Skill Link"), makeMove("Toxic Spikes"),
        makeMove("Shell Smash"), makeMove("Icicle Spear"), makeMove("Rapid Spin"),
		(Stats) {50, 95, 180, 85, 45, 70}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//RU Uber
  } else if (strcmp(pName, "Gengar") == 0) {
    return initPokemon("Gengar", "", 100, 255, 0, 0, GHOST, POISON,
      makeItem("Life Orb"), makeAbility("Tinted Lens"), makeMove("Shadow Ball"),
        makeMove("Taunt"), makeMove("Focus Blast"), makeMove("Sludge Wave"),
		(Stats) {60, 65, 60, 130, 75, 110}, (Stats){4, 0, 0, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//Uber UU OU
  } else if (strcmp(pName, "Onix") == 0) {
    return initPokemon("Onix", "", 100, 255, 0, 0, ROCK, GROUND,
      makeItem("Eviolite"), makeAbility("Sturdy"), makeMove("Stealth Rock"),
        makeMove("Earthquake"), makeMove("Rock Blast"), makeMove("Explosion"),
		(Stats) {35, 45, 160, 30, 45, 70}, (Stats){76, 236, 0, 0, 0, 196}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Hypno") == 0) {
    return initPokemon("Hypno", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Psychium Z"), makeAbility("Insomnia"), makeMove("Hypnosis"),
        makeMove("Belly Drum"), makeMove("Zen Headbutt"), makeMove("Drain Punch"),
		(Stats) {85, 73, 70, 73, 115, 67}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//RUBL
  } else if (strcmp(pName, "Kingler") == 0) {
    return initPokemon("Kingler", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Life Orb"), makeAbility("Sheer Force"), makeMove("Agility"),
        makeMove("Swords Dance"), makeMove("Liquidation"), makeMove("X-Scissor"),
		(Stats) {55, 130, 115, 50, 50, 75}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//PUBL
  } else if (strcmp(pName, "Electrode") == 0) {
    return initPokemon("Electrode", "", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Light Clay"), makeAbility("Aftermath"), makeMove("Reflect"),
        makeMove("Light Screen"), makeMove("Taunt"), makeMove("Volt Switch"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){252, 0, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//RUBL
  } else if (strcmp(pName, "Exeggcutor") == 0) {
    return initPokemon("Exeggcutor", "", 100, 255, 0, 0, GRASS, PSYCHIC,
      makeItem("Grassium Z"), makeAbility("Harvest"), makeMove("Trick Room"),
        makeMove("Leaf Storm"), makeMove("Psychic"), makeMove("Hidden Power Fighting"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){248, 0, 8, 252, 0, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Quiet"));//RUBL
  } else if (strcmp(pName, "Cubone") == 0) {
    return initPokemon("Cubone", "Lonely Cubone", 100, 255, 0, 0, GROUND, NONE,
      makeItem("Eviolite"), makeAbility("Battle Armor"), makeMove("Bonemerang"),
        makeMove("Knock Off"), makeMove("Rock Slide"), makeMove("Fire Punch"),
		(Stats) {50, 50, 95, 40, 50, 35}, (Stats){0, 196, 76, 0, 0, 236}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Marowak") == 0) {
    return initPokemon("Marowak", "", 100, 255, 0, 0, GROUND, NONE,
      makeItem("Thick Club"), makeAbility("Battle Armor"), makeMove("Bonemerang"),
        makeMove("Stone Edge"), makeMove("Knock Off"), makeMove("Swords Dance"),
		(Stats) {60, 80, 110, 50, 80, 45}, (Stats){248, 252, 8, 0, 0, 0}, (Stats){31, 31, 31, 31, 31, 0},
      makeNature("Brave"));//RUBL
  } else if (strcmp(pName, "Hitmonlee") == 0) {
    return initPokemon("Hitmonlee", "", 100, 255, 0, 0, FIGHTING, NONE,
      makeItem("White Herb"), makeAbility("Unburden"), makeMove("Curse"),
        makeMove("Close Combat"), makeMove("Knock Off"), makeMove("Earthquake"),
		(Stats) {50, 120, 53, 35, 110, 87}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//NU
  } else if (strcmp(pName, "Hitmonchan") == 0) {
    return initPokemon("Hitmonchan", "", 100, 255, 0, 0, FIGHTING, NONE,
      makeItem("Assault Vest"), makeAbility("Iron Fist"), makeMove("Drain Punch"),
        makeMove("Mach Punch"), makeMove("Thunder Punch"), makeMove("Rapid Spin"),
		(Stats) {50, 105, 79, 35, 110, 76}, (Stats){156, 224, 0, 0, 0, 128}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//PU
  } else if (strcmp(pName, "Weezing") == 0) {
    return initPokemon("Weezing", "", 100, 255, 0, 0, POISON, NONE,
      makeItem("Rocky Helmet"), makeAbility("Levitate"), makeMove("Will-O-Wisp"),
        makeMove("Pain Split"), makeMove("Toxic Spikes"), makeMove("Sludge Bomb"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){252, 0, 152, 0, 88, 16}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//NU
  } else if (strcmp(pName, "Rhydon") == 0) {
    return initPokemon("Rhydon", "", 100, 255, 0, 0, GROUND, ROCK,
      makeItem("Eviolite"), makeAbility("Lightning Rod"), makeMove("Earthquake"),
        makeMove("Swords Dance"), makeMove("Stealth Rock"), makeMove("Stone Edge"),
		(Stats) {105, 130, 120, 45, 45, 40}, (Stats){4, 252, 0, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//NU
  } else if (strcmp(pName, "Chansey") == 0) {
    return initPokemon("Chansey", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Eviolite"), makeAbility("Natural Cure"), makeMove("Seismic Toss"),
        makeMove("Toxic"), makeMove("Heal Bell"), makeMove("Soft-Boiled"),
		(Stats) {250, 5, 5, 35, 105, 40}, (Stats){248, 0, 252, 0, 8, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//OU Uber
  } else if (strcmp(pName, "Tangela") == 0) {
    return initPokemon("Tangela", "", 100, 255, 0, 0, GRASS, NONE,
      makeItem("Eviolite"), makeAbility("Regenerator"), makeMove("Giga Drain"),
        makeMove("Knock Off"), makeMove("Leech Seed"), makeMove("Hidden Power Fire"),
		(Stats) {65, 55, 115, 100, 40, 60}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//PU RU
  } else if (strcmp(pName, "Kangaskhan") == 0) {
    return initPokemon("Kangaskhan", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Leftovers"), makeAbility("Scrappy"), makeMove("Substitute"),
        makeMove("Toxic"), makeMove("Power-Up Punch"), makeMove("Return"),
		(Stats) {105, 95, 80, 40, 80, 90}, (Stats){252, 0, 148, 0, 108, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));//PU Uber
  } else if (strcmp(pName, "Seadra") == 0) {
    return initPokemon("Seadra", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Eviolite"), makeAbility("Poison Point"), makeMove("Agility"),
        makeMove("Ice Beam"), makeMove("Hydro Pump"), makeMove("Flash Cannon"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){4, 0, 252, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));
  } else if (strcmp(pName, "Seaking") == 0) {
    return initPokemon("Seaking", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Life Orb"), makeAbility("Lightning Rod"), makeMove("Waterfall"),
        makeMove("Knock Off"), makeMove("Drill Run"), makeMove("Megahorn"),
		(Stats) {80, 92, 65, 65, 80, 68}, (Stats){64, 252, 0, 0, 0, 192}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Starmie") == 0) {
    return initPokemon("Starmie", "", 100, 255, 0, 0, WATER, PSYCHIC,
      makeItem("Waterium Z"), makeAbility("Analytic"), makeMove("Hydro Pump"),
        makeMove("Ice Beam"), makeMove("Psyshock"), makeMove("Thunderbolt"),
		(Stats) {60, 75, 85, 100, 85, 110}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//UU
  } else if (strcmp(pName, "Mr. Mime") == 0) {
    return initPokemon("Mr. Mime", "", 100, 255, 0, 0, PSYCHIC, FAIRY,
      makeItem("Fightinium Z"), makeAbility("Soundproof"), makeMove("Nasty Plot"),
        makeMove("Dazzling Gleam"), makeMove("Focus Blast"), makeMove("Psyshock"),
		(Stats) {40, 45, 65, 100, 120, 90}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Scyther") == 0) {
    return initPokemon("Scyther", "", 100, 255, 0, 0, BUG, FLYING,
      makeItem("Eviolite"), makeAbility("Technician"), makeMove("Swords Dance"),
        makeMove("Roost"), makeMove("U-turn"), makeMove("Aerial Ace"),
		(Stats) {70, 110, 80, 55, 80, 105}, (Stats){248, 8, 0, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//PU
  } else if (strcmp(pName, "Jynx") == 0) {
    return initPokemon("Jynx", "", 100, 255, 0, 0, ICE, PSYCHIC,
      makeItem("Normalium Z"), makeAbility("Dry Skin"), makeMove("Lovely Kiss"),
        makeMove("Nasty Plot"), makeMove("Ice Beam"), makeMove("Psyshock"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Electabuzz") == 0) {
    return initPokemon("Electabuzz", "", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Eviolite"), makeAbility("Static"), makeMove("Power-Up Punch"),
        makeMove("Cross Chop"), makeMove("Thunder Punch"), makeMove("Ice Punch"),
		(Stats) {65, 83, 57, 95, 85, 105}, (Stats){0, 4, 252, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Magmar") == 0) {
    return initPokemon("Magmar", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Eviolite"), makeAbility("Flame Body"), makeMove("Clear Smog"),
        makeMove("Flamethrower"), makeMove("Psychic"), makeMove("Focus Blast"),
		(Stats) {65, 95, 57, 100, 85, 93}, (Stats){4, 0, 252, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Pinsir") == 0) {
    return initPokemon("Pinsir", "", 100, 255, 0, 0, BUG, NONE,
      makeItem("Normalium Z"), makeAbility("Moxie"), makeMove("Me First"),
        makeMove("X-Scissor"), makeMove("Earthquake"), makeMove("Stone Edge"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//PU
  } else if (strcmp(pName, "Tauros") == 0) {
    return initPokemon("Tauros", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Life Orb"), makeAbility("Sheer Force"), makeMove("Body Slam"),
        makeMove("Fire Blast"), makeMove("Zen Headbutt"), makeMove("Earthquake"),
		(Stats) {75, 100, 95, 40, 70, 110}, (Stats){0, 252, 0, 4, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PUBL
  } else if (strcmp(pName, "Gyarados") == 0) {
    return initPokemon("Gyarados", "", 100, 255, 0, 0, WATER, FLYING,
      makeItem("Flyinium Z"), makeAbility("Moxie"), makeMove("Dragon Dance"),
        makeMove("Waterfall"), makeMove("Bounce"), makeMove("Earthquake"),
		(Stats) {95, 125, 79, 60, 100, 81}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//UUBL OU
  } else if (strcmp(pName, "Lapras") == 0) {
    return initPokemon("Lapras", "", 100, 255, 0, 0, WATER, ICE,
      makeItem("Choice Specs"), makeAbility("Water Absorb"), makeMove("Freeze-Dry"),
        makeMove("Hydro Pump"), makeMove("Ice Beam"), makeMove("Hidden Power Fire"),
		(Stats) {130, 55, 50, 85, 95, 60}, (Stats){120, 0, 0, 252, 0, 136}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//PU
  } else if (strcmp(pName, "Ditto") == 0) {
    return initPokemon("Ditto", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Choice Scarf"), makeAbility("Imposter"), makeMove("Transform"),
        makeMove("No Move"), makeMove("No Move"), makeMove("No Move"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU OU UBER lol
  } else if (strcmp(pName, "Eevee") == 0) {
    return initPokemon("Eevee", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Eevium Z"), makeAbility("Anticipation"), makeMove("Baton Pass"),
        makeMove("Substitute"), makeMove("Stored Power"), makeMove("Last Resort"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){212, 0, 0, 92, 0, 204}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Vaporeon") == 0) {
    return initPokemon("Vaporeon", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Leftovers"), makeAbility("Water Absorb"), makeMove("Scald"),
        makeMove("Heal Bell"), makeMove("Wish"), makeMove("Protect"),
		(Stats) {70, 65, 60, 90, 75, 90}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//NU
  } else if (strcmp(pName, "Jolteon") == 0) {
    return initPokemon("Jolteon", "", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Life Orb"), makeAbility("Volt Absorb"), makeMove("Thunderbolt"),
        makeMove("Volt Switch"), makeMove("Hidden Power Ice"), makeMove("Shadow Ball"),
		(Stats) {65, 65, 60, 110, 95, 130}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
     //RU
  } else if (strcmp(pName, "Flareon") == 0) {
    return initPokemon("Flareon", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Choice Band"), makeAbility("Flash Fire"), makeMove("Flare Blitz"),
        makeMove("Superpower"), makeMove("Double-Edge"), makeMove("Quick Attack"),
		(Stats) {65, 130, 60, 95, 110, 65}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//RUBL
  } else if (strcmp(pName, "Porygon") == 0) {
    return initPokemon("Porygon", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Eviolite"), makeAbility("Analytic"), makeMove("Tri Attack"),
        makeMove("Charge Beam"), makeMove("Shadow Ball"), makeMove("Signal Beam"),
		(Stats) {65, 60, 70, 85, 75, 40}, (Stats){0, 0, 252, 4, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));
  } else if (strcmp(pName, "Omastar") == 0) {
    return initPokemon("Omastar", "", 100, 255, 0, 0, WATER, ROCK,
      makeItem("White Herb"), makeAbility("Weak Armor"), makeMove("Hydro Pump"),
        makeMove("Ice Beam"), makeMove("Earth Power"), makeMove("Shell Smash"),
		(Stats) {70, 60, 125, 115, 70, 55}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Kabutops") == 0) {
    return initPokemon("Kabutops", "", 100, 255, 0, 0, WATER, ROCK,
      makeItem("Choice Scarf"), makeAbility("Swift Swim"), makeMove("Liquidation"),
        makeMove("Stone Edge"), makeMove("Knock Off"), makeMove("Rapid Spin"),
		(Stats) {60, 115, 105, 65, 70, 80}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//PU
  } else if (strcmp(pName, "Aerodactyl") == 0) {
    return initPokemon("Aerodactyl", "", 100, 255, 0, 0, ROCK, FLYING,
      makeItem("Life Orb"), makeAbility("Unnerve"), makeMove("Stone Edge"),
        makeMove("Earthquake"), makeMove("Roost"), makeMove("Pursuit"),
		(Stats) {80, 105, 65, 60, 75, 130}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//NU RU UU
  } else if (strcmp(pName, "Snorlax") == 0) {
    return initPokemon("Snorlax", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Leftovers"), makeAbility("Thick Fat"), makeMove("Curse"),
        makeMove("Rest"), makeMove("Body Slam"), makeMove("Earthquake"),
		(Stats) {160, 110, 65, 65, 110, 30}, (Stats){188, 0, 128, 0, 192, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Careful"));//RU UU
  } else if (strcmp(pName, "Articuno") == 0) {
    return initPokemon("Articuno", "", 100, 255, 0, 0, ICE, FLYING ,
      makeItem("Leftovers"), makeAbility("Pressure"), makeMove("Substitute"),
        makeMove("Roost"), makeMove("Freeze-Dry"), makeMove("Hurricane"),
		(Stats) {90, 85, 100, 95, 125, 85}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU UU
  } else if (strcmp(pName, "Zapdos") == 0) {
    return initPokemon("Zapdos", "", 100, 255, 0, 0, ELECTRIC, FLYING,
      makeItem("Leftovers"), makeAbility("Static"), makeMove("Discharge"),
        makeMove("Roost"), makeMove("Heat Wave"), makeMove("Defog"),
		(Stats) {90, 90, 85, 125, 90, 100}, (Stats){248, 0, 240, 0, 0, 20}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//OU
  } else if (strcmp(pName, "Moltres") == 0) {
    return initPokemon("Moltres", "", 100, 255, 0, 0, FIRE, FLYING,
      makeItem("Flyinium Z"), makeAbility("Flame Body"), makeMove("Hurricane"),
        makeMove("Fire Blast"), makeMove("Roost"), makeMove("U-turn"),
		(Stats) {90, 100, 90, 125, 85, 90}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//UU
  } else if (strcmp(pName, "Dragonite") == 0) {
    return initPokemon("Dragonite", "", 100, 255, 0, 0, DRAGON, FLYING,
      makeItem("Flyinium Z"), makeAbility("Multiscale"), makeMove("Dragon Dance"),
        makeMove("Fly"), makeMove("Earthquake"), makeMove("Extreme Speed"),
		(Stats) {91, 134, 95, 100, 100, 80}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//UUBL
  } else if (strcmp(pName, "Mewtwo") == 0) {
    return initPokemon("Mewtwo", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Life Orb"), makeAbility("Unnerve"), makeMove("Psystrike"),
        makeMove("Ice Beam"), makeMove("Fire Blast"), makeMove("Calm Mind"),
		(Stats) {106, 110, 90, 154, 90, 130}, (Stats){0, 40, 0, 216, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//Uber
  } else if (strcmp(pName, "Mew") == 0) {
    return initPokemon("Mew", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Leftovers"), makeAbility("Synchronize"), makeMove("Earthquake"),
        makeMove("Will-O-Wisp"), makeMove("Soft-Boiled"), makeMove("Stealth Rock"),
		(Stats) {100, 100, 100, 100, 100, 100}, (Stats){240, 0, 52, 0, 0, 216}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//OU
  } else if (strcmp(pName, "Meganium") == 0) {
    return initPokemon("Meganium", "", 100, 255, 0, 0, GRASS, NONE,
      makeItem("Leftovers"), makeAbility("Overgrow"), makeMove("Aromatherapy"),
        makeMove("Giga Drain"), makeMove("Synthesis"), makeMove("Dragon Tail"),
		(Stats) {80, 82, 100, 83, 100, 80}, (Stats){252, 0, 4, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//untiered
  } else if (strcmp(pName, "Typhlosion") == 0) {
    return initPokemon("Typhlosion", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Choice Specs"), makeAbility("Blaze"), makeMove("Eruption"),
        makeMove("Fire Blast"), makeMove("Focus Blast"), makeMove("Hidden Power Grass"),
		(Stats) {78, 84, 78, 109, 85, 100}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//nu
  } else if (strcmp(pName, "Feraligatr") == 0) {
    return initPokemon("Feraligatr", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Life Orb"), makeAbility("Sheer Force"), makeMove("Dragon Dance"),
        makeMove("Liquidation"), makeMove("Ice Punch"), makeMove("Crunch"),
		(Stats) {85, 105, 100, 79, 83, 78}, (Stats){4, 252, 0, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//uu ru
  } else if (strcmp(pName, "Furret") == 0) {
    return initPokemon("Furret", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Choice Scarf"), makeAbility("Frisk"), makeMove("Trick"),
        makeMove("Double-Edge"), makeMove("U-turn"), makeMove("Knock Off"),
		(Stats) {85, 76, 64, 45, 55, 90}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Noctowl") == 0) {
    return initPokemon("Noctowl", "", 100, 255, 0, 0, NORMAL, FLYING,
      makeItem("Flyinium Z"), makeAbility("Tinted Lens"), makeMove("Agility"),
        makeMove("Work Up"), makeMove("Hurricane"), makeMove("Roost"),
		(Stats) {100, 50, 50, 86, 96, 70}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//untiered - pu
  } else if (strcmp(pName, "Ledian") == 0) {
    return initPokemon("Ledian", "Trololol", 100, 255, 0, 0, BUG, FLYING,
      makeItem("Life Orb"), makeAbility("Iron Fist"), makeMove("Power-Up Punch"),
        makeMove("Drain Punch"), makeMove("Ice Punch"), makeMove("Thunder Punch"),
		(Stats) {55, 35, 50, 55, 110, 85}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//absolute shit 35 base attack no niche lol
    
  } else if (strcmp(pName, "Ariados") == 0) {
    return initPokemon("Ariados", "", 100, 255, 0, 0, BUG, POISON,
      makeItem("Focus Sash"), makeAbility("Swarm"), makeMove("Sticky Web"),
        makeMove("Toxic Spikes"), makeMove("Megahorn"), makeMove("Sucker Punch"),
		(Stats) {70, 90, 70, 60, 70, 40}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Crobat") == 0) {
    return initPokemon("Crobat", "", 100, 255, 0, 0, POISON, FLYING,
      makeItem("Flyinium Z"), makeAbility("Infiltrator"), makeMove("Brave Bird"),
        makeMove("U-Turn"), makeMove("Roost"), makeMove("Taunt"),
		(Stats) {85, 90, 80, 70, 80, 130}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//UU mono
  } else if (strcmp(pName, "Lanturn") == 0) {
    return initPokemon("Lanturn", "", 100, 255, 0, 0, WATER, ELECTRIC,
      makeItem("Assault Vest"), makeAbility("Volt Absorb"), makeMove("Scald"),
        makeMove("Volt Switch"), makeMove("Ice Beam"), makeMove("Hidden Power Grass"),
		(Stats) {125, 58, 58, 76, 76, 67}, (Stats){0, 0, 0, 172, 136, 200}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//PU good at it
  } else if (strcmp(pName, "Togetic") == 0) {
    return initPokemon("Togetic", "", 100, 255, 0, 0, FAIRY, FLYING,
      makeItem("Eviolite"), makeAbility("Serene Grace"), makeMove("Ancient Power"),
        makeMove("Ominous Wind"), makeMove("Silver Wind"), makeMove("Stored Power"),
		(Stats) {55, 40, 85, 80, 105, 40}, (Stats){252, 0, 160, 0, 96, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));
  } else if (strcmp(pName, "Xatu") == 0) {
    return initPokemon("Xatu", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Rocky Helmet"), makeAbility("Magic Bounce"), makeMove("Night Shade"),
        makeMove("Roost"), makeMove("U-turn"), makeMove("Toxic"),
		(Stats) {65, 75, 70, 95, 70, 95}, (Stats){252, 0, 196, 0, 0, 60}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));
  } else if (strcmp(pName, "Ampharos") == 0) {
    return initPokemon("Ampharos", "", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Ampharosite"), makeAbility("Static"), makeMove("Volt Switch"),
        makeMove("Dragon Pulse"), makeMove("Focus Blast"), makeMove("Thunderbolt"),
		(Stats) {90, 75, 85, 115, 90, 55}, (Stats){4, 0, 0, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Bellossom") == 0) {
    return initPokemon("Bellossom", "", 100, 255, 0, 0, GRASS, NONE,
      makeItem("Leftovers"), makeAbility("Chlorophyll"), makeMove("Strength Sap"),
        makeMove("Quiver Dance"), makeMove("Giga Drain"), makeMove("Moonblast"),
		(Stats) {75, 80, 95, 90, 100, 50}, (Stats){248, 0, 8, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Azumarill") == 0) {
    return initPokemon("Azumarill", "", 100, 255, 0, 0, WATER, FAIRY,
      makeItem("Normalium Z"), makeAbility("Huge Power"), makeMove("Belly Drum"),
        makeMove("Aqua Jet"), makeMove("Play Rough"), makeMove("Knock Off"),
		(Stats) {100, 50, 80, 60, 80, 50}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//OU
  } else if (strcmp(pName, "Sudowoodo") == 0) {
    return initPokemon("Sudowoodo", "", 100, 255, 0, 0, ROCK, NONE,
      makeItem("Choice Band"), makeAbility("Rock Head"), makeMove("Head Smash"),
        makeMove("Earthquake"), makeMove("Wood Hammer"), makeMove("Sucker Punch"),
		(Stats) {70, 100, 115, 30, 65, 30}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));
  } else if (strcmp(pName, "Politoed") == 0) {
    return initPokemon("Politoed", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Chesto Berry"), makeAbility("Drizzle"), makeMove("Toxic"),
        makeMove("Protect"), makeMove("Scald"), makeMove("Rest"),
		(Stats) {90, 75, 75, 90, 100, 70}, (Stats){248, 0, 0, 0, 252, 8}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//PU
  } else if (strcmp(pName, "Jumpluff") == 0) {
    return initPokemon("Jumpluff", "", 100, 255, 0, 0, GRASS, FLYING,
      makeItem("No Item"), makeAbility("Infiltrator"), makeMove("Swords Dance"),
        makeMove("Strength Sap"), makeMove("Sleep Powder"), makeMove("Acrobatics"),
		(Stats) {75, 55, 70, 55, 95, 110}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));
  } else if (strcmp(pName, "Aipom") == 0) {
    return initPokemon("Aipom", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Eviolite"), makeAbility("Skill Link"), makeMove("Tail Slap"),
        makeMove("Agility"), makeMove("Gunk Shot"), makeMove("Power-Up Punch"),
		(Stats) {55, 70, 55, 40, 55, 85}, (Stats){80, 0, 176, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));
  } else if (strcmp(pName, "Sunflora") == 0) {
    return initPokemon("Sunflora", "", 100, 255, 0, 0, GRASS, NONE,
      makeItem("Life Orb"), makeAbility("Solar Power"), makeMove("Solar Beam"),
        makeMove("Earth Power"), makeMove("Sludge Bomb"), makeMove("Giga Drain"),
		(Stats) {75, 75, 55, 105, 85, 30}, (Stats){92, 0, 0, 252, 0, 164}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));
  } else if (strcmp(pName, "Yanma") == 0) {
    return initPokemon("Yanma", "", 100, 255, 0, 0, BUG, FLYING,
      makeItem("Eviolite"), makeAbility("Speed Boost"), makeMove("Bug Buzz"),
        makeMove("Protect"), makeMove("Air Slash"), makeMove("Giga Drain"),
		(Stats) {85, 76, 64, 45, 55, 90}, (Stats){4, 0, 252, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));
  } else if (strcmp(pName, "Quagsire") == 0) {
    return initPokemon("Quagsire", "", 100, 255, 0, 0, WATER, GROUND,
      makeItem("Leftovers"), makeAbility("Unaware"), makeMove("Earthquake"),
        makeMove("Waterfall"), makeMove("Recover"), makeMove("Curse"),
		(Stats) {95, 85, 85, 65, 65, 35}, (Stats){252, 4, 252, 0, 0, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));//pu nu ru uu ou
  } else if (strcmp(pName, "Espeon") == 0) {
    return initPokemon("Espeon", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Leftovers"), makeAbility("Magic Bounce"), makeMove("Calm Mind"),
        makeMove("Psychic"), makeMove("Shadow Ball"), makeMove("Morning Sun"),
		(Stats) {65, 65, 60, 130, 95, 110}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//ru uu
  } else if (strcmp(pName, "Umbreon") == 0) {
    return initPokemon("Umbreon", "", 100, 255, 0, 0, DARK, NONE,
      makeItem("Leftovers"), makeAbility("Magic Bounce"), makeMove("Wish"),
        makeMove("Heal Bell"), makeMove("Protect"), makeMove("Foul Play"),
		(Stats) {95, 65, 110, 60, 130, 65}, (Stats){252, 0, 4, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//ru uu
  } else if (strcmp(pName, "Murkrow") == 0) {
    return initPokemon("Murkrow", "", 100, 255, 0, 0, DARK, FLYING,
      makeItem("Eviolite"), makeAbility("Prankster"), makeMove("Thunder Wave"),
        makeMove("Roost"), makeMove("Brave Bird"), makeMove("Sucker Punch"),
		(Stats) {60, 85, 42, 85, 42, 91}, (Stats){68, 0, 188, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));
  } else if (strcmp(pName, "Slowking") == 0) {
    return initPokemon("Slowking", "", 100, 255, 0, 0, WATER, PSYCHIC,
      makeItem("Assault Vest"), makeAbility("Regenerator"), makeMove("Scald"),
        makeMove("Psyshock"), makeMove("Fire Blast"), makeMove("Dragon Tail"),
		(Stats) {95, 75, 80, 100, 110, 30}, (Stats){212, 0, 0, 252, 0, 44}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//NU RU
  }  else if (strcmp(pName, "Misdreavus") == 0) {
    return initPokemon("Misdreavus", "", 100, 255, 0, 0, GHOST, NONE,
      makeItem("Eviolite"), makeAbility("Levitate"), makeMove("Hex"),
        makeMove("Will-O-Wisp"), makeMove("Taunt"), makeMove("Pain Split"),
		(Stats) {60, 60, 60, 85, 85, 85}, (Stats){252, 0, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Unown") == 0) {
    return initPokemon("Unown", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Choice Specs"), makeAbility("Levitate"), makeMove("Hidden Power Psychic"),
        makeMove("No Move"), makeMove("No Move"), makeMove("No Move"),
		(Stats) {48, 72, 48, 72, 48, 48}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  } else if (strcmp(pName, "Wobbuffet") == 0) {
    return initPokemon("Wobbuffet", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Shadow Tag"), makeAbility("Custap Berry"), makeMove("Counter"),
        makeMove("Mirror Coat"), makeMove("Encore"), makeMove("Destiny Bond"),
		(Stats) {190, 33, 58, 33, 58, 33}, (Stats){252, 0, 4, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//Uber because of shadow tag
  } else if (strcmp(pName, "Girafarig") == 0) {
    return initPokemon("Girafarig", "", 100, 255, 0, 0, PSYCHIC, NORMAL,
      makeItem("Choice Band"), makeAbility("Sap Sipper"), makeMove("Return"),
        makeMove("Psychic Fangs"), makeMove("Earthquake"), makeMove("Trick"),
		(Stats) {70, 80, 65, 90, 65, 85}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//absolute shit
  } else if (strcmp(pName, "Forretress") == 0) {
    return initPokemon("Forretress", "", 100, 255, 0, 0, BUG, STEEL,
      makeItem("Leftovers"), makeAbility("Overcoat"), makeMove("Spikes"),
        makeMove("Rapid Spin"), makeMove("Volt Switch"), makeMove("Gyro Ball"),
		(Stats) {75, 90, 140, 60, 60, 40}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 0},
      makeNature("Relaxed"));//RU
  } else if (strcmp(pName, "Dunsparce") == 0) {
    return initPokemon("Dunsparce", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Leftovers"), makeAbility("Serene Grace"), makeMove("Glare"),
        makeMove("Headbutt"), makeMove("Rock Slide"), makeMove("Roost"),
		(Stats) {100, 70, 70, 65, 65, 45}, (Stats){252, 36, 0, 0, 0, 220}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//absolute shit
  } else if (strcmp(pName, "Gligar") == 0) {
    return initPokemon("Gligar", "", 100, 255, 0, 0, GROUND, FLYING,
      makeItem("Eviolite"), makeAbility("Immunity"), makeMove("Earthquake"),
        makeMove("Roost"), makeMove("Defog"), makeMove("U-turn"),
		(Stats) {65, 75, 105, 35, 65, 85}, (Stats){4, 0, 252, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));//UU
  } else if (strcmp(pName, "Steelix") == 0) {
    return initPokemon("Steelix", "", 100, 255, 0, 0, STEEL, GROUND,
      makeItem("Steelixite"), makeAbility("Sturdy"), makeMove("Stealth Rock"),
        makeMove("Gyro Ball"), makeMove("Earthquake"), makeMove("Curse"),
		(Stats) {75, 85, 200, 55, 65, 30}, (Stats){252, 208, 0, 0, 48, 0}, (Stats){31, 31, 31, 31, 31, 0},
      makeNature("Brave"));//uu nu non mega
  } else if (strcmp(pName, "Granbull") == 0) {
    return initPokemon("Granbull", "", 100, 255, 0, 0, FAIRY, NONE,
      makeItem("Leftovers"), makeAbility("Intimidate"), makeMove("Heal Bell"),
        makeMove("Thunder Wave"), makeMove("Play Rough"), makeMove("Earthquake"),
		(Stats) {90, 120, 75, 60, 60, 45}, (Stats){212, 252, 0, 0, 0, 44}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//absolute shit
  } else if (strcmp(pName, "Qwilfish") == 0) {
    return initPokemon("Qwilfish", "", 100, 255, 0, 0, WATER, POISON,
      makeItem("Rocky Helmet"), makeAbility("Intimidate"), makeMove("Spikes"),
        makeMove("Toxic Spikes"), makeMove("Taunt"), makeMove("Waterfall"),
		(Stats) {65, 95, 85, 55, 55, 85}, (Stats){252, 0, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//PU
  } else if (strcmp(pName, "Scizor") == 0) {
    return initPokemon("Scizor", "", 100, 255, 0, 0, BUG, STEEL,
      makeItem("Scizorite"), makeAbility("Light Metal"), makeMove("Roost"),
        makeMove("Swords Dance"), makeMove("Bullet Punch"), makeMove("Knock Off"),
		(Stats) {70, 130, 100, 55, 80, 65}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));//UU OU
  } else if (strcmp(pName, "Shuckle") == 0) {
    return initPokemon("Shuckle", "", 100, 255, 0, 0, BUG, ROCK,
      makeItem("Mental Herb"), makeAbility("Sturdy"), makeMove("Sticky Web"),
        makeMove("Stealth Rock"), makeMove("Encore"), makeMove("Infestation"),
		(Stats) {20, 10, 230, 10, 230, 5}, (Stats){248, 0, 8, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//absolute shit
  } else if (strcmp(pName, "Heracross") == 0) {
    return initPokemon("Heracross", "", 100, 255, 0, 0, BUG, FIGHTING,
      makeItem("Heracrossite"), makeAbility("Moxie"), makeMove("Swords Dance"),
        makeMove("Close Combat"), makeMove("Rock Blast"), makeMove("Bullet Seed"),
		(Stats) {80, 125, 75, 40, 95, 85}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//UUBL RUBL
  } else if (strcmp(pName, "Sneasel") == 0) {
    return initPokemon("Sneasel", "", 100, 255, 0, 0, DARK, ICE,
      makeItem("Choice Band"), makeAbility("Inner Focus"), makeMove("Knock Off"),
        makeMove("Icicle Crash"), makeMove("Ice Shard"), makeMove("Pursuit"),
		(Stats) {55, 95, 55, 35, 75, 115}, (Stats){0, 252, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//NU RU
  } else if (strcmp(pName, "Ursaring") == 0) {
    return initPokemon("Ursaring", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Flame Orb"), makeAbility("Guts"), makeMove("Swords Dance"),
        makeMove("Facade"), makeMove("Crunch"), makeMove("Close Combat"),
		(Stats) {90, 130, 75, 75, 75, 55}, (Stats){252, 252, 4, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 0},
      makeNature("Brave"));//absolute shit
  } else if (strcmp(pName, "Magcargo") == 0) {
    return initPokemon("Magcargo", "", 100, 255, 0, 0, FIRE, ROCK,
      makeItem("Leftovers"), makeAbility("Flame Body"), makeMove("Stealth Rock"),
        makeMove("Recover"), makeMove("Yawn"), makeMove("Lava Plume"),
		(Stats) {60, 50, 120, 90, 80, 30}, (Stats){248, 0, 8, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//absolute shit
  } else if (strcmp(pName, "Piloswine") == 0) {
    return initPokemon("Piloswine", "", 100, 255, 0, 0, ICE, GROUND,
      makeItem("Eviolite"), makeAbility("Thick Fat"), makeMove("Stealth Rock"),
        makeMove("Earthquake"), makeMove("Icicle Crash"), makeMove("Ice Shard"),
		(Stats) {100, 100, 80, 60, 60, 50}, (Stats){252, 252, 4, 0, 0, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//absolute shit
  } else if (strcmp(pName, "Corsola") == 0) {
    return initPokemon("Corsola", "", 100, 255, 0, 0, WATER, ROCK,
      makeItem("Leftovers"), makeAbility("Regenerator"), makeMove("Recover"),
        makeMove("Scald"), makeMove("Stealth Rock"), makeMove("Toxic"),
		(Stats) {65, 55, 95, 65, 95, 35}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//absolute shit
  } else if (strcmp(pName, "Octillery") == 0) {
    return initPokemon("Octillery", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Life Orb"), makeAbility("Sniper"), makeMove("Hydro Pump"),
        makeMove("Fire Blast"), makeMove("Energy Ball"), makeMove("Ice Beam"),
		(Stats) {75, 105, 75, 105, 75, 45}, (Stats){252, 0, 0, 252, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Modest"));//absolute shit
  } else if (strcmp(pName, "Delibird") == 0) {
    return initPokemon("Delibird", "", 100, 255, 0, 0, ICE, FLYING,
      makeItem("Focus Sash"), makeAbility("Vital Spirit"), makeMove("Spikes"),
        makeMove("Rapid Spin"), makeMove("Icy Wind"), makeMove("Destiny Bond"),
		(Stats) {45, 55, 45, 65, 45, 75}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//absolute shit
  } else if (strcmp(pName, "Mantine") == 0) {
    return initPokemon("Espeon", "", 100, 255, 0, 0, WATER, FLYING,
      makeItem("Leftovers"), makeAbility("Water Absorb"), makeMove("Roost"),
        makeMove("Defog"), makeMove("Scald"), makeMove("Air Slash"),
		(Stats) {85, 40, 70, 80, 140, 70}, (Stats){252, 0, 0, 0, 120, 136}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));// ru uu ou
  } else if (strcmp(pName, "Skarmory") == 0) {
    return initPokemon("Skarmory", "", 100, 255, 0, 0, PSYCHIC, NONE,
      makeItem("Rocky Helmet"), makeAbility("Sturdy"), makeMove("Roost"),
        makeMove("Spikes"), makeMove("Whirlwind"), makeMove("Toxic"),
		(Stats) {65, 80, 140, 40, 70, 70}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//absolute shit
  } else if (strcmp(pName, "Houndoom") == 0) {
    return initPokemon("Houndoom", "", 100, 255, 0, 0, FIRE, DARK,
      makeItem("Houndoominite"), makeAbility("Flash Fire"), makeMove("Nasty Plot"),
        makeMove("Fire Blast"), makeMove("Dark Pulse"), makeMove("Sludge Bomb"),
		(Stats) {75, 90, 90, 140, 90, 115}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//RUBL UU
  } else if (strcmp(pName, "Kingdra") == 0) {
    return initPokemon("Kingdra", "", 100, 255, 0, 0, WATER, DRAGON,
      makeItem("Scope Lens"), makeAbility("Sniper"), makeMove("Focus Energy"),
        makeMove("Draco Meteor"), makeMove("Hydro Pump"), makeMove("Substitute"),
		(Stats) {75, 95, 95, 95, 95, 85}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//absolute shit
  } else if (strcmp(pName, "Donphan") == 0) {
    return initPokemon("Donphan", "", 100, 255, 0, 0, GROUND, NONE,
      makeItem("Leftovers"), makeAbility("Sturdy"), makeMove("Rapid Spin"),
        makeMove("Earthquake"), makeMove("Knock Off"), makeMove("Ice Shard"),
		(Stats) {90, 120, 120, 60, 60, 50}, (Stats){252, 252, 0, 0, 0, 4}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//ru
  } else if (strcmp(pName, "Porygon2") == 0) {
    return initPokemon("Porygon2", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Eviolite"), makeAbility("Trace"), makeMove("Recover"),
        makeMove("Ice Beam"), makeMove("Foul Play"), makeMove("Toxic"),
		(Stats) {85, 80, 90, 105, 95, 60}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//ru uu
  } else if (strcmp(pName, "Stantler") == 0) {
    return initPokemon("Stantler", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Life Orb"), makeAbility("Intimidate"), makeMove("Double-Edge"),
        makeMove("Sucker Punch"), makeMove("Jump Kick"), makeMove("Energy Ball"),
		(Stats) {73, 95, 62, 85, 65, 85}, (Stats){0, 252, 0, 4, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Lonely"));//absolute shit
  } else if (strcmp(pName, "Smeargle") == 0) {
    return initPokemon("Smeargle", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Focus Sash"), makeAbility("Own Tempo"), makeMove("Sticky Web"),
        makeMove("Nuzzle"), makeMove("Taunt"), makeMove("Whirlwind"),
		(Stats) {65, 65, 60, 130, 95, 110}, (Stats){252, 0, 4, 0, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Jolly"));//uber pu
  } else if (strcmp(pName, "Hitmontop") == 0) {
    return initPokemon("Hitmontop", "", 100, 255, 0, 0, FIGHTING, NONE,
      makeItem("Leftovers"), makeAbility("Intimidate"), makeMove("Rapid Spin"),
        makeMove("Toxic"), makeMove("Foresight"), makeMove("Close Combat"),
		(Stats) {50, 95, 95, 35, 110, 70}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Impish"));//absolute shit
  } else if (strcmp(pName, "Miltank") == 0) {
    return initPokemon("Miltank", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Leftovers"), makeAbility("Thick Fat"), makeMove("Stealth Rock"),
        makeMove("Seismic Toss"), makeMove("Milk Drink"), makeMove("Toxic"),
		(Stats) {95, 80, 105, 40, 70, 100}, (Stats){252, 0, 236, 0, 0, 20}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Calm"));//nu
  } else if (strcmp(pName, "Blissey") == 0) {
    return initPokemon("Blissey", "", 100, 255, 0, 0, NORMAL, NONE,
      makeItem("Leftovers"), makeAbility("Natural Cure"), makeMove("Seismic Toss"),
        makeMove("Toxic"), makeMove("Soft-Boiled"), makeMove("Heal Bell"),
		(Stats) {255, 10, 10, 75, 135, 55}, (Stats){252, 0, 252, 0, 4, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//uu but chansey is ou lololol
  } else if (strcmp(pName, "Raikou") == 0) {
    return initPokemon("Raikou", "", 100, 255, 0, 0, ELECTRIC, NONE,
      makeItem("Leftovers"), makeAbility("Pressure"), makeMove("Calm Mind"),
        makeMove("Substitute"), makeMove("Thunderbolt"), makeMove("Hidden Power Ice"),
		(Stats) {90, 85, 75, 115, 100, 115}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//RU
  } else if (strcmp(pName, "Entei") == 0) {
    return initPokemon("Entei", "", 100, 255, 0, 0, FIRE, NONE,
      makeItem("Choice Band"), makeAbility("Pressure"), makeMove("Sacred Fire"),
        makeMove("Extreme Speed"), makeMove("Stone Edge"), makeMove("Flare Blitz"),
		(Stats) {115, 115, 85, 90, 75, 100}, (Stats){0, 252, 0, 0, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//RUBL
  } else if (strcmp(pName, "Suicune") == 0) {
    return initPokemon("Suicune", "", 100, 255, 0, 0, WATER, NONE,
      makeItem("Leftovers"), makeAbility("Magic Bounce"), makeMove("Calm Mind"),
        makeMove("Protect"), makeMove("Scald"), makeMove("Substitute"),
		(Stats) {100, 75, 115, 90, 115, 85}, (Stats){252, 0, 0, 0, 40, 216}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//uu ou
  } else if (strcmp(pName, "Tyranitar") == 0) {
    return initPokemon("Tyranitar", "", 100, 255, 0, 0, ROCK, DARK,
      makeItem("Assault Vest"), makeAbility("Sand Stream"), makeMove("Rock Slide"),
        makeMove("Crunch"), makeMove("Pursuit"), makeMove("Earthquake"),
		(Stats) {100, 134, 110, 95, 100, 61}, (Stats){224, 32, 0, 0, 252, 0}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Careful"));//ou AG Uber!!!!
  } else if (strcmp(pName, "Lugia") == 0) {
    return initPokemon("Lugia", "", 100, 255, 0, 0, PSYCHIC, FLYING,
      makeItem("Leftovers"), makeAbility("Multiscale"), makeMove("Roost"),
        makeMove("Toxic"), makeMove("Aeroblast"), makeMove("Psychic"),
		(Stats) {106, 90, 130, 90, 154, 110}, (Stats){252, 0, 160, 0, 0, 96}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Bold"));//ubers
  } else if (strcmp(pName, "Ho-oh") == 0) {
    return initPokemon("Ho-oh", "", 100, 255, 0, 0, FIRE, FLYING,
      makeItem("Life Orb"), makeAbility("Regenerator"), makeMove("Sacred Fire"),
        makeMove("Brave Bird"), makeMove("Recover"), makeMove("Substitute"),
		(Stats) {106, 130, 90, 110, 154, 90}, (Stats){104, 252, 0, 0, 0, 152}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Adamant"));//ubers
  } else if (strcmp(pName, "Celebi") == 0) {
    return initPokemon("Celebi", "", 100, 255, 0, 0, GRASS, PSYCHIC,
      makeItem("Psychium Z"), makeAbility("Natural Cure"), makeMove("Nasty Plot"),
        makeMove("Psychic"), makeMove("Giga Drain"), makeMove("Dazzling Gleam"),
		(Stats) {100, 100, 100, 100, 100, 100}, (Stats){0, 0, 0, 252, 4, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));//uu
  } else {
    return initPokemon("Missingno", "Mystical Missingno", 100, 255, 0, 0, NONE, NONE,
      makeItem("Light Ball"), makeAbility("Static"), makeMove("Volt Tackle"),
        makeMove("Iron Tail"), makeMove("Brick Break"), makeMove("Nuzzle"),
		(Stats) {65, 65, 60, 130, 95, 110}, (Stats){0, 0, 4, 252, 0, 252}, (Stats){31, 31, 31, 31, 31, 31},
      makeNature("Timid"));
  }
}

float modCalculator(Move aMove, Pokemon ap, Pokemon dp) {
  float mod = 1.0f;
  int i; //iterator
  switch (aMove.type) { //first deal with type of attack
    case NONE: break;
    case NORMAL: { //for each attack iterate throw defending pokemons types
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) { //and adjust the modifier according to the type grid
          case ROCK: case STEEL: mod /= 2.f; break;
          case GHOST: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case FIRE: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case GRASS: case ICE: case BUG: case STEEL: mod *= 2.f; break;
          case ROCK: case WATER: case FIRE: case DRAGON: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case WATER: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case FIRE: case GROUND: case ROCK: mod *= 2.f; break;
          case GRASS: case WATER: case DRAGON: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case GRASS: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case WATER: case GROUND: case ROCK: mod *= 2.f; break;
          case FLYING: case BUG: case POISON: case STEEL: case GRASS: case FIRE: case DRAGON: mod /= 2; break;
          default: break;
        }
      } break;
    } case ELECTRIC: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case WATER: case FLYING: case BUG: case STEEL: mod *= 2.f; break;
          case ELECTRIC: case DRAGON: case GRASS: mod /= 2.f; break;
          case GROUND: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case ICE: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case GRASS: case GROUND: case FLYING: case DRAGON: mod *= 2.f; break;
          case FIRE: case WATER: case ICE: case STEEL: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case POISON: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case GRASS: case FAIRY: mod *= 2.f; break;
          case POISON: case GROUND: case ROCK: case GHOST: mod /= 2.f; break;
          case STEEL: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case GROUND: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case ELECTRIC: case FIRE: case ROCK: case POISON: case STEEL: mod *= 2.f; break;
          case BUG: case GRASS: mod /= 2.f; break;
          case FLYING: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case FLYING: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case GRASS: case FIGHTING: case BUG: mod *= 2.f; break;
          case ELECTRIC: case ROCK: case STEEL: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case PSYCHIC: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case FIGHTING: case POISON: mod *= 2.f; break;
          case PSYCHIC: case STEEL: case GRASS: mod /= 2.f; break;
          case DARK: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case BUG: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case GRASS: case PSYCHIC: case DARK: mod *= 2.f; break;
          case FIRE: case FIGHTING: case POISON: case FLYING: case ROCK: case STEEL: case FAIRY: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case ROCK: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case FIRE: case ICE: case BUG: case FLYING: mod *= 2.f; break;
          case FIGHTING: case GROUND: case STEEL: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case FIGHTING: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case NORMAL: case ICE: case ROCK: case DARK: case STEEL: mod *= 2.f; break;
          case PSYCHIC: case FLYING: case POISON: case BUG: case FAIRY: mod /= 2.f; break;
          case GHOST: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case GHOST: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case PSYCHIC: case GHOST: mod *= 2.f; break;
          case DARK: mod /= 2.f; break;
          case NORMAL: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case DRAGON: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case DRAGON: mod *= 2.f; break;
          case STEEL: mod /= 2.f; break;
          case FAIRY: mod = 0.00f; break;
          default: break;
        }
      } break;
    } case DARK: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case PSYCHIC: case GHOST: mod *= 2.f; break;
          case FIGHTING: case DARK: case FAIRY: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case STEEL: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case ROCK: case ICE: case FAIRY: mod *= 2.f; break;
          case ELECTRIC: case STEEL: case FIRE: case WATER: mod /= 2.f; break;
          default: break;
        }
      } break;
    } case FAIRY: {
      for (i = 0; i < 2; ++i) {
        switch (dp.type[i]) {
          case FIGHTING: case DRAGON: case DARK: mod *= 2.f; break;
          case FIRE: case POISON: case STEEL: mod /= 2.f; break;
          default: break;
        }
      } break;
    } default: break;
  }
  if (mod >= 2.00f) printf("it's super effective!\n");
  else if (mod <= 0.50f) printf("It's not very effective...\n");
  else if (mod <= 0.00f) printf("Target is immune...\n");
  if (aMove.type == ap.type[0] || aMove.type == ap.type[1]) mod *= 1.50f; //STAB bonus
  if ((rand() % 100 + 1) <= 5) { printf("Critical Hit!\n"); mod *= 1.50f; }
  mod *= (rand() % 16 + 85) /100.f; //random num between 0.85 and 1.00
  return mod;
}

void printPokemon(Pokemon p) {
  char ptype1[9], ptype2[9], pgender[11], pshiny[4];
  switch (p.gender) {
    case 0: strcpy(pgender, "Male"); break;
    case 1: strcpy(pgender, "Female"); break;
    default: strcpy(pgender, "Genderless");
  }
  if (p.shiny == 0) strcpy(pshiny, "No");
  else strcpy(pshiny, "Yes");
  strcpy(ptype1, typeToString(p.type[0]));
  strcpy(ptype2, typeToString(p.type[1]));
  printf("*************\nName: %s\nDescription: %s\nLevel: %d\nHappiness: %d\nGender: %s\n"
         "Shiny: %s\nType 1: %s\nType 2: %s\nItem: %s\nAbility: %s\n"
         "Moves:\t\t\t\tType\t\tPwr\tAcc\tPP\tDesc\nMove 1: %s\t%s\t%d\t%d\t%d\n"
         "Move 2: %s\t%s\t%d\t%d\t%d\nMove 3: %s\t%s\t%d\t%d\t%d\nMove 4: %s\t%s\t%d\t%d\t%d\n"
         "HP: %d\nAttack: %d\nDefense: %d\n"
         "Sp Atk: %d\nSp Def: %d\nSpeed: %d\nNature: %s\n*************\n\n",
         p.name, p.desc, p.level, p.happiness, pgender, pshiny, ptype1, ptype2, p.item.name, p.ability.name,
         p.move[0].name, typeToString(p.move[0].type), p.move[0].power, p.move[0].acc, p.move[0].pp, 
         p.move[1].name, typeToString(p.move[1].type), p.move[1].power, p.move[1].acc, p.move[1].pp,
         p.move[2].name, typeToString(p.move[2].type), p.move[2].power, p.move[2].acc, p.move[2].pp,
         p.move[3].name, typeToString(p.move[3].type), p.move[3].power, p.move[3].acc, p.move[3].pp,
         p.stats.hp, p.stats.atk, p.stats.def, p.stats.spa, p.stats.spd,
         p.stats.spe, p.nature.name);
}

unsigned short damageCalculator(Pokemon ap, Move aMove, Pokemon dp, float mod) {
  unsigned int level = ap.level, power = aMove.power;
  float atk, def;
  if (aMove.movecat == SPECIAL) {
    atk = (float)ap.stats.spa;
    def = (float)dp.stats.spd;
  } else {
    atk = (float)ap.stats.atk;
    def = (float)ap.stats.def;
  }
  if (power == 0) return (unsigned short)0;
  unsigned int result = (unsigned int)((((((2 * level) / 5 + 2) * power * ((atk / def))) / 50) + 2) * mod);
  return (unsigned short)result;
}

int testAllPokemon() { //make a big old stack of pokes and test all their attacks against each other On^2
  srand((unsigned int)time(0));
  const char * pStack[] = {"Bulbasaur", "Venusaur", "Charizard", "Blastoise", "Butterfree", "Beedrill", "Pidgeot",
    "Raticate", "Fearow", "Arbok", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Oddish", "Vileplume",
    "Parasect", "Venomoth", "Dugtrio", "Persian", "Golduck", "Primeape", "Arcanine", "Poliwrath", "Alakazam", "Machamp",
    "Victreebel", "Tentacruel", "Golem", "Rapidash", "Slowbro", "Magneton", "Farfetch'd", "Dodrio", "Dewgong", "Muk", "Cloyster",
    "Gengar", "Hypno", "Kingler", "Electrode", "Exeggcutor", "Cubone", "Marowak", "Hitmonlee", "Hitmonchan", "Weezing", "Rhydon",
    "Chansey", "Tangela", "Kangaskhan", "Seadra", "Seaking", "Starmie", "Mr. Mime", "Scyther", "Jynx", "Electabuzz", "Magmar",
    "Pinsir", "Tauros", "Gyarados", "Lapras", "Ditto", "Eevee", "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omastar", "Kabutops",
    "Aerodactyl", "Snorlax", "Articuno", "Zapdos", "Moltres", "Dragonite", "Mewtwo", "Mew",
    "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn",
    "Togetic", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Aipom",
    "Sunflora", "Yanma", "Quagsire", "Espeon", "Umbreon", "Murkrow", "Slowking", "Misdreavus", "Unown", "Wobbuffet", "Girafarig",
    "Forretress", "Dunsparce", "Gligar", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Sneasel", "Ursaring",
    "Magcargo", "Piloswine", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Porygon2",
    "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Raikou", "Entei", "Suicune", "Tyranitar", "Lugia", "Ho-oh", "Celebi"};
  Pokemon* pokemonbank = (Pokemon *)malloc(sizeof(Pokemon) * DEX_SIZE);
  int i, j, k;
  for (i = 0; i < DEX_SIZE && pokemonbank; ++i) {
    pokemonbank[i] = makePokemon(pStack[i]);
    printPokemon(*pokemonbank);
  }
  for (i = 0; i < DEX_SIZE && pokemonbank; ++i) {
    for (j = 0; j < DEX_SIZE; ++j) {
      for (k = 0; k < 4; ++k) {
        float mod = modCalculator(pokemonbank[i].move[k], pokemonbank[i], pokemonbank[j]);
        unsigned short dmg = damageCalculator(pokemonbank[i], pokemonbank[i].move[k],
            pokemonbank[j], mod); 
        short remhp = pokemonbank[j].stats.hp - dmg; //this might be negative! take note
        float losspercent = (dmg / (float)pokemonbank[j].stats.hp)*100.f;
        printf("%s's %s did %d damage to %s, (%.2f%%), (rem hp: %d)\n", pStack[i],
          pokemonbank[i].move[k].name, dmg, pStack[j], losspercent, remhp);
      }
    }
  }
  free(pokemonbank);
  return 0;
}

int buildTeam() {
  int i;
  char userIn[MAX_NAME_LENGTH];
  fgets(userIn, MAX_NAME_LENGTH, stdin); //clear buffer
  Pokemon team[6];
  for (i=1; i <=6; ++i) {
    printf("Please enter Pokemon in slot %d:\n", i);
    fgets(userIn, MAX_NAME_LENGTH, stdin);
    userIn[strcspn(userIn, "\n")] = '\0'; //get rid of newline added by fgets
    for (char * p = userIn; *p; ++p) *p = tolower(*p); //lowercase the whole string with this pointer
    userIn[0] = toupper(userIn[0]); //force capitalize first letter
    team[i-1] = makePokemon(userIn); //make the pokemon with its formatted name and pray
    printPokemon(team[i-1]);
  }
  printf("All done making the team!\n");
  return 0;
}

int displayDex() {
  unsigned int i;
  const char pStack[DEX_SIZE][MAX_NAME_LENGTH] = {"Bulbasaur", "Venusaur", "Charizard", "Blastoise", "Butterfree", "Beedrill", "Pidgeot",
    "Raticate", "Fearow", "Arbok", "Raichu", "Sandslash", "Nidoqueen", "Nidoking", "Clefable", "Ninetales", "Wigglytuff", "Oddish", "Vileplume",
    "Parasect", "Venomoth", "Dugtrio", "Persian", "Golduck", "Primeape", "Arcanine", "Poliwrath", "Alakazam", "Machamp",
    "Victreebel", "Tentacruel", "Golem", "Rapidash", "Slowbro", "Magneton", "Farfetch'd", "Dodrio", "Dewgong", "Muk", "Cloyster",
    "Gengar", "Hypno", "Kingler", "Electrode", "Exeggcutor", "Cubone", "Marowak", "Hitmonlee", "Hitmonchan", "Weezing", "Rhydon",
    "Chansey", "Tangela", "Kangaskhan", "Seadra", "Seaking", "Starmie", "Mr. Mime", "Scyther", "Jynx", "Electabuzz", "Magmar",
    "Pinsir", "Tauros", "Gyarados", "Lapras", "Ditto", "Eevee", "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omastar", "Kabutops",
    "Aerodactyl", "Snorlax", "Articuno", "Zapdos", "Moltres", "Dragonite", "Mewtwo", "Mew",
    "Meganium", "Typhlosion", "Feraligatr", "Furret", "Noctowl", "Ledian", "Ariados", "Crobat", "Lanturn",
    "Togetic", "Xatu", "Ampharos", "Bellossom", "Azumarill", "Sudowoodo", "Politoed", "Jumpluff", "Aipom",
    "Sunflora", "Yanma", "Quagsire", "Espeon", "Umbreon", "Murkrow", "Slowking", "Misdreavus", "Unown", "Wobbuffet", "Girafarig",
    "Forretress", "Dunsparce", "Gligar", "Steelix", "Granbull", "Qwilfish", "Scizor", "Shuckle", "Heracross", "Sneasel", "Ursaring",
    "Magcargo", "Piloswine", "Corsola", "Octillery", "Delibird", "Mantine", "Skarmory", "Houndoom", "Kingdra", "Donphan", "Porygon2",
    "Stantler", "Smeargle", "Hitmontop", "Miltank", "Blissey", "Raikou", "Entei", "Suicune", "Tyranitar", "Lugia", "Ho-oh", "Celebi"};
  for (i = 0; i < DEX_SIZE; ++i)  printPokemon(makePokemon(pStack[i]));
  return 0;
}

int playPokemonMatch(/*Pokemon team1[], Pokemon team2[]*/) {
  int i, k;
  char userIn[MAX_NAME_LENGTH];
  //fgets(userIn, MAX_NAME_LENGTH, stdin); //clear buffer
  //Pokemon * matchup = (Pokemon *)malloc(sizeof(Pokemon) * 2);
  Pokemon matchup[2];
  for (i=1; i <=2; ++i) {
    printf("Please enter Pokemon in slot %d:\n", i);
    fgets(userIn, MAX_NAME_LENGTH, stdin);
    userIn[strcspn(userIn, "\n")] = '\0'; //get rid of newline added by fgets
    for (char * p = userIn; *p; ++p) *p = tolower(*p); //lowercase the whole string with this pointer
    userIn[0] = toupper(userIn[0]); //force capitalize first letter
    matchup[i-1] = makePokemon(userIn); //make the pokemon with its formatted name and pray
    printPokemon(matchup[i-1]);
  }
  float pokeAloss = 0.0f, pokeBloss = 0.0f;
  for (k = 0; k < 4; ++k) {
    float mod = modCalculator(matchup[0].move[k], matchup[0], matchup[1]);
    unsigned short dmg = damageCalculator(matchup[0], matchup[0].move[k],
        matchup[1], mod); 
    short remhp = matchup[1].stats.hp - dmg; //this might be negative! take note
    float losspercent = (dmg / (float)matchup[1].stats.hp)*100.f;
    printf("%s's %s did %d damage to %s, (%.2f%%), (rem hp: %d)\n", matchup[0].name,
      matchup[0].move[k].name, dmg, matchup[1].name, losspercent, remhp);
    pokeAloss += losspercent;
    //reuse it for defending pokemon counterattack
    mod = modCalculator(matchup[1].move[k], matchup[1], matchup[0]);
    dmg = damageCalculator(matchup[1], matchup[1].move[k],
        matchup[0], mod); 
    remhp = matchup[0].stats.hp - dmg; //this might be negative! take note
    losspercent = (dmg / (float)matchup[0].stats.hp)*100.f;
    printf("%s's %s did %d damage to %s, (%.2f%%), (rem hp: %d)\n", matchup[1].name,
      matchup[1].move[k].name, dmg, matchup[0].name, losspercent, remhp);
    pokeBloss += losspercent;
  }
  if (pokeAloss > pokeBloss)
    printf("%s wins matchup by %.2f%%\n", matchup[0].name, (double)pokeAloss - pokeBloss);
  else
    printf("%s wins the matchup by %.2f%%\n", matchup[1].name, (double)pokeBloss - pokeAloss);
  return 0;
}

int mainPokemonMenu() {
  int statusCode = 0;
  bool reloop = 0;
  do {
    printf("Please enter what you mode you'd like to do:\nTest\nPlay\nBuild\nDex\nQuit\n:");
    char userIn[USER_INPUT_LIMIT];
    char * p = userIn;
    fgets(userIn, USER_INPUT_LIMIT, stdin);
    userIn[strcspn(userIn, "\n")] = '\0'; //get rid of newline added by fgets
    //printf("userIn: %s\n", userIn);
    for (; *p; ++p) *p = tolower(*p); //lowercase the whole string with this pointer
    userIn[0] = toupper(userIn[0]); //force capitalize first letter
    if (strcmp(userIn, "Test") == 0) {
      statusCode = testAllPokemon();
    } else if (strcmp(userIn, "Play") == 0) {
      statusCode = playPokemonMatch();
    } else if (strcmp(userIn, "Build") == 0) {
      statusCode = buildTeam();
    } else if (strcmp(userIn, "Dex") == 0) {
      statusCode = displayDex();
    } else if (strcmp(userIn, "Quit") == 0) {
      printf("Quiting...");
      return statusCode;
    } else {
      printf("User input was unrecognized as a command.\n");
      return 1;
    }
    printf("Would you like to continue?\n");
    fgets(userIn, USER_INPUT_LIMIT, stdin);
    userIn[strcspn(userIn, "\n")] = '\0'; //get rid of newline added by fgets
    //printf("userIn: %s\n", userIn);
    for (p = userIn; *p; ++p) *p = tolower(*p); //lowercase the whole string with this pointer
    userIn[0] = toupper(userIn[0]); //force capitalize first letter
    if (strcmp(userIn, "Yes") == 0) {
      reloop = 1;
    } else if (strcmp(userIn, "No") == 0) {
      printf("Okay, Quiting...");
      return statusCode;
    } else {
      printf("User input was unrecognized as a command.\n");
      return 1;
    }
  } while (reloop == 1);
  return 0;
}
