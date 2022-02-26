#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>


#define PADDLE_WIDTH 10
#define PADDLE_HEIGHT 140
#define PADDLE_SPEED 200
#define PADDLE_COLOR (Color) { 50, 100, 50, 255 }  // { 100, 20, 75, 255 }

struct Paddle {
	Vector2 pos;
};

struct Paddle *PaddleNew(Vector2 position);
void PaddleDel(struct Paddle *paddle);

void PaddleUpdate(struct Paddle *paddle, float input, float deltaTime);
void PaddleRender(struct Paddle *paddle);
