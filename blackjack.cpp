#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>

using namespace std;

class Carte
{
private:
    string culoare;
    int valoare;

public:
    Carte(string c, int v)
    {
        culoare = c;
        valoare = v;
    }
    string getCuloare() { return culoare; }
    int getValoare() { return valoare; }
};

class Pachet
{
private:
    vector<Carte> carti;

public:
    Pachet()
    {
        vector<string> culori = {"Inima", "Romb", "Frunza", "Trefla"};
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 13; j++)
            {
                carti.push_back(Carte(culori[i], j + 1));
            }
        }
    }
    void amestecare()
    {
        mt19937 rng(random_device{}());
        shuffle(carti.begin(), carti.end(), rng);
    }
    Carte trageCarte()
    {
        Carte c = carti.back();
        carti.pop_back();
        return c;
    }
};

class Jucator
{
protected:
    string nume;
    vector<Carte> mana;

public:
    Jucator(string n)
    {
        nume = n;
    }
    void adaugaCarte(Carte c)
    {
        mana.push_back(c);
    }
    int calculeazaPuncte()
    {
        int s = 0;
        for (int i = 0; i < mana.size(); i++)
        {
            int v = mana[i].getValoare();
            if (v > 10)
                v = 10;
            else if (v == 1)
                v = 11;
            s += v;
        }
        return s;
    }
};

class Player : public Jucator
{
public:
    Player(string n) : Jucator(n) {};
    void joaca(Pachet &p)
    {
        char decizie;
        while (true)
        {
            cout << "Puncte :" << calculeazaPuncte() << "\n";
            cout << "Hit (h) sau stand (s)?";
            cin >> decizie;

            if (decizie == 'h')
            {
                adaugaCarte(p.trageCarte());
                if (calculeazaPuncte() > 21)
                {
                    cout << "Bust!\n";
                    return;
                }
                if (calculeazaPuncte() == 21)
                {
                    cout << "Blackjack!\n";
                    return;
                }
            }
            else
            {
                return;
            }
        }
    }
};

class Calculator : public Jucator
{
public:
    Calculator(string n) : Jucator(n) {};
    void joaca(Pachet &p)
    {
        while (calculeazaPuncte() < 17)
        {
            adaugaCarte(p.trageCarte());
        }
        cout << "Puncte calculator: " << calculeazaPuncte() << '\n';
    }
};

void Castigator(int x, int y)
{
    if (x <= 21 && y > 21)
        cout << "Jucatorul a castigat!";
    else if (x <= 21 && y <= 21 && x > y)
        cout << "Jucatorul a castigat!";
    else if (x <= 21 && y <= 21 && x < y)
        cout << "Dealerul a castigat!";
    else if (y <= 21 && x > 21)
        cout << "Dealerul a castigat!";
    else if (x > 21 && y > 21)
        cout << "Dealerul a castigat!";
    else if (x == y)
        cout << "Egalitate!";
}

int main()
{
    Pachet pachet;
    Player jucator("Jucator");
    Calculator pc("Dealer");

    pachet.amestecare();
    jucator.adaugaCarte(pachet.trageCarte());
    pc.adaugaCarte(pachet.trageCarte());
    jucator.adaugaCarte(pachet.trageCarte());
    pc.adaugaCarte(pachet.trageCarte());

    jucator.joaca(pachet);
    pc.joaca(pachet);

    Castigator(jucator.calculeazaPuncte(), pc.calculeazaPuncte());
};
