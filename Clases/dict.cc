// Només per a C++11 (cal compilar amb g++ -std=c++11)

#include <iostream>
#include <functional>     // per a hash<T>
#include <unordered_map> 
#include <unordered_set>

using namespace std;

int main() {
  
  // template <class T> struct hash
  // ja definit, per exemple, per a string
  hash<string> h_string;

  // És determinista.
  cout << h_string("hola") << endl;
  cout << h_string("hola") << endl;
  cout << endl;

  // Dispersa bé.
  cout << h_string("a") << endl;
  cout << h_string("b") << endl;
  cout << h_string("c") << endl;  
  cout << endl;

  // hash<T> també definit si T és un tipus bàsic
  hash<double> h_double;
  cout << h_double(3.1416) << endl;

  hash<int*> h_int_pt;
  int x;
  cout << h_int_pt(&x) << endl;

  cout << endl;
 
  ////////////////

  // Diccionari implementat amb taules de dispersió.
  
  unordered_map<string, double> m = {{"pressec", 2.5}, {"poma", 1.2}, {"pera", 1.4}};

  // Els parells (clau, valor> no es recorren en ordre creixent de clau!
  for (auto p : m)
    cout << p.first << " -> " << p.second << endl;
  cout << "Preu de la pera: " << m["pera"]  << endl;

  ////////////////

  // Ídem, però els parells no contenen valors, només claus.
  
  unordered_set<string> s = {"pi", "roure", "avet", "alzina"};
  for (string str : s)
    cout << str << endl;
}
