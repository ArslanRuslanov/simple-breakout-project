#include "portal.h"
#include "level.h"

#include "raylib.h"

#include <cmath>

void spawn_portal()
{
    for (int column = 0; column < current_level.columns; column++) {
        for (int row = 0; row < current_level.rows; row++) {
            if (get_level_cell(row, column) == PORTAL1) {
                set_level_cell(row, column, VOID);
                portal1_pos = { static_cast<float>(column), static_cast<float>(row) };
            }
            if (get_level_cell(row, column) == PORTAL2) {
                set_level_cell(row, column, VOID);
                portal2_pos = { static_cast<float>(column), static_cast<float>(row) };
            }
        }
    }
}

bool is_colliding_with_portal1(const Vector2 pos, const Vector2 size)
{
    const Rectangle portal1_box = {portal1_pos.x, portal1_pos.y, portal_size.x, portal_size.y};
    const Rectangle hitbox = { pos.x, pos.y, size.x, size.y };
    return CheckCollisionRecs(portal1_box, hitbox);
}

bool is_colliding_with_portal2(const Vector2 pos, const Vector2 size)
{
    const Rectangle portal2_box = {portal2_pos.x, portal2_pos.y, portal_size.x, portal_size.y};
    const Rectangle hitbox = { pos.x, pos.y, size.x, size.y };
    return CheckCollisionRecs(portal2_box, hitbox);
}