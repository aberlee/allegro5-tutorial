// C++ ALLEGRO 5 MADE EASY TUTORIAL 5 - FONT & TEXT
// CODINGMADEEASY

#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 
#include<allegro5/allegro_ttf.h> 
#include<allegro5/allegro_font.h> 
#include<allegro5/allegro_color.h> 

#define ScreenWidth 800 
#define ScreenHeight 600 

int main4()
{
	if(!al_init())
	{
		al_show_native_message_box(NULL, NULL, "Error", "Could not initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_ERROR); 
		return -1;
	}

	// You generally want to do this after you check to see if the display was created. If the display wasn't created then there's
	// no point in calling this function
	al_set_new_display_flags(ALLEGRO_WINDOWED);
	
	ALLEGRO_DISPLAY *display = display = al_create_display(ScreenWidth, ScreenHeight); 

	if(!display)
	{
		al_show_native_message_box(NULL, NULL, "Error", "Could not create Allegro 5 display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	al_set_window_position(display, 200, 100);
	al_set_window_title(display, "CodingMadeEasy");

	al_init_font_addon(); 
	al_init_ttf_addon();

	ALLEGRO_FONT *font1 = al_load_font("orbitron-black.ttf", 36, NULL); 
	ALLEGRO_FONT *font2 = al_load_font("orbitron-black.ttf", 20, NULL); 
	
	al_draw_text(font1, al_map_rgb(44, 117, 255), ScreenWidth / 2, ScreenHeight / 2, ALLEGRO_ALIGN_CENTRE, "www.thiagoh.com");
	al_draw_text(font2, al_color_name("red"), (ScreenWidth / 2) + 80, (ScreenHeight / 2) + 60, ALLEGRO_ALIGN_RIGHT, "yeah");

	al_flip_display(); 
	al_rest(5.0);

	al_destroy_font(font1);
	al_destroy_font(font2);
	al_destroy_display(display);

	return 0;
}