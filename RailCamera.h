#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "MathUtilitie.h"

/// <summary>
/// レールカメラ
/// </summary>
class RailCamera {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(WorldTransform worldTransform,Vector3 radian);
	
	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	ViewProjection GetViewProjection(){ return viewProjection_; }

private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;
};
