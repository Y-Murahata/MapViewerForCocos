#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

/// <summary>
///		チップタイプによって読み込む画像を変える
/// </summary>
void Chip::SetImage()
{
	switch (m_type)
	{
	case 0:
		m_image = Sprite::create("facebook.png");
		break;
	case 1:
		m_image = Sprite::create("twitter_32.png");
		break;
	case 2:
		m_image = Sprite::create("google.png");
		break;
	case 3:
		m_image = Sprite::create("linkedin.png");
		break;
	}
}

