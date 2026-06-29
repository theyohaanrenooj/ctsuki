#include "tsuki.h"
#include "image.h"

#ifndef ENTITY_H
#define ENTITY_H

tsukiEntity tsukiCreateEntity(tsukiTexture tex,float x,float y);
void tsukiDrawEntity(tsukiEntity *entity);

#endif
