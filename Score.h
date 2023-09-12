#pragma once
#include <Enums.h>
#include <Model.h>
#include <Sprite.h>

class Score {
public:
	/// <summary>
	/// initialize
	/// </summary>
	void Initialize();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Score();

	/// <summary>
	/// スコア描画
	/// </summary>
	/// <param name="score">描画するスコア</param>
	void Draw(int score);

	void DrawPVal(int val);

	/// <summary>
	/// スコア数値セッター
	/// </summary>
	/// <param name="score">数値</param>
	void SetScore(int score) { score_.val_ = score; }

	/// <summary>
	/// スコア数値ADD
	/// </summary>
	/// <param name="score">増加させる数値</param>
	void AddScore(int score) { score_.val_ += score; }

	/// <summary>
	/// スコア数値ゲッター
	/// </summary>
	/// <returns></returns>
	int GetScore() { return score_.val_; }

	/// <summary>
	/// ポジションセッター
	/// </summary>
	/// <param name="pos">ポジション 記入例：{8,10}</param>
	void SetPos(Vector2 pos) { score_.wldTForm_.translation_ = {pos.x, pos.y}; }

	void SetPValPos(Vector2 pos) { playerVal_.wldTForm_.translation_ = {pos.x+=20, pos.y-=30}; }

private:
	// 描画時座標格納
	Status score_;
	// 描画時座標格納
	Status playerVal_;

	// 数値格納用変数（[桁数][数字数（０～９：１０個）]）
	Sprite* sprite2DNum_[6][10];
	Sprite* spritePVal2DNum_[3][10];
};