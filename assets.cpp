#include "assets.h"

#include "raylib.h"

void load_fonts()
{
    menu_font = LoadFontEx("data/fonts/ARCADECLASSIC.TTF", 256, nullptr, 0);
}

void unload_fonts()
{
    UnloadFont(menu_font);
}

void load_textures()
{
    wall_texture = LoadTexture("data/images/block.png");
    void_texture = LoadTexture("data/images/void.png");
    block_texture = LoadTexture("data/images/wall.png");
    paddle_texture = load_sprite("data/images/skeleton/skeleton", ".png", 13, true, 1);
    button_sprite = load_sprite("data/images/start/start", ".png", 3, true, 1);
    ball_sprite = LoadTexture("data/images/ball0.png");
    quit_button_sprite = load_sprite("data/images/quit/quit", ".png", 3, true, 1);
}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    unload_sprite(paddle_texture);
    unload_sprite(button_sprite);
    UnloadTexture(ball_sprite);
    unload_sprite(quit_button_sprite);
}

void load_sounds()
{
    InitAudioDevice();
    win_sound = LoadSound("data/sounds/win.wav");
    lose_sound = LoadSound("data/sounds/lose.wav");
}

void unload_sounds()
{
    UnloadSound(win_sound);
    UnloadSound(lose_sound);
    CloseAudioDevice();
}
