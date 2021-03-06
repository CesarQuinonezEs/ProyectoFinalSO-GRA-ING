template <class T> int comp(T a, T b) {
	return a->depth > b->depth;
}

class Object {
	private:
		unsigned short int cont[280];
	public:
		//variables
		float x; // coordenada x
		float y; // coordenada y
		BITMAP* sprite; // imagen que se le asigna al objeto
		Alarm* System_alarm;
		int fps;		//velocidad de cambio
		int seccion;
		int w;			//ancho de frame
		int h;			//largo de frame
		int index;		//en que frame se encuentra
		int img_speed;
		char id[190];
		int depth;
		int mask_w;
		int mask_h;
		bool solid;
		string phat;
		bool Pressed[280];

		//Funcines
		Object(); // constructor
		~Object(); // destructor
		const virtual void action() = 0; // funcion virtual pura
		void draw();
		void animated(int seccion);
		bool Mouse_Pressed(int b);
		void __INit(const char* name,int x, int y, int depth, int solid,  int mask_w, int mask_h, int img_speed,const char* phat);
		void set_sprite(string phat);
		bool rect_coll(Object* obj);
		bool EndAnimation();
		bool KeyReleased(int KEY);
};
list<Object*>instancias;
list<Object*>Remove;




Object::Object() {
	this->x 		= 	0;
	this->y 		= 	0;
	this->sprite 	= 	NULL;
	System_alarm	=	new Alarm[5]();
	this->fps		=	0;						//velocidad de cambio
	this->w			=	0;						//ancho de frame
	this->h			=	0;						//largo de frame
	this->index		=	0;						//en que frame se encuentra
	this->seccion 	=	0;
	for(int i=0;i<280;i++) this->Pressed[i] = false;
	for(int i=0;i<280;i++) this->cont[i] = 0;
}


void Object::draw() {
	draw_sprite(lienzo,sprite,x,y);
}


Object::~Object() {
	destroy_bitmap(this->sprite);
	delete System_alarm;
}

void Object::animated(int seccion) {
	this->seccion = seccion;
	if(System_alarm[0].alarm(fps)) {
		index >= (sprite->w/w)-1 ? index = 0 : index++;
	}
	masked_blit(sprite,lienzo,index * w, this->seccion * h, x, y, w, h);
}


bool Object::Mouse_Pressed(int b) {
	if(mouse_b & b and Rango(x, x+w, mouse_x) and Rango(y, y+h, mouse_y))
		return true;
	else
		return false;
}

void Object::__INit(const char* name,int x, int y, int depth, int solid,  int mask_w, int mask_h, int img_speed,const char* phat) {
	this->x				=	x;
	this->y				=	y;
	this->img_speed 	= 	img_speed;
	this->sprite 		= 	load_bitmap((string("img\\") + phat + string(".bmp")).c_str(),NULL);
	strcpy(id,name);
	this->depth	 		=	 depth;
	this->mask_w  		= 	mask_w;
	this->mask_h  		= 	mask_h;
	this->w  			= 	mask_w;
	this->h  			= 	mask_h;
	this->solid 		=	solid;
	this->phat          = 	phat;
}


void Object::set_sprite(string phat) {
	if(this->sprite)	destroy_bitmap(sprite);
	
	string SPR = "img/" + phat + ".bmp";
	this->sprite = load_bitmap(SPR.c_str(),NULL);

	if(sprite) {
		this->w = this->sprite->w;
		this->h = this->sprite->h;
	} else {
		string MSG = "No se encontro " + SPR;
		allegro_message("%s",MSG.c_str());
	}
}


bool Object::rect_coll(Object* obj) {
	return Rango(x-w, x+w, obj->x) and Rango(y-w, y+h, obj->y);
}


bool Object::EndAnimation(){
	return index >= (sprite->w/w)-1;
}



bool Object::KeyReleased(int KEY)
{
	if(key[KEY] and !cont[KEY])
	{
		this->cont[KEY] = 1;
	}else
		this->Pressed[KEY] = false;	
	

	if(!key[KEY]){
		if(cont[KEY] == 1){
			this->Pressed[KEY] = true;	
		}	
		this->cont[KEY] = 0;
	}
		
	
	
	
	return false;
}









Object* whit(const char* name) {

	for(list<Object*>::iterator it = instancias.begin(); it != instancias.end(); it++) {
		Object *other = *it;
		if(!strcmp(other->id,name))
			return other;
	}

	return NULL;
}

