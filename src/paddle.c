#include "paddle.h"


struct Paddle *PaddleNew(Vector2 p_Pos)
{
	struct Paddle *newPaddle = malloc(sizeof(struct Paddle));
	newPaddle->pos = p_Pos;
	return newPaddle;
}

void PaddleDel(struct Paddle *p_Pad)
{
	free(p_Pad);
}

void PaddleUpdate(struct Paddle *p_Pad, float p_Input, float p_DT)
{
	p_Pad->pos.y += p_Input * p_DT * PADDLE_SPEED;
}

void PaddleRender(struct Paddle *p_Pad)
{
	Vector2 size = { PADDLE_WIDTH, PADDLE_HEIGHT };
	DrawRectangleV(p_Pad->pos, size, PADDLE_COLOR);
}
