#pragma once

#include "SDL.h"
#include <iostream>
#include "Commons.h"
#include<string>

using namespace std;

class Texture2D;


class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D startPosition);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	void SetPosition(Vector2D newPosition);
	Vector2D GetPosition();


protected:
	SDL_Renderer* mRenderer;
	Vector2D mPosition;
	Texture2D* mTexture;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);

	virtual void AddGravity(float deltaTime);
	bool mJumping;
	bool mCanJump;
	float mJumpForce;
	void Jump();

	FACING mFacingDirection;

	bool mMovingLeft;
	bool mMovingRight;

};