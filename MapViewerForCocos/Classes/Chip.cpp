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
	default:
		m_image = Sprite::create("twitter_32.png");
		break;
	}
}

