#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

//	�c�[����
enum TOOLS
{
	PENCIL,
	SQUARE,

};

class Chip
{
public:
	Chip();		//�@�R���X�g���N�^
	~Chip();	//	�f�X�g���N�^

	void Update(int chipType , bool isClick, cocos2d::Vec2 mousePos);

	//	getter
	cocos2d::Sprite* GetSprite() { return m_image; }
	//cocos2d::ui::Button* GetSprite() { return m_image; }
	int GetType() { return m_type; }

	//	setter
	void SetType(int chipType) { m_type = chipType; }
	void SetImage();
	void ChengeImage(int chipType);


private:
	cocos2d::Sprite* m_image;	//	�`�b�v�̉摜
	//cocos2d::ui::Button* m_image;	//	�`�b�v�̉摜

	int m_type;					//	�`�b�v�̃^�C�v



};

