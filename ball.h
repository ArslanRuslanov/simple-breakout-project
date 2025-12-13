#ifndef BALL_H
#define BALL_H

#include "boss.h"
#include "raylib.h"

inline constexpr float ball_launch_vel_mag = 0.15f;
inline constexpr float ball_launch_angle_degrees = 49.6f;
inline constexpr Vector2 ball_size = { 1.0f, 1.0f };

inline int hit = boss_hp;
inline Vector2 ball_pos;
inline Vector2 ball_vel;

void spawn_ball();
void move_ball();
bool is_ball_inside_level();

#endif // BALL_H
