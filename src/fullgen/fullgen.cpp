#include <iostream>
#include <chrono>
#include <cstring>

static_assert(std::numeric_limits<double>::is_iec559, "This code requires IEEE-754 doubles");

#define Random uint64_t
#define RANDOM_MULTIPLIER 0x5DEECE66DULL
#define RANDOM_ADDEND 0xBULL
#define RANDOM_MASK ((1ULL << 48u) - 1)
#define RANDOM_SCALE 0x1.0p-53
#define get_random(seed) ((Random)((seed ^ RANDOM_MULTIPLIER) & RANDOM_MASK))


static inline int32_t random_next(Random *random, int bits) {
    *random = (*random * RANDOM_MULTIPLIER + RANDOM_ADDEND) & RANDOM_MASK;
    return (int32_t) (*random >> (48u - bits));
}

static inline int32_t random_next_int(Random *random, const uint16_t bound) {
    int32_t r = random_next(random, 31);
    const uint16_t m = bound - 1u;
    if ((bound & m) == 0) {
        r = (int32_t) ((bound * (uint64_t) r) >> 31u);
    } else {
        for (int32_t u = r;
             u - (r = u % bound) + m < 0;
             u = random_next(random, 31));
    }
    return r;
}

static inline double next_double(Random *random) {
    return (double) ((((uint64_t) ((uint32_t) random_next(random, 26)) << 27u)) + random_next(random, 27)) * RANDOM_SCALE;
}

static inline uint64_t random_next_long(Random *random) {
    return (((uint64_t) random_next(random, 32)) << 32u) + (int32_t) random_next(random, 32);
}

static inline void advance2(Random *random) {
    *random = (*random * 0xBB20B4600A69LLU + 0x40942DE6BALLU) & RANDOM_MASK;
}

/* Display stuff */
enum Biomes {
    Rainforest,
    Swampland,
    Seasonal_forest,
    Forest,
    Savanna,
    Shrubland,
    Taiga,
    Desert,
    Plains,
    IceDesert,
    Tundra,
};

const char *biomesNames[] = {"Rainforest", "Swampland", "Seasonal Forest", "Forest", "Savanna", "Shrubland", "Taiga", "Desert", "Plains", "IceDesert", "Tundra"};
// @formatter:off
const Biomes biomesTable[4096]={Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Desert, Desert, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Desert, Desert, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Savanna, Savanna, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Plains, Plains, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Shrubland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Seasonal_forest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Seasonal_forest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Forest, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Tundra, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Taiga, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Swampland, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Forest, Rainforest, Rainforest,};
// @formatter:on

struct BiomeResult {
    double *temperature;
    double *humidity;
    Biomes *biomes;
};
/* End of Display stuff */

/* constant for simplex noise*/
#define F2 0.3660254037844386
#define G2 0.21132486540518713

int grad2[12][2] = {{1,  1,},
                    {-1, 1,},
                    {1,  -1,},
                    {-1, -1,},
                    {1,  0,},
                    {-1, 0,},
                    {1,  0,},
                    {-1, 0,},
                    {0,  1,},
                    {0,  -1,},
                    {0,  1,},
                    {0,  -1,}};

/* End of constant for simplex noise*/



/* simplex noise result is in buffer */
static inline void getSimplexNoise(double *buffer, double chunkX, double chunkZ, int sizeX, int sizeZ, double offsetX, double offsetZ, double ampFactor, uint8_t nbOctaves, Random *random) {
    offsetX /= 1.5;
    offsetZ /= 1.5;
    // cache should be created by the caller
    memset(buffer, 0, sizeof(double) * sizeX * sizeZ);

    double octaveDiminution = 1.0;
    double octaveAmplification = 1.0;
    double xo;
    double yo;
    uint8_t permutations[256];
    for (uint8_t j = 0; j < nbOctaves; ++j) {
        xo = next_double(random) * 256.0;
        yo = next_double(random) * 256.0;
        advance2(random);
        uint8_t w = 0;
        do {
            permutations[w] = w;
        } while (w++ != 255);
        uint8_t index = 0;
        do {
            uint32_t randomIndex = random_next_int(random, 256u - index) + index;
            if (randomIndex != index) {
                // swap
                permutations[index] ^= permutations[randomIndex];
                permutations[randomIndex] ^= permutations[index];
                permutations[index] ^= permutations[randomIndex];
            }
        } while (index++ != 255);
        int k = 0;
        for (int X = 0; X < sizeX; X++) {
            double XCoords = (chunkX + (double) X) * offsetX * octaveAmplification + xo;
            for (int Z = 0; Z < sizeZ; Z++) {
                double ZCoords = (chunkZ + (double) Z) * offsetZ * octaveAmplification + yo;
                // Skew the input space to determine which simplex cell we're in
                double hairyFactor = (XCoords + ZCoords) * F2;
                auto tempX = static_cast<int32_t>(XCoords + hairyFactor);
                auto tempZ = static_cast<int32_t>(ZCoords + hairyFactor);
                int32_t xHairy = (XCoords + hairyFactor < tempX) ? (tempX - 1) : (tempX);
                int32_t zHairy = (ZCoords + hairyFactor < tempZ) ? (tempZ - 1) : (tempZ);
                double d11 = (double) (xHairy + zHairy) * G2;
                double X0 = (double) xHairy - d11; // Unskew the cell origin back to (x,y) space
                double Y0 = (double) zHairy - d11;
                double x0 = XCoords - X0; // The x,y distances from the cell origin
                double y0 = ZCoords - Y0;
                // For the 2D case, the simplex shape is an equilateral triangle.
                // Determine which simplex we are in.
                int offsetSecondCornerX, offsetSecondCornerZ; // Offsets for second (middle) corner of simplex in (i,j) coords

                if (x0 > y0) {  // lower triangle, XY order: (0,0)->(1,0)->(1,1)
                    offsetSecondCornerX = 1;
                    offsetSecondCornerZ = 0;
                } else { // upper triangle, YX order: (0,0)->(0,1)->(1,1)
                    offsetSecondCornerX = 0;
                    offsetSecondCornerZ = 1;
                }

                double x1 = (x0 - (double) offsetSecondCornerX) + G2; // Offsets for middle corner in (x,y) unskewed coords
                double y1 = (y0 - (double) offsetSecondCornerZ) + G2;
                double x2 = (x0 - 1.0) + 2.0 * G2; // Offsets for last corner in (x,y) unskewed coords
                double y2 = (y0 - 1.0) + 2.0 * G2;

                // Work out the hashed gradient indices of the three simplex corners
                uint8_t ii = (uint32_t) xHairy & 0xffu;
                uint8_t jj = (uint32_t) zHairy & 0xffu;
                uint8_t gi0 = permutations[(uint16_t) (ii + permutations[jj]) & 0xffu] % 12u;
                uint8_t gi1 = permutations[(uint16_t)(ii + offsetSecondCornerX + permutations[(uint16_t) (jj + offsetSecondCornerZ) & 0xffu])& 0xffu] % 12u;
                uint8_t gi2 = permutations[(uint16_t)(ii + 1 + permutations[(uint16_t)(jj + 1)& 0xffu])& 0xffu] % 12u;

                // Calculate the contribution from the three corners
                double t0 = 0.5 - x0 * x0 - y0 * y0;
                double n0;
                if (t0 < 0.0) {
                    n0 = 0.0;
                } else {
                    t0 *= t0;
                    n0 = t0 * t0 * ((double) grad2[gi0][0] * x0 + (double) grad2[gi0][1] * y0);  // (x,y) of grad2 used for 2D gradient
                }
                double t1 = 0.5 - x1 * x1 - y1 * y1;
                double n1;
                if (t1 < 0.0) {
                    n1 = 0.0;
                } else {
                    t1 *= t1;
                    n1 = t1 * t1 * ((double) grad2[gi1][0] * x1 + (double) grad2[gi1][1] * y1);
                }
                double t2 = 0.5 - x2 * x2 - y2 * y2;
                double n2;
                if (t2 < 0.0) {
                    n2 = 0.0;
                } else {
                    t2 *= t2;
                    n2 = t2 * t2 * ((double) grad2[gi2][0] * x2 + (double) grad2[gi2][1] * y2);
                }
                // Add contributions from each corner to get the final noise value.
                // The result is scaled to return values in the interval [-1,1].
                buffer[k] = buffer[k] + 70.0 * (n0 + n1 + n2) * 0.55000000000000004 / octaveDiminution;
                k++;

            }

        }
        octaveAmplification *= ampFactor;
        octaveDiminution *= 0.5;
    }

}

/* End of simplex noise result is in buffer */


static inline BiomeResult *getBiomes(uint64_t worldSeed, int posX, int posZ, int sizeX, int sizeZ) {
    auto *biomes = new Biomes[16 * 16];
    auto *biomeResult = new BiomeResult;
    auto *temperature = new double[sizeX * sizeZ];
    auto *humidity = new double[sizeX * sizeZ];
    auto *precipitation = new double[sizeX * sizeZ];
    Random worldRandom;
    worldRandom = get_random(worldSeed * 9871L);
    getSimplexNoise(temperature, posX, posZ, sizeX, sizeZ, 0.02500000037252903, 0.02500000037252903, 0.25, 4, &worldRandom);
    worldRandom = get_random(worldSeed * 39811L);
    getSimplexNoise(humidity, posX, posZ, sizeX, sizeZ, 0.05000000074505806, 0.05000000074505806, 0.33333333333333331, 4, &worldRandom);
    worldRandom = get_random(worldSeed * 0x84a59L);
    getSimplexNoise(precipitation, posX, posZ, sizeX, sizeZ, 0.25, 0.25, 0.58823529411764708, 2, &worldRandom);
    int index = 0;
    for (int X = 0; X < sizeX; X++) {
        for (int Z = 0; Z < sizeZ; Z++) {
            double preci = precipitation[index] * 1.1000000000000001 + 0.5;
            double temp = (temperature[index] * 0.14999999999999999 + 0.69999999999999996) * (1.0 - 0.01) + preci * 0.01;
            temp = 1.0 - (1.0 - temp) * (1.0 - temp);
            if (temp < 0.0) {
                temp = 0.0;
            }
            if (temp > 1.0) {
                temp = 1.0;
            }
            double humi = (humidity[index] * 0.14999999999999999 + 0.5) * (1.0 - 0.002) + preci * 0.002;
            if (humi < 0.0) {
                humi = 0.0;
            }
            if (humi > 1.0) {
                humi = 1.0;
            }
            temperature[index] = temp;
            humidity[index] = humi;
            biomes[index] = biomesTable[(int) (temp * 63) + (int) (humi * 63) * 64];
            index++;
        }
    }
    delete[] precipitation;
    biomeResult->biomes = biomes;
    biomeResult->temperature = temperature;
    biomeResult->humidity = humidity;
    return biomeResult;
}

void delete_biome_result(BiomeResult *biomeResult) {
    delete[] biomeResult->biomes;
    delete[] biomeResult->temperature;
    delete[] biomeResult->humidity;
    delete biomeResult;
}

BiomeResult *BiomeWrapper(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ) {
    auto *biomes = getBiomes(worldSeed, chunkX * 16, chunkZ * 16, 16, 16);
    return biomes;
}

static inline void printBiomes(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ) {
    BiomeResult *biomeResult = BiomeWrapper(worldSeed, chunkX, chunkZ);
    double *temp = biomeResult->temperature;
    Biomes *biomes = biomeResult->biomes;
    for (int i = 0; i < 16 * 16; ++i) {
        //std::cout << temp[i] << " ";
        std::cout << biomesNames[biomes[i]] << " ";
    }
    std::cout << std::endl;
    delete_biome_result(biomeResult);
}

struct PermutationTable {
    double xo;
    double yo;
    double zo; // this actually never used in fixed noise aka 2d noise;)
    uint8_t permutations[512];
};

static inline void initOctaves(PermutationTable octaves[], Random *random, int nbOctaves) {
    for (int i = 0; i < nbOctaves; ++i) {
        octaves[i].xo = next_double(random) * 256.0;
        octaves[i].yo = next_double(random) * 256.0;
        octaves[i].zo = next_double(random) * 256.0;
        uint8_t *permutations = octaves[i].permutations;
        uint8_t j=0;
        do{
            permutations[j] = j;
        }while(j++!=255);
        uint8_t index = 0;
        do {
            uint32_t randomIndex = random_next_int(random, 256u - index) + index;
            if (randomIndex != index) {
                // swap
                permutations[index] ^= permutations[randomIndex];
                permutations[randomIndex] ^= permutations[index];
                permutations[index] ^= permutations[randomIndex];
            }
            permutations[index + 256] = permutations[index];
        }while(index++!=255);
    }
}



struct TerrainNoises {
    PermutationTable minLimit[16];
    PermutationTable maxLimit[16];
    PermutationTable mainLimit[8];
    PermutationTable shoresBottomComposition[4];
    PermutationTable surfaceElevation[4];
    PermutationTable scale[10];
    PermutationTable depth[16];
    PermutationTable forest[8];
};
enum blocks {
    AIR,
    STONE,
    GRASS,
    DIRT,
    BEDROCK,
    MOVING_WATER,
    SAND,
    GRAVEL,
    ICE,
};

struct TerrainResult {
    BiomeResult *biomeResult;
    uint8_t *chunkCache;
    uint8_t *chunkHeights;
};

static_assert(std::numeric_limits<double>::is_iec559, "This code requires IEEE-754 doubles");

static inline double lerp(double x, double a, double b) {
    return a + x * (b - a);
}

static inline double grad(uint8_t hash, double x, double y, double z) {
    switch (hash & 0xFu) {
        case 0x0:
            return x + y;
        case 0x1:
            return -x + y;
        case 0x2:
            return x - y;
        case 0x3:
            return -x - y;
        case 0x4:
            return x + z;
        case 0x5:
            return -x + z;
        case 0x6:
            return x - z;
        case 0x7:
            return -x - z;
        case 0x8:
            return y + z;
        case 0x9:
            return -y + z;
        case 0xA:
            return y - z;
        case 0xB:
            return -y - z;
        case 0xC:
            return y + x;
        case 0xD:
            return -y + z;
        case 0xE:
            return y - x;
        case 0xF:
            return -y - z;
        default:
            return 0; // never happens
    }
}

static inline double grad2D(uint8_t hash, double x, double z) {
    return grad(hash, x, 0, z);
}



static inline void generateFixedPermutations(double **buffer, double x, double z, int sizeX, int sizeZ, double noiseFactorX,double noiseFactorZ, double octaveSize, PermutationTable permutationTable) {
    int index = 0;
    uint8_t *permutations = permutationTable.permutations;
    double octaveWidth = 1.0 / octaveSize;
    for (int X = 0; X < sizeX; X++) {
        double xCoord = (x + (double) X) * noiseFactorX + permutationTable.xo;
        int clampedXCoord = (int) xCoord;
        if (xCoord < (double) clampedXCoord) {
            clampedXCoord--;
        }
        auto xBottoms = (int32_t) ((uint32_t) clampedXCoord & 0xffu);
        xCoord -= clampedXCoord;
        double fadeX = xCoord * xCoord * xCoord * (xCoord * (xCoord * 6.0 - 15.0) + 10.0);
        for (int Z = 0; Z < sizeZ; Z++) {
            double zCoord = (z + (double) Z) * noiseFactorZ + permutationTable.zo;
            int clampedZCoord = (int) zCoord;
            if (zCoord < (double) clampedZCoord) {
                clampedZCoord--;
            }
            auto zBottoms = (int32_t) ((uint32_t) clampedZCoord & 0xffu);
            zCoord -= clampedZCoord;
            double fadeZ = zCoord * zCoord * zCoord * (zCoord * (zCoord * 6.0 - 15.0) + 10.0);
            int hashXZ = permutations[permutations[xBottoms]] + zBottoms;
            int hashOffXZ = permutations[permutations[xBottoms + 1]] + zBottoms;
            double x1 = lerp(fadeX, grad2D(permutations[hashXZ], xCoord, zCoord),
                             grad2D(permutations[hashOffXZ], xCoord - 1.0, zCoord));
            double x2 = lerp(fadeX, grad2D(permutations[hashXZ + 1], xCoord, zCoord - 1.0),
                             grad2D(permutations[hashOffXZ + 1], xCoord - 1.0, zCoord - 1.0));
            double y1 = lerp(fadeZ, x1, x2);
            (*buffer)[index] = (*buffer)[index] + y1 * octaveWidth;
            index++;
        }
    }
}

static inline void generateNormalPermutations(double **buffer, double x, double y, double z, int sizeX, int sizeY, int sizeZ,double noiseFactorX, double noiseFactorY, double noiseFactorZ, double octaveSize,PermutationTable permutationTable) {
    uint8_t *permutations = permutationTable.permutations;
    double octaveWidth = 1.0 / octaveSize;
    int32_t i2 = -1;
    double x1 = 0.0;
    double x2 = 0.0;
    double xx1 = 0.0;
    double xx2 = 0.0;
    double t;
    double w;
    int columnIndex = 0;
    for (int X = 0; X < sizeX; X++) {
        double xCoord = (x + (double) X) * noiseFactorX + permutationTable.xo;
        auto clampedXcoord = (int32_t) xCoord;
        if (xCoord < (double) clampedXcoord) {
            clampedXcoord--;
        }
        auto xBottoms = (uint8_t) ((uint32_t) clampedXcoord & 0xffu);
        xCoord -= clampedXcoord;
        t = xCoord * 6 - 15;
        w = (xCoord * t + 10);
        double fadeX = xCoord * xCoord * xCoord * w;
        for (int Z = 0; Z < sizeZ; Z++) {
            double zCoord = (z + (double) Z) * noiseFactorZ + permutationTable.zo;
            auto clampedZCoord = (int32_t) zCoord;
            if (zCoord < (double) clampedZCoord) {
                clampedZCoord--;
            }
            auto zBottoms = (uint8_t) ((uint32_t) clampedZCoord & 0xffu);
            zCoord -= clampedZCoord;
            t = zCoord * 6 - 15;
            w = (zCoord * t + 10);
            double fadeZ = zCoord * zCoord * zCoord * w;
            for (int Y = 0; Y < sizeY; Y++) {
                double yCoords = (y + (double) Y) * noiseFactorY + permutationTable.yo;
                auto clampedYCoords = (int32_t) yCoords;
                if (yCoords < (double) clampedYCoords) {
                    clampedYCoords--;
                }
                auto yBottoms = (uint8_t) ((uint32_t) clampedYCoords & 0xffu);
                yCoords -= clampedYCoords;
                t = yCoords * 6 - 15;
                w = yCoords * t + 10;
                double fadeY = yCoords * yCoords * yCoords * w;
                // ZCoord

                if (Y == 0 || yBottoms !=
                              i2) { // this is wrong on so many levels, same ybottoms doesnt mean x and z were the same...
                    i2 = yBottoms;
                    uint16_t k2 = permutations[permutations[xBottoms] + yBottoms] + zBottoms;
                    uint16_t l2 = permutations[permutations[xBottoms] + yBottoms + 1] + zBottoms;
                    uint16_t k3 = permutations[permutations[xBottoms + 1] + yBottoms] + zBottoms;
                    uint16_t l3 = permutations[permutations[xBottoms + 1] + yBottoms + 1] + zBottoms;
                    x1 = lerp(fadeX, grad(permutations[k2], xCoord, yCoords, zCoord),grad(permutations[k3], xCoord - 1.0, yCoords, zCoord));
                    x2 = lerp(fadeX, grad(permutations[l2], xCoord, yCoords - 1.0, zCoord),grad(permutations[l3], xCoord - 1.0, yCoords - 1.0, zCoord));
                    xx1 = lerp(fadeX, grad(permutations[k2 + 1], xCoord, yCoords, zCoord - 1.0),grad(permutations[k3 + 1], xCoord - 1.0, yCoords, zCoord - 1.0));
                    xx2 = lerp(fadeX, grad(permutations[l2 + 1], xCoord, yCoords - 1.0, zCoord - 1.0),grad(permutations[l3 + 1], xCoord - 1.0, yCoords - 1.0, zCoord - 1.0));
                }
                double y1 = lerp(fadeY, x1, x2);
                double y2 = lerp(fadeY, xx1, xx2);
                (*buffer)[columnIndex] = (*buffer)[columnIndex] + lerp(fadeZ, y1, y2) * octaveWidth;
                columnIndex++;
            }
        }
    }
}


static inline void generateNoise(double *buffer, double chunkX, double chunkY, double chunkZ, int sizeX, int sizeY, int sizeZ,double offsetX, double offsetY, double offsetZ, PermutationTable *permutationTable, int nbOctaves,int type) {
    memset(buffer, 0, sizeof(double) * sizeX * sizeZ * sizeY);
    double octavesFactor = 1.0;
    for (int octave = 0; octave < nbOctaves; octave++) {
        // optimized if 0
        generateNormalPermutations(&buffer, chunkX, chunkY, chunkZ, sizeX, sizeY, sizeZ, offsetX * octavesFactor,offsetY * octavesFactor, offsetZ * octavesFactor, octavesFactor,permutationTable[octave]);

        octavesFactor /= 2.0;
    }
}

static inline void generateFixedNoise(double *buffer, double chunkX, double chunkZ, int sizeX, int sizeZ, double offsetX, double offsetZ,PermutationTable *permutationTable, int nbOctaves) {
    memset(buffer, 0, sizeof(double) * sizeX * sizeZ);
    double octavesFactor = 1.0;
    for (int octave = 0; octave < nbOctaves; octave++) {
        generateFixedPermutations(&buffer, chunkX, chunkZ, sizeX, sizeZ, offsetX * octavesFactor,offsetZ * octavesFactor, octavesFactor, permutationTable[octave]);
        octavesFactor /= 2.0;
    }
}


static inline void fillNoiseColumn(double **NoiseColumn, int chunkX, int chunkZ, const double *temperature, const double *humidity,TerrainNoises terrainNoises) {

    double d = 684.41200000000003;
    double d1 = 684.41200000000003;
    auto *surfaceNoise = new double[5 * 5];
    auto *depthNoise = new double[5 * 5];
    generateFixedNoise(surfaceNoise, chunkX, chunkZ, 5, 5, 1.121, 1.121, terrainNoises.scale, 10);
    generateFixedNoise(depthNoise, chunkX, chunkZ, 5, 5, 200.0, 200.0, terrainNoises.depth, 16);

    auto *mainLimitPerlinNoise = new double[5 * 17 * 5];
    auto *minLimitPerlinNoise = new double[5 * 17 * 5];
    auto *maxLimitPerlinNoise = new double[5 * 17 * 5];
    // use optimized noise
    generateNoise(mainLimitPerlinNoise, chunkX, 0, chunkZ, 5, 17, 5, d / 80, d1 / 160, d / 80, terrainNoises.mainLimit,8, 0);
    generateNoise(minLimitPerlinNoise, chunkX, 0, chunkZ, 5, 17, 5, d, d1, d, terrainNoises.minLimit, 16, 0);
    generateNoise(maxLimitPerlinNoise, chunkX, 0, chunkZ, 5, 17, 5, d, d1, d, terrainNoises.maxLimit, 16, 0);
    int columnCounter = 0;
    int cellCounter = 0;
    for (int xCell = 0; xCell < 5; xCell++) {
        int X = xCell * 3 + 1; // 1 4 7 10 13
        for (int zCell = 0; zCell < 5; zCell++) {
            int Z = zCell * 3 + 1; // 1 4 7 10 13
            double aridityXZ = 1.0 - humidity[X * 16 + Z] * temperature[X * 16 + Z];
            aridityXZ *= aridityXZ;
            aridityXZ *= aridityXZ;
            aridityXZ = 1.0 - aridityXZ;  // 1-(1-X)*(1-X)*(1-X)*(1-X) with X=humidity*Temp
            double surface = (surfaceNoise[cellCounter] / 512.0 + 256.0 / 512.0) * aridityXZ;
            if (surface > 1.0) {
                surface = 1.0; // clamp
            }
            double depth = depthNoise[cellCounter] / 8000.0;
            if (depth < 0.0) {
                depth = -depth * 0.29999999999999999;
            }
            depth = depth * 3 - 2;
            if (depth < 0.0) {
                depth /= 2.0;
                if (depth < -1) {
                    depth = -1;
                }
                depth /= 1.3999999999999999;
                depth /= 2.0;
                surface = 0.0;
            } else {
                if (depth > 1.0) {
                    depth = 1.0;
                }
                depth /= 8.0;
            }
            if (surface < 0.0) {
                surface = 0.0;
            }
            surface += 0.5;
            depth = (depth * (double) 17) / 16.0;
            double depthColumn = (double) 17 / 2.0 + depth * 4.0;
            cellCounter++;
            for (int column = 9; column < 11; column++) { // we only care at pos 9 and 10 in the column so 2 times

                double limit;
                double columnPerSurface = (((double) column - depthColumn) * 12.0) / surface;
                if (columnPerSurface < 0.0) {
                    columnPerSurface *= 4.0;
                }
                double minLimit = minLimitPerlinNoise[columnCounter] / 512.0;
                double maxLimit = maxLimitPerlinNoise[columnCounter] / 512.0;
                double mainLimit = (mainLimitPerlinNoise[columnCounter] / 10.0 + 1.0) / 2.0;
                if (mainLimit < 0.0) {
                    limit = minLimit;
                } else if (mainLimit > 1.0) {
                    limit = maxLimit;
                } else {
                    limit = minLimit + (maxLimit - minLimit) * mainLimit; // interpolation
                }
                limit -= columnPerSurface;
                (*NoiseColumn)[columnCounter] = limit;
                columnCounter++;
            }

        }
    }
    delete[] surfaceNoise;
    delete[] depthNoise;
    delete[] mainLimitPerlinNoise;
    delete[] minLimitPerlinNoise;
    delete[] maxLimitPerlinNoise;
}

static inline void generateTerrain(int chunkX, int chunkZ, uint8_t **chunkCache, double *temperatures, double *humidity,TerrainNoises terrainNoises) {
    uint8_t seaLevel = 64;
    uint8_t quadrant = 4;
    uint8_t columnSize = 17;
    uint8_t cellsize = 5;
    double interpFirstOctave = 0.125;
    double interpSecondOctave = 0.25;
    double interpThirdOctave = 0.25;
    auto *NoiseColumn = new double[5 * 5 * 17];
    memset(NoiseColumn, 0, sizeof(double) * 5 * 5 * 17);
    fillNoiseColumn(&NoiseColumn, chunkX * quadrant, chunkZ * quadrant, temperatures, humidity, terrainNoises);
    for (uint8_t x = 0; x < quadrant; x++) {
        for (uint8_t z = 0; z < quadrant; z++) { ;
            for (uint8_t height = 0; height < 16; height++) {
                int off_0_0 = x * cellsize + z;
                int off_0_1 = x * cellsize + (z + 1);
                int off_1_0 = (x + 1) * cellsize + z;
                int off_1_1 = (x + 1) * cellsize + (z + 1);
                double firstNoise_0_0 = NoiseColumn[(off_0_0) * columnSize + (height)];
                double firstNoise_0_1 = NoiseColumn[(off_0_1) * columnSize + (height)];
                double firstNoise_1_0 = NoiseColumn[off_1_0 * columnSize + (height)];
                double firstNoise_1_1 = NoiseColumn[off_1_1 * columnSize + (height)];
                double stepFirstNoise_0_0 =(NoiseColumn[(off_0_0) * columnSize + (height + 1)] - firstNoise_0_0) * interpFirstOctave;
                double stepFirstNoise_0_1 =(NoiseColumn[(off_0_1) * columnSize + (height + 1)] - firstNoise_0_1) * interpFirstOctave;
                double stepFirstNoise_1_0 =(NoiseColumn[off_1_0 * columnSize + (height + 1)] - firstNoise_1_0) * interpFirstOctave;
                double stepFirstNoise_1_1 =(NoiseColumn[off_1_1 * columnSize + (height + 1)] - firstNoise_1_1) * interpFirstOctave;

                for (uint8_t heightOffset = 0; heightOffset < 8; heightOffset++) {
                    double secondNoise_0_0 = firstNoise_0_0;
                    double secondNoise_0_1 = firstNoise_0_1;
                    double stepSecondNoise_1_0 = (firstNoise_1_0 - firstNoise_0_0) * interpSecondOctave;
                    double stepSecondNoise_1_1 = (firstNoise_1_1 - firstNoise_0_1) * interpSecondOctave;
                    for (uint8_t xOffset = 0; xOffset < 4; xOffset++) {
                        uint8_t currentHeight = height * 8u + heightOffset; // max is 128
                        uint16_t index = (xOffset + x * 4u) << 11u | (z * 4u) << 7u | currentHeight;
                        double stoneLimit = secondNoise_0_0; // aka thirdNoise
                        double stepThirdNoise_0_1 = (secondNoise_0_1 - secondNoise_0_0) * interpThirdOctave;
                        for (int zOffset = 0; zOffset < 4; zOffset++) {
                            double temperature = temperatures[(x * 4 + xOffset) * 16 + (z * 4 + zOffset)];
                            int block = AIR;
                            if (currentHeight< seaLevel) {
                                if (temperature < 0.5 && currentHeight >= seaLevel - 1) { // ice on water
                                    block = ICE;
                                } else {
                                    block = MOVING_WATER;
                                }
                            }
                            if (stoneLimit > 0.0) { //3d perlin condition
                                block = STONE;
                            }
                            (*chunkCache)[index] = block;
                            index += 128;
                            stoneLimit += stepThirdNoise_0_1;
                        }

                        secondNoise_0_0 += stepSecondNoise_1_0;
                        secondNoise_0_1 += stepSecondNoise_1_1;
                    }

                    firstNoise_0_0 += stepFirstNoise_0_0;
                    firstNoise_0_1 += stepFirstNoise_0_1;
                    firstNoise_1_0 += stepFirstNoise_1_0;
                    firstNoise_1_1 += stepFirstNoise_1_1;
                }
            }
        }
    }
    delete[]NoiseColumn;
}


static inline void replaceBlockForBiomes(int chunkX, int chunkZ, uint8_t **chunkCache, Random *worldRandom, TerrainNoises terrainNoises) {
    uint8_t oceanLevel = 64;
    double noiseFactor = 0.03125;
    auto *sandFields = new double[16 * 16];
    auto *gravelField = new double[16 * 16];
    auto *heightField = new double[16 * 16];
    generateNoise(sandFields, chunkX * 16, chunkZ * 16, 0.0, 16, 16, 1, noiseFactor, noiseFactor, 1.0,terrainNoises.shoresBottomComposition, 4, 1);
    // beware this error in alpha ;)
    generateFixedNoise(gravelField, chunkZ * 16, chunkX * 16, 16, 16, noiseFactor, noiseFactor,terrainNoises.shoresBottomComposition, 4);
    generateNoise(heightField, chunkX * 16, chunkZ * 16, 0.0, 16, 16, 1, noiseFactor * 2.0, noiseFactor * 2.0,noiseFactor * 2.0, terrainNoises.surfaceElevation, 4, 1);

    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            bool sandy = sandFields[x + z * 16] + next_double(worldRandom) * 0.20000000000000001 > 0.0;
            bool gravelly = gravelField[x + z * 16] + next_double(worldRandom) * 0.20000000000000001 > 3;
            int elevation = (int) (heightField[x + z * 16] / 3.0 + 3.0 + next_double(worldRandom) * 0.25);
            int state = -1;
            uint8_t aboveOceanAkaLand = GRASS;
            uint8_t belowOceanAkaEarthCrust = DIRT;
            for (int y = 127; y >= 0; y--) {
                int chunkCachePos = (x * 16 + z) * 128 + y;
                if (y <=  random_next_int(worldRandom, 5)) {
                    (*chunkCache)[chunkCachePos] = BEDROCK;
                    continue;
                }
                uint8_t previousBlock = (*chunkCache)[chunkCachePos];

                if (previousBlock == 0) {
                    state = -1;
                    continue;
                }
                if (previousBlock != STONE) {
                    continue;
                }
                if (state == -1) { // AIR
                    if (elevation <= 0) { // if in a deep
                        aboveOceanAkaLand = 0;
                        belowOceanAkaEarthCrust = STONE;
                    } else if (y >= oceanLevel - 4 && y <= oceanLevel + 1) { // if at sea level do the shore and rivers
                        aboveOceanAkaLand = GRASS;
                        belowOceanAkaEarthCrust = DIRT;
                        if (gravelly) {
                            aboveOceanAkaLand = 0;
                        }
                        if (gravelly) {
                            belowOceanAkaEarthCrust = GRAVEL;
                        }
                        if (sandy) {
                            aboveOceanAkaLand = SAND;
                        }
                        if (sandy) {
                            belowOceanAkaEarthCrust = SAND;
                        }
                    }
                    if (y < oceanLevel && aboveOceanAkaLand == 0) { // set deep water
                        aboveOceanAkaLand = MOVING_WATER;
                    }
                    state = elevation;
                    if (y >= oceanLevel - 1) { // above ocean level
                        (*chunkCache)[chunkCachePos] = aboveOceanAkaLand;
                    } else {
                        (*chunkCache)[chunkCachePos] = belowOceanAkaEarthCrust;
                    }

                    continue;
                }
                if (state > 0) {
                    state--;
                    (*chunkCache)[chunkCachePos] = belowOceanAkaEarthCrust;

                }
            }

        }
    }
    delete[] sandFields;
    delete[] gravelField;
    delete[] heightField;
}


static inline TerrainNoises *initTerrain(uint64_t worldSeed) {
    auto *terrainNoises = new TerrainNoises;
    Random worldRandom = get_random(worldSeed);
    PermutationTable *octaves = terrainNoises->minLimit;
    initOctaves(octaves, &worldRandom, 16);
    octaves = terrainNoises->maxLimit;
    initOctaves(octaves, &worldRandom, 16);
    octaves = terrainNoises->mainLimit;
    initOctaves(octaves, &worldRandom, 8);
    octaves = terrainNoises->shoresBottomComposition;
    initOctaves(octaves, &worldRandom, 4);
    octaves = terrainNoises->surfaceElevation;
    initOctaves(octaves, &worldRandom, 4);
    octaves = terrainNoises->scale;
    initOctaves(octaves, &worldRandom, 10);
    octaves = terrainNoises->depth;
    initOctaves(octaves, &worldRandom, 16);
    octaves = terrainNoises->forest;
    initOctaves(octaves, &worldRandom, 8);
    return terrainNoises;
}

static inline uint8_t *provideChunk(int chunkX, int chunkZ, BiomeResult *biomeResult, TerrainNoises *terrainNoises) {
    Random worldRandom = get_random((uint64_t) ((long) chunkX * 0x4f9939f508L + (long) chunkZ * 0x1ef1565bd5L));
    auto *chunkCache = new uint8_t[32768];
    generateTerrain(chunkX, chunkZ, &chunkCache, biomeResult->temperature, biomeResult->humidity, *terrainNoises);
    replaceBlockForBiomes(chunkX, chunkZ, &chunkCache, &worldRandom, *terrainNoises);
    return chunkCache;
}

void delete_terrain_result(TerrainResult *terrainResult) {
    delete[] terrainResult->chunkCache;
    delete[] terrainResult->chunkHeights;
    delete_biome_result(terrainResult->biomeResult);
    delete terrainResult;
}

uint8_t *TerrainInternalWrapper(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ, BiomeResult *biomeResult) {
    TerrainNoises *terrainNoises = initTerrain(worldSeed);
    uint8_t *chunkCache = provideChunk(chunkX, chunkZ, biomeResult, terrainNoises);
    delete terrainNoises;
    return chunkCache;
}

uint8_t *TerrainHeights(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ, BiomeResult *biomeResult) {
    TerrainNoises *terrainNoises = initTerrain(worldSeed);
    auto *chunkCache = provideChunk(chunkX, chunkZ, biomeResult, terrainNoises);
    delete[] terrainNoises;
    auto *chunkHeights = new uint8_t[16 * 16];
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            int pos = 128 * x * 16 + 128 * z;
            int y;
            for (y = 128; y >= 0 && chunkCache[pos + y] == AIR; y--);
            chunkHeights[x * 16 + z] = (y + 1);
        }
    }
    delete[] chunkCache;
    return chunkHeights;
}


TerrainResult *TerrainWrapper(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ) {
    BiomeResult *biomeResult = BiomeWrapper(worldSeed, chunkX, chunkZ);
    auto *chunkCache = TerrainInternalWrapper(worldSeed, chunkX, chunkZ, biomeResult);
    auto *chunkHeights = new uint8_t[16 * 16];
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            int pos = 128 * x * 16 + 128 * z;
            int y;
            for (y = 127; y >= 0 && chunkCache[pos + y] == AIR; y--);
            chunkHeights[x * 16 + z] = y;
        }
    }
    auto *terrainResult = new TerrainResult;
    terrainResult->biomeResult = biomeResult;
    terrainResult->chunkHeights = chunkHeights;
    terrainResult->chunkCache = chunkCache;
    return terrainResult;
}

static void printHeights(uint64_t worldSeed, int32_t chunkX, int32_t chunkZ) {
    auto *terrainResult = TerrainWrapper(worldSeed, chunkX, chunkZ);
    for (int x = 0; x < 16; ++x) {
        for (int z = 0; z < 16; ++z) {
            std::cout << (int) terrainResult->chunkHeights[x * 16 + z] << " ";
        }
        std::cout << std::endl;
    }
    delete_terrain_result(terrainResult);
}

int main() {
    printHeights(1755275 ,8 ,-2);
}