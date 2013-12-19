
// C++ ALLEGRO 5 MADE EASY TUTORIAL 21~22 - ALTERNATE INDIVIDUAL SPRITE ANIMATION

// CODINGMADEEASY

#include "JSONObject.h"
#include <allegro5\allegro5.h> 
#include <allegro5\allegro_native_dialog.h> 
#include <allegro5\allegro_image.h>
#include "SpriteUtil.h"

#define ScreenWidth 800 
#define ScreenHeight 600

int main22() {

	ALLEGRO_DISPLAY *display;

	enum Direction { DOWN, LEFT, RIGHT, UP };

	const float FPS = 60.0;
	const float frameFPS = 15.0;

	if(!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 

	display = al_create_display(ScreenWidth, ScreenHeight);

	if(!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true, active = false;
	float x = 10, y = 10, moveSpeed = 5;
	int dir = DOWN; 

	int imageNumber = -1; 
	bool startAnimation = false;

	al_install_keyboard();
	al_init_image_addon();

	SpriteSeq iorySpriteSeq = SpriteUtil::process("iory-yagami.png", al_map_rgba(255, 0, 0, 255));

	ALLEGRO_KEYBOARD_STATE keyState;

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / FPS);
	ALLEGRO_TIMER *frameTimer = al_create_timer(1.0 / frameFPS);

	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_timer_event_source(frameTimer));
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	al_start_timer(timer);
	al_start_timer(frameTimer);
	
	Sprite * sprite = NULL;

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);
		al_get_keyboard_state(&keyState);

		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		
			done = true;
			
		} else if (events.type == ALLEGRO_EVENT_TIMER) {
		
			if (events.timer.source == timer) {

				active = true;
				if(al_key_down(&keyState, ALLEGRO_KEY_DOWN))
				{
					y += moveSpeed; 
					dir = DOWN;
				}
				else if(al_key_down(&keyState, ALLEGRO_KEY_UP))
				{
					y -= moveSpeed; 
					dir = UP;
				}
				else if(al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
				{
					x += moveSpeed; 
					dir = RIGHT;
				}
				else if(al_key_down(&keyState, ALLEGRO_KEY_LEFT))
				{
					x -= moveSpeed; 
					dir = LEFT;
				}
				else 
					active = false;			
					
			} else if (events.timer.source == frameTimer) {
			
				if (al_key_down(&keyState, ALLEGRO_KEY_A))
					startAnimation = !startAnimation;
				
			
				if (startAnimation) {
				
					if (iorySpriteSeq.hasNext()) {
					
						sprite = &(iorySpriteSeq.next());
						
					} else {
					
						iorySpriteSeq.reset();
					}
						
				} else {
				
					iorySpriteSeq.reset();
				}
			}
			
			draw = true;
		}

		if(draw)
		{
			if (startAnimation) {
				
				//al_draw_bitmap_region(sprite->getBitmap(), sprite->x, sprite->y, sprite->width, sprite->height, x, y, NULL);
			}
				
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_timer(frameTimer);
	al_destroy_bitmap(sprite->getBitmap());
	al_destroy_event_queue(event_queue);
	
	return 0;
}