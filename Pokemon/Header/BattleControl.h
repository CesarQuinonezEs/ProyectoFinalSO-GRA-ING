enum
{
    _Aliado = 0,
    _Enemigo
};

class BattleControl : public Object
{
private:
    bool visible;
    Pokemon *pokemones[2];
    Ataque *PokemonAtack;
    BITMAP *Cursor;
    Barravida *bar[2];
    Client *cliente;
     //Server *servidor;
    int posx;
    int posy;
    int opcion;
    int turn;
    int damag;
    int sendDam;
    
public:
    BattleControl(/* args */);
    ~BattleControl();
    const void action();

    //getters
    //setters
    //int getID(){return id;}
    void SetEnemy(Pokemon *pokemon);
    void SetAliado(Pokemon *pokemon);
    void SetVisible(bool visible) { this->visible = visible; };
    void MoveCursor();
    void ShowAtacks();
    void AtackEnemy();
    void AtackAliade();
    void conexion();
    //v//oid SetDamag(int damage){this->damag = damage;};
    //void GetDamag(){return damag};
};

BattleControl::BattleControl(/* args */)
{
    strcpy(id, "BattleControl");
    this->set_sprite("DialogBar");
    this->h = h / 2;
    this->fps = 0;
    this->y = SCREEN_H - h;
    pokemones[0] = NULL;
    pokemones[1] = NULL;
    this->visible = false;
    PokemonAtack = new Ataque();
    Cursor = load_bitmap("img/Cursor.bmp", NULL);
    posx = 0;
    posy = 0;
    opcion = 0;
    turn = 0;
    bar[_Aliado] = new Barravida();
    bar[_Enemigo] = new Barravida;
    bar[_Enemigo]->x = 0;
    bar[_Enemigo]->y = 0;
    this->sendDam = 0;
    //cliente = new Client();
     //servidor = new Server();

}

BattleControl::~BattleControl()
{
}

const void BattleControl::action()
{

    if (this->pokemones[_Aliado])
    {
        this->pokemones[_Aliado]->action();
        this->bar[0]->action();
        this->bar[1]->action();
    }

    if (this->visible)
    {
        KeyReleased(KEY_ENTER);
        this->animated(0);
        if (!bar[_Enemigo]->AnimateDecrese() and !bar[_Aliado]->AnimateDecrese()) //si la animacion esta en ejecucion no se hace ningun movimiento
        {


            this->AtackEnemy();
            this->AtackAliade();
            this->MoveCursor();
            this->ShowAtacks();
            //this->conexion();
            //cliente->~Client();
            //servidor->~Server();

        }
        
    }
}

void BattleControl::SetEnemy(Pokemon *pokemon)
{
    this->pokemones[_Enemigo] = pokemon;
    this->bar[_Enemigo]->SetVida(pokemon->GetLife());
}

void BattleControl::SetAliado(Pokemon *pokemon)
{
    this->pokemones[_Aliado] = pokemon;
    this->bar[_Aliado]->SetVida(pokemon->GetLife());
}

void BattleControl::MoveCursor()
{

    int Positions[8][2] =
        {
            {SCREEN_W - 81, SCREEN_H - 51},  //luchar
            {SCREEN_W - 167, SCREEN_H - 51}, //mochila
            {SCREEN_W - 81, SCREEN_H - 27},  //Pokemon
            {SCREEN_W - 167, SCREEN_H - 27}, //huir

            {SCREEN_W / 2 - 81, SCREEN_H - 51},  //ataque 1
            {SCREEN_W / 2 - 280, SCREEN_H - 51}, //ataque 2
            {SCREEN_W / 2 - 81, SCREEN_H - 27},  //ataque 3
            {SCREEN_W / 2 - 280, SCREEN_H - 27}  //ataque 4
        };

    if (key[KEY_LEFT])
        posx = 1;
    if (key[KEY_RIGHT])
        posx = 0;
    if (key[KEY_UP])
        posy = 0;
    if (key[KEY_DOWN])
        posy = 2;
    if (this->Pressed[KEY_ENTER] and posx + posy == 1) //cambiar al menu de ataque
        opcion = 4;
    if (key[KEY_BACKSPACE] and opcion == 4) // entrar al menu de seleccion de accion
        opcion = 0;

    int row = opcion + posy + posx;
    draw_sprite(lienzo, Cursor, Positions[row][0], Positions[row][1]);
}

void BattleControl::ShowAtacks()
{
    int Position[4][2] =
        {
            {SCREEN_W / 2 - 81, SCREEN_H - 51},  //ataque 1
            {SCREEN_W / 2 - 280, SCREEN_H - 51}, //ataque 2
            {SCREEN_W / 2 - 81, SCREEN_H - 27},  //ataque 3
            {SCREEN_W / 2 - 280, SCREEN_H - 27}  //ataque 4
        };

    for (int i = 0; i < 4; i++) //Muestra los ataques del pokemon
    {
        draw_text(lienzo, Position[i][0] + 10, Position[i][1] + 2, 0x000000, pokemones[_Aliado]->Movimientos[i].c_str());
    }
}

void BattleControl::AtackEnemy()
{
    
    if (this->Pressed[KEY_ENTER] and opcion == 4)
    {
        int Damage = this->PokemonAtack->Atack(this->pokemones[_Aliado], this->pokemones[_Enemigo]);
       
        damag = Damage;

        bar[_Enemigo]->Decreser(Damage);
        turn = 1;
        this->conexion();
    }
}
void BattleControl::AtackAliade(){
    
    int Damage2 = sendDam;
    bar[_Aliado]->Decreser(Damage2);
    this->sendDam = 0;
}
void BattleControl::conexion(){
     this->cliente = new Client();
    //this->servidor = new Server();
    this->cliente->clientSend(damag);
    //this->servidor->ServerSend(damag);
    //this->sendDam = servidor->ServerRead();

     this->sendDam = cliente->clientRead();
     this->cliente->~Client();
     //this->servidor->~Server();
    
    this->damag = 0;

}
