#pragma once
#include "cocos2d.h"

class Chip
{
public:
	Chip();		//�@�R���X�g���N�^
	~Chip();	//	�f�X�g���N�^

public:

	//	setter
	void SetType(int chipType) { m_type = chipType; }
	void SetSprite();

	cocos2d::Sprite* m_sprite;	//	�`�b�v�̉摜

private:
	int m_type;					//	�`�b�v�̃^�C�v



};

