#include "raylib.h"
#include "raymath.h"

#include "stdlib.h"

#include "paddle.h"


#define BALL_RADIUS 6
#define BALL_COLOR (Color) { 75, 20, 100, 255 }

#define BALL_TRAIL_NUMBER 6
#define BALL_TRAIL_COLOR (Color) { 7, 1, 10, 255 }
#define BALL_TRAIL_SEP_TIME 0.02f

struct Ball {
	Vector2 pos;
	Vector2 vel;
	float speed;

	Vector2 *trail;
	float trailTime;
};

struct Ball *BallNew(Vector2 position, float rotation, float speed);
void BallDel(struct Ball *ball);

void BallWindowCollision(struct Ball *ball, int windowWidth, int windowHeight);
void BallPaddleCollision(struct Ball *ball, struct Paddle *paddle);
void BallMove(struct Ball *ball, float deltaTime);

int BallGetWinner(struct Ball *ball);

void BallTrailUpdate(struct Ball *ball, float deltaTime);
void BallTrailRender(struct Ball *ball);

void BallUpdate(struct Ball *ball, float deltaTime);
void BallRender(struct Ball *ball);
