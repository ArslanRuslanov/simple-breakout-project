#include "boss.h"
#include "level.h"

#include "raylib.h"

#include <cmath>

void spawn_boss()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == BOSS) {
                set_level_cell(row, column, VOID);
                boss_pos = { static_cast<float>(column), static_cast<float>(row) };
                boss_vel.x = 2.0f;
                boss_vel.y = 0.0f;
                goto outer_loop_end;
            }
        }
    }
    outer_loop_end:;
}

void move_boss()
{
    Vector2 next_boss_pos = {
        boss_pos.x + boss_vel.x,
        boss_pos.y + boss_vel.y
    };

    if (is_colliding_with_level_cell(next_boss_pos, boss_size, WALL)) {
        if (is_colliding_with_level_cell({ next_boss_pos.x, boss_pos.y }, boss_size, WALL)) {
            boss_vel.x = -boss_vel.x;
            next_boss_pos.x = std::round(next_boss_pos.x);
        }
    }

    boss_pos = next_boss_pos;
}

bool is_colliding_with_boss(const Vector2 pos, const Vector2 size)
{
    const Rectangle boss_hitbox = { boss_pos.x, boss_pos.y, boss_size.x, boss_size.y };
    const Rectangle hitbox = { pos.x, pos.y, size.x, size.y };
    return CheckCollisionRecs(boss_hitbox, hitbox);
}
