#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

/// <summary>
///		�`�b�v�^�C�v�ɂ���ēǂݍ��މ摜��ς���
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

