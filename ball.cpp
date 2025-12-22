#include "ball.h"
#include "assets.h"
#include "boss.h"
#include "level.h"
#include "paddle.h"
#include "shield.h"
#include "portal.h"

#include "raylib.h"

#include <cmath>
#include <numbers>



void spawn_ball()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == BALL) {
                set_level_cell(row, column, VOID);
                ball_pos = { static_cast<float>(column), static_cast<float>(row) };
                constexpr float ball_launch_angle_radians = ball_launch_angle_degrees * (std::numbers::pi_v<float> / 180.0f);
                ball_vel.y = -ball_launch_vel_mag * std::sin(ball_launch_angle_radians);
                ball_vel.x = (rand() % 2 == 0) ? ball_launch_vel_mag * std::cos(ball_launch_angle_radians) : -ball_launch_vel_mag * std::cos(ball_launch_angle_radians);
                goto outer_loop_end;
            }
        }
    }
outer_loop_end:;
}

void move_ball()
{
    Vector2 next_ball_pos = {
        ball_pos.x + ball_vel.x,
        ball_pos.y + ball_vel.y
    };

    if (is_colliding_with_level_cell(next_ball_pos, ball_size, WALL)) {
        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, WALL)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, WALL)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }
    } else if (is_colliding_with_level_cell(next_ball_pos, ball_size, BOUNDARY)) {
        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, BOUNDARY)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, BOUNDARY)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }
    } else if (is_colliding_with_level_cell(next_ball_pos, ball_size, ENEMY)) {
        char& temp = get_colliding_level_cell(next_ball_pos, ball_size, ENEMY);
        PlaySound(hit_sound);
        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, ENEMY)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, ENEMY)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }

        temp = VOID;
        --current_level_blocks;
    } else if (is_colliding_with_level_cell(next_ball_pos, ball_size, SHIELD)) {
        char& temp = get_colliding_level_cell(next_ball_pos, ball_size, SHIELD);
        shield_hp--;
        PlaySound(break_sound);

        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, SHIELD)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, SHIELD)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }
        if (shield_hp <= 0) {
            temp = VOID;
            --current_level_blocks;
        }
    } else if (is_colliding_with_level_cell(next_ball_pos, ball_size, BREAKABLE)) {
        char& temp = get_colliding_level_cell(next_ball_pos, ball_size, BREAKABLE);
        PlaySound(break_sound);

        if (is_colliding_with_level_cell({ next_ball_pos.x, ball_pos.y }, ball_size, BREAKABLE)) {
            ball_vel.x = -ball_vel.x;
            next_ball_pos.x = std::round(next_ball_pos.x);
        }
        if (is_colliding_with_level_cell({ ball_pos.x, next_ball_pos.y }, ball_size, BREAKABLE)) {
            ball_vel.y = -ball_vel.y;
            next_ball_pos.y = std::round(next_ball_pos.y);
        }

        temp = VOID;
    } else if (is_colliding_with_paddle(next_ball_pos, ball_size)) {
        ball_vel.y = -std::abs(ball_vel.y);
    }
    if (current_level_index == 2) {
        portal_cooldown++;
        if (portal_cooldown >= 15) {
            if (is_colliding_with_portal1(next_ball_pos, ball_size)) {
                PlaySound(portal_sound);
                next_ball_pos = portal2_pos;
                portal_cooldown = 0;
            }
        }
        if (portal_cooldown >= 15) {
            if (is_colliding_with_portal2(next_ball_pos, ball_size)) {
                PlaySound(portal_sound);
                next_ball_pos = portal1_pos;
                portal_cooldown = 0;
            }
        }
    }
    if (current_level_index == 4) {
        if (is_colliding_with_boss(next_ball_pos, ball_size)) {
            PlaySound(boss_hit_sound);
            char& temp = get_colliding_level_cell(next_ball_pos, ball_size, BOSS);
            hit--;
            PlaySound(hit_sound);
            if (is_colliding_with_boss({ next_ball_pos.x, ball_pos.y }, ball_size)) {
                ball_vel.x = -ball_vel.x;
                next_ball_pos.x = std::round(next_ball_pos.x);
            }
            if (is_colliding_with_boss({ ball_pos.x, next_ball_pos.y }, ball_size)) {
                ball_vel.y = -ball_vel.y;
                next_ball_pos.y = std::round(next_ball_pos.y);
            }
            if (hit <= 0) {
                temp = VOID;
                current_level_blocks--;
            }
        }
    }

    ball_pos = next_ball_pos;
}

bool is_ball_inside_level()
{
    return is_inside_level(static_cast<int>(ball_pos.y), static_cast<int>(ball_pos.x));
}
