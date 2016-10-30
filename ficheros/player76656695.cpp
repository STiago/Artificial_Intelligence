#include <iostream>
#include <cstdlib>
#include "player76656695.h"
#include "environment.h"

using namespace std;

Player76656695::Player76656695(int jug){
    jugador_=jug;
}


void Player76656695::Perceive(const Environment & env){
    actual_=env;
}


/**
Calcula el valor heuristico de un estado de la frontera de busqueda
Devuelve: El valor heuristico asociado al estado "actual" desde el punto de vista del jugador "jug"
Parametros:
    "actual" estado que contiene el tablero a evaluar.
    "jug" indique que jugador esta pidiendo el valor heuristico.
OBSERVACION: esta parametrizacion es solo indicativa, y el alumno podra modificarla segun sus necesidades
*/
double Heuristica (const Environment & actual, int jug){
    int marcador_propio, marcador_rival;
    int valorHeuristico=0;
    int rival;

    if(jug==1)
        rival=2;
    else
        rival=1;


    if (jug==1){
        marcador_propio=actual.Marcador(1);
        marcador_rival=actual.Marcador(2);
    }
    else {
        marcador_propio=actual.Marcador(2);
        marcador_rival=actual.Marcador(1);
    }

    if (marcador_propio>marcador_rival+actual.Total_Suciedad()){
        valorHeuristico += 1000000;
    }
    else if (marcador_rival>marcador_propio+actual.Total_Suciedad()){
        valorHeuristico += -1000000;
    }

    valorHeuristico += marcador_propio-marcador_rival;

    if(!actual.a_movement_is_possible(jug)){
        valorHeuristico += -10000;
    }
    if(!actual.a_movement_is_possible(rival)){
        valorHeuristico += 10000;
    }

    return valorHeuristico;
}


/**
Esta funcion devuelve la siguiente mejor accion guiada por la heuristica usando el algoritmo minimax.
Devuelve: La siguiente accion a realizar.
Parametros:
    "actual" contiene el estado del tablero.
    "jug" indica que jugador esta pidiendo el valor heuristico.
    "limite_profundidad" establece el limite de exploracion del grafo.
OBSERVACION: esta parametrizacion es solo indicativa, y el alumno podra modificarla segun sus necesidades
*/
    double valor_max(const Environment & actual, int jug, int limite_profundidad, int profundidad, int &accion);
    double valor_min(const Environment & actual, int jug, int limite_profundidad, int profundidad);

double valor_max(const Environment & actual, int jug, int limite_profundidad, int profundidad, int &accion){
    Environment *descendientes = new Environment [4];
    int accionPrometedora=0;

    if(profundidad == limite_profundidad){

        return Heuristica(actual,jug);
    }

    double v = -10000000000;
    double aux=0;

    int sucesores = actual.GenerateNextMove(descendientes,jug);

    if(sucesores == 0){
        v = Heuristica(actual,jug);
    }

    for(int s=0; s<sucesores; s++){
        aux=valor_min(descendientes[s],jug,limite_profundidad, profundidad+1);
        if(aux > v){
            v = aux;
            accionPrometedora = descendientes[s].Last_Action(jug);
        }
    }
    accion = accionPrometedora;
    return v;
}

double valor_min(const Environment & actual, int jug, int limite_profundidad, int profundidad){
    Environment *descendientes = new Environment[4];
    int accion;
    double aux=0;
    if(profundidad == limite_profundidad){
        return Heuristica(actual,jug);
    }

    double v = 10000000000;
    int jugadorActual=0;

    if(jug == 1)
        jugadorActual=2;
    else
        jugadorActual=1;

    int sucesores = actual.GenerateNextMove(descendientes,jugadorActual);
    if(sucesores == 0){
        v = Heuristica(actual,jug);
    }

    for(int s=0; s<sucesores; s++){
       aux= valor_max(descendientes[s],jug,limite_profundidad,profundidad+1,accion);
        if(aux < v)
            v = aux;
    }

    return v;
}

Environment::ActionType MiniMax(const Environment & actual, int jug, int limite_profundidad){
  int accion, heuristicaFinalEscogida;
   heuristicaFinalEscogida = valor_max(actual,jug,limite_profundidad, 0, accion);
  return static_cast<Environment::ActionType> (accion);

}



/**
Funcion que invoca al metodo Minimax
*/
Environment::ActionType Player76656695::Think(){
    return MiniMax(actual_,jugador_,10);
}

