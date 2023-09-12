#include "Score.h"
#include <stdio.h>

void Score::Initialize() {
	// ワールドトランスフォーム初期化
	score_.wldTForm_.Initialize();
	playerVal_.wldTForm_.Initialize();
	// スプライトデータ null 代入
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] = nullptr;
		}
	};
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			spritePVal2DNum_[i][j] = nullptr;
		}
	};

	// スコア初期化
	score_.val_ = 0;
	playerVal_.val_ = 1;
	//  テクスチャ読み込み
	uint32_t textureNum[10] = {
	    TextureManager::Load("num/0.png"), TextureManager::Load("num/1.png"),
	    TextureManager::Load("num/2.png"), TextureManager::Load("num/3.png"),
	    TextureManager::Load("num/4.png"), TextureManager::Load("num/5.png"),
	    TextureManager::Load("num/6.png"), TextureManager::Load("num/7.png"),
	    TextureManager::Load("num/8.png"), TextureManager::Load("num/9.png"),
	};
	uint32_t textureSNum[10] = {
	    TextureManager::Load("num/s0.png"), TextureManager::Load("num/s1.png"),
	    TextureManager::Load("num/s2.png"), TextureManager::Load("num/s3.png"),
	    TextureManager::Load("num/s4.png"), TextureManager::Load("num/s5.png"),
	    TextureManager::Load("num/s6.png"), TextureManager::Load("num/s7.png"),
	    TextureManager::Load("num/s8.png"), TextureManager::Load("num/s9.png"),
	};
	// 数値格納用変数初期化
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j] =
			    Sprite::Create(textureNum[j], {0, 0}, {1, 1, 1, 1}, {(1.0f), (0.5f)});
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			spritePVal2DNum_[i][j] =
			    Sprite::Create(textureSNum[j], {0, 0}, {1, 1, 1, 1}, {(1.0f), (0.5f)});
		}
	}
}

void Score::Draw(int score) {
	// wldTForm の値にスコア描画位置を調整
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			sprite2DNum_[i][j]->SetPosition(
			    {score_.wldTForm_.translation_.x - (50 * i), score_.wldTForm_.translation_.y});
		}
	}
	// 数字1文字分割
	// 分割した文字を1文字づつ格納
	int nums[6];
	// 分割処理用右辺数値格納
	int division = 0;
	for (int i = 0; i < 6; i++) {
		if (i == 0) {
			// 0の数は 桁数 - 1 記入例：6桁の場合 100000（０が5個）
			division = 100000;
		}
		// 1文字分割処理
		nums[i] = score / division;
		score -= nums[i] * division;
		division /= 10;
	}
	// 描画
	sprite2DNum_[0][nums[5]]->Draw();
	sprite2DNum_[1][nums[4]]->Draw();
	sprite2DNum_[2][nums[3]]->Draw();
	sprite2DNum_[3][nums[2]]->Draw();
	sprite2DNum_[4][nums[1]]->Draw();
	sprite2DNum_[5][nums[0]]->Draw();
}

void Score::DrawPVal(int val) {
	// wldTForm の値にスコア描画位置を調整
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			spritePVal2DNum_[i][j]->SetPosition(
			    {playerVal_.wldTForm_.translation_.x - (13 * i), playerVal_.wldTForm_.translation_.y});
		}
	}
	// 数字1文字分割
	// 分割した文字を1文字づつ格納
	int nums[3];
	// 分割処理用右辺数値格納
	int division = 0;
	for (int i = 0; i < 3; i++) {
		if (i == 0) {
			// 0の数は 桁数 - 1 記入例：6桁の場合 100000（０が5個）
			division = 100;
		}
		// 1文字分割処理
		nums[i] = val / division;
		val -= nums[i] * division;
		division /= 10;
	}
	// 描画
	spritePVal2DNum_[0][nums[2]]->Draw();
	spritePVal2DNum_[1][nums[1]]->Draw();
	spritePVal2DNum_[2][nums[0]]->Draw();
}

Score::~Score() {
	// 数値格納用変数削除
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 10; j++) {
			delete sprite2DNum_[i][j];
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 10; j++) {
			delete spritePVal2DNum_[i][j];
		}
	}
}
