//	2017/09/29
//	疑似マウスを扱うクラス
//	村端優真

#include "Mouse.h"

USING_NS_CC;


Mouse::Mouse()
{
	m_position = Vec2(0, 0);
	m_isClick = false;
}


Mouse::~Mouse()
{
}

/// <summary>
/// タッチされているときのみ更新する
/// </summary>
void Mouse::Update(Vec2 position)
{

}
