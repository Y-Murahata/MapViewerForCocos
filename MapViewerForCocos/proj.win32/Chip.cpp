#include "Chip.h"

USING_NS_CC;

/// <summary>
///		チップタイプによって読み込む画像を変える
/// </summary>
void Chip::SetSprite()
{
	switch (m_type)
	{
	default:
		m_sprite = Sprite::create("twitter_32.png");
		break;
	}
}
