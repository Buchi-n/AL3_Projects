
#include "Player.h"
#include "Input.h"
#include "cassert"
#include "ImGuiManager.h"

void Player::Initialize(Model* model, uint32_t texturehandle) 
{
	assert(model);
	model_ = model;
	textureHandle_ = texturehandle;
	worldTransform_.Initialize();
	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
}

void Player::Update() 
{ 
	worldTransform_.TransferMatrix(); 
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};
	//�L�����N�^�[�̈ړ����x
	const float kCharacterSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX(���E)
	if (input_->PushKey(DIK_LEFT))
	{
		move.x -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_RIGHT))
	{
		move.x += kCharacterSpeed;
	}
	//�����������ňړ��x�N�g����ύX(�㉺)
	if (input_->PushKey(DIK_UP))
	{
		move.y -= kCharacterSpeed;
	}
	else if (input_->PushKey(DIK_DOWN))
	{
		move.y += kCharacterSpeed;
	}
	//���W�ړ�(�x�N�g���̉��Z)
	worldTransform_.translation_.x += move.x;
	worldTransform_.translation_.y += move.y;
	worldTransform_.translation_.z += move.z;

	//worldTransform_.matWorld_=
		
	const float kMoveLimitX = 10.0f;
	const float kMoveLimitY = 10.0f;

	worldTransform_.translation_.x = max(worldTransform_.translation_.x,-kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	//�s��]��
	//worldTransform_.
	
	//�L�����N�^�[�̍��W����ʕ\�����鏈��
	ImGui::Begin("player");
	float sliderValue[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("position", sliderValue, -20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValue[0], sliderValue[1], sliderValue[2]};
	ImGui::End();
}

void Player::Draw(ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}
