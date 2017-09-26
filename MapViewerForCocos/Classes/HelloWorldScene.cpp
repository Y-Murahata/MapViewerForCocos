#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
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


	//	cocos2d �e�X�g�摜��\��
    //auto rootNode = CSLoader::createNode("MainScene.csb");

    //addChild(rootNode);

	//	csv �ǂݍ���
	ReadingDate("test1.csv");

	//	�}�b�v�`�b�v�̐ݒ�
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
/// �X�V����
/// </summary>
void HelloWorld::update(float delta)
{

}

/// <summary>
///	�ǂݍ��񂾃}�b�v�`�b�v��\������
/// 30 x 20 �̃}�b�v
/// </summary>
void HelloWorld::DrawMap()
{

}

/// <summary>
/// csv�ǂݍ���
/// </summary>
/// <param name="fileName"></param>
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
