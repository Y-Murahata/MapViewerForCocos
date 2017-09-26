#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <fstream>

using namespace std;
USING_NS_CC;
using namespace cocostudio::timeline;

//マップサイズ



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{    
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

	//	update関数の登録
	this->scheduleUpdate();


	//	cocos2d テスト画像を表示
    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);

	//	csv 読み込み
	ReadingDate("test1.csv");

	//	マップチップの設定
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			testChip.SetType(m_Map[h][w]);
			testChip.SetImage();
			this->addChild(testChip.GetSprite());
			testChip.GetSprite()->setAnchorPoint(Vec2(0, 0));
			testChip.GetSprite()->setPosition(Vec2(w * 32, h * 32));
		}
	}

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void HelloWorld::update(float delta)
{

}

/// <summary>
///	読み込んだマップチップを表示する
/// 30 x 20 のマップ
/// </summary>
void HelloWorld::DrawMap()
{

}

/// <summary>
/// csv読み込み
/// </summary>
/// <param name="fileName"></param>
void HelloWorld::ReadingDate(string fileName)
{
	ifstream ifs(fileName);
	string str;
	int i;

	//読めなかったとき
	if (!ifs)
	{
		for (i = 0; i < MAX_TIP; i++)
		{
			m_Map[i / MAP_WIDTH][i % MAP_WIDTH] = 0;
		}
		return;
	}

	i = 0;
	while (getline(ifs, str))
	{
		string token;
		istringstream stream(str);
		//1行のうち、文字列とコンマを分解する
		while (getline(stream, token, ','))
		{
			//すべて文字列として読み込まれるため
			//数値は変換が必要
			m_Map[i / MAP_WIDTH][i % MAP_WIDTH] = atoi(token.c_str());
			i++;
		}
	}

}
