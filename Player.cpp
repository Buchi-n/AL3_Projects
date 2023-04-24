#include "Player.h"
#include <Vector3.h>

void Player::Inisialize()
{
	input_ = Input::GetInstance(); }

void Player::Update()
{
	Vector3 move = {0, 0, 0};

	const float kCharacterSpeed = 0.2f;
	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x += kCharacterSpeed;
	}
	if (input_->PushKey)
}
