#ifndef BOSS_H
#define BOSS_H

#include "raylib.h"

inline constexpr Vector2 boss_size = { 3.0f, 3.0f };
inline constexpr int boss_hp = 10;

inline Vector2 boss_vel;
inline Vector2 boss_pos;

void spawn_boss();
void move_boss();
bool is_colliding_with_boss(Vector2 pos, Vector2 size);

#endif // BOSS_H