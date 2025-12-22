#include "sword.h"
#include "level.h"

#include "raylib.h"
#include <cstdlib>

void spawn_sword()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == SWORD) {
                set_level_cell(row, column, VOID);
                rand_pos_x[column] = static_cast<float>(column);
                rand_pos_y[row] = static_cast<float>(row);
            }
        }
    }
    int random_position_x = GetRandomValue(1, static_cast<float>(current_level.columns) - 1);

    sword_pos = { rand_pos_x[random_position_x], rand_pos_y[0] };
    sword_vel.y = 0.1;
}

bool is_sword_inside_level()
{
    return is_inside_level(static_cast<int>(sword_pos.y), static_cast<int>(sword_pos.x));
}

void move_sword()
{
    Vector2 next_sword_pos = {
        sword_pos.x,
        sword_pos.y + sword_vel.y
    };
    if (!is_sword_inside_level()) {
        next_sword_pos.x = GetRandomValue(0, current_level.columns - 1);
        next_sword_pos.y = 0;
    }
    sword_pos = next_sword_pos;
}
