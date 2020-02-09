#include <iostream>
#include <queue>
#include <map>
#include <cstdlib>

using namespace std;

typedef pair<string, int> jugador;

int main(){
	string nombre, accion;
	int n;
	map<string, int> casino;

	while(cin >> nombre >> accion){
		if(accion == "enters"){
                pair<map<string, int>::iterator, bool> p = casino.insert(jugador(nombre, 0));
                if(not p.second) cout << nombre << "is already in the casino" << endl;
        }

        else if(accion == "wins"){
            cin >> n;
            map<string, int>::iterator it = casino.find(nombre);
            if(it != casino.end()){
                it -> second += n;
            }
            else cout << nombre << "is not in the casino" << endl;
        }

        else if(accion =="leaves"){
            map<string, int>::iterator it = casino.find(nombre);
            if(it != casino.end()){
                cout << nombre << " has won" << it->second << endl;
                casino.erase(nombre);
            }
            else cout << nombre << "is not in the casino" << endl;

        }


	}

	cout << "----------" << endl;
	map<string,int>::iterator it = casino.begin();
	while(it != casino.end()) {
		cout << it->first << " is winning " << it->second << endl;
		++it;
	}
	//return 0;
}
