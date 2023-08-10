#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <experimental/random>
#include <ranges>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

ALLEGRO_FONT* G_FONT = nullptr;
#define AUTO_WIDTH 0

#include "include/cControl.h"
#include "include/sTextCTL.h"
#include "include/sButtonCTL.h"
#include "include/sRect.h"
#include "include/sAABB.h"
#include "include/cUnit.h"
#include "include/cAI.h"
#include "cPlayer.h"

/*
    cUnit / cGill do not have responsibilities in moving/thinking
    cAI has a responsibility to calculate a path
    cGill has a responsibility to render itself (including when instructed to do so by an external factor

    cController (manual/automatic) -> cUnit/cGill -> iAI (interface) -> cAI
*/

void displayFPS(double& game_time, double& old_time, double& fps, int& frames_done) {
    game_time = al_get_time();

    if (game_time - old_time >= 0.15d) {
        fps = frames_done / (game_time - old_time);

        frames_done = 0;
        old_time = game_time;
    }

    frames_done++;

    al_draw_text(G_FONT, al_map_rgba(24, 100, 64, 0), 0, 0, 0, std::string("FPS: " + std::to_string(fps)).c_str());
}

int main() {
    std::experimental::reseed();

    ALLEGRO_DISPLAY *display = NULL;
    //ALLEGRO_FONT *font = G_FONT;
    ALLEGRO_TIMER* timer = NULL;

    al_init();
    al_install_mouse();
    al_install_keyboard();
    al_install_audio();

    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_init_acodec_addon();

    G_FONT = al_create_builtin_font();

    al_reserve_samples(127);

    //al_show_native_message_box(display, "** CRITICAL ERROR **", "NEWS FLASH YOU NERDS", "DO-DO BRAIN!!", "WTF? DON'T CLICK ME!", ALLEGRO_MESSAGEBOX_ERROR);

    al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
    al_set_new_display_flags(ALLEGRO_NOFRAME);
    ALLEGRO_MONITOR_INFO info;
    int i = 0;
    do {
        al_get_monitor_info(i++, &info);
    } while (!(info.x1 == 0 && info.y1 == 0));
    int display_width = info.x2 - info.x1;
    int display_height = info.y2 - info.y1;

    if (!(display = al_create_display(display_width,display_height))) {
        return false;
    }

    al_toggle_display_flag(display,  ALLEGRO_FULLSCREEN_WINDOW, true);
    al_toggle_display_flag(display,  ALLEGRO_NOFRAME,true);

    al_resize_display(display, display_width, display_height);

    al_set_target_backbuffer(display);

    ALLEGRO_EVENT_QUEUE* q = al_create_event_queue();
    al_register_event_source(q, al_get_keyboard_event_source());
    al_register_event_source(q, al_get_mouse_event_source());
    al_register_event_source(q, al_get_display_event_source(display));

    timer = al_create_timer(1.0 / 144);
    al_register_event_source(q, al_get_timer_event_source(timer));

    al_hide_mouse_cursor(display);

    std::vector<std::unique_ptr<cControl>> widgets { };
    widgets.reserve(10);

    widgets.emplace_back(std::make_unique<sTextCTL>(sRect { 0, 50, 0, 0 }, al_map_rgb(0, 255, 255)));
    static_cast<sTextCTL *>(widgets.back().get())->m_text = "This is quite the learning experience! :D";

    widgets.emplace_back(std::make_unique<sButtonCTL>(sRect { 400, 100, AUTO_WIDTH, 100 + 20 }, al_map_rgb(0, 255, 0)));
    static_cast<sButtonCTL *>(widgets.back().get())->stapleText(static_cast<sTextCTL*>(&*widgets[0]));

    bool quit = false;

    al_start_timer(timer);

    ALLEGRO_BITMAP* playerImg = nullptr;
    playerImg = al_load_bitmap("/home/noviochok/Desktop/mj.jpg");

    int fNum = std::experimental::randint(0, 9);
    std::string childAudio { "a00" + std::to_string(fNum) + ".wav" };

    std::vector<ALLEGRO_SAMPLE*> audioFile(9);
    audioFile.reserve(9);

    for (auto n = 0; n < 9; ++n) {
        audioFile[n] = al_load_sample(std::string("a00" + std::to_string(n) + ".wav").c_str());
    }

    //ALLEGRO_AUDIO_STREAM* music = al_load_audio_stream("bg.mp3", 8, 1);
    //al_set_audio_stream_playing(music, false);

//    al_play_sample(al_load_sample("bg.wav"), 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);

    //ALLEGRO_AUDIO_STREAM* stream = al_load_audio_stream("bg.wav", 4, 64);
    //al_attach_audio_stream_to_mixer(stream, al_get_default_mixer());

    //for (auto& e : audioFile) {
    //    *e = al_load_sample(childAudio.c_str());
    //}
    /*
        ALLEGRO_SAMPLE* spl = al_load_sample(childAudio.c_str());
        al_play_sample(spl, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        spl = al_load_sample("a001.wav");
        al_play_sample(spl, 1.0, ALLEGRO_AUDIO_PAN_NONE, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
    */

    cPlayer Gill(playerImg);
    bool flashlight { false };
    bool AIlines { false };

    int F_R { 255 }, F_G { 0 }, F_B { 255 };

    double game_time = al_get_time();
    double old_time = game_time;
    double fps = 0;
    int frames_done = 0;

    int GillAINextIns = 0;

    sPoint mousie { 0, 0 };
    bool run = true;

    while (!quit) {
        do {
            ALLEGRO_EVENT e;
            ALLEGRO_MOUSE_STATE state;
            al_get_mouse_state(&state);
            al_wait_for_event(q, &e);

            al_clear_to_color(al_map_rgb(0, 0, 0));

            displayFPS(game_time, old_time, fps, frames_done);

            if (e.type == ALLEGRO_EVENT_MOUSE_AXES || e.type == ALLEGRO_EVENT_MOUSE_WARPED) {
                mousie.x = e.mouse.x;
                mousie.y = e.mouse.y;

                // Gill is controlled by the MOUSE :o
                if (Gill.m_AI.m_pathCalculated) {
                    Gill.m_Rect.m_X = mousie.x;
                    Gill.m_Rect.m_Y = mousie.y;
                }
            }

            std::string mouseX { "Mouse X: " + std::to_string(mousie.x) };
            al_draw_text(G_FONT, al_map_rgba(24, 255, 64, 0), 0, 20, 0, mouseX.data());

            std::string mouseY { "Mouse Y: " + std::to_string(mousie.y) };
            al_draw_text(G_FONT, al_map_rgba(24, 255, 64, 0), 0, 30, 0, mouseY.data());

            // LOOPING HERE :(
            if (Gill.m_AI.m_instructions.size() > 0 && Gill.m_AI.m_actuate) {
                if (GillAINextIns < Gill.m_AI.m_instructions.size()) {
                    Gill.m_Rect.m_X = Gill.m_AI.m_instructions[GillAINextIns].x;
                    Gill.m_Rect.m_Y = Gill.m_AI.m_instructions[GillAINextIns].y;

                    mousie.x = Gill.m_Rect.m_X;
                    mousie.y = Gill.m_Rect.m_Y;
                    ++GillAINextIns;
                } else {
                    std::cout << "Actuation disabled (Bob found his mark) :(\n";
                    //Gill.m_AI.m_actuate = false;
                    GillAINextIns = 0;
                }
            }

            std::string insSS { "Instruction set size: " + std::to_string(Gill.m_AI.m_instructions.size()) };
            al_draw_text(G_FONT, al_map_rgba(255, 50, 64, 0), 0, 50, 0, insSS.data());

            // MAGIC SAUCE FUCKING ME UP
            if (!Gill.m_AI.m_pathCalculated) {
                Gill.m_AI.init(&Gill.m_Rect, &widgets.back().get()->m_Rect);
            }

            std::string tof { "" };
            tof.reserve(6);

            tof = Gill.m_AI.m_pathCalculated ? "true" : "false";

            std::string pathBool { "m_pathCalculated: " + tof };
            al_draw_text(G_FONT, al_map_rgba(255, 50, 64, 0), 0, 70, 0, pathBool.data());

            tof = Gill.m_AI.m_actuate ? "true" : "false";

            std::string actuateBool { "m_actuate: " + tof };
            al_draw_text(G_FONT, al_map_rgba(255, 50, 64, 0), 0, 80, 0, actuateBool.data());

            std::ranges::reverse_view reverseView {widgets};
            for (auto& pObjC : reverseView) {
                if (pObjC->collided(&Gill.m_Rect)) {
                    int x = std::experimental::randint(0, display_width - pObjC->m_Rect.m_width);
                    int y = std::experimental::randint(0, display_height - pObjC->m_Rect.m_height);

                    sRect newPos { x, y, AUTO_WIDTH, y + 20 };
                    pObjC->updatePos(newPos);
                    Gill.m_AI.m_objective = pObjC->m_Rect;

                    Gill.m_AI.m_pathCalculated = false;
                    Gill.m_AI.m_actuate = true; // True = repeat behavior, false = shut it off
                    Gill.m_AI.clearShortTermMemory();
                }

                pObjC->draw();
            }

            al_draw_rectangle(mousie.x - 15, mousie.y - 15, mousie.x + 15, mousie.y + 15, al_map_rgb_f(255, 0, 0), -1);
            al_draw_rectangle(mousie.x, mousie.y, mousie.x, mousie.y, al_map_rgb_f(0, 255, 0), 2);
            al_draw_text(G_FONT, al_map_rgba(0, 255, 0, 0), mousie.x + 25, mousie.y - 40, 0, "Transparent");

            if (e.type == ALLEGRO_EVENT_KEY_UP && e.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                quit = true;
            }

            // Teleports mouse to { 0, 0 } of the object
            if (e.type == ALLEGRO_EVENT_KEY_CHAR && e.keyboard.keycode == ALLEGRO_KEY_Z) {
                al_set_mouse_xy(display, static_cast<sButtonCTL *>(widgets[1].get())->m_Rect.m_X, static_cast<sButtonCTL *>(widgets[1].get())->m_Rect.m_Y);
                std::cout << "{ TELEPORT } -> " << static_cast<sButtonCTL *>(widgets[1].get())->m_Rect.m_X << ", " << static_cast<sButtonCTL *>(widgets[1].get())->m_Rect.m_Y << "\n";
            }

            if (AIlines && Gill.m_AI.m_instructions.size() >= 2) {
                int a = 0;
                for (auto n = 1; n < Gill.m_AI.m_instructions.size() - 1; ++n) {
                    al_draw_line(Gill.m_AI.m_instructions[a].x, Gill.m_AI.m_instructions[a].y,
                                 Gill.m_AI.m_instructions[n].x, Gill.m_AI.m_instructions[n].y, al_map_rgb(F_R, F_G, F_B), 2);
                }
            }

            if (e.type == ALLEGRO_EVENT_KEY_CHAR && e.keyboard.keycode == ALLEGRO_KEY_W) {
                Gill.m_AI.m_actuate = !Gill.m_AI.m_actuate;
            }

            if (e.type == ALLEGRO_EVENT_KEY_CHAR && e.keyboard.keycode == ALLEGRO_KEY_Q) {
                AIlines = !AIlines;
            }

            if (e.type == ALLEGRO_EVENT_TIMER) {
                // DRAW ALL OBJECTS
                std::ranges::reverse_view reverseView {widgets};
                for (auto& pObjC : reverseView) {
                    pObjC->draw();
                }

                // Gill is drawn LAST
                Gill.draw();

                al_flip_display();
                al_flush_event_queue(q);
            }
        } while (!al_is_event_queue_empty(q));
    }

// Clean up resources
    al_destroy_timer(timer);
    al_destroy_display(display);
    al_destroy_font(G_FONT);
    al_uninstall_keyboard();

    return 0;
}
