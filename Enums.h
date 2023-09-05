#pragma once
#include <WorldTransform.h>

// ステータス系
struct Status {
	// ワールドトランスフォーム
	WorldTransform wldTForm_;
	// 移動速度
	int moveSpeed_;
	// 生存フラグ
	int isAlive_ = true;
};
