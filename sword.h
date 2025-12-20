#ifndef BREAKOUT_SWORD_H
#define BREAKOUT_SWORD_H
#include "level.h"

inline constexpr Vector2 sword_size = {0.5f, 1.0f};

inline float rand_pos_x[13];
inline float rand_pos_y[13];
inline Vector2 sword_vel;
inline Vector2 sword_pos;

void spawn_sword();
void move_sword();
#endif // BREAKOUT_SWORD_H
