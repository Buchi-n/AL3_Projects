#include "RailCamera.h"


void RailCamera::Initialize(WorldTransform worldTransform) { 
	//ワールドトランスフォームの初期設定
	//ワールド座標設定
	worldTransform_.Initialize();
	worldTransform_ = worldTransform;
	//回転角(ラジアン)設定

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void RailCamera::Update() {}
