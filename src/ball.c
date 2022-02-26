#include "ball.h"


struct Ball *BallNew(Vector2 p_Pos, float p_Rot, float p_Speed)
{
	struct Ball *newBall = malloc(sizeof(struct Ball));

	newBall->pos = p_Pos;
	newBall->vel = Vector2Rotate((Vector2) { 1.0f, 1.0f }, p_Rot);
	newBall->speed = p_Speed;

	newBall->trail = malloc(sizeof(Vector2) * BALL_TRAIL_NUMBER);

	for (int i = 0; i < BALL_TRAIL_NUMBER; i++) {
		newBall->trail[i] = (Vector2) { -100.0f, -100.0f };
	}

	newBall->trailTime = 0.0f;

	return newBall;
}

void BallDel(struct Ball *p_Ball)
{
	free(p_Ball->trail);
	free(p_Ball);
}

void BallWindowCollision(struct Ball *p_Ball, int p_WinW, int p_WinH)
{
	/* This function resolves the colision between the ball and the edges of
	 * the screen. The top left coordinates of the screen are (0, 0).
	 */

	if (p_Ball->pos.y < BALL_RADIUS && p_Ball->vel.y < 0) {
		p_Ball->vel.y *= -1;
		p_Ball->pos.y = BALL_RADIUS;
	} else if (p_Ball->pos.y > p_WinH - BALL_RADIUS && p_Ball->vel.y > 0) {
		p_Ball->vel.y *= -1;
		p_Ball->pos.y = p_WinH - BALL_RADIUS;
	}
}

void BallPaddleCollision(struct Ball *p_Ball, struct Paddle *p_Pad)
{
	/* This function resolves the colision between the ball and the paddle.
	 */

	Vector2 padToBall = {
		p_Ball->pos.x - (p_Pad->pos.x + PADDLE_WIDTH / 2.f),
		p_Ball->pos.y - (p_Pad->pos.y + PADDLE_HEIGHT / 2.f) };
	Vector2 absPadToBall = { abs(padToBall.x), abs(padToBall.y) };

	float overlap_x = absPadToBall.x - BALL_RADIUS - (PADDLE_WIDTH / 2.f);
	if (overlap_x > 0)
		return;
	
	float overlap_y = absPadToBall.y - BALL_RADIUS - (PADDLE_HEIGHT / 2.f);
	if (overlap_y > 0)
		return;

	if (overlap_x > overlap_y) {
		if (absPadToBall.x < PADDLE_WIDTH / 2.f + BALL_RADIUS) {
			if (padToBall.x > 0 && p_Ball->vel.x < 0) {
				p_Ball->pos.x = p_Pad->pos.x + PADDLE_WIDTH + BALL_RADIUS;
				p_Ball->vel.x *= -1;
			} else if (padToBall.x < 0 && p_Ball->vel.x > 0) {
				p_Ball->pos.x = p_Pad->pos.x - BALL_RADIUS;
				p_Ball->vel.x *= -1;
			}
		}
	} else {
		if (absPadToBall.y < PADDLE_HEIGHT / 2.f + BALL_RADIUS) {
			if (padToBall.y > 0 && p_Ball->vel.y < 0) {
				p_Ball->pos.y = p_Pad->pos.y + PADDLE_HEIGHT + BALL_RADIUS;
				p_Ball->vel.y *= -1;
			} else if (padToBall.y < 0 && p_Ball->vel.y > 0) {
				p_Ball->pos.y = p_Pad->pos.y - BALL_RADIUS;
				p_Ball->vel.y *= -1;
			}
		}
	}
}

void BallMove(struct Ball *p_Ball, float p_DT)
{
	p_Ball->vel = Vector2Add(p_Ball->vel, Vector2Scale(p_Ball->vel, 0.05f * p_DT));

	Vector2 motion = Vector2Scale(p_Ball->vel, p_Ball->speed * p_DT);
	p_Ball->pos = Vector2Add(p_Ball->pos, motion);
}

int BallGetWinner(struct Ball *p_Ball)
{
	if (p_Ball->pos.x < BALL_RADIUS)
		return 2;
	else if (p_Ball->pos.x > 640 - BALL_RADIUS)
		return 1;
	else
		return 0;
}

void BallTrailUpdate(struct Ball *p_Ball, float p_DT)
{
	p_Ball->trailTime += p_DT;

	if (p_Ball->trailTime > BALL_TRAIL_SEP_TIME) {
		p_Ball->trailTime -= BALL_TRAIL_SEP_TIME;

		for (int i = 1; i < BALL_TRAIL_NUMBER; i++)
			p_Ball->trail[i - 1] = p_Ball->trail[i];

		p_Ball->trail[BALL_TRAIL_NUMBER - 1] = (Vector2) p_Ball->pos;
	}
}

void BallTrailRender(struct Ball *p_Ball)
{
	BeginBlendMode(BLEND_ADDITIVE);
	for (int i = 0; i < BALL_TRAIL_NUMBER; i++) {
		Color color = { (BALL_TRAIL_COLOR).r * i, (BALL_TRAIL_COLOR).g *
			i, (BALL_TRAIL_COLOR).b * i, 255 };
		DrawCircleV(p_Ball->trail[i], BALL_RADIUS, color);
	}
	EndBlendMode();
}

void BallUpdate(struct Ball *p_Ball, float p_DT)
{
	BallMove(p_Ball, p_DT);
	BallWindowCollision(p_Ball, 640, 460);
	BallTrailUpdate(p_Ball, p_DT);
}

void BallRender(struct Ball *p_Ball)
{
	BallTrailRender(p_Ball);
	DrawCircleV(p_Ball->pos, BALL_RADIUS, BALL_COLOR);
}
