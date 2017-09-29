#include "Chip.h"

USING_NS_CC;


Chip::Chip()
{
}


Chip::~Chip()
{
}

void Chip::Update(int chipType)
{
	//	���g�������ꂽ��
	if (m_image->isHighlighted())
	{
		//	���݂̃`�b�v�^�C�v�ƈ���Ă�����
		if (m_type != chipType)
		{
			//	�`�b�v�^�C�v�̍X�V
			m_type = chipType;

			switch (m_type)
			{
			case 0:
				//m_image = Sprite::create("facebook.png");
				m_image->loadTextureNormal("Dirt.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 1:
				//m_image = Sprite::create("twitter_32.png");
				m_image->loadTextureNormal("Seed.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 2:
				//m_image = Sprite::create("google.png");
				m_image->loadTextureNormal("google.png", ui::Widget::TextureResType::LOCAL);
				break;
			case 3:
				//m_image = Sprite::create("linkedin.png");
				m_image->loadTextureNormal("linkedin.png", ui::Widget::TextureResType::LOCAL);
				break;
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
		//m_image = Sprite::create("facebook.png");
		m_image = ui::Button::create("Dirt.png");
		break;
	case 1:
		//m_image = Sprite::create("twitter_32.png");
		m_image = ui::Button::create("Seed.png");
		break;
	case 2:
		//m_image = Sprite::create("google.png");
		m_image = ui::Button::create("google.png");
		break;
	case 3:
		//m_image = Sprite::create("linkedin.png");
		m_image = ui::Button::create("linkedin.png");
		break;
	}
}

