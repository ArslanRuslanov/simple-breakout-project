#ifndef BOSS_H
#define BOSS_H
#include "raylib.h"

inline constexpr Vector2 boss_size = { 3.0f, 3.0f };
inline constexpr float boss_speed = 0.1f;

inline Vector2 boss_pos;
inline Vector2 boss_vel;

void spawn_boss();
void move_boss();
bool is_colliding_with_boss(Vector2 pos, Vector2 size);

#endif // BOSS_H
