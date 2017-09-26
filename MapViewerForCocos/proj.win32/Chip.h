#pragma once
#include "cocos2d.h"

class Chip
{
public:
	Chip();		//　コンストラクタ
	~Chip();	//	デストラクタ

public:

	//	setter
	void SetType(int chipType) { m_type = chipType; }
	void SetSprite();

	cocos2d::Sprite* m_sprite;	//	チップの画像

private:
	int m_type;					//	チップのタイプ



};

