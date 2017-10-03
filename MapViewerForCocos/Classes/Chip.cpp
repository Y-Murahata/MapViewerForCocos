#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

void Chip::Update(int chipType,bool isClick, Vec2 mousePos, int selectedTool)
{
	//	�N���b�N����Ă��鎞
	if (isClick == true)
	{
		//	���M�c�[���̂Ƃ�
		if (selectedTool == TOOLS::PENCIL)
		{
			//	�}�b�v�`�b�v�̓����蔻����擾
			Rect boxRect = m_image->getBoundingBox();
			//	�q�b�g���Ă��邩����
			bool hit = boxRect.containsPoint(mousePos);
			//	�q�b�g���Ă�����
			if (hit)
			{
				ChengeImage(chipType);
			}
		}
		
	}
}

/// <summary>
///		�`�b�v�^�C�v�ɂ���ēǂݍ��މ摜��ς���
/// </summary>
void Chip::SetImage()
{
	switch (m_type)
	{
	case 0:
		m_image = Sprite::create("Dirt.png");
		break;
	case 1:
		m_image = Sprite::create("Grass.png");
		break;
	case 2:
		m_image = Sprite::create("Seed.png");
		break;
	case 3:
		m_image = Sprite::create("Forest.png");
		break;
	case 4:
		m_image = Sprite::create("Mountain.png");
	case 5:
		m_image = Sprite::create("Desert.png");
		break;
	}
}

/// <summary>
///		�`�b�v�^�C�v�ɂ���ēǂݍ��މ摜��ς���
/// </summary>
void Chip::ChengeImage(int chipType)
{
		//	�`�b�v�^�C�v�̍X�V
		m_type = chipType;

		switch (m_type)
		{
		case 0:
			m_image->setTexture("Dirt.png");
			break;
		case 1:
			m_image->setTexture("Grass.png");
			break;
		case 2:
			m_image->setTexture("Seed.png");
			break;
		case 3:
			m_image->setTexture("Forest.png");
			break;
		case 4:
			m_image->setTexture("Mountain.png");
			break;
		case 5:
			m_image->setTexture("Desert.png");
			break;
		}

		m_type = chipType;
}

