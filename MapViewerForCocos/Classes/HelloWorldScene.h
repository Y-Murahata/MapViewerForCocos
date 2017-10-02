#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Chip.h"
#include "Mouse.h"

//マップサイズ
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
	Chip m_Chip[MAP_HEIGHT][MAP_WIDTH];	//	マップチップ
	bool m_keyD;	//	Dキー
	bool m_keyA;	//	Aキー
	bool m_keyW;	//	Wキー
	bool m_keyS;	//	Sキー

	int m_selectedChipType;	//	現在選択されているチップタイプ
	int m_selectedTools;	//	現在選択されているツール

	cocos2d::Vec2 m_CameraShiftPos;
	cocos2d::Camera* m_pCamera;
	cocos2d::Sprite* m_pMenu;

	//	ツール
	

	//	マップ関連
	int  m_Map[MAP_HEIGHT][MAP_WIDTH];	// マップ
	int m_ReturnRecord[MAP_HEIGHT][MAP_WIDTH];// 入力履歴
	int m_BackRecord[MAP_HEIGHT][MAP_WIDTH];// 入力履歴

	//	ボタンの作成
	cocos2d::ui::Button* m_pButtonDirt;	//	土
	cocos2d::ui::Button* m_pButtonGrass;	//	原っぱ
	cocos2d::ui::Button* m_pButtonSeed;	//	草
	cocos2d::ui::Button* m_pButtonForest;	//	森
	cocos2d::ui::Button* m_pButtonMountain;	//	山
	cocos2d::ui::Button* m_pButtonDeset;	//	砂
	cocos2d::ui::Button* m_pButtonSave;	//	セーブ
	cocos2d::ui::Button* m_pButtonBack;	//	戻る
	cocos2d::ui::Button* m_pButtonReturn;	//	やり直し


	//	仮想マウス
	Mouse m_mouse;

	//	デバック情報
	cocos2d::Label* debugtext;

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
