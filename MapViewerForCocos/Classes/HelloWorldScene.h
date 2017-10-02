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
	//	関数==============
    virtual bool init();	
	void update(float delta)override;													//	アップデート関数
	void ReadingDate(std::string fileName);												//	読み込み

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	//	キーボードが押された時
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);	//	キーボードが離された時

	bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
	void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	void reverse(Chip array[][MAP_WIDTH], int w, int h);								//	投げた配列の順序を逆にする（Chip）
	void reverse(int array[][MAP_WIDTH], int w, int h);									//	投げた配列の順序を逆にする（int）
	void OutPutCsv();																	//	csv形式で吐き出す
	void CreateUI();																	//	UI関係の作成
	void CameraUpdate();																//	メインカメラのアプデート


	//	変数==============
	Chip testChip[MAP_HEIGHT][MAP_WIDTH];	//	マップチップ
	bool m_keyD;	//	Dキー
	bool m_keyA;	//	Aキー
	bool m_keyW;	//	Wキー
	bool m_keyS;	//	Sキー

	int m_selectedChipType;	//	現在選択されているチップタイプ

	cocos2d::Camera* m_pCamera;
	cocos2d::Sprite* m_pMenu;

	//	マップ
	int  m_Map[MAP_HEIGHT][MAP_WIDTH];	//マップ

	//	ボタンの作成
	cocos2d::ui::Button* m_pButtonDirt;
	cocos2d::ui::Button* m_pButtonTree;
	cocos2d::ui::Button* m_pButtonSave;

	//	仮想マウス
	Mouse m_mouse;

	//	デバック情報
	cocos2d::Label* debugtext;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
