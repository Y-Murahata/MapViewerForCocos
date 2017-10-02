#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"


class Mouse
{
public:
	Mouse();
	~Mouse();
	//	getter
	bool GetClick() { return m_isClick; }
	cocos2d::Vec2 GetPosition() { return m_position; }
	//	setter
	void SetClick(bool isClick) { m_isClick = isClick; }
	void SetPositon(cocos2d::Vec2 position) { m_position = position; }

	void Update(cocos2d::Vec2 position);

private:
	cocos2d::Vec2 m_position;	//	疑似マウスポインタの座標
	bool m_isClick;				//	クリックされたかどうか

};

