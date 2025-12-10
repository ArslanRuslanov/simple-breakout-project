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
    wall_texture = LoadTexture("data/images/wall.png");
    void_texture = LoadTexture("data/images/void.png");
    block_texture = LoadTexture("data/images/block.png");
    paddle_sprite = load_sprite("data/images/skeleton/skeli", ".png", 11, true, 1);
    button_sprite = load_sprite("data/images/start/start", ".png", 3, true, 1);
    ball_texture = LoadTexture("data/images/ball0.png");
    background_texture = LoadTexture("data/images/background2.png");
    background_of_level_texture = LoadTexture("data/images/background3.png");
    logo_sprite = load_sprite("data/images/logo/logo", ".png", 17, true, 1);
    victory_texture = LoadTexture("data/images/VICTORY.png");
    win_sprite = load_sprite("data/images/win/win", ".png", 4, true, 1);
    quit_button_sprite = load_sprite("data/images/quit/quit", ".png", 3, true, 1);
    sword_texture = LoadTexture("data/images/sword0.png");
    boss_sprite = load_sprite("data/images/boss/boss", ".png", 2, true, 1);
    enemy_sprite = load_sprite("data/images/enemy/enemy", ".png", 5, true, 1);
    heart_sprite = load_sprite("data/images/heart/heart", ".png", 2, true, 1);
}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    unload_sprite(paddle_sprite);
    unload_sprite(button_sprite);
    UnloadTexture(ball_texture);
    unload_sprite(quit_button_sprite);
    UnloadTexture(background_texture);
    UnloadTexture(background_of_level_texture);
    unload_sprite(logo_sprite);
    UnloadTexture(victory_texture);
    unload_sprite(win_sprite);
    UnloadTexture(sword_texture);
    unload_sprite(boss_sprite);
    unload_sprite(enemy_sprite);
    unload_sprite(heart_sprite);
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
