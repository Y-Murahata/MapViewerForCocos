#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "EventListenerGesture.h"
#include <iostream>
#include <fstream>

using namespace std;
USING_NS_CC;
using namespace cocostudio::timeline;




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
	EventListenerKeyboard* keyBoardListener = EventListenerKeyboard::create();		//	キーボードリスナー
	EventListenerTouchOneByOne* tapListener = EventListenerTouchOneByOne::create();				//	タップリスナー
	//	コールバック関数をセット
	//	キーボード
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//	タップ
	tapListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	tapListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	tapListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	tapListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	//	イベントリスナーを登録
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tapListener, this);


	//	csv 読み込み
	ReadingDate("test.csv");

	//	cocos2d-xは縦の表示が逆になる
	reverse(m_Map, MAP_WIDTH, MAP_HEIGHT);

	//	マップチップの設定
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			m_Chip[h][w].SetType(m_Map[h][w]);
			m_Chip[h][w].SetImage();
			this->addChild(m_Chip[h][w].GetSprite());
			m_Chip[h][w].GetSprite()->setAnchorPoint(Vec2(0, 0));
			m_Chip[h][w].GetSprite()->setPosition(Vec2(w * 32, h * 32));
		}
	}

	//	履歴情報を初期化
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_ReturnRecord[h][w] = m_Map[h][w];
			m_BackRecord[h][w] = m_Map[h][w];
		}
	}


	// UIを作成する
	CreateUI();

	//	選択ツールの初期化
	m_selectedTools = TOOLS::PENCIL;
	//	カメラのズレ分の座標を初期化
	m_CameraShiftPos = Vec2(0, 0);


	//	デバック文字
	//debugtext = Label::createWithSystemFont("NoClick!", "Arial", 48);
	//debugtext->setPosition(Point(300, 200));
	//this->addChild(debugtext);

    return true;
}

/// <summary>
/// 更新処理
/// </summary>
void HelloWorld::update(float delta)
{
	//	カメラの更新
	CameraUpdate();

	//	各種ボタン処理
	{
		//	チップボタンが押された
		if (m_pButtonDirt->isHighlighted())
		{
			m_selectedChipType = 0;
		}
		if (m_pButtonGrass->isHighlighted())
		{
			m_selectedChipType = 1;
		}
		if (m_pButtonSeed->isHighlighted())
		{
			m_selectedChipType = 2;
		}
		if (m_pButtonForest->isHighlighted())
		{
			m_selectedChipType = 3;
		}
		if (m_pButtonMountain->isHighlighted())
		{
			m_selectedChipType = 4;
		}
		if (m_pButtonDeset->isHighlighted())
		{
			m_selectedChipType = 5;
		}
		//	セーブボタン
		if (m_pButtonSave->isHighlighted())
		{
			reverse(m_Chip, MAP_WIDTH, MAP_HEIGHT);	//	マップチップの上下をひっくり返す
			OutPutCsv();							//	csv形式で書き出す
			reverse(m_Chip, MAP_WIDTH, MAP_HEIGHT);	//	マップチップの上下をひっくり返す
		}
		//	戻るボタン
		if (m_pButtonBack->isHighlighted())
		{
			//	全てのマップチップに履歴を上書きする
			for (int h = 0; h < MAP_HEIGHT; h++)
			{
				for (int w = 0; w < MAP_WIDTH; w++)
				{
					//	チップ画像を入れ替える
					m_Chip[h][w].ChengeImage(m_BackRecord[h][w]);
				}
			}
		}

		//	やり直しボタン
		if (m_pButtonReturn->isHighlighted())
		{
			//	全てのマップチップに履歴を上書きする
			for (int h = 0; h < MAP_HEIGHT; h++)
			{
				for (int w = 0; w < MAP_WIDTH; w++)
				{
					//	チップ画像を入れ替える
					m_Chip[h][w].ChengeImage(m_ReturnRecord[h][w]);
				}
			}
		}
	}


	//	マップチップの更新
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			m_Chip[h][w].Update(m_selectedChipType,m_mouse.GetClick(),m_mouse.GetPosition());
		}
	}

	//	デバック表示
	//if (m_mouse.GetClick())
	//{
	//	debugtext->setString("ClickNow");
	//}
	//else
	//{
	//	debugtext->setString("NoClick!");
	//}

	

	
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
	case EventKeyboard::KeyCode::KEY_Z:
		//	全てのマップチップに履歴を上書きする
		for (int h = 0; h < MAP_HEIGHT; h++)
		{
			for (int w = 0; w < MAP_WIDTH; w++)
			{
				//	チップ画像を入れ替える
				m_Chip[h][w].ChengeImage(m_BackRecord[h][w]);
			}
		}
		break;
	}
	m_pCamera->setPosition(cameraPos);
}

/// <summary>
///		キーボードが離された時
/// </summary>
/// <param name="keyCode"></param>
/// <param name="event"></param>
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
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
/// タッチされた時（クリックされた時）
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
bool HelloWorld::onTouchBegan(Touch * touch, Event * unused_event)
{
	//	最新のマップの状態を保存する
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_BackRecord[h][w] = m_Chip[h][w].GetType();
		}
	}


	//	タッチ座標を取得
	Vec2 touch_pos = touch->getLocation();
	//	カメラがズレてる分タッチ座標をずらす
	touch_pos += m_CameraShiftPos;
	//	仮想マウスに座標を渡す
	m_mouse.SetPositon(touch_pos);
	//	仮想マウスのクリック状態をオン
	m_mouse.SetClick(true);

	//	タッチしたところがマップチップ上
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			//	マップチップの当たり判定を取得
			Rect boxRect = m_Chip[h][w].GetSprite()->getBoundingBox();
			//	ヒットしているか判定
			bool hit = boxRect.containsPoint(touch_pos);
			//	ヒットしていたら
			if (hit)
			{
				switch (m_selectedChipType)
				{
				case TOOLS::PENCIL:
					m_Chip[h][w].ChengeImage(m_selectedChipType);
					break;
				case TOOLS::SQUARE:
					break;
				}
			}
		}
	}


	return true;
}

/// <summary>
/// 押しつづけている状態
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchMoved(Touch * touch, Event * unused_event)
{
	//	タッチ座標を取得
	Vec2 touch_pos = touch->getLocation();
	//	カメラがズレてる分タッチ座標をずらす
	touch_pos += m_CameraShiftPos;
	//	仮想マウスに座標を渡す
	m_mouse.SetPositon(touch_pos);
	//	仮想マウスのクリック状態をオン
	m_mouse.SetClick(true);


}

/// <summary>
///	タッチ終了
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchEnded(Touch * touch, Event * unused_event)
{
	//	タッチ座標を取得
	Vec2 touch_pos = touch->getLocation();
	//	カメラがズレてる分タッチ座標をずらす
	touch_pos += m_CameraShiftPos;
	//	仮想マウスに座標を渡す
	m_mouse.SetPositon(touch_pos);
	//	仮想マウスのクリック状態をオン
	m_mouse.SetClick(false);


	//	最新のマップの状態を保存する
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_ReturnRecord[h][w] = m_Chip[h][w].GetType();
		}
	}

}


/// <summary>
///	タッチキャンセル
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchCancelled(Touch * touch, Event * unused_event)
{
	//	タッチ座標を取得
	Vec2 touch_pos = touch->getLocation();
	//	仮想マウスに座標を渡す
	m_mouse.SetPositon(touch_pos);
	//	仮想マウスのクリック状態をオン
	m_mouse.SetClick(false);


}

/// <summary>
/// ２次元配列array[y][x]のyを逆順にする
/// </summary>
/// <param name="array"></param>
/// <param name="w"></param>
/// <param name="h"></param>
void HelloWorld::reverse(Chip array[][MAP_WIDTH], int w, int h)
{
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
			ofs << m_Chip[i][j].GetType() << ",";


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
	//	はらっぱ
	m_pButtonGrass = ui::Button::create("GrassIcon.png");
	m_pButtonGrass->setPosition(Vec2(910, 500));
	m_pButtonGrass->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonGrass);
	//	草
	m_pButtonSeed = ui::Button::create("TreeIcon.png");
	m_pButtonSeed->setPosition(Vec2(910, 400));
	m_pButtonSeed->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSeed);
	//	森
	m_pButtonForest = ui::Button::create("ForestIcon.png");
	m_pButtonForest->setPosition(Vec2(910, 300));
	m_pButtonForest->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonForest);
	//	山
	m_pButtonMountain = ui::Button::create("MountainIcon.png");
	m_pButtonMountain->setPosition(Vec2(910, 200));
	m_pButtonMountain->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonMountain);
	//	砂
	m_pButtonDeset = ui::Button::create("DesertIcon.png");
	m_pButtonDeset->setPosition(Vec2(910, 100));
	m_pButtonDeset->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonDeset);
	//	セーブ
	m_pButtonSave = ui::Button::create("saveButton.png");
	m_pButtonSave->setPosition(Vec2(48 / 2 + 48 * 2, 640 - 48 / 2));
	m_pButtonSave->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSave);
	//	戻る
	m_pButtonBack = ui::Button::create("BackButton.png");
	m_pButtonBack->setPosition(Vec2(48/2, 640-48/2));
	m_pButtonBack->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonBack);
	//	やり直し
	m_pButtonReturn = ui::Button::create("ReturnButton.png");
	m_pButtonReturn->setPosition(Vec2(48 / 2 + 48, 640 - 48 / 2));
	m_pButtonReturn->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonReturn);




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
		m_CameraShiftPos.x += -3;
	}
	if (m_keyD)
	{
		cameraPos.x = cameraPos.x + 3;
		m_CameraShiftPos.x += 3;
	}
	if (m_keyW)
	{
		cameraPos.y = cameraPos.y + 3;
		m_CameraShiftPos.y += 3;
	}
	if (m_keyS)
	{
		cameraPos.y = cameraPos.y - 3;
		m_CameraShiftPos.y += -3;
	}
	m_pCamera->setPosition(cameraPos);
}







