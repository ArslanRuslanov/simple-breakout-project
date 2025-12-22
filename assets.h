#ifndef ASSETS_H
#define ASSETS_H

#include "raylib.h"

#include "sprite.h"

inline Font menu_font;

inline Texture2D wall_texture;
inline Texture2D void_texture;
inline Texture2D ball_texture;
inline Texture2D block_texture;
inline Texture2D background_texture;
inline Texture2D background_of_level_texture;
inline Texture2D victory_texture;
inline Texture2D sword_texture;
inline Texture2D background_defeat;
inline Texture2D shield_texture;

inline sprite win_sprite;
inline sprite enemy_sprite;
inline sprite heart_sprite;
inline sprite boss_sprite;
inline sprite quit_button_sprite;
inline sprite paddle_sprite;
inline sprite button_sprite;
inline sprite logo_sprite;
inline sprite portal_sprite;

inline Sound hit_sound;
inline Sound lose_sound;
inline Sound portal_sound;
inline Sound break_sound;
inline Sound boss_hit_sound;

inline Music boss_level_sound;
inline Music win_sound;
inline Music level_sound;
inline Music main_menu_sound;

void load_fonts();
void unload_fonts();

void load_textures();
void unload_textures();

void load_sounds();
void unload_sounds();

#endif // ASSETS_H
