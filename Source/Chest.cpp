#include <cstdlib>
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "GameMap.h"
#include "Hero.h"
#include "Chest.h"

namespace game_framework
{
Chest::Chest(int x, int y, int id)
{
	this->x = x;
	this->y = y;
	this->id = id;
	this->open = false;
	show_item_background = false;
	had_been_opened = false;
	delay = false;
	gain = false;
	delay_time = 0;
	money = 0;
	isCollision = false;
	open_animation.SetDelayCount(3);
}
void Chest::LoadBitmap()
{
	open_animation.AddBitmap(IDB_CHEST0, RGB(255, 255, 255));
	open_animation.AddBitmap(IDB_CHEST1, RGB(255, 255, 255));
	open_animation.AddBitmap(IDB_CHEST2, RGB(255, 255, 255));
	item_background.LoadBitmap(IDB_ITEM_MENU, RGB(255, 255, 255));
}

void Chest::init()
{
	show_item_background = false;
	had_been_opened = false;
	delay = false;
	gain = false;
	delay_time = 0;
	money = 0;
	isCollision = false;
	Reset();
}

int Chest::GetX1()
{
	return x;
}

int Chest::GetY1()
{
	return y;
}

int Chest::GetX2()
{
	return x + open_animation.Width();
}

int Chest::GetY2()
{
	return y + open_animation.Height();
}

int Chest::RandMoney()
{
	srand((unsigned)time(NULL));
	money = rand() % 950 + 50;
	return money;
}

void Chest::OnKeyDown(UNIT nChar)
{
	const int ENTER_KEY = 0x0D;
	press_Enter = nChar == ENTER_KEY ? true : false;
}

void Chest::OnMove(Hero *hero)
{
	// ��D���b����B�_�c���}�L�P���UENTER��
	if (isCollision && !had_been_opened && press_Enter)
	{
		open = true;
		press_Enter = false;
	}

	OpenChest(hero);

	if (delay)
		Delay();

	CloseWindow(hero);
}

void Chest::CloseWindow(Hero *hero)
{
	//�����}������ؤ�k
	//���UENTER�� �M �������}�_�c
	if (had_been_opened && isCollision && show_item_background && press_Enter)
	{
		show_item_background = false;
		HeroGainItem(hero);
	}
}
void Chest::Reset()
{
	open_animation.Reset();
}
void Chest::Delay()
{
	if (delay_time == 10)
	{
		delay = false;
		delay_time = 0;
	}
	else
	{
		delay_time++;
	}
}

void Chest::OpenChest(Hero *hero)
{
	if (open)
	{
		open_animation.OnMove();

		if (open_animation.IsFinalBitmap())
		{
			RandMoney();
			hero->SetFinallyChest(1);
			hero->GetFinallyChest() >= 10 ? finally_chest = true : finally_chest = false;
			open = false;
			delay = true;
			had_been_opened = true;
			show_item_background = true;
		}
	}
}

void Chest::HeroGainItem(Hero *hero)
{
	hero->SetGold(money);

	if (gain)
	{
		if (hero->GetTreasureAmount() == 0)
		{
			if (id == 0)
				hero->SetTreasureAmount(1);
			else if (id == 1)
				hero->SetTreasureAmount(2);
		}
		else if (hero->GetTreasureAmount() == 1)
		{
			if (id == 1)
				hero->SetTreasureAmount(3);
		}
		else if (hero->GetTreasureAmount() == 2)
		{
			if (id == 0)
				hero->SetTreasureAmount(3);
		}
	}
}

void Chest::OnShow(GameMap &map)
{
	open_animation.SetTopLeft(map.ScreenX(x), map.ScreenY(y));
	open_animation.OnShow();
}

void Chest::ShowItemGet(CInteger *printNum)
{
	//�� �٦b�_�c���� �M �_�c�w���} �M ���� �M �D���S������ �~�����o���p
	if (isCollision && had_been_opened && !delay && show_item_background)
	{
		int rd = rand() % 4;
		item_background.SetTopLeft(300, 230);
		item_background.ShowBitmap();
		/*---------�����o���~------------*/
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(300, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		char str[80];
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		/*-----------�s�W�F��--------------*/
		pDC->TextOut(465, 270, "��o");
		pDC->TextOut(550, 350, "����");
		sprintf(str, "%d", money);
		pDC->TextOut(400, 350, str);

		if (rd == 1 || finally_chest)
		{
			gain = true;
			sprintf(str, "%d", 1);
			pDC->TextOut(445, 430, str);
			id == 0 ? pDC->TextOut(520, 430, "�r�ߴ�") : pDC->TextOut(520, 430, "������");
		}

		/*--------------------------------*/
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
		/*--------------------------------*/
	}
}

bool Chest::HasCollision(int x1, int y1, int x2, int y2)
{
	int minX1 = GetX1() - 30;
	int minY1 = GetY1() - 30;
	int maxX1 = GetX2() + 30;
	int maxY1 = GetY2() + 30;
	int minX2 = x1;
	int minY2 = y1;
	int maxX2 = x2;
	int maxY2 = y2;

	// ��Ӫ��魱�n���|�N�|�I��
	if (maxX1 > minX2 && maxX2 > minX1 &&
	        maxY1 > minY2 && maxY2 > minY1)
	{
		isCollision = true;
		return true;
	}

	isCollision = false;
	return false;
}
bool Chest::IsOpening()
{
	return open || show_item_background;
}
}