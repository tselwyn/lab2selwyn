// Tyler Selwyn
// CPSC 440 - Game Programming
// Lab 2 - Moving Object with Directional Pointer
// Green circle moves with arrow keys and UDRL keys, yellow pointer shows direction

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

int main(void)
{
    ALLEGRO_DISPLAY* Screen = NULL;

    // initialize allegro
    if (!al_init())
    {
        al_show_native_message_box(NULL, "Error!", "Allegro has failed to initialize.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    // create 800x600 display
    int width = 800, height = 600;
    Screen = al_create_display(width, height);
    if (Screen == NULL)
    {
        al_show_native_message_box(Screen, "Error!", "Failed to create the display.", 0, 0, ALLEGRO_MESSAGEBOX_ERROR);
        return -1;
    }

    bool done = false;
    int pos_x = width / 2;  // start at center
    int pos_y = height / 2;
    int direction = 0;  // 0=up 1=down 2=right 3=left 4=UL 5=DR 6=UR 7=DL

    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_EVENT ev;

    // initialize addons and keyboard
    al_init_primitives_addon();
    al_install_keyboard();

    // set up event queue with keyboard and display sources
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_display_event_source(Screen));

    // main game loop
    while (!done)
    {
        al_wait_for_event(event_queue, &ev);

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        {
            switch (ev.keyboard.keycode)
            {
                // arrow keys for cardinal movement
            case ALLEGRO_KEY_UP:
                pos_y -= 10;
                direction = 0;
                break;
            case ALLEGRO_KEY_DOWN:
                pos_y += 10;
                direction = 1;
                break;
            case ALLEGRO_KEY_RIGHT:
                pos_x += 10;
                direction = 2;
                break;
            case ALLEGRO_KEY_LEFT:
                pos_x -= 10;
                direction = 3;
                break;
                // UDRL keys for diagonal movement
            case ALLEGRO_KEY_U:
                pos_x -= 10;
                pos_y -= 10;
                direction = 4;
                break;
            case ALLEGRO_KEY_D:
                pos_x += 10;
                pos_y += 10;
                direction = 5;
                break;
            case ALLEGRO_KEY_R:
                pos_x += 10;
                pos_y -= 10;
                direction = 6;
                break;
            case ALLEGRO_KEY_L:
                pos_x -= 10;
                pos_y += 10;
                direction = 7;
                break;
            case ALLEGRO_KEY_ESCAPE:
                done = true;
                break;
            }
        }

        // clear screen to erase old position
        al_clear_to_color(al_map_rgb(0, 0, 0));

        // draw green circle at current position
        al_draw_filled_circle(pos_x, pos_y, 20, al_map_rgb(0, 255, 0));

        // draw yellow triangle pointer based on current direction
        if (direction == 0) // up
            al_draw_filled_triangle(pos_x, pos_y - 30, pos_x - 8, pos_y - 20, pos_x + 8, pos_y - 20, al_map_rgb(255, 255, 0));
        else if (direction == 1) // down
            al_draw_filled_triangle(pos_x, pos_y + 30, pos_x - 8, pos_y + 20, pos_x + 8, pos_y + 20, al_map_rgb(255, 255, 0));
        else if (direction == 2) // right
            al_draw_filled_triangle(pos_x + 30, pos_y, pos_x + 20, pos_y - 8, pos_x + 20, pos_y + 8, al_map_rgb(255, 255, 0));
        else if (direction == 3) // left
            al_draw_filled_triangle(pos_x - 30, pos_y, pos_x - 20, pos_y - 8, pos_x - 20, pos_y + 8, al_map_rgb(255, 255, 0));
        else if (direction == 4) // upper left
            al_draw_filled_triangle(pos_x - 25, pos_y - 25, pos_x - 20, pos_y - 10, pos_x - 10, pos_y - 20, al_map_rgb(255, 255, 0));
        else if (direction == 5) // lower right
            al_draw_filled_triangle(pos_x + 25, pos_y + 25, pos_x + 20, pos_y + 10, pos_x + 10, pos_y + 20, al_map_rgb(255, 255, 0));
        else if (direction == 6) // upper right
            al_draw_filled_triangle(pos_x + 25, pos_y - 25, pos_x + 20, pos_y - 10, pos_x + 10, pos_y - 20, al_map_rgb(255, 255, 0));
        else if (direction == 7) // lower left
            al_draw_filled_triangle(pos_x - 25, pos_y + 25, pos_x - 20, pos_y + 10, pos_x - 10, pos_y + 20, al_map_rgb(255, 255, 0));

        al_flip_display();
    }

    // cleanup
    al_destroy_event_queue(event_queue);
    al_destroy_display(Screen);
    return 0;
}