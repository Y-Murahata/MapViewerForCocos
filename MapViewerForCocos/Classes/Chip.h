#pragma once
#include "cocos2d.h"

class Chip
{
public:
	Chip();		//　コンストラクタ
	~Chip();	//	デストラクタ

	//	getter
	cocos2d::Sprite* GetSprite() { return m_image; }
	//	setter
	void SetType(int chipType) { m_type = chipType; }
	void SetImage();

private:
	cocos2d::Sprite* m_image;	//	チップの画像
	int m_type;					//	チップのタイプ



};

