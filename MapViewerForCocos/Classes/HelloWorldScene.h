#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Chip.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;
const int MAX_TIP = MAP_WIDTH * MAP_HEIGHT;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();	
	//	�A�b�v�f�[�g�֐�
	void update(float delta)override;
	//	�}�b�v��`�悷��
	void DrawMap();
	//	�ǂݍ���
	void ReadingDate(std::string fileName);

	//	�}�b�v�`�b�v
	Chip testChip;

	//	�}�b�v
	unsigned __int8  m_Map[MAP_HEIGHT][MAP_WIDTH];	//�}�b�v



    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
