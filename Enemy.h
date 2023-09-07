//#pragma once
//#include "Vector2.h"
//#include "ViewProjection.h"
//#include "WorldTransform.h"
//#include <Model.h>
//#include"Sprite.h"
//#include "Enums.h"
//
//// GameSceneの前方宣言
//class GameScene;
//
//class Enemy {
//	/// <summary>
//	/// デストラクタ
//	/// </summary>
//	~Enemy();
//
//	/// <summary>
//	/// 初期化
//	/// </summary>
//	/// <param name="pos">初期座標(vector2型) 入力例{19,19}</param>
//	void initialize(Vector2 pos);
//
//	/// <summary>
//	/// 更新
//	/// </summary>
//	void Update();
//    
//	/// <summary>
//	/// 描画
//	/// </summary>
//	void Draw();
//
// 衝突を検出したら呼び出されるコールバック関数
//void OnCollision();
//bool IsDead() const { return isDead_; }
//private:
//	Status enemy_;
//	uint32_t textureHandle_;
//    
//	// HP
//	int32_t HP = 100;
//	// スプライトデータ
//	Sprite* sprite_ = nullptr;
//	// デスフラグ
//	bool isDead_ = false;
//};
