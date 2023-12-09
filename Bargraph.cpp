#include <Arduino.h>
const int defaultpins[] = {12,13,14,15,16,17,18,19,21,22};
const int invertedpins[] = {19,18,17,16,15,14,13,12};
// const int defaultpins[] = {12,13,14,15,18,19,21,22};

// classe Bargraph
class Bargraph
{
  public:
    Bargraph();         // constructeur
    Bargraph(int[]);    // constructeur avec paramètres
    void Set(int);    
    void Clear();
    void Setmode(int);

  private:
    static const int _nbpins = 8;
	  int _usedpins[_nbpins];
    int _mode; // 0 = colonne, 1 = trait
    int _value;
};

Bargraph::Bargraph()
{
  // initialisation des attributs
  _mode = 0;
  _value = 0;
  for (int i = 0 ; i < _nbpins ; i++) 
  { // Donc j'utilise les 8 premiers GPIO disponibles dans defaultpins
    _usedpins[i] = defaultpins[i];
    pinMode(_usedpins[i],OUTPUT);
  }
}

Bargraph::Bargraph(int pins[])
{
  if (sizeof(pins) != _nbpins) // Si le tableau n'a pas 8 éléments, on ne fait rien
  {
    return;
  }
  // initialisation des attributs
  _mode = 0;
  _value = 0;
  for (int i = 0 ; i < _nbpins ; i++)
  {
    _usedpins[i] = pins[i];
    pinMode(_usedpins[i],OUTPUT);
  }
}

void Bargraph::Clear()
{
  for (int i = 0 ; i < _nbpins ; i++)
  {
    digitalWrite(_usedpins[i],LOW);
  }
}

void Bargraph::Set(int value)
{
  if (value < 0 || value > 8) // Si la valeur n'est pas entre 0 et 8, on ne fait rien
  {
    return;
  }
  _value = value;
  if (_mode == 0) // Mode colonne
  {
    for (int i = 0 ; i < _nbpins ; i++)
    {
      Serial.println(i);
      Serial.println(_usedpins[i]);
      if (i < _value)
      {
        digitalWrite(_usedpins[i],HIGH);
      }
      else
      {
        digitalWrite(_usedpins[i],LOW);
      }
    }
  }
  else // Mode trait
  {
    for (int i = 0 ; i < _nbpins ; i++)
    {
      if (i == _value)
      {
        digitalWrite(_usedpins[i],HIGH);
      }
      else
      {
        digitalWrite(_usedpins[i],LOW);
      }
    }
  }
}

void Bargraph::Setmode(int mode)
{
  if (mode != 0 && mode != 1) // Si le mode n'est pas 0 ou 1, on ne fait rien
  {
    return;
  }
  _mode = mode;
}

// instancion d'un objet bargraph
Bargraph mybargraph;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello World!");
}

void loop() {
  // test de la classe
  // affichage de valeurs de 0 à 8
  for (int i = 0 ; i <= 8 ; i++)
  {
    mybargraph.Set(i);
    delay(400);
  }

  // RAZ
  mybargraph.Clear();
  // changement de mode
  mybargraph.Setmode(1);
  // affichage de valeurs de 0 à 8
  for (int i = 0 ; i <= 8 ; i++)
  {
    mybargraph.Set(i);
    delay(400);
  }
  mybargraph.Clear();
  mybargraph.Setmode(0);
}
