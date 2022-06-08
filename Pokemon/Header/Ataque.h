class Ataque : public Object
{
private:
    
public:
    Ataque();
    ~Ataque();
    const void action(){};
    int Atack(Pokemon* Figth, Pokemon* Defense);
};

Ataque::Ataque(/* args */)
{
    
}

Ataque::~Ataque()
{

}

int Ataque::Atack(Pokemon* Figth, Pokemon* Defense){
    Defense->SetDamage(Figth->GetAtack());
    return Figth->GetAtack();
}