#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "EventListenerGesture.h"
#include <iostream>
#include <fstream>

using namespace std;
USING_NS_CC;
using namespace cocostudio::timeline;

//�}�b�v�T�C�Y



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
    

	//	update�֐��̓o�^
	this->scheduleUpdate();

	//	�C�x���g���X�i�[���쐬
	EventListenerKeyboard* keyBoardListener = EventListenerKeyboard::create();		//	�L�[�{�[�h���X�i�[
	EventListenerTouchOneByOne* tapListener = EventListenerTouchOneByOne::create();				//	�^�b�v���X�i�[
	//	�R�[���o�b�N�֐����Z�b�g
	//	�L�[�{�[�h
	keyBoardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	keyBoardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	//	�^�b�v
	tapListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	tapListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	tapListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	tapListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	//	�C�x���g���X�i�[��o�^
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyBoardListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tapListener, this);


	//	csv �ǂݍ���
	ReadingDate("test.csv");

	//	cocos2d-x�͏c�̕\�����t�ɂȂ�
	reverse(m_Map, MAP_WIDTH, MAP_HEIGHT);

	//	�}�b�v�`�b�v�̐ݒ�
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

	Sprite* testSprite = Sprite::create("linkedin.png");
	addChild(testSprite);

	Rect rect = testSprite->getBoundingBox();

	// UI���쐬����
	CreateUI();

	//	�f�o�b�N����
	debugtext = Label::createWithSystemFont("NoClick!", "Arial", 48);
	debugtext->setPosition(Point(300, 200));
	this->addChild(debugtext);

    return true;
}

/// <summary>
/// �X�V����
/// </summary>
void HelloWorld::update(float delta)
{
	//	�J�����̍X�V
	CameraUpdate();

	{//	�e��{�^������
		//	�y�{�^���������ꂽ��
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
			reverse(testChip, MAP_WIDTH, MAP_HEIGHT);	//	�}�b�v�`�b�v�̏㉺���Ђ�����Ԃ�
			OutPutCsv();							//	csv�`���ŏ����o��
			reverse(testChip, MAP_WIDTH, MAP_HEIGHT);	//	�}�b�v�`�b�v�̏㉺���Ђ�����Ԃ�

		}
	}


	//	�}�b�v�`�b�v�̍X�V
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			testChip[h][w].Update(m_selectedChipType,m_mouse.GetClick(),m_mouse.GetPosition());
		}
	}

	if (m_mouse.GetClick())
	{
		debugtext->setString("ClickNow");
	}
	else
	{
		debugtext->setString("NoClick!");
	}

	

	
}

/// <summary>
/// csv�ǂݍ���
/// </summary>
/// <param name="fileName">�ǂݍ��ރt�@�C���l�[��</param>
void HelloWorld::ReadingDate(string fileName)
{
	ifstream ifs(fileName);
	string str;
	int i;

	//�ǂ߂Ȃ������Ƃ�
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
		//1�s�̂����A������ƃR���}�𕪉�����
		while (getline(stream, token, ','))
		{
			//���ׂĕ�����Ƃ��ēǂݍ��܂�邽��
			//���l�͕ϊ����K�v
			m_Map[i / MAP_WIDTH][i % MAP_WIDTH] = atoi(token.c_str());
			i++;

		}

	}

}

/// <summary>
/// �L�[�{�[�h�������ꂽ��
/// </summary>
/// <param name="keyCode"></param>
/// <param name="event"></param>
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	//	�f�t�H���g�J�������擾����
	m_pCamera = getScene()->getDefaultCamera();
	//	���݂̃J�������W���擾
	Vec2 cameraPos = m_pCamera->getPosition();

	//	�L�[���Ƃ̏���
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
///		�L�[�{�[�h�������ꂽ��
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
/// �^�b�`���ꂽ���i�N���b�N���ꂽ���j
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
bool HelloWorld::onTouchBegan(Touch * touch, Event * unused_event)
{
	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	���z�}�E�X�ɍ��W��n��
	m_mouse.SetPositon(touch_pos);
	//	���z�}�E�X�̃N���b�N��Ԃ��I��
	m_mouse.SetClick(true);

	//	�^�b�`�����Ƃ��낪�}�b�v�`�b�v��
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			//	�}�b�v�`�b�v�̓����蔻����擾
			Rect boxRect = testChip[h][w].GetSprite()->getBoundingBox();
			//	�q�b�g���Ă��邩����
			bool hit = boxRect.containsPoint(touch_pos);
			//	�q�b�g���Ă�����
			if (hit)
			{
				testChip[h][w].ChengeImage(m_selectedChipType);
			}
		}
	}


	return true;
}

/// <summary>
/// �����Â��Ă�����
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchMoved(Touch * touch, Event * unused_event)
{
	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	���z�}�E�X�ɍ��W��n��
	m_mouse.SetPositon(touch_pos);
	//	���z�}�E�X�̃N���b�N��Ԃ��I��
	m_mouse.SetClick(true);


}

/// <summary>
///	�^�b�`�I��
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchEnded(Touch * touch, Event * unused_event)
{
	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	���z�}�E�X�ɍ��W��n��
	m_mouse.SetPositon(touch_pos);
	//	���z�}�E�X�̃N���b�N��Ԃ��I��
	m_mouse.SetClick(false);


}


/// <summary>
///	�^�b�`�L�����Z��
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchCancelled(Touch * touch, Event * unused_event)
{
	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	���z�}�E�X�ɍ��W��n��
	m_mouse.SetPositon(touch_pos);
	//	���z�}�E�X�̃N���b�N��Ԃ��I��
	m_mouse.SetClick(false);


}

/// <summary>
/// �Q�����z��array[y][x]��y���t���ɂ���
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
/// csv�����o��
/// </summary>
void HelloWorld::OutPutCsv()
{
	// csv�̏����o��
		ofstream ofs("csvFile/MapEditor.csv", ios::trunc);//�t�@�C���̏o�̓X�g���[��

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
/// UI�֘A�̍쐬���s��
/// </summary>
void HelloWorld::CreateUI()
{
	//	UI�p�J����
	Camera* uiCamera = Camera::create();
	uiCamera->setCameraFlag(CameraFlag::USER1);
	this->addChild(uiCamera);

	//	���j���[�o�[�̕\��
	m_pMenu = Sprite::create("menubar.png");
	m_pMenu->setAnchorPoint(Vec2(0, 0));
	m_pMenu->setPosition(Vec2(960 - 100, 0));
	m_pMenu->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pMenu);

	//	�{�^�����쐬����
	//	�y
	m_pButtonDirt = ui::Button::create("DirtIcon.png");
	m_pButtonDirt->setPosition(Vec2(910, 600));
	m_pButtonDirt->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonDirt);
	//	��
	m_pButtonTree = ui::Button::create("TreeIcon.png");
	m_pButtonTree->setPosition(Vec2(910, 500));
	m_pButtonTree->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonTree);
	//	�Z�[�u
	m_pButtonSave = ui::Button::create("saveButton.png");
	m_pButtonSave->setPosition(Vec2(910, 32));
	m_pButtonSave->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSave);




	m_selectedChipType = 0;
}

/// <summary>
/// �J�������ړ�������Y�[�������肷��
/// </summary>
void HelloWorld::CameraUpdate()
{
	//	�f�t�H���g�J�������擾����
	m_pCamera = getScene()->getDefaultCamera();
	//	���݂̃J�������W���擾
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







