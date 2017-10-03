/// <summary>
/// 四角形塗りつぶしツールクラス
/// </summary>

#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Chip.h"

//マップサイズ
const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 20;

class SquareTool
{
private:
	int m_startW, m_startH;
	int m_endW, m_endH;
	
public:
	SquareTool();

	//	選択開始
	void SetStart(int w,int h);
	void SetEnd(int w, int h);

	void ChengeSelectedRange(Chip chip[][MAP_WIDTH], int selectedChipType);
};

