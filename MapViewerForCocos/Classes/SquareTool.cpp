#include "SquareTool.h"


USING_NS_CC;


SquareTool::SquareTool()
{
	//	‰Šú‰»
	m_startW = 0;
	m_startH = 0;
	m_endW = 0;
	m_endH = 0;
}

void SquareTool::SetStart(int w, int h)
{
	m_startW = w;
	m_startH = h;
}

void SquareTool::SetEnd(int w, int h)
{
	m_endW = w;
	m_endH = h;
}

void SquareTool::ChengeSelectedRange(Chip chip[][MAP_WIDTH], int selectedChipType)
{
	//	‰Eã‚Å—£‚µ‚½
	if (m_startW <= m_endW && m_startH <= m_endH)
	{
		for (int h = m_startH; h <= m_endH; h++)
		{
			for (int w = m_startW; w <= m_endW; w++)
			{
				chip[h][w].ChengeImage(selectedChipType);
			}
		}
	}
	//	‰E‰º‚Å—£‚µ‚½
	else if (m_startW <= m_endW && m_startH >= m_endH)
	{
		for (int h = m_endH; h <= m_startH; h++)
		{
			for (int w = m_startW; w <= m_endW; w++)
			{
				chip[h][w].ChengeImage(selectedChipType);
			}
		}
	}
	//	¶‰º‚Å—£‚µ‚½
	else if (m_startW >= m_endW && m_startH >= m_endH)
	{
		for (int h = m_endH; h <= m_startH; h++)
		{
			for (int w = m_endW; w <= m_startW; w++)
			{
				chip[h][w].ChengeImage(selectedChipType);
			}
		}
	}
	//	¶ã‚Å—£‚µ‚½ê‡
	else if (m_startW >= m_endW && m_startH <= m_endH)
	{
		for (int h = m_startH; h <= m_endH; h++)
		{
			for (int w = m_endW; w <= m_startW; w++)
			{
				chip[h][w].ChengeImage(selectedChipType);
			}
		}
	}

	
}
