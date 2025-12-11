#include "assets.h"
#include "ball.h"
#include "boss.h"
#include "game.h"
#include "graphics.h"
#include "level.h"
#include "paddle.h"

#include "raylib.h"

void update()
{
    switch (game_state) {
    case menu_state:

        break;
    case in_game_state:
        if (IsKeyPressed(KEY_V)) {
            current_level_blocks = 0;
        }
        if (IsKeyPressed(KEY_SPACE)) {
            game_state = paused_state;
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            move_paddle(-paddle_speed);
        }
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            move_paddle(paddle_speed);
        }
        if (current_level_index == 3) {
            move_boss();
        }
        move_ball();
        if (!is_ball_inside_level()) {
            load_level();
            PlaySound(lose_sound);
        } else if (current_level_blocks == 0) {
            load_level(1);
            PlaySound(win_sound);
        }
        break;
    case paused_state:
        if (IsKeyPressed(KEY_SPACE)) {
            game_state = in_game_state;
        }
        break;
    case victory_state:
        current_level_index = -1;
        if (IsKeyPressed(KEY_ENTER)) {
            game_state = menu_state;
        }
        break;
    case cut_scene_state:

        break;
    }
}

void draw()
{
    // TODO
    switch (game_state) {
    case menu_state:
        draw_menu();
        break;
    case in_game_state:
        draw_level();
        draw_paddle();
        draw_ball();
        draw_ui();
        if (current_level_index == 3) {
            draw_boss();
            draw_boss_hp();
        }
        break;
    case paused_state:
        draw_pause_menu();
        break;
    case victory_state:
        draw_victory_menu();
        break;
    }
}

int main()
{
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(1280, 720, "Breakout");
    SetTargetFPS(60);

    load_fonts();
    load_textures();
    load_level();
    load_sounds();

    while (!WindowShouldClose()) {
        BeginDrawing();
        draw();
        update();
        EndDrawing();
    }
    CloseWindow();

    unload_sounds();
    unload_level();
    unload_textures();
    unload_fonts();

    return 0;
}