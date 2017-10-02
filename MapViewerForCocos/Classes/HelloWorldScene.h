#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Chip.h"
#include "Mouse.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;
const int MAX_TIP = MAP_WIDTH * MAP_HEIGHT;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	//	�֐�==============
    virtual bool init();	
	void update(float delta)override;													//	�A�b�v�f�[�g�֐�
	void ReadingDate(std::string fileName);												//	�ǂݍ���

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	//	�L�[�{�[�h�������ꂽ��
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	//	�L�[�{�[�h�������ꂽ��

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void reverse(Chip array[][MAP_WIDTH], int w, int h);								//	�������z��̏������t�ɂ���iChip�j
	void reverse(int array[][MAP_WIDTH], int w, int h);									//	�������z��̏������t�ɂ���iint�j
	void OutPutCsv();																	//	csv�`���œf���o��
	void CreateUI();																	//	UI�֌W�̍쐬
	void CameraUpdate();																//	���C���J�����̃A�v�f�[�g


	//	�ϐ�==============
	Chip testChip[MAP_HEIGHT][MAP_WIDTH];	//	�}�b�v�`�b�v
	bool m_keyD;	//	D�L�[
	bool m_keyA;	//	A�L�[
	bool m_keyW;	//	W�L�[
	bool m_keyS;	//	S�L�[

	int m_selectedChipType;	//	���ݑI������Ă���`�b�v�^�C�v

	cocos2d::Camera* m_pCamera;
	cocos2d::Sprite* m_pMenu;

	//	�}�b�v
	int  m_Map[MAP_HEIGHT][MAP_WIDTH];	//�}�b�v

	//	�{�^���̍쐬
	cocos2d::ui::Button* m_pButtonDirt;
	cocos2d::ui::Button* m_pButtonTree;
	cocos2d::ui::Button* m_pButtonSave;

	//	���z�}�E�X
	Mouse m_mouse;

	//	�f�o�b�N���
	cocos2d::Label* debugtext;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
