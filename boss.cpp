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
                boss_vel.x = 0.04;
                goto outer_loop_end;
            }
        }
    }
outer_loop_end:;
}

void move_boss()
{
    float next_boss_pos_x = boss_pos.x + boss_vel.x;
    if (is_colliding_with_level_cell({ next_boss_pos_x, boss_pos.y }, boss_size, WALL)) {
        boss_vel.x = -boss_vel.x;
    }
    boss_pos.x = next_boss_pos_x;
}

bool is_colliding_with_boss(const Vector2 pos, const Vector2 size)
{
    const Rectangle boss_hitbox = { boss_pos.x, boss_pos.y, boss_size.x, boss_size.y };
    const Rectangle hitbox = { pos.x, pos.y, size.x, size.y };
    return CheckCollisionRecs(boss_hitbox, hitbox);
}
