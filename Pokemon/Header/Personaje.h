enum {
    WALK = 0
};


class Personaje : public Object {
	public:
		//variables
		int state;
		int dir;
		//funciones
		Personaje();
		~Personaje();
		const void action();
		void walk();
};

Personaje::Personaje() {
	this->y = 150;
	this->x = 80;
	this->fps = 3;
	this->set_sprite("SprPersonaje");
	this->w = sprite->w/3;
	this->h = sprite->h/4;
	this->state = WALK;
	this->dir = 0;
}



const void Personaje::action() {
	switch(state) {
		case WALK:
			this->walk();
			break;
	}
	animated(dir);
}


void Personaje::walk() {
	int mov_v = key[KEY_W] - key[KEY_S];
	int mov_h = key[KEY_A] - key[KEY_D];

	if(mov_v == -1) {
		y-=2;
		dir = 2;
	} else if (mov_v == 1) {
		y+=2;
		dir = 3;
	} else if (mov_h == -1) {
		x-=2;
		dir = 1;
	} else if (mov_h == 1) {
		x+=2;
		dir = 0;
	}


	if(!mov_v and !mov_h) {
		fps = 0;
		this->index = 0;
	} else {
		fps = 15;
	}


}


Personaje::~Personaje() {

}

