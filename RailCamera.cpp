#include "RailCamera.h"
#include <ImGuiManager.h>

void RailCamera::Initialize(WorldTransform worldTransform,Vector3 radian) { 
	//ワールドトランスフォームの初期設定
	//ワールド座標設定
	worldTransform_.Initialize();
	worldTransform_ = worldTransform;
	//回転角(ラジアン)設定
	worldTransform.rotation_ = radian;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	//ワールドトランスフォームの座標の数値を更新(移動)
	worldTransform_.translation_.x += 0;
	worldTransform_.translation_.y += 0;
	worldTransform_.translation_.z += 0;
	//ワールドトランスフォームの角度の数値を更新(回転)
	worldTransform_.rotation_.x += 0;
	worldTransform_.rotation_.y += 0;
	worldTransform_.rotation_.z += 0;
	//ワールドトランスフォームのワールド行列再計算
	worldTransform_.UpdateMatrix();
	//カメラオブジェクトのワールド行列からビュー行列を計算する
	viewProjection_.matView = Inverse(worldTransform_.matWorld_);
	//カメラの座標を画面表示する処理
	ImGui::Begin("Camera");
	//スライダーでカメラのtranslationを表示
	float sliderValueT[3] = {
	    worldTransform_.translation_.x, worldTransform_.translation_.y,
	    worldTransform_.translation_.z};
	ImGui::SliderFloat3("position", sliderValueT, -20.0f, 20.0f);
	worldTransform_.translation_ = {sliderValueT[0], sliderValueT[1], sliderValueT[2]};
	//スライダーでカメラのrotationを表示
	float sliderValueR[3] = {
	    worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	    worldTransform_.rotation_.z};
	ImGui::SliderFloat3("rotation", sliderValueR, -20.0f, 20.0f);
	worldTransform_.rotation_ = {sliderValueR[0], sliderValueR[1], sliderValueR[2]};

	ImGui::End();
}
