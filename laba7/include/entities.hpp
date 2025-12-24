#pragma once
#include <string>
#include <iostream>

enum NPCType {
    DragonType,
    BullType,
    ToadType,
    Unknown
};

std::string typeToString(NPCType t);

std::istream& operator>>(std::istream& is, NPCType& t);