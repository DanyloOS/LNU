#include <iostream>
#include <string>

using namespace std;


class Weapon
{
public:
    virtual void Use() = 0;
    virtual ~Weapon();
};

class Pistol : public Weapon
{
public:
    void Use() override
    {
        cout << "BANG!" << endl;
    }

    ~Pistol() override;
};

class AutomaticPistol : public Pistol
{
public:
    void Use() override
    {
        cout << "BANG! BANG! BANG!" << endl;
    }

    ~AutomaticPistol() override;
};

class Bazooka :public Weapon
{
public:
    void Use() override
    {
        cout << "BADABUB!!!" << endl;
    }

    ~Bazooka() override;
};

class Knife :public Weapon
{
public:
    void Use() override
    {
        cout << "VJUH!!!" << endl;
    }

    ~Knife() override;
};

class Player
{
public:
    void Use(Weapon *weapon)
    {
        weapon->Use();
    }
};

int main()
{
    Player player;
    Weapon *weapon = nullptr;

    Pistol pistol;
    AutomaticPistol automaticPistol;
    Bazooka bazooka;
    Knife knife;

    int choice = 0;

    while (true) {
        cout << "What you want to use:\n"
                "1)Pistol\n"
                "2)AutomaticPistol\n"
                "3)Knife\n"
                "4)Bazooka\n"
                "0)Exit\n\n";
        cin >> choice;

        system("cls");

        switch(choice) {
        case 1:  weapon = &pistol; break;
        case 2:  weapon = &automaticPistol; break;
        case 3:  weapon = &knife; break;
        case 4:  weapon = &bazooka; break;
        case 0:  delete weapon; return 0;
        default: cout << "You need to choose correct weapon!\n"; weapon = nullptr;
        }
        if (weapon != nullptr) player.Use(weapon);
        cout << endl;
    }
}


Weapon::~Weapon() {}
Pistol::~Pistol() {}
AutomaticPistol::~AutomaticPistol() {}
Knife::~Knife() {}
Bazooka::~Bazooka() {}
