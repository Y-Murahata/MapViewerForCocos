#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

void Chip::Update(int chipType,bool isClick, Vec2 mousePos)
{
	//	クリックされている時
	if (isClick == true)
	{
		//	マップチップの当たり判定を取得
		Rect boxRect = m_image->getBoundingBox();
		//	ヒットしているか判定
		bool hit = boxRect.containsPoint(mousePos);
		//	ヒットしていたら
		if (hit)
		{
			ChengeImage(chipType);
		}
	}
}

/// <summary>
///		チップタイプによって読み込む画像を変える
/// </summary>
void Chip::SetImage()
{
	switch (m_type)
	{
	case 0:
		//m_image = Sprite::create("facebook.png");
		m_image = Sprite::create("Dirt.png");
		break;
	case 1:
		//m_image = Sprite::create("twitter_32.png");
		m_image = Sprite::create("Seed.png");
		break;
	case 2:
		//m_image = Sprite::create("google.png");
		m_image = Sprite::create("google.png");
		break;
	case 3:
		//m_image = Sprite::create("linkedin.png");
		m_image = Sprite::create("linkedin.png");
		break;
	}
}

/// <summary>
///		チップタイプによって読み込む画像を変える
/// </summary>
void Chip::ChengeImage(int chipType)
{
		//	チップタイプの更新
		m_type = chipType;

		switch (m_type)
		{
		case 0:
			m_image->setTexture("Dirt.png");
			break;
		case 1:
			m_image->setTexture("Seed.png");
			break;
		case 2:
			m_image->setTexture("google.png");
			break;
		case 3:
			m_image->setTexture("linkedin.png");
			break;
		}

		m_type = chipType;
}

