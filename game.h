#ifndef BARBARIA99_GAME_H
#define BARBARIA99_GAME_H

#include "global_values.h"
#include "engine/shader.h"
#include "engine/object.h"
#include "engine/camera.h"
#include "engine/gamewindow.h"
#include "game/gameobject.h"

void gameStart();

void gameBindShader(int id);

void gameResetGL();

void gameUpdate();

void gameSet2D();

void gameSet3D();

void gameFree();

#endif //BARBARIA99_GAME_H
