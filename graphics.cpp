#include "graphics.h"

#include "assets.h"
#include "ball.h"
#include "boss.h"
#include "level.h"
#include "paddle.h"
#include "portal.h"
#include "shield.h"
#include "sword.h"

#include "raylib.h"

#include <cmath>
#include <iostream>
#include <string>

struct Text {
    std::string str;
    Vector2 position = { 0.50f, 0.50f };
    float size = 32.0f;
    Color color = WHITE;
    float spacing = 4.0f;
    Font* font = nullptr;
};

int logo_frame = 0;
int logo_frame_counter = 0;
int logo_frame_speed = 10;

int win_frame = 0;
int win_frame_counter = 0;
int win_frame_speed = 10;

int paddleFrame = 0;

int enemy_frame = 0;
int enemy_frame_counter = 0;
int enemy_frame_speed = 10;

int boss_frame = 0;
int boss_frame_counter = 0;
int boss_frame_speed = 10;

int portal_frame_counter = 0;
int portal_frame = 0;
int portal_frame_speed = 10;

constexpr float cell_scale = 0.6f;
constexpr float screen_scale_divisor = 700.0f;

constexpr size_t victory_ball_launch_degree_offset = 3;
constexpr size_t victory_balls_count = 360 / victory_ball_launch_degree_offset;
constexpr float victory_balls_speed = 7.0f;
constexpr float victory_balls_size = 3.0f;

Vector2 screen_size;
float screen_scale;

Vector2 shift_to_center;

Vector2 victory_balls_pos[victory_balls_count];
Vector2 victory_balls_vel[victory_balls_count];

size_t game_frame = 0;

void draw_image(const Texture2D& image, const float x, const float y, const float width, const float height)
{
    const Rectangle source = { 0.0f, 0.0f, static_cast<float>(image.width), static_cast<float>(image.height) };
    const Rectangle destination = { x, y, width, height };
    DrawTexturePro(image, source, destination, { 0.0f, 0.0f }, 0.0f, WHITE);
}

void draw_image(const Texture2D& image, const float x, const float y, const float size)
{
    draw_image(image, x, y, size, size);
}

void draw_sprite(sprite& sprite, const float x, const float y, const float width, const float height)
{
    draw_image(sprite.frames[sprite.frame_index], x, y, width, height);

    if (sprite.prev_game_frame == game_frame) {
        return;
    }
    if (sprite.frames_skipped < sprite.frames_to_skip) {
        ++sprite.frames_skipped;
    } else {
        sprite.frames_skipped = 0;

        ++sprite.frame_index;
        if (sprite.frame_index >= sprite.frame_count) {
            sprite.frame_index = sprite.loop ? 0 : sprite.frame_count - 1;
        }
    }
    sprite.prev_game_frame = game_frame;
}

void draw_sprite(sprite& sprite, const float x, const float y, const float size)
{
    draw_sprite(sprite, x, y, size, size);
}

void draw_text(const Text& text)
{
    const auto [x, y] = MeasureTextEx(*text.font, text.str.c_str(), text.size * screen_scale, text.spacing);
    const Vector2 pos = {
        screen_size.x * text.position.x - 0.5f * x,
        screen_size.y * text.position.y - 0.5f * y
    };
    DrawTextEx(*text.font, text.str.c_str(), pos, y, text.spacing, text.color);
}

void derive_graphics_metrics()
{
    screen_size.x = static_cast<float>(GetScreenWidth());
    screen_size.y = static_cast<float>(GetScreenHeight());

    cell_size = std::min(screen_size.x / static_cast<float>(current_level.columns), screen_size.y / static_cast<float>(current_level.rows));
    screen_scale = std::min(screen_size.x, screen_size.y) / screen_scale_divisor;

    const float level_width = static_cast<float>(current_level.columns) * cell_size;
    const float level_height = static_cast<float>(current_level.rows) * cell_size;
    shift_to_center = {
        (screen_size.x - level_width) * 0.5f,
        (screen_size.y - level_height)
    };
}

void animate_texture(sprite sprite, int framecount, float x_pos, float y_pos, float width, float height, int frameWidth, int frameHeight)
{
    Rectangle source = {
        (float)framecount * frameWidth,
        0,
        (float)frameWidth,
        (float)frameHeight
    };
    Rectangle dest = { x_pos, y_pos, width, height };
    Vector2 origin = { 0, 0 };
    Texture2D texture = sprite.frames[framecount];
    DrawTexturePro(texture, source, dest, origin, 0, WHITE);
}

void button_action(bool action, enum game_state state)
{
    if (action) {
        game_state = state;
    }
}

void draw_button_quit()
{
    int buttonFrame = 0;
    int frameWidth = 512;
    int frameHeight = 288;
    Rectangle btnBounds = { 850, 400, 150, 80 };
    Vector2 mousePoint = GetMousePosition();
    bool btnAction = false;

    if (CheckCollisionPointRec(mousePoint, btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            buttonFrame = 2;
        else
            buttonFrame = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    } else {
        buttonFrame = 0;
    }
    animate_texture(quit_button_sprite, buttonFrame, 850, 400, 150, 80, frameWidth, frameHeight);
    if (btnAction) {
        CloseWindow();
        unload_sounds();
        unload_level();
        unload_textures();
        unload_fonts();
    }
}

void draw_button_start()
{

    int buttonFrame = 0;
    int frameWidth = 512;
    int frameHeight = 288;
    Rectangle btnBounds = { 850, 300, 150, 80 };
    Vector2 mousePoint = GetMousePosition();
    bool btnAction = false;

    if (CheckCollisionPointRec(mousePoint, btnBounds)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            buttonFrame = 2;
        else
            buttonFrame = 1;
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            btnAction = true;
    } else {
        buttonFrame = 0;
    }
    animate_texture(button_sprite, buttonFrame, 850, 300, 150, 80, frameWidth, frameHeight);
    button_action(btnAction, in_game_state);
}

void draw_title()
{
    animate_texture(logo_sprite, logo_frame, 550, 100, 600, 150, 1024, 256);
    logo_frame_counter++;
    if (logo_frame_counter >= logo_frame_speed) {
        logo_frame++;
        if (logo_frame > 16)
            logo_frame = 0;

        logo_frame_counter = 0;
    }
}

void draw_menu()
{
    ClearBackground(RAYWHITE);

    DrawTexturePro(
        background_texture,
        { 0, 0, 640.0, 360.0 },
        { 0, 0, 1280.0, 720.0 },
        { 0, 0 },
        0,
        WHITE);

    draw_image(ball_texture, 270, 560, 80, 80);
    draw_title();
    draw_button_start();
    draw_button_quit();
}

void draw_ui()
{
    const float texture_x_pos = cell_size + 75;
    const float texture_y_pos = shift_to_center.y + cell_size;
    const Text counter = {
        "LEVEL " + std::to_string(current_level_index + 1) + " BLOCKS " + std::to_string(current_level_blocks),
        { 0.5f, 0.0375f },
        48.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    for (int j = 0; j < 3; j++) {
        animate_texture(heart_sprite, 1, texture_x_pos, texture_y_pos + j * 100, 75, 75, 256, 256);
    }

    for (int i = 0; i < paddle_hp; ++i) {
        animate_texture(heart_sprite, 0, texture_x_pos, texture_y_pos + i * 100, 75, 75, 256, 256);
    }

    draw_text(counter);
}

void draw_level()
{
    ClearBackground(RAYWHITE);

    DrawTexturePro(
        background_of_level_texture,
        { 0, 0, 640.0, 360.0 },
        { 0, 0, 1280.0, 720.0 },
        { 0, 0 },
        0,
        WHITE);

    enemy_frame_counter++;
    if (enemy_frame_counter >= enemy_frame_speed) {
        enemy_frame++;
        if (enemy_frame > 3)
            enemy_frame = 0;

        enemy_frame_counter = 0;
    }

    for (size_t row = 0; row < current_level.rows; ++row) {
        for (size_t column = 0; column < current_level.columns; ++column) {
            const char data = current_level.data[row * current_level.columns + column];
            const float texture_x_pos = shift_to_center.x + static_cast<float>(column) * cell_size;
            const float texture_y_pos = shift_to_center.y + static_cast<float>(row) * cell_size;

            switch (data) {
            case WALL:
                draw_image(wall_texture, texture_x_pos, texture_y_pos, cell_size);
                break;
            case ENEMY:
                animate_texture(enemy_sprite, enemy_frame, texture_x_pos, texture_y_pos, 1.2 * cell_size, cell_size * 1.2, 16, 20);
                break;
            case BREAKABLE:
                draw_image(block_texture, texture_x_pos, texture_y_pos, cell_size);
                break;
            case SHIELD:
                animate_texture(enemy_sprite, enemy_frame, texture_x_pos, texture_y_pos, 1.2 * cell_size, cell_size * 1.2, 16, 20);
                if (shield_hp == 2)
                    draw_image(shield_texture, texture_x_pos - 10, texture_y_pos - 10, cell_size * 1.5);
                break;
            default:;
            }
        }
    }
}

void draw_portal()
{
    const float texture_x_pos = shift_to_center.x + portal1_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + portal1_pos.y * cell_size;
    const float texture_x1_pos = shift_to_center.x + portal2_pos.x * cell_size;
    const float texture_y1_pos = shift_to_center.y + portal2_pos.y * cell_size;

    portal_frame_counter++;
    if (portal_frame_counter >= portal_frame_speed) {
        portal_frame++;
        if (portal_frame > 2)
            portal_frame = 0;

        portal_frame_counter = 0;
    }

    animate_texture(portal_sprite, portal_frame, texture_x_pos, texture_y_pos, cell_size, cell_size, 11, 33);
    animate_texture(portal_sprite, portal_frame, texture_x1_pos, texture_y1_pos, cell_size, cell_size, 11, 33);

}

void draw_boss_hp()
{
    const float texture_x_pos = shift_to_center.x + boss_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + boss_pos.y * cell_size - 20;
    DrawRectangle(texture_x_pos, texture_y_pos, cell_size * 3, 10, RED);
    float hp_bar = cell_size * 3 / boss_hp;
    for (int i = 0; i < hit; ++i) {
        DrawRectangle(texture_x_pos + hp_bar * i, texture_y_pos, hp_bar, 10, GREEN);
    }
}

void draw_boss()
{
    const float texture_x_pos = shift_to_center.x + boss_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + boss_pos.y * cell_size;
    int frameWidth = 400;
    int frameHeight = 384;
    boss_frame_counter++;
    if (boss_frame_counter >= boss_frame_speed) {
        boss_frame++;
        if (boss_frame > 1)
            boss_frame = 0;

        boss_frame_counter = 0;
    }
    animate_texture(boss_sprite, boss_frame, texture_x_pos, texture_y_pos, cell_size * 3, cell_size * 3, frameWidth, frameHeight);
}

void draw_sword()
{
    const float texture_x_pos = shift_to_center.x + sword_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + sword_pos.y * cell_size;
    int frameWidth = 50;
    int frameHeight = 125;
    draw_image(sword_texture, texture_x_pos, texture_y_pos, frameWidth - 20, frameHeight - 20);
}

void draw_paddle()
{
    const float texture_x_pos = shift_to_center.x + paddle_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + paddle_pos.y * cell_size;
    int frameWidth = 32;
    int frameHeight = 32;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D) || IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_RIGHT)) {
        paddleFrame++;
        if (paddleFrame > 10) {
            paddleFrame = 1;
        }
    } else {
        paddleFrame = 0;
    }
    animate_texture(paddle_sprite, paddleFrame, texture_x_pos, texture_y_pos, 166, 166, frameWidth, frameHeight);
}

void draw_ball()
{
    const float texture_x_pos = shift_to_center.x + ball_pos.x * cell_size;
    const float texture_y_pos = shift_to_center.y + ball_pos.y * cell_size;
    draw_image(ball_texture, texture_x_pos, texture_y_pos, cell_size, cell_size);
}

void draw_pause_menu()
{
    ClearBackground(BLACK);

    DrawTexturePro(
        background_of_level_texture,
        { 0, 0, 640.0, 360.0 },
        { 0, 0, 1280.0, 720.0 },
        { 0, 0 },
        0,
        WHITE);

    const Text paused_title = {
        "Press Space to Resume",
        { 0.50f, 0.50f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(paused_title);
}

void init_victory_menu()
{
    for (size_t i = 0; i < victory_balls_count; ++i) {
        victory_balls_pos[i] = { screen_size.x / 2, screen_size.y / 2 };
        victory_balls_vel[i] = {
            std::cos(static_cast<float>(i * victory_ball_launch_degree_offset)) * victory_balls_speed,
            std::sin(static_cast<float>(i * victory_ball_launch_degree_offset)) * victory_balls_speed
        };
    }
}

void animate_victory_menu()
{
    for (size_t i = 0; i < victory_balls_count; ++i) {
        if (victory_balls_pos[i].x + victory_balls_vel[i].x > screen_size.x || victory_balls_pos[i].x + victory_balls_vel[i].x < 0) {
            victory_balls_vel[i].x *= -1.0f;
        }
        if (victory_balls_pos[i].y + victory_balls_vel[i].y > screen_size.y || victory_balls_pos[i].y + victory_balls_vel[i].y < 0) {
            victory_balls_vel[i].y *= -1.0f;
        }
        victory_balls_pos[i] = {
            victory_balls_pos[i].x + victory_balls_vel[i].x,
            victory_balls_pos[i].y + victory_balls_vel[i].y
        };
    }
}

void draw_victory_menu()
{
    animate_texture(win_sprite, win_frame, 0, 0, 1280, 720, 640, 360);
    win_frame_counter++;
    if (win_frame_counter >= win_frame_speed) {
        win_frame++;
        if (win_frame > 3)
            win_frame = 0;

        win_frame_counter = 0;
    }

    DrawTexturePro(victory_texture, { 0, 0, 1024, 256 }, { 650, 100, 600, 140 }, { 0, 0 }, 0, RAYWHITE);

    const Text victory_subtitle = {
        "Press Enter to Restart",
        { 0.75f, 0.40f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(victory_subtitle);
}

void draw_game_over_menu()
{
    ClearBackground(BLACK);
    DrawTexturePro(
        background_defeat,
        { 0, 0, 640.0, 360.0 },
        { 0, 0, 1280.0, 720.0 },
        { 0, 0 },
        0,
        WHITE);
    const Text game_over_title = {
        "GAME OVER",
        { 0.75, 0.20 },
        40.0f,
        WHITE,
        4.0f,
        &menu_font
    };

    draw_text(game_over_title);
    const Text game_over_subtitle = {
        "Press Enter to Restart",
        { 0.75f, 0.40f },
        32.0f,
        WHITE,
        4.0f,
        &menu_font
    };
    draw_text(game_over_subtitle);
}
