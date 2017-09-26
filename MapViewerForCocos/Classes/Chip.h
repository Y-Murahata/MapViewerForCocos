#pragma once
#include "cocos2d.h"

class Chip
{
public:
	Chip();		//�@�R���X�g���N�^
	~Chip();	//	�f�X�g���N�^

	//	getter
	cocos2d::Sprite* GetSprite() { return m_image; }
	//	setter
	void SetType(int chipType) { m_type = chipType; }
	void SetImage();

private:
	cocos2d::Sprite* m_image;	//	�`�b�v�̉摜
	int m_type;					//	�`�b�v�̃^�C�v



};

