#include "raylib.h"
#include "raymath.h"

#include "ball.h"

#include <stdio.h>


int main(void)
{
	InitWindow(640, 460, "Pong");

	struct Ball *ball = BallNew((Vector2) { 320.0f, 230.0f }, 0.785f, 100.0f);
	
	struct Paddle *leftPad = PaddleNew((Vector2) { 20.0f, 230.0f -
		PADDLE_HEIGHT });
	struct Paddle *rightPad = PaddleNew((Vector2){ 620.0f - PADDLE_WIDTH,
		230.0f });

	float lPadInput = 0.f;
	float rPadInput = 0.f;

	int lScore = 0;
	int rScore = 0;
	char *sLScore = malloc(sizeof(char) * 3);
	char *sRScore = malloc(sizeof(char) * 3);

	int winner = 1;
	float countdown = 3.5f;
	char *countdownText = malloc(sizeof(char));

	SetTargetFPS(30);

	double new_time = GetTime();
	float dt = 0.f;
	double last_time = new_time;

	while (!WindowShouldClose()) {
		if (IsKeyDown(KEY_Q) && !IsKeyDown(KEY_A))
			lPadInput = -1.f;
		else if (IsKeyDown(KEY_A) && !IsKeyDown(KEY_Q))
			lPadInput = 1.f;
		else
			lPadInput = 0.f;
		
		if (IsKeyDown(KEY_UP) && !IsKeyDown(KEY_DOWN))
			rPadInput = -1.f;
		else if (IsKeyDown(KEY_DOWN) && !IsKeyDown(KEY_UP))
			rPadInput = 1.f;
		else
			rPadInput = 0.f;

		if (countdown < 0.f) {
			BallUpdate(ball, dt);
			PaddleUpdate(leftPad, lPadInput, dt);
			PaddleUpdate(rightPad, rPadInput, dt);

			BallPaddleCollision(ball, leftPad);
			BallPaddleCollision(ball, rightPad);
		} else {
			countdown -= dt;
		}

		winner = BallGetWinner(ball);
		if (winner != 0) {
			if (winner == 1)
				lScore++;
			else
				rScore++;

			BallDel(ball);
			ball = BallNew((Vector2) { 320.0f, 230.0f },
				(float) GetRandomValue(0, 360), 100.0f);

			countdown = 3.5f;		
		}

		BeginDrawing();
			ClearBackground(BLACK);

			BallRender(ball);

			PaddleRender(leftPad);
			PaddleRender(rightPad);

			sprintf(sLScore, "%d", lScore);
			DrawText(sLScore, 5, 5, 24, RAYWHITE);

			sprintf(sRScore, "%d", rScore);
			DrawText(sRScore, 580, 5, 24, RAYWHITE);

			if (countdown > 0) {
				sprintf(countdownText, "%d", (int)
					(countdown + 0.49f));
				DrawText(countdownText, 320, 230, 24, RAYWHITE);
			}
		EndDrawing();

		new_time = GetTime();
		dt = (float) (new_time - last_time);
		last_time = new_time;
	}

	free(sLScore);
	free(sRScore);

	free(countdownText);

	PaddleDel(leftPad);
	PaddleDel(rightPad);

	BallDel(ball);

	CloseWindow();

	return 0;
}
