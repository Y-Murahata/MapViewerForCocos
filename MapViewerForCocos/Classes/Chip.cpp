#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

void Chip::Update(int chipType)
{
	//	自身が押された時
	if (m_image->isHighlighted())
	{
		//	現在のチップタイプと違っていたら
		if (m_type != chipType)
		{
			//	チップタイプの更新
			m_type = chipType;

			switch (m_type)
			{
			case 0:
				//m_image = Sprite::create("facebook.png");
				m_image->loadTextureNormal("Dirt.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 1:
				//m_image = Sprite::create("twitter_32.png");
				m_image->loadTextureNormal("Seed.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 2:
				//m_image = Sprite::create("google.png");
				m_image->loadTextureNormal("google.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 3:
				//m_image = Sprite::create("linkedin.png");
				m_image->loadTextureNormal("linkedin.png", ui::Widget::TextureResType::LOCAL);
				break;
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
		//m_image = Sprite::create("facebook.png");
		m_image = ui::Button::create("Dirt.png");
		break;
	case 1:
		//m_image = Sprite::create("twitter_32.png");
		m_image = ui::Button::create("Seed.png");
		break;
	case 2:
		//m_image = Sprite::create("google.png");
		m_image = ui::Button::create("google.png");
		break;
	case 3:
		//m_image = Sprite::create("linkedin.png");
		m_image = ui::Button::create("linkedin.png");
		break;
	}
}

