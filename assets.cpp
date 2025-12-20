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
    ball_texture = LoadTexture("data/images/ball0.png");
    background_texture = LoadTexture("data/images/background2.png");
    background_of_level_texture = LoadTexture("data/images/background3.png");
    victory_texture = LoadTexture("data/images/VICTORY.png");
    sword_texture = LoadTexture("data/images/sword0.png");
    background_defeat = LoadTexture("data/images/background4.png");
    shield_texture = LoadTexture("data/images/shield.png");

    portal_sprite = load_sprite("data/images/portal/portal", ".png", 3, true, 1);
    paddle_sprite = load_sprite("data/images/skeleton/skeli", ".png", 11, true, 1);
    button_sprite = load_sprite("data/images/start/start", ".png", 3, true, 1);
    logo_sprite = load_sprite("data/images/logo/logo", ".png", 17, true, 1);
    win_sprite = load_sprite("data/images/win/win", ".png", 4, true, 1);
    quit_button_sprite = load_sprite("data/images/quit/quit", ".png", 3, true, 1);
    boss_sprite = load_sprite("data/images/boss/boss", ".png", 2, true, 1);
    enemy_sprite = load_sprite("data/images/enemy/enemy", ".png", 5, true, 1);
    heart_sprite = load_sprite("data/images/heart/heart", ".png", 2, true, 1);

}

void unload_textures()
{
    UnloadTexture(wall_texture);
    UnloadTexture(void_texture);
    UnloadTexture(block_texture);
    UnloadTexture(ball_texture);
    UnloadTexture(background_texture);
    UnloadTexture(background_of_level_texture);
    UnloadTexture(victory_texture);
    UnloadTexture(sword_texture);
    UnloadTexture(background_defeat);
    UnloadTexture(shield_texture);

    unload_sprite(portal_sprite);
    unload_sprite(paddle_sprite);
    unload_sprite(button_sprite);
    unload_sprite(quit_button_sprite);
    unload_sprite(logo_sprite);
    unload_sprite(win_sprite);
    unload_sprite(boss_sprite);
    unload_sprite(enemy_sprite);
    unload_sprite(heart_sprite);
}

void load_sounds()
{
    InitAudioDevice();

    hit_sound = LoadSound("data/sounds/win.wav");
    lose_sound = LoadSound("data/sounds/lose.wav");

    boss_level_sound = LoadMusicStream("data/sounds/boss_soundtrack.wav");
    level_sound = LoadMusicStream("data/sounds/level_soundtrack.wav");
    main_menu_sound = LoadMusicStream("data/sounds/main_menu_soundtrack.wav");
    win_sound = LoadMusicStream("data/sounds/victory_menu_soundtrack.wav");

    main_menu_sound.looping = true;
    boss_level_sound.looping = true;
    level_sound.looping = true;
    win_sound.looping = true;

}

void unload_sounds()
{
    UnloadSound(hit_sound);
    UnloadSound(lose_sound);
    UnloadMusicStream(boss_level_sound);
    UnloadMusicStream(level_sound);
    UnloadMusicStream(main_menu_sound);
    UnloadMusicStream(win_sound);
    CloseAudioDevice();
}
