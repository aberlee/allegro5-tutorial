// C++ ALLEGRO 5 MADE EASY TUTORIAL 6 - DRAWING PRIMITIVES
// CODINGMADEEASY

#include<allegro5/allegro.h> 
#include<allegro5/allegro_native_dialog.h> 
#include<allegro5/allegro_primitives.h>

#include <Box2D/Box2D.h>

#define ScreenWidth 800 
#define ScreenHeight 600


// convert screen (pixel) coordinates to box2d world coordinates
float px2m(float screenPos)
{
	return (screenPos * 0.01666f);
}

// convert box2d coordinates to screen (pixel) coordinates
float m2px(float worldPos)
{
	return (worldPos * 60.0f);
}

int main5()
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
	
	al_init_primitives_addon();

	ALLEGRO_COLOR electricBlue = al_map_rgb(44, 117, 255);

	al_draw_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);
	//al_draw_filled_triangle(10, 10, 20, 10, 25, 50, al_map_rgb(255, 0, 0), 1.0);

	al_draw_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);
	//al_draw_filled_rounded_rectangle(10, 10, 100, 100, 5, 5, al_map_rgb(0, 255, 0), 3);

	al_draw_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);
	//al_draw_filled_rectangle(400, 400, 450, 500, al_map_rgb(255, 98, 100), 9.0);

	al_draw_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0), 3.0);
	al_draw_filled_circle(ScreenWidth / 2, ScreenHeight / 2, 10, al_map_rgb(255, 255, 0));

	al_draw_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);
	//al_draw_filled_ellipse(ScreenWidth / 2, ScreenHeight - 100, 10, 5, al_map_rgb(255, 0, 255), 4.0);

	al_draw_arc(10, ScreenHeight - 100, 10, 0, 4.0, al_map_rgb(255, 0, 0), 2.0);

	al_draw_line(100, 500, 300, 500, electricBlue, 6.0);

	al_draw_pixel(500, 500, electricBlue);
	
	float points[8] = { 0, 0, 400, 100, 50, 200, ScreenWidth, ScreenHeight };

	al_draw_spline(points, electricBlue, 4.0);

	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	////////////////////////////////////////////////////// 
	//////////////////////////////////////////////////////
	
	// Define the gravity vector.
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	b2World world(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, px2m(ScreenHeight));
	b2Body* body = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;
	
	fixtureDef.restitution = 0.6f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	// This is our little game loop.
	for (int32 i = 0; i < 200; ++i) {	
	
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();

		printf("%d: %4.2f %4fpx %4.2f %4fpx\n ", i, position.x, m2px(position.x), position.y, m2px(position.y));
		
		al_draw_ellipse(0, 0, 4, 4, al_map_rgb(255, 0, 0), 4.0);
		al_draw_ellipse(400, 400, 4, 4, al_map_rgb(0, 0, 255), 4.0);
		
		al_draw_filled_circle(m2px(position.x), ScreenHeight - m2px(position.y), 10, al_map_rgb(255, 255, 0));
		
		al_rest(0.02);
		
		al_flip_display();
		al_clear_to_color(al_map_rgb(0, 0, 0));
	}

	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	////////////////////////////////////////////////////// 
	//////////////////////////////////////////////////////
	
	al_rest(25.0);
	al_destroy_display(display);

	return 0;
}
