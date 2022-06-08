class Pokemon : public Object
{
private:
    int type;
    int life;
    int Atack;
public:

    string Movimientos[4];
    Pokemon(int type = 0);
    ~Pokemon();
    const void action();
    void Presentacion();
    void Enemy();
    void Aliado();
    void SetDamage(int Damage); // resiva daño

    int GetAtack() { return Atack; };
    int GetLife() { return life; };
};

Pokemon::Pokemon(int type)
{
    this->type = type;
    type == 0 ? this->set_sprite("Pokemones") : this->set_sprite("Pokemones_back");
    this->w = 112;
    this->h = 112;
    this->x = SCREEN_W + 124;
    this->y = 124;
    this->index = 2;
    this->seccion = 4;
    this->life = 100;
    this->Atack = 5;

    Movimientos[0] = "Golpe";
    Movimientos[1] = "Gruñido";
    Movimientos[2] = "Rayo solar";
    Movimientos[3] = "latigo";

}

Pokemon::~Pokemon()
{
}

const void Pokemon::action()
{
    if (type == 0)
        Enemy();
    else
    {
        Aliado();
    }

    this->animated(0);
}

void Pokemon::Presentacion()
{
    if (this->x > SCREEN_W - 204)
        x -= 3;
}

void Pokemon::Aliado()
{
    this->x = (SCREEN_W / 2) - (w);
    this->y = SCREEN_H - 180;
}

void Pokemon::Enemy()
{
    this->Presentacion();
}

void Pokemon::SetDamage(int Damage)
{
    this->life -= Damage;
}