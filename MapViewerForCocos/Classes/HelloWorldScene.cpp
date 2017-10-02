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
			m_Chip[h][w].SetType(m_Map[h][w]);
			m_Chip[h][w].SetImage();
			this->addChild(m_Chip[h][w].GetSprite());
			m_Chip[h][w].GetSprite()->setAnchorPoint(Vec2(0, 0));
			m_Chip[h][w].GetSprite()->setPosition(Vec2(w * 32, h * 32));
		}
	}

	//	��������������
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_ReturnRecord[h][w] = m_Map[h][w];
			m_BackRecord[h][w] = m_Map[h][w];
		}
	}


	// UI���쐬����
	CreateUI();

	//	�I���c�[���̏�����
	m_selectedTools = TOOLS::PENCIL;
	//	�J�����̃Y�����̍��W��������
	m_CameraShiftPos = Vec2(0, 0);


	//	�f�o�b�N����
	//debugtext = Label::createWithSystemFont("NoClick!", "Arial", 48);
	//debugtext->setPosition(Point(300, 200));
	//this->addChild(debugtext);

    return true;
}

/// <summary>
/// �X�V����
/// </summary>
void HelloWorld::update(float delta)
{
	//	�J�����̍X�V
	CameraUpdate();

	//	�e��{�^������
	{
		//	�`�b�v�{�^���������ꂽ
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
		//	�Z�[�u�{�^��
		if (m_pButtonSave->isHighlighted())
		{
			reverse(m_Chip, MAP_WIDTH, MAP_HEIGHT);	//	�}�b�v�`�b�v�̏㉺���Ђ�����Ԃ�
			OutPutCsv();							//	csv�`���ŏ����o��
			reverse(m_Chip, MAP_WIDTH, MAP_HEIGHT);	//	�}�b�v�`�b�v�̏㉺���Ђ�����Ԃ�
		}
		//	�߂�{�^��
		if (m_pButtonBack->isHighlighted())
		{
			//	�S�Ẵ}�b�v�`�b�v�ɗ������㏑������
			for (int h = 0; h < MAP_HEIGHT; h++)
			{
				for (int w = 0; w < MAP_WIDTH; w++)
				{
					//	�`�b�v�摜�����ւ���
					m_Chip[h][w].ChengeImage(m_BackRecord[h][w]);
				}
			}
		}

		//	��蒼���{�^��
		if (m_pButtonReturn->isHighlighted())
		{
			//	�S�Ẵ}�b�v�`�b�v�ɗ������㏑������
			for (int h = 0; h < MAP_HEIGHT; h++)
			{
				for (int w = 0; w < MAP_WIDTH; w++)
				{
					//	�`�b�v�摜�����ւ���
					m_Chip[h][w].ChengeImage(m_ReturnRecord[h][w]);
				}
			}
		}
	}


	//	�}�b�v�`�b�v�̍X�V
	for (int h = 0; h < 20; h++)
	{
		for (int w = 0; w < 30; w++)
		{
			m_Chip[h][w].Update(m_selectedChipType,m_mouse.GetClick(),m_mouse.GetPosition());
		}
	}

	//	�f�o�b�N�\��
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
	case EventKeyboard::KeyCode::KEY_Z:
		//	�S�Ẵ}�b�v�`�b�v�ɗ������㏑������
		for (int h = 0; h < MAP_HEIGHT; h++)
		{
			for (int w = 0; w < MAP_WIDTH; w++)
			{
				//	�`�b�v�摜�����ւ���
				m_Chip[h][w].ChengeImage(m_BackRecord[h][w]);
			}
		}
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
	//	�ŐV�̃}�b�v�̏�Ԃ�ۑ�����
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_BackRecord[h][w] = m_Chip[h][w].GetType();
		}
	}


	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	�J�������Y���Ă镪�^�b�`���W�����炷
	touch_pos += m_CameraShiftPos;
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
			Rect boxRect = m_Chip[h][w].GetSprite()->getBoundingBox();
			//	�q�b�g���Ă��邩����
			bool hit = boxRect.containsPoint(touch_pos);
			//	�q�b�g���Ă�����
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
/// �����Â��Ă�����
/// </summary>
/// <param name="touch"></param>
/// <param name="unused_event"></param>
/// <returns></returns>
void HelloWorld::onTouchMoved(Touch * touch, Event * unused_event)
{
	//	�^�b�`���W���擾
	Vec2 touch_pos = touch->getLocation();
	//	�J�������Y���Ă镪�^�b�`���W�����炷
	touch_pos += m_CameraShiftPos;
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
	//	�J�������Y���Ă镪�^�b�`���W�����炷
	touch_pos += m_CameraShiftPos;
	//	���z�}�E�X�ɍ��W��n��
	m_mouse.SetPositon(touch_pos);
	//	���z�}�E�X�̃N���b�N��Ԃ��I��
	m_mouse.SetClick(false);


	//	�ŐV�̃}�b�v�̏�Ԃ�ۑ�����
	for (int h = 0; h < MAP_HEIGHT; h++)
	{
		for (int w = 0; w < MAP_WIDTH; w++)
		{
			m_ReturnRecord[h][w] = m_Chip[h][w].GetType();
		}
	}

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
			ofs << m_Chip[i][j].GetType() << ",";


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
	//	�͂����
	m_pButtonGrass = ui::Button::create("GrassIcon.png");
	m_pButtonGrass->setPosition(Vec2(910, 500));
	m_pButtonGrass->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonGrass);
	//	��
	m_pButtonSeed = ui::Button::create("TreeIcon.png");
	m_pButtonSeed->setPosition(Vec2(910, 400));
	m_pButtonSeed->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSeed);
	//	�X
	m_pButtonForest = ui::Button::create("ForestIcon.png");
	m_pButtonForest->setPosition(Vec2(910, 300));
	m_pButtonForest->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonForest);
	//	�R
	m_pButtonMountain = ui::Button::create("MountainIcon.png");
	m_pButtonMountain->setPosition(Vec2(910, 200));
	m_pButtonMountain->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonMountain);
	//	��
	m_pButtonDeset = ui::Button::create("DesertIcon.png");
	m_pButtonDeset->setPosition(Vec2(910, 100));
	m_pButtonDeset->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonDeset);
	//	�Z�[�u
	m_pButtonSave = ui::Button::create("saveButton.png");
	m_pButtonSave->setPosition(Vec2(48 / 2 + 48 * 2, 640 - 48 / 2));
	m_pButtonSave->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonSave);
	//	�߂�
	m_pButtonBack = ui::Button::create("BackButton.png");
	m_pButtonBack->setPosition(Vec2(48/2, 640-48/2));
	m_pButtonBack->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonBack);
	//	��蒼��
	m_pButtonReturn = ui::Button::create("ReturnButton.png");
	m_pButtonReturn->setPosition(Vec2(48 / 2 + 48, 640 - 48 / 2));
	m_pButtonReturn->setCameraMask((unsigned short)CameraFlag::USER1);
	this->addChild(m_pButtonReturn);




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







