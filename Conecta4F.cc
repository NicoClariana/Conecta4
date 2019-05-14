//si el el joc s'acosta a l'empat, es probable que per culpa de la llavor generada, tardi massa en escullir una
//columna valida i el programa peti, potser no passa, depen de la llavor aleatoria.
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

typedef vector <vector<char> > Matriu;
void tornMaquina(Matriu & mat, int torn);
void joc(int columna, Matriu &mat, int torn);
bool FinalJoc(const Matriu &mat,int torn);

bool recorrerH(const Matriu &mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: la funcio retorna un bool dient si hi ha hagut un cuatre en ratlla//
  char a;
  if (torn % 2 == 0){
    a = 'X';
  } else {
    a = 'O';
  }
  int contador = 0;
  bool cuatre_en_ratlla = false;
  for(int i = 0; i <= 5; i++){
    contador = 0;
    for(int j = 0; j <= 6; j++){
      if (mat[i][j] == a){
        contador++;
      } else {
        contador = 0;
      }
      if(contador == 4){
        cuatre_en_ratlla = true;
      }
    }
  }
  return cuatre_en_ratlla;
}

bool recorrerV(const Matriu &mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: la funcio retorna un bool dient si hi ha hagut un cuatre en ratlla//
  char a;
  if (torn % 2 == 0){
    a = 'X';
  } else {
    a = 'O';
  }
  int contador = 0;
  bool cuatre_en_ratlla = false;
  for(int i = 0 ; i <= 6 ; i++){
    contador = 0;
    for(int j = 0 ; j <= 5 ; j++){
      if (mat[j][i] == a){
        contador++;
      } else {
        contador = 0;
      }
      if(contador == 4){
        cuatre_en_ratlla = true;
      }
    }
  }
  return cuatre_en_ratlla;
}

bool recorrer_diagonal_esquerra(const Matriu &mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: la funcio retorna un bool dient si hi ha hagut un cuatre en ratlla//
  char a;
  if (torn % 2 == 0){
    a = 'X';
  } else {
    a = 'O';
  }
  bool cuatre_en_ratlla = false;
  for(int i = 3; i <= 5; i++){
    for(int j = 3; j <= 6; j++){
      if (mat[i][j] == a and mat[i-1][j-1] == a and mat[i-2][j-2] == a and mat[i-3][j-3] == a){
        cuatre_en_ratlla = true;
      }
    }
  }
  return cuatre_en_ratlla;
}

bool recorrer_diagonal_dreta(const Matriu &mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: la funcio retorna un bool dient si hi ha hagut un cuatre en ratlla//
  char a;
  if (torn % 2 == 0){
    a = 'X';
  } else {
    a = 'O';
  }
  bool cuatre_en_ratlla = false;
  for(int i = 3; i <= 5; i++){
    for(int j = 0; j <= 3; j++){
      if (mat[i][j] == a and mat[i-1][j+1] == a and mat[i-2][j+2] == a and mat[i-3][j+3] == a){
        cuatre_en_ratlla = true;
      }
    }
  }
  return cuatre_en_ratlla;
}

bool empat(const Matriu &mat){
//Pre: La funcio reb el taulell//
//Post: La funcio retorna un bool dient si el taulell esta ple de chars, si es aixi, es un empat;//
  bool empate = true;
  for(int i = 0; i < 6; i++){
    for(int j = 0; j < 7; j++){
      if(mat[i][j] == ' '){
        empate = false;
      }
    }
  }
  return empate;
}

void tornJugador( Matriu & mat, int torn){
//Pre: La funcio reb el taulell y el torn//
//Post: La funcio crida a joc passant una columna correcte//
  int columna;
  bool columnaCorrecte = false;
  while(not columnaCorrecte){
    cout << "A quina columna vols col·locar la teva fitxa (0-6)?" << endl;
    cin >> columna;
    if (columna >= 0 and columna <= 6){
      columnaCorrecte = true;
    } else {
      cout << "Columna incorrecta" << endl;
    }
  }
  joc(columna, mat, torn);
}

void joc(int columna, Matriu & mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: La funcio modifica el valor de mat[fila][columna] amb el caracter del jugador/maquina//
  int fila;
  bool ple = true;
  char o = 'O', x = 'X';
  for (int i = 5; i >= 0; i-- ){
    if(mat[i][columna] == ' '){
      fila = i;
      ple = false;
      break;
    }
  }
  if(ple){
    if(torn % 2 == 0){
      cout << "columna plena, escull un altre columna" << endl;
      tornJugador(mat, torn);
    } else {
      tornMaquina(mat, torn);
    }
  } else {
    if(torn % 2 == 0){
      mat[fila][columna] = x;
    } else {
      mat[fila][columna] = o;
    }
  }
}

void taulell(const Matriu & mat){
//Pre: La funcio reb el taulell//
//Post: La funcio retorna per pantalla el taulell//
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[0][0] << " | " << mat[0][1] << " | " << mat[0][2] << " | " << mat[0][3] << " | " << mat[0][4] << " | " << mat[0][5] << " | " << mat[0][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[1][0] << " | " << mat[1][1] << " | " << mat[1][2] << " | " << mat[1][3] << " | " << mat[1][4] << " | " << mat[1][5] << " | " << mat[1][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[2][0] << " | " << mat[2][1] << " | " << mat[2][2] << " | " << mat[2][3] << " | " << mat[2][4] << " | " << mat[2][5] << " | " << mat[2][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[3][0] << " | " << mat[3][1] << " | " << mat[3][2] << " | " << mat[3][3] << " | " << mat[3][4] << " | " << mat[3][5] << " | " << mat[3][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[4][0] << " | " << mat[4][1] << " | " << mat[4][2] << " | " << mat[4][3] << " | " << mat[4][4] << " | " << mat[4][5] << " | " << mat[4][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout << "| "  << mat[5][0] << " | " << mat[5][1] << " | " << mat[5][2] << " | " << mat[5][3] << " | " << mat[5][4] << " | " << mat[5][5] << " | " << mat[5][6] << " | " << endl;
  cout <<"−−−−−−−−−−−−−−−−−−−−−−−−−−−−−"<< endl;
  cout <<"| 0 | 1 | 2 | 3 | 4 | 5 | 6 |" << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
  cout << endl;
}

void tornMaquina(Matriu & mat, int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: La funcio crida a joc amb la columna escullida per la maquina//
  int columna;
  columna = rand()% 7;
  cout << columna << endl;
  joc(columna, mat, torn);
}

bool FinalJoc(const Matriu &mat,int torn){
//Pre: La funcio reb el taulell i el torn//
//Post: La funcio retorna un bool dient si es final de joc depenent de les diferentes crides a les funcions de recorregut//
  bool guanyaJugador = false, guanyaMaquina  = false, si_empat = false;
  bool end = false;
  if (recorrerH(mat, torn)){
    if (torn % 2 == 0){
      guanyaJugador = true;
    } else {
      guanyaMaquina = true;
    }
  } else if(recorrerV(mat, torn)){
    if (torn % 2 == 0){
      guanyaJugador = true;
    } else {
      guanyaMaquina = true;
    }
  } else if (recorrer_diagonal_dreta(mat, torn)){
    if (torn % 2 == 0){
      guanyaJugador = true;
    } else {
      guanyaMaquina = true;
    }
  } else if (recorrer_diagonal_esquerra(mat, torn)){
    if (torn % 2 == 0){
      guanyaJugador = true;
    } else {
      guanyaMaquina = true;
    }
  } else if (empat(mat)){
      si_empat = true;
  }
  if (guanyaJugador){
    cout << "Has Guanyat!" << endl;
    end = true;
  } else if (guanyaMaquina){
    cout << "Has perdut" << endl;
    end = true;
  } else if (si_empat){
    cout << "Tauler ple, aixo es un empat!" << endl;
    end = true;
  }
  return end;
}

int main(){
  srand(time(NULL));
  Matriu mat(6, vector<char>(7));
  int torn = 0;
  for (int i = 0; i <= 5; i++){
    for(int j = 0; j <= 6; j++){
      mat[i][j] = ' ';
    }
  }
  bool acabat = false;
  taulell(mat);
  while(not acabat) {
    if (torn % 2 == 0){
      tornJugador(mat, torn);
    } else {
      tornMaquina(mat, torn);
    }
    taulell(mat);
	acabat = FinalJoc(mat, torn);
    torn++;
  }
}
