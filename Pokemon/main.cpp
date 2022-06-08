//JUGADOR 1: SERVER
#include <allegro.h>
void init();
void deinit();
using namespace std;
BITMAP  *SCREEN;
BITMAP 	*System;
BITMAP 	*lienzo;
void 	*focus = NULL;
int WIDTH		=	640; 
int HEIGHT	= 	480; 
# include <math.h>
# include <iostream>
# include <list>
# include <sstream>
# include <time.h>
# include <stdlib.h>
# include <vector>
# include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
# include "Header/Server.h"
# include "Header/Client.h"
# include "Header/Alarm.h"
# include "Header/Functions.h"
# include "Header/Object.h"
# include "Header/Pokemon.h"
# include "Header/Personaje.h"
# include "Header/Barravida.h"
# include "Header/Ataque.h"
# include "Header/BattleControl.h"
# include "Header/Animation.h"
# define PORT 8080



volatile long speed_counter=0;

void increment_speed_counter()
{
    speed_counter++;
}
END_OF_FUNCTION(increment_speed_counter);



int main() {
	init();
	//juego
	lienzo = create_bitmap(SCREEN_W,SCREEN_H);
	System = create_bitmap(SCREEN_W,SCREEN_H);
	SCREEN = create_bitmap(SCREEN_W,SCREEN_H);
	srand(time(NULL));

	//instancias.push_back(new Personaje());
	BITMAP* background = load_bitmap("img/Tile_Batalla.bmp",NULL);
	instancias.push_back(new BattleControl());
	instancias.push_back(new Animation());
	
	
	while (!key[KEY_ESC])
	{
		draw_sprite(lienzo,background,0,0);
		if ( speed_counter > 0 )
		{			
			for(list<Object*>::iterator it = instancias.begin(); it != instancias.end();it++)
			{
				Object *other = *it;
				other->action();
			}		
			speed_counter--;
			draw_sprite(screen,lienzo,0,0);
			clear_bitmap(lienzo);
		}

		while(!Remove.empty()){
			Object *other = reinterpret_cast<Object*>(*Remove.begin());
			instancias.remove(other);
			Remove.remove(other);
			delete other;
		}
		
	}
	
	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
	if (res != 0) {
		allegro_message("%s",allegro_error);
		exit(-1);
	}

	enable_triple_buffer();
	LOCK_VARIABLE(speed_counter);
	LOCK_FUNCTION(increment_speed_counter);
	
     
    // Iniciamos el limitador de FPS  
    install_int_ex(increment_speed_counter, BPS_TO_TIMER(60));
	install_sound(DIGI_AUTODETECT  ,MIDI_NONE, NULL);
	install_timer();
	install_keyboard();
	install_mouse();
	show_mouse(screen);
	/* add other initializations here */
    set_uformat(U_ASCII);
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

