#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

void Chip::Update(int chipType,bool isClick, Vec2 mousePos, int selectedTool)
{
	//	クリックされている時
	if (isClick == true)
	{
		//	鉛筆ツールのとき
		if (selectedTool == TOOLS::PENCIL)
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
}

/// <summary>
///		チップタイプによって読み込む画像を変える
/// </summary>
void Chip::SetImage()
{
	switch (m_type)
	{
	case 0:
		m_image = Sprite::create("Dirt.png");
		break;
	case 1:
		m_image = Sprite::create("Grass.png");
		break;
	case 2:
		m_image = Sprite::create("Seed.png");
		break;
	case 3:
		m_image = Sprite::create("Forest.png");
		break;
	case 4:
		m_image = Sprite::create("Mountain.png");
	case 5:
		m_image = Sprite::create("Desert.png");
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
			m_image->setTexture("Grass.png");
			break;
		case 2:
			m_image->setTexture("Seed.png");
			break;
		case 3:
			m_image->setTexture("Forest.png");
			break;
		case 4:
			m_image->setTexture("Mountain.png");
			break;
		case 5:
			m_image->setTexture("Desert.png");
			break;
		}

		m_type = chipType;
}

