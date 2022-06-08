class Animation : public Object
{
private:
    int _x;
    int _y;
    BITMAP* Pokeball;
    int cont;
    BattleControl* control;
public:
    Animation(/* args */);
    ~Animation();
    const void action();
    
};

Animation::Animation(/* args */)
{
    this->set_sprite("Presentation");
    this->x = 130;
    this->y = SCREEN_H - sprite->h;
    this->fps = 60;
    this->w = sprite->w / 4;
    this->Pokeball = load_bitmap("img/Pokeball.bmp",NULL);
    this->_x = 130;
    this->_y = SCREEN_H - sprite->h;
    control = reinterpret_cast<BattleControl*>(whit("BattleControl"));
    Pokemon* pk = new Pokemon();
    control->SetEnemy(pk);
    instancias.push_back(pk);
    this->cont = 0;
}

Animation::~Animation()
{
}

const void Animation::action(){

    if(this->EndAnimation()){
        this->fps = 0;
        x-=2;
        cont < 261 ? cont+=6 : cont = 0;
        rotate_sprite(lienzo,Pokeball,_x + 180,_y,ftofix(cont));
    }

    if(this->x < -210){
        control->SetAliado(new Pokemon(1));
        control->SetVisible(true);
        Remove.push_back(this);
    }
    
    this->animated(0);
}
