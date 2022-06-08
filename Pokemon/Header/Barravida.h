class Barravida : public Object
{
private:
    int vida;
    int vida_max;
    BITMAP *bar;
    int cont;
    int color; //color de la barra de vida

public:
    Barravida();
    ~Barravida();
    void Decreser(int damage);
    bool AnimateDecrese();
    void SetVida(int vida);
    const void action();
};

Barravida::Barravida(/* args */)
{
    vida = 100;
    set_sprite("Stats");
    this->x = SCREEN_W - w;
    this->y = (SCREEN_H - h) - 72;
    bar = load_bitmap("img/Bar.bmp", NULL);
    cont = 0;
    color = 0;
}

Barravida::~Barravida()
{
}

void Barravida::Decreser(int damage)
{
    this->cont = damage;
}

const void Barravida::action()
{
    int size = (float(vida) / float(vida_max)) * 100.0f; //ancho de la barra de vida
    this->draw();
    
    stretch_blit(bar, lienzo, 0, color * 6, 18, 6, x + 76, y + 32, size, 10);

    //mostrar informacion de la vida maxima y actual
    string info_vida = std::to_string(this->vida) + "/" + std::to_string(this->vida_max);
    draw_text(lienzo, x + 10, y + 15, 0x000000, info_vida.c_str());
}

void Barravida::SetVida(int vida)
{
    this->vida = vida;
    this->vida_max = vida;
}

bool Barravida::AnimateDecrese()
{
    if (vida == 0) //evitar vida negativa
        cont = 0;

    if (this->cont > 0 and this->System_alarm[0].alarm(4) and vida > 0)
    {
        vida--;
        cont--;
    }

    if (vida > (vida_max / 2)) //vida verde
        this->color = 0;
    else if (vida < (vida_max / 4)) // vida roja
        this->color = 2;
    else
        this->color = 1; //vida amarilla

    return cont > 0;
}
