// C++ ALLEGRO 5 MADE EASY TUTORIAL 27- BITMAP EFFECTS
// CODINGMADEEASY

#include<allegro5\allegro5.h> 
#include<allegro5\allegro_primitives.h>
#include<allegro5\allegro_native_dialog.h> 
#include<allegro5\allegro_image.h>
#include<allegro5\allegro_color.h>
#include "SpriteUtil.h"

enum Direction { 
	NONE,
	UP,
	UP_RIGHT,
	RIGHT,
	DOWN_RIGHT,
	DOWN,
	DOWN_LEFT,
	LEFT,
	UP_LEFT
};

#define ScreenWidth 800 
#define ScreenHeight 600

int main() {

	ALLEGRO_DISPLAY *display;

	const float FPS = 60.0;
	const float frameFPS = 15.0;

	float degrees = 0.0f;

	if (!al_init())
		al_show_native_message_box(NULL, "Error", NULL, "Could not Initialize Allegro", NULL, NULL); 

	display = al_create_display(ScreenWidth, ScreenHeight);

	if (!display)
		al_show_native_message_box(NULL, "Error", NULL, "Could not create Allegro Display", NULL, NULL);

	al_set_window_position(display, 200, 200);

	bool done = false, draw = true, active = false;
	float moveSpeed = 5;
	int dir = NONE;

	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();

	SpriteSeq iory1SpriteSeq = SpriteUtil::process("iory-yagami.png", al_map_rgba(255, 0, 0, 255));
	SpriteSeq iory2SpriteSeq = SpriteUtil::process("iory-yagami.png", al_map_rgba(255, 0, 0, 255));
	
	iory1SpriteSeq.setX(200);
	iory2SpriteSeq.setX(200);

	iory1SpriteSeq.setY(200);
	iory2SpriteSeq.setY(200);

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

	while(!done)
	{
		ALLEGRO_EVENT events; 
		al_wait_for_event(event_queue, &events);
		al_get_keyboard_state(&keyState);

		if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (events.type == ALLEGRO_EVENT_TIMER)
		{
			if (events.timer.source == timer)
			{
				dir = NONE;
				active = true;
				
				if (al_key_down(&keyState, ALLEGRO_KEY_DOWN)) {
				
					iory1SpriteSeq.incY(moveSpeed);
					
					if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
					{
						iory1SpriteSeq.incX(moveSpeed);
						dir = DOWN_RIGHT;
						
					} else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
					
						iory1SpriteSeq.decX(moveSpeed);
						dir = DOWN_LEFT;
					}
					
				} else if (al_key_down(&keyState, ALLEGRO_KEY_UP)) {
				
					iory1SpriteSeq.decY(moveSpeed);
					
					if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
					
						iory1SpriteSeq.incX(moveSpeed);
						dir = UP_RIGHT;

					} else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {

						iory1SpriteSeq.decX(moveSpeed);
						dir = UP_LEFT;
					}
				
				} else if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT)) {
				
					iory1SpriteSeq.incX(moveSpeed);
					dir = RIGHT;
					
				} else if (al_key_down(&keyState, ALLEGRO_KEY_LEFT)) {
				
					iory1SpriteSeq.decX(moveSpeed);
					dir = LEFT;
					
				} else {
				
					active = false;
				}

				if (al_key_down(&keyState, ALLEGRO_KEY_W))
					degrees++; 
				else if (al_key_down(&keyState, ALLEGRO_KEY_S))
					degrees--;

				if (degrees >= 360 || degrees <= -360)
					degrees = 0;
					
			} else if (events.timer.source == frameTimer) {
			
				iory1SpriteSeq.next();

				if (!iory1SpriteSeq.hasNext())
					iory1SpriteSeq.reset();
					
				iory2SpriteSeq.next();

				if (!iory2SpriteSeq.hasNext())
					iory2SpriteSeq.reset();

			}

			draw = true;
		}

		if (draw) {
		
			Sprite sprite1 = iory1SpriteSeq.current();
			Sprite sprite2 = iory2SpriteSeq.current();
			
			iory1SpriteSeq.setInFrontOf(&iory2SpriteSeq);
			iory2SpriteSeq.setInFrontOf(&iory1SpriteSeq);
			
			al_draw_bitmap(iory2SpriteSeq.getSubBitmap(), iory2SpriteSeq.getX(), iory2SpriteSeq.getY(), iory2SpriteSeq.getDrawFlags());
			al_draw_bitmap(iory1SpriteSeq.getSubBitmap(), iory1SpriteSeq.getX(), iory1SpriteSeq.getY(), iory1SpriteSeq.getDrawFlags());
			
			//al_draw_rotated_bitmap(iory1SpriteSeq.getSubBitmap(), sprite1.width/2, sprite1.height/2, iory1SpriteSeq.getX(), iory1SpriteSeq.getY(), 
			//						degrees * 3.1415 / 180, iory1SpriteSeq.getDrawFlags());
			
			//al_draw_tinted_bitmap(sprite.bitmap, al_map_rgb(255, 0, 0), x, y, NULL);
			
			//al_draw_scaled_bitmap(subBitmap, 16, 16, 16, 16, x, y, 32 * degrees, 32 * degrees, NULL);
			
			ALLEGRO_COLOR red = al_map_rgb(255,0,0);
			ALLEGRO_COLOR blue = al_map_rgb(0,0,255);

			al_draw_line(
				(float) iory1SpriteSeq.getX(), 
				(float) iory1SpriteSeq.getY() - 10.10, 
				(float) iory1SpriteSeq.getX(), 
				(float) iory1SpriteSeq.getY() - 20.0, 
				red, 
				1.0);

			al_draw_line(
				(float) iory1SpriteSeq.getCenterX(), 
				(float) iory1SpriteSeq.getY() - 30.0, 
				(float) iory1SpriteSeq.getCenterX(), 
				(float) iory1SpriteSeq.getY() - 40.0, 
				blue, 
				1.0);

			al_draw_line(
				(float) iory2SpriteSeq.getX(), 
				(float) iory2SpriteSeq.getY() - 10.10, 
				(float) iory2SpriteSeq.getX(), 
				(float) iory2SpriteSeq.getY() - 20.0, 
				red, 
				1.0);

			al_draw_line(
				(float) iory2SpriteSeq.getCenterX(), 
				(float) iory2SpriteSeq.getY() - 30.0, 
				(float) iory2SpriteSeq.getCenterX(), 
				(float) iory2SpriteSeq.getY() - 40.0, 
				blue, 
				1.0);
			
			al_flip_display();
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
	}
	
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return 0;
}