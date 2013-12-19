// C++ ALLEGRO 5 MADE EASY TUTORIAL 3 - NATIVE MESSAGE BOXES
// CODINGMADEEASY
#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 

int main2()
{
	ALLEGRO_DISPLAY *display; 

	if(al_init()) {
	
		al_show_native_message_box(NULL, NULL, "Error", "Could not initialize Allegro 5", NULL, ALLEGRO_MESSAGEBOX_OK_CANCEL | ALLEGRO_MESSAGEBOX_WARN);
	}
	
	display = al_create_display(800, 600); 

	if(!display) {
	
		al_show_native_message_box(NULL, NULL, "Error", "Could not create Allegro 5 display", NULL, ALLEGRO_MESSAGEBOX_ERROR);
	}
	
	al_destroy_display(display);

	return 0;
}