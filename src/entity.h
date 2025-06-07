#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "SDL.h"

class Entity {

public:
    Entity();
    ~Entity();

protected:
    virtual void update() = 0;
    virtual void render() = 0;
};

#endif