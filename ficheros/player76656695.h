#ifndef PLAYER76656695_H
#define PLAYER76656695_H

#include "environment.h"

class Player76656695{
    public:
      Player76656695(int jug);
      Environment::ActionType Think();
      void Perceive(const Environment &env);
    private:
      int jugador_;
      Environment actual_;
};
#endif
