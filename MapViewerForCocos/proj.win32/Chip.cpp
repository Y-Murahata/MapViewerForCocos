#include "Chip.h"

USING_NS_CC;

/// <summary>
///		�`�b�v�^�C�v�ɂ���ēǂݍ��މ摜��ς���
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
