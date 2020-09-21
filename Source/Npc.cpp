#include <cstdlib>
#include <ctime>
#include <math.h>
#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "Hero.h"
#include "GameMap.h"
#include "Npc.h"
#include "mygame.h"

namespace game_framework
{
Npc::Npc(int x, int y, int endPos, int direction, Hero *hero)
{
	Initialize(x, y, endPos, direction, hero);
}

void Npc::Initialize(int x, int y, int endPos, int direction, Hero *hero)
{
	this->x = x;
	this->y = y;
	STEP_SIZE = 3;
	talkId = 0;
	cursor_x = 270;
	cursor_y = 230;
	menuId = 0;
	respone = 0;
	isMovingDown = false;
	isMovingLeft = false;
	isMovingRight = false;
	isMovingUp = false;
	isCollision = false;
	enterFoolproof = false;
	InPotionShop = false;
	InBlacksmith = false;
	openSpeechBubble = false;
	openShopUI = false;
	openResponeUI = false;
	openTalk = false;
	Pauper = false;
	startPos = x;
	this->endPos = endPos;
	this->direction = direction;
	this->hero = hero;

	if (direction)
	{
		startPos = x;
		isMovingRight = true;
	}
	else
	{
		startPos = y;
		isMovingUp = true;
	}

	countTime = 0;
}

void Npc::LoadBitmap()
{
	animation_U.AddBitmap(IDB_NPC_UP0, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_NPC_UP1, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_NPC_UP2, RGB(255, 255, 255));
	animation_U.AddBitmap(IDB_NPC_UP3, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_NPC_DOWN0, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_NPC_DOWN1, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_NPC_DOWN2, RGB(255, 255, 255));
	animation_D.AddBitmap(IDB_NPC_DOWN3, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_NPC_LEFT0, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_NPC_LEFT1, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_NPC_LEFT2, RGB(255, 255, 255));
	animation_L.AddBitmap(IDB_NPC_LEFT3, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_NPC_RIGHT0, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_NPC_RIGHT1, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_NPC_RIGHT2, RGB(255, 255, 255));
	animation_R.AddBitmap(IDB_NPC_RIGHT3, RGB(255, 255, 255));
	shopUI.LoadBitmap(IDB_BATTLE_FINISH, RGB(255, 255, 255));
	speechBubble.LoadBitmap(IDB_SPEECH_BUBBLE, RGB(0, 0, 0));
	responeUI.LoadBitmap(IDB_ITEM_MENU, RGB(255, 255, 255));
	Cursor.LoadBitmap(IDB_CURSOR, RGB(255, 255, 255));
}

int Npc::GetX1()
{
	return x;
}

int Npc::GetY1()
{
	return y;
}

int Npc::GetX2()
{
	return x + animation_L.Width();
}

int Npc::GetY2()
{
	return y + animation_L.Height();
}

void Npc::SetXY(int nx, int ny)
{
	x = nx;
	y = ny;
}

void Npc::SetMovingDown(bool flag)
{
	isMovingDown = flag;
}

void Npc::SetMovingLeft(bool flag)
{
	isMovingLeft = flag;
}

void Npc::SetMovingRight(bool flag)
{
	isMovingRight = flag;
}

void Npc::SetMovingUp(bool flag)
{
	isMovingUp = flag;
}

void Npc::SetAllMovingToFalse()
{
	SetMovingLeft(false);
	SetMovingRight(false);
	SetMovingUp(false);
	SetMovingDown(false);
}

void Npc::SetAllMovingToTrue()
{
	SetMovingLeft(true);
	SetMovingRight(true);
	SetMovingUp(true);
	SetMovingDown(true);
}

bool Npc::isMoving()
{
	return isMovingDown || isMovingLeft || isMovingRight || isMovingUp;
}

void Npc::OnMove(GameMap *map)
{
	if (!isCollision)
	{
		movingArea(map);

		if (isMovingRight)
		{
			animation_R.OnMove();
			x += STEP_SIZE;
		}

		if (isMovingLeft)
		{
			animation_L.OnMove();
			x -= STEP_SIZE;
		}

		if (isMovingUp)
		{
			animation_U.OnMove();
			y -= STEP_SIZE;
		}

		if (isMovingDown)
		{
			animation_D.OnMove();
			y += STEP_SIZE;
		}
	}
}

void Npc::SetMovingState(int flag)
{
	lastMovingState = flag;
}

bool Npc::HasCollision(int x1, int y1, int x2, int y2)
{
	int minX1 = GetX1() - 50;
	int minY1 = GetY1() - 50;
	int maxX1 = GetX2() + 50;
	int maxY1 = GetY2() + 50;
	int minX2 = x1;
	int minY2 = y1;
	int maxX2 = x2;
	int maxY2 = y2;

	// ��Ӫ��魱�n���|�N�|�I��
	if (maxX1 > minX2 && maxX2 > minX1 &&
	        maxY1 > minY2 && maxY2 > minY1)
	{
		animation_D.Reset();
		animation_L.Reset();
		animation_R.Reset();
		animation_U.Reset();
		isCollision = true;
		return true;
	}

	isCollision = false;
	NoCollisionTurnOffAllThing();
	return false;
}

void Npc::NoCollisionTurnOffAllThing()
{
	talkId = 0;
	respone = 0;
	menuId = 0;
	enterFoolproof = true;
	openSpeechBubble = true;
	openShopUI = false;
	openResponeUI = false;
	openTalk = false;
}

bool Npc::IsRespone()
{
	return openResponeUI || openShopUI;
	//�N���ܿ�ܤ�
}

void Npc::movingArea(GameMap *map)
{
	// ���k
	if (direction == 1)
	{
		if (x < startPos)
			StopAMoment(animation_L, isMovingLeft, isMovingRight);
		else if (x > endPos)
			StopAMoment(animation_R, isMovingRight, isMovingLeft);
	}
	else if (direction == 0)
	{
		// �W�U
		if (y < startPos)
			StopAMoment(animation_U, isMovingUp, isMovingDown);
		else if (y > endPos)
			StopAMoment(animation_D, isMovingDown, isMovingUp);
	}
}

void Npc::StopAMoment(CAnimation &animation_move, bool &movingDir1, bool &movingDir2)
{
	if (countTime == 100)
	{
		STEP_SIZE = 3;
		countTime = 0;
		movingDir1 = false;
		movingDir2 = true;
	}
	else
	{
		STEP_SIZE = 0;
		animation_move.Reset();
		countTime++;
	}
}

void Npc::OnShow(GameMap *map, CInteger *printNum)
{
	AnimationMove(map);
	ShowShopUI();
	ShowSpeechBubble(map, printNum);
	talk(map, printNum);
	ShowResponeUI();
	ShowCursor();
	ShowPauper();
}

void Npc::AnimationMove(GameMap *map)
{
	if (isMovingRight)
	{
		animation_R.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_R.OnShow();
	}
	else if (isMovingLeft)
	{
		animation_L.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_L.OnShow();
	}
	else if (isMovingUp)
	{
		animation_U.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_U.OnShow();
	}
	else if (isMovingDown)
	{
		animation_D.SetTopLeft(map->ScreenX(x), map->ScreenY(y));
		animation_D.OnShow();
	}
}

void Npc::ShowSpeechBubble(GameMap *map, CInteger *printNum)
{
	//��ܹ�ܭI���}��
	if (isCollision && openSpeechBubble)
	{
		speechBubble.SetTopLeft(map->ScreenX(x) - 30, map->ScreenY(y) - 160);
		speechBubble.ShowBitmap();
		openTalk = true;
	}
}

void Npc::ShowResponeUI()
{
	//��ܦ^���I���}��
	if (openResponeUI)
	{
		responeUI.SetTopLeft(300, 150);
		responeUI.ShowBitmap();
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(400, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(450, 180, "���");
		pDC->TextOut(450, 265, "�j��");
		pDC->TextOut(450, 350, "�T�T");
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}

void Npc::ShowCursor()
{
	//��ܹ���
	if (openResponeUI)
	{
		//�b�Ĥ@���^���ﶵ�ɶ}��
		switch (respone)
		{
			//�ھڡ��A������ܥثe���Ц�l
			case 0:
				cursor_y = 210;
				break;

			case 1:
				cursor_y = 295;
				break;

			case 2:
				cursor_y = 380;
				break;
		}

		Cursor.SetTopLeft(cursor_x + 130, cursor_y);
		Cursor.ShowBitmap();
	}

	if (openShopUI)
	{
		//�i�J�ө������ɡA��ܹ���
		if (menuId == 0)
			//�ھڡ��A���A���A������ܥثe���Ц�l
			Cursor.SetTopLeft(290, 320);

		if (menuId == 1)
			Cursor.SetTopLeft(290, 380);

		if (menuId == 2)
			Cursor.SetTopLeft(290, 440);

		if (menuId == 3)
			Cursor.SetTopLeft(290, 500);

		if (menuId == 4)
			Cursor.SetTopLeft(435, 550);

		Cursor.ShowBitmap();
	}
}

void Npc::ShowShopUI()
{
	//��ܰө����I���A�쥻�ΨӲM�ů}���Ϊ�
	if (openShopUI)
	{
		shopUI.SetTopLeft(255, 210);
		shopUI.ShowBitmap();
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(100, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(495, 540, "���}");
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}

void Npc::ShowShopItem(CInteger *printNum, CDC *pDC)
{
	//��ܰө����~
	char str[80];
	pDC->TextOut(470, 250, "����");
	pDC->TextOut(620, 250, "����");
	/*-------------------------------------*/
	pDC->TextOut(350, 310, "Potion");
	sprintf(str, "%d", hero->GetItemAmount(0));
	pDC->TextOut(480, 310, str);
	pDC->TextOut(630, 310, "50");
	/*-------------------------------------*/
	pDC->TextOut(350, 370, "Ether");
	sprintf(str, "%d", hero->GetItemAmount(1));
	pDC->TextOut(480, 370, str);
	pDC->TextOut(630, 370, "50");
}
void Npc::ShowBlacksmith(CInteger *printNum, CDC *pDC)
{
	//����K�K�Q�\��
	char str[80];
	pDC->TextOut(460, 250, "��e����");
	pDC->TextOut(620, 250, "����");
	/*-------------------------------------*/
	pDC->TextOut(350, 310, "�Z��");
	sprintf(str, "Lv.%d", hero->GetWeaponGrade());
	pDC->TextOut(480, 310, str);
	sprintf(str, "%d", hero->GetWeaponGrade() * 100);
	pDC->TextOut(620, 310, str);
	/*-------------------------------------*/
	pDC->TextOut(350, 370, "����");
	sprintf(str, "Lv.%d", hero->GetArmorGrade());
	pDC->TextOut(480, 370, str);
	sprintf(str, "%d", hero->GetArmorGrade() * 100);
	pDC->TextOut(620, 370, str);
	/*-------------------------------------*/
	pDC->TextOut(350, 430, "�޵P");
	sprintf(str, "Lv.%d", hero->GetShieldGrade());
	pDC->TextOut(480, 430, str);
	sprintf(str, "%d", hero->GetShieldGrade() * 100);
	pDC->TextOut(620, 430, str);

	/*-------------------------------------*/
	if (hero->GetGold() >= 939000)
	{
		pDC->TextOut(350, 490, "��X��");
		pDC->TextOut(465, 490, "�}�K����");
	}
	else
	{
		pDC->TextOut(350, 490, "???");
		pDC->TextOut(465, 490, "????");
	}

	pDC->TextOut(605, 490, "93.9�U");
}

void Npc::ShowPauper()
{
	//��ܧA�a
	if (Pauper)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(1900, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOut(50, 100, "�i����");
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}

void Npc::talk(GameMap *map, CInteger *printNum)
{
	//��ܹ��
	if (openTalk)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(120, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);

		switch (talkId)
		{
			case 0:
				pDC->TextOut(map->ScreenX(x) + 10, map->ScreenY(y) - 125, "�A�n��~");
				break;

			case 1:
				pDC->TextOut(map->ScreenX(x) - 10, map->ScreenY(y) - 125, "�Q��ڶi���");
				pDC->TextOut(map->ScreenX(x) + 20, map->ScreenY(y) - 100, "���ʣv");
				break;

			case 2:
				ShowShopItem(printNum, pDC);
				break;

			case 3:
				ShowBlacksmith(printNum, pDC);
				break;
		}

		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
	}
}

void Npc::CursorControl(UNIT nChar)
{
	const int LEFT_ARROW_KEY = 0x25;
	const int UP_ARROW_KEY = 0x26;
	const int RIGHT_ARROW_KEY = 0x27;
	const int DOWN_ARROW_KEY = 0x28;

	if (nChar == DOWN_ARROW_KEY)
		menuId = menuId + 1 > 4 ? 0 : menuId + 1;

	if (nChar == UP_ARROW_KEY)
		menuId = menuId - 1 < 0 ? 4 : menuId - 1;
}

void Npc::OnkeyDown(UINT nChar)
{
	if (isCollision)
	{
		const int ENTER_KEY = 0x0D;

		if (nChar == ENTER_KEY)
		{
			//������ܡA���Uenter�~����
			CAudio::Instance()->Play(AUDIO_SELECT, false);

			if (talkId == 1)
				//���ܶi���ĤG�y�ɡA�n�i����
				openResponeUI = true;

			//��ܮɡA���}�^����ܪ��I���}��
			talkId = talkId > 0 ? talkId : talkId + 1;
			//���ݿ�ܡA����ܰ��U
		}

		if (openResponeUI)
		{
			//���}��ܮɪ��I���}��
			CAudio::Instance()->Play(AUDIO_SELECT, false);
			Respone(nChar);
			//�ثe�ҿ諸�^��
		}

		if (openShopUI)
		{
			//���}�ө��I��
			CAudio::Instance()->Play(AUDIO_SELECT, false);
			Shopping(nChar);
			//�i��R���~�����
		}
	}
}

void Npc::Respone(UNIT nChar)
{
	//�^���ɪ��ޱ�
	const int UP_ARROW_KEY = 0x26;
	const int DOWN_ARROW_KEY = 0x28;
	const int ENTER_KEY = 0x0D;

	if (nChar == UP_ARROW_KEY)
	{
		//����W�U����
		respone -= 1;

		if (respone < 0)
			respone = 2;
	}

	if (nChar == DOWN_ARROW_KEY)
	{
		respone += 1;

		if (respone > 2)
			respone = 0;
	}

	if (!enterFoolproof)
	{
		//���b���}
		if (nChar == ENTER_KEY)
		{
			if (respone == 2)
			{
				//��ܩڵ���ܡA������ܭI��
				openSpeechBubble = false;
				openResponeUI = false;
				openTalk = false;
			}
			else if (respone == 1)
			{
				openShopUI = true;
				openResponeUI = false;
				openSpeechBubble = false;
				enterFoolproof = true;
				InBlacksmith = true;
				talkId += 2;
				//��ܩ��U�i�h
				return;
			}
			else if (respone == 0)
			{
				//��ܶi�J�ө��A���}�ө�����
				openShopUI = true;
				openResponeUI = false;
				openSpeechBubble = false;
				enterFoolproof = true;
				InPotionShop = true;
				talkId += 1;
				//��ܩ��U�i�h
				return;
			}
		}
	}

	enterFoolproof = false;
}

void Npc::Shopping(UNIT nChar)
{
	//�R�F�褤
	const int ENTER_KEY = 0x0D;
	const int BACKSPACE_KEY = 0x08;

	if (!enterFoolproof)
	{
		//���b���}
		CursorControl(nChar);

		if (nChar == ENTER_KEY)
			BuySomeThing(nChar);
	}

	enterFoolproof = false;
}

void Npc::BuySomeThing(UNIT nChar)
{
	//�R�F��
	int WeaponGradeMoney = hero->GetWeaponGrade() * 100;
	int ArmorGradeMoney = hero->GetArmorGrade() * 100;
	int ShieldGradeMoney = hero->GetShieldGrade() * 100;

	switch (menuId)
	{
		case 0:
			if (InPotionShop)
			{
				if (hero->GetGold() >= 50)
				{
					hero->SetItemAmount(menuId, 1);
					hero->SetGold(-50);
				}
				else
					Pauper = true;
			}

			if (InBlacksmith)
			{
				if (hero->GetGold() >= WeaponGradeMoney)
				{
					hero->SetWeaponGrade(1);
					hero->SetGold(-WeaponGradeMoney);
				}
				else
					Pauper = true;
			}

			break;

		case 1:
			if (InPotionShop)
			{
				if (hero->GetGold() >= 50)
				{
					hero->SetItemAmount(menuId, 1);
					hero->SetGold(-50);
				}
				else
					Pauper = true;
			}

			if (InBlacksmith)
			{
				if (hero->GetGold() >= ArmorGradeMoney)
				{
					hero->SetArmorGrade(1);
					hero->SetGold(-ArmorGradeMoney);
				}
				else
					Pauper = true;
			}

			break;

		case 2:
			if (InBlacksmith)
			{
				if (hero->GetGold() >= ShieldGradeMoney)
				{
					hero->SetShieldGrade(1);
					hero->SetGold(-ShieldGradeMoney);
				}
				else
					Pauper = true;
			}

			break;

		case 3:
			if (InBlacksmith)
			{
				if (hero->GetGold() >= 939000)
				{
					hero->SetGold(-939000);
				}
				else
					Pauper = true;
			}

			break;

		case 4:
			openShopUI = false;
			openSpeechBubble = false;
			openTalk = false;
			InPotionShop = false;
			InBlacksmith = false;
			Pauper = false;
			break;
	}
}
}