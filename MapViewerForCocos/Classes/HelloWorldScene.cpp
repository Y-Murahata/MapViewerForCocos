#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
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

	//	イベントリスナーを作成
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	//	コールバック関数をセット
	listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//	イベントリスナーを登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	//	csv 読み込み
	ReadingDate("test.csv");

	//	cocos2d-xは縦の表示が逆になる
	reverse(m_Map, MAP_WIDTH, MAP_HEIGHT);

	//	マップチップの設定
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			testChip[h][w].SetType(m_Map[h][w]);
			testChip[h][w].SetImage();
			this->addChild(testChip[h][w].GetSprite());
			testChip[h][w].GetSprite()->setAnchorPoint(Vec2(0, 0));
			testChip[h][w].GetSprite()->setPosition(Vec2(w * 32, h * 32));
		}
	}


	// UIを作成する
	CreateUI();

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void HelloWorld::update(float delta)
{
	//	カメラの更新
	CameraUpdate();

	{//	各種ボタン処理
		//	土ボタンが押された状況
		if (m_pButtonDirt->isHighlighted())
		{
			m_selectedChipType = 0;
		}
		if (m_pButtonTree->isHighlighted())
		{
			m_selectedChipType = 1;
		}
		if (m_pButtonSave->isHighlighted())
		{
			reverse(testChip, MAP_WIDTH, MAP_HEIGHT);	//	マップチップの上下をひっくり返す
			OutPutCsv();							//	csv形式で書き出す
			reverse(testChip, MAP_WIDTH, MAP_HEIGHT);	//	マップチップの上下をひっくり返す

		}
	}


	//	マップチップの更新
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			testChip[h][w].Update(m_selectedChipType);
		}
	}


	
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
/// <param name="fileName">読み込むファイルネーム</param>
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

/// <summary>
/// キーボードが押された時
/// </summary>
/// <param name="keyCode"></param>
/// <param name="event"></param>
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//	デフォルトカメラを取得する
	m_pCamera = getScene()->getDefaultCamera();
	//	現在のカメラ座標を取得
	Vec2 cameraPos = m_pCamera->getPosition();

	//	キーごとの処理
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_D:
		m_keyD = true;
		break;
	case EventKeyboard::KeyCode::KEY_A:
		m_keyA = true;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_keyW = true;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_keyS = true;
		break;
	}
	m_pCamera->setPosition(cameraPos);
}

/// <summary>
///		キーボードが離された時
/// </summary>
/// <param name="keyCode"></param>
/// <param name="event"></param>
void HelloWorld::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{

	//if (keyCode == EventKeyboard::KeyCode::KEY_D)
	//{
	//	m_keyD = false;
	//}
	//if (keyCode == EventKeyboard::KeyCode::KEY_A)
	//{
	//	m_keyA = false;
	//}
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_D:
		m_keyD = false;
	case EventKeyboard::KeyCode::KEY_A:
		m_keyA = false;
		break;
	case EventKeyboard::KeyCode::KEY_W:
		m_keyW = false;
		break;
	case EventKeyboard::KeyCode::KEY_S:
		m_keyS = false;
		break;
	}
}

/// <summary>
/// ２次元配列array[y][x]のyを逆順にする
/// </summary>
/// <param name="array"></param>
/// <param name="w"></param>
/// <param name="h"></param>
void HelloWorld::reverse(Chip array[][MAP_WIDTH], int w, int h)
{
	int i, j;
	Chip temp;

	for (int i = 0, j= h -1; i < j; i++,j--)
	{
		for (int n = 0; n < w; n++)
		{
			temp = array[i][n];
			array[i][n] = array[j][n];
			array[j][n] = temp;
		}

	}
}

void HelloWorld::reverse(int array[][MAP_WIDTH], int w, int h)
{
	int i, j;
	int temp;

	for (int i = 0, j = h - 1; i < j; i++, j--)
	{
		for (int n = 0; n < w; n++)
		{
			temp = array[i][n];
			array[i][n] = array[j][n];
			array[j][n] = temp;
		}

	}
}

/// <summary>
/// csv書き出し
/// </summary>
void HelloWorld::OutPutCsv()
{
	// csvの書き出し
		ofstream ofs("csvFile/MapEditor.csv", ios::trunc);//ファイルの出力ストリーム

	for (int i = 0; i < MAP_HEIGHT; i++)
	{
		for (int j = 0; j < MAP_WIDTH; j++)
		{
			int num = i*j;

			//ofs << (int)m_Map[i][j] << ",";
			ofs << testChip[i][j].GetType() << ",";


		}

		ofs << endl;

	}
}

/// <summary>
/// UI関連の作成を行う
/// </summary>
void HelloWorld::CreateUI()
{
	//	UI用カメラ
	Camera* uiCamera = Camera::create();
	uiCamera->setCameraFlag(CameraFlag::USER1);
	this->addChild(uiCamera);

	//	メニューバーの表示
	m_pMenu = Sprite::create("menubar.png");
	m_pMenu->setAnchorPoint(Vec2(0, 0));
	m_pMenu->setPosition(Vec2(960 - 100, 0));
	m_pMenu->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pMenu);

	//	ボタンを作成する
	//	土
	m_pButtonDirt = ui::Button::create("DirtIcon.png");
	m_pButtonDirt->setPosition(Vec2(910, 600));
	m_pButtonDirt->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonDirt);
	//	草
	m_pButtonTree = ui::Button::create("TreeIcon.png");
	m_pButtonTree->setPosition(Vec2(910, 500));
	m_pButtonTree->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonTree);
	//	セーブ
	m_pButtonSave = ui::Button::create("saveButton.png");
	m_pButtonSave->setPosition(Vec2(910, 32));
	m_pButtonSave->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSave);




	m_selectedChipType = 0;
}

/// <summary>
/// カメラを移動したりズームしたりする
/// </summary>
void HelloWorld::CameraUpdate()
{
	//	デフォルトカメラを取得する
	m_pCamera = getScene()->getDefaultCamera();
	//	現在のカメラ座標を取得
	Vec2 cameraPos = m_pCamera->getPosition();

	if (m_keyA)
	{
		cameraPos.x = cameraPos.x - 3;
	}
	if (m_keyD)
	{
		cameraPos.x = cameraPos.x + 3;
	}
	if (m_keyW)
	{
		cameraPos.x = cameraPos.x + 3;
	}
	if (m_keyS)
	{
		cameraPos.x = cameraPos.x + 3;
	}
	m_pCamera->setPosition(cameraPos);
}







