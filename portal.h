#ifndef BREAKOUT_PORTAL_H
#define BREAKOUT_PORTAL_H

#include "raylib.h"

inline constexpr Vector2 portal_size = { 1.0f, 1.0f };
inline int portal_cooldown = 0;

inline Vector2 portal1_pos;
inline Vector2 portal2_pos;

void spawn_portal();
bool is_colliding_with_portal1(Vector2 pos, Vector2 size);
bool is_colliding_with_portal2(Vector2 pos, Vector2 size);

#endif // BREAKOUT_PORTAL_H
