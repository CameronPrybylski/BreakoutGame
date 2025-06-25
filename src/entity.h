#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "SDL.h"
#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "source/vbo.h"
#include "source/vao.h"
#include "source/ebo.h"
#include "source/renderer.h"
#include "source/texture.h"

class Entity {

public:
    Entity();
    ~Entity();

protected:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void cleanup() = 0;
};

#endif