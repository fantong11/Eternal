#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include <memory>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"
#include "GameMap.h"
#include "BattleUI.h"
#include "Level.h"
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C���}�Y�e������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame *g)
	: CGameState(g)
{
}

void CGameStateInit::OnInit()
{
	Title.LoadBitmap(IDB_TITLE, RGB(255, 255, 255));
	Start.LoadBitmap(IDB_START, RGB(255, 255, 255));
	TutorialFont.LoadBitmap(IDB_TUTORIAL, RGB(255, 255, 255));
	About.LoadBitmapA(IDB_ABOUT);
	Exit.LoadBitmap(IDB_EXIT, RGB(255, 255, 255));
	Cursor.LoadBitmap(IDB_CURSOR, RGB(255, 255, 255));
	Tutorial.LoadBitmap(IDB_TUTORIAL_FONT);
	Story.LoadBitmap(IDB_STORY);
	Background.LoadBitmap(IDB_BATTLE_BACK);
	Actress.LoadBitmap(IDB_ACTRESS, RGB(255, 255, 255));
	Actor.LoadBitmap(IDB_ACTOR, RGB(255, 255, 255));
	AboutBtn.LoadBitmap(IDB_ABOUT_BTN, RGB(255, 255, 255));
	Temp1.LoadBitmap(IDB_FLYING_EYE_IDLE0, RGB(255, 255, 255));
	Temp2.LoadBitmap(IDB_GOBLIN_IDLE0, RGB(255, 255, 255));
	Temp3.LoadBitmap(IDB_MUSHSROOM_IDLE0, RGB(255, 255, 255));
	Temp4.LoadBitmap(IDB_SKULL_IDLE0, RGB(255, 255, 255));
	CAudio::Instance()->Load(AUDIO_SELECT, "sounds\\menu_select.wav");
}

void CGameStateInit::OnBeginState()
{
	menu_index = 0;
	total_menu = 4;
	cursor_x = 200;
	cursor_y = 200;
	about_y = 0;
	story = 0;
	tutorialIsOpen = false;
	enterFoolproof = true;
	aboutIsOpen = false;
	storyIsOpen = false;
	jumpStory = false;
	result = false;

	if (!loadReadlly)
		CAudio::Instance()->Load(AUDIO_MAIN_MENU, "sounds\\main_menu_theme.wav");

	loadReadlly = true;
	CAudio::Instance()->Play(AUDIO_MAIN_MENU, true);
}

void CGameStateInit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const int ENTER_KEY = 0x0D;
	const int UP_ARROW_KEY = 0x26;
	const int DOWN_ARROW_KEY = 0x28;

	if (nChar == UP_ARROW_KEY)
		menu_index = menu_index > 0 ? --menu_index : total_menu - 1;

	if (nChar == DOWN_ARROW_KEY)
		menu_index = menu_index < (total_menu - 1) ? ++menu_index : 0;

	if (nChar == ENTER_KEY)
	{
		if (aboutIsOpen && about_y > -2500)
		{
			aboutIsOpen = false;
			about_y = 0;
		}
		else if (tutorialIsOpen)
		{
			tutorialIsOpen = false;
		}
		else if (storyIsOpen)
		{
			if (jumpStory)
				GotoGameState(GAME_STATE_RUN);
			// ������GAME_STATE_RUN
			else
				jumpStory = true;
		}
		else if (menu_index == 0)
		{
			storyIsOpen = true;
		}
		else if (menu_index == 1)
		{
			tutorialIsOpen = true;
		}
		else if (menu_index == 2)
		{
			aboutIsOpen = true;
		}
		else if (menu_index == 3)
		{
			PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE, 0, 0);
		}
	}
	else
	{
		CAudio::Instance()->Play(AUDIO_SELECT, false);
	}
}

void CGameStateInit::OnShowBackground()
{
	Background.SetTopLeft(0, 0);
	Background.ShowBitmap();
	Actress.SetTopLeft(30, 540);
	Actress.ShowBitmap();
	Actor.SetTopLeft(250, 540);
	Actor.ShowBitmap();
	Temp4.SetTopLeft(650, 600);
	Temp4.ShowBitmap();
	Temp1.SetTopLeft(800, 500);
	Temp1.ShowBitmap();
	Temp3.SetTopLeft(730, 650);
	Temp3.ShowBitmap();
	Temp2.SetTopLeft(850, 600);
	Temp2.ShowBitmap();
}

void CGameStateInit::OnShow()
{
	OnShowBackground();
	Title.SetTopLeft(170, 30);
	Title.ShowBitmap();
	Start.SetTopLeft(400, 250);
	Start.ShowBitmap();
	TutorialFont.SetTopLeft(400, 350);
	TutorialFont.ShowBitmap();
	AboutBtn.SetTopLeft(400, 450);
	AboutBtn.ShowBitmap();
	Exit.SetTopLeft(400, 550);
	Exit.ShowBitmap();
	OnShowCursor();
	OnShowTutorial();
	OnShowAbout();
	OnShowStoryBackground();
	OnShowStory();
}

void CGameStateInit::OnShowCursor()
{
	if (menu_index == 0)
	{
		cursor_x = 350;
		cursor_y = 270;
	}
	else if (menu_index == 1)
	{
		cursor_x = 350;
		cursor_y = 370;
	}
	else if (menu_index == 2)
	{
		cursor_x = 350;
		cursor_y = 470;
	}
	else if (menu_index == 3)
	{
		cursor_x = 350;
		cursor_y = 570;
	}

	Cursor.SetTopLeft(cursor_x, cursor_y);
	Cursor.ShowBitmap();
}

void CGameStateInit::OnShowTutorial()
{
	if (tutorialIsOpen)
	{
		Tutorial.SetTopLeft(0, 0);
		Tutorial.ShowBitmap();
	}
}

void CGameStateInit::OnShowAbout()
{
	if (aboutIsOpen)
	{
		About.SetTopLeft(0, about_y -= 5);
		About.ShowBitmap();
	}

	if (about_y <= -3000)
	{
		aboutIsOpen = false;
		about_y = 0;
	}
}

void CGameStateInit::OnShowStoryBackground()
{
	if (storyIsOpen)
	{
		Story.SetTopLeft(0, 0);
		Story.ShowBitmap();
	}
}

void CGameStateInit::OnShowStory()
{
	if (storyIsOpen)
	{
		CDC *pDC = CDDraw::GetBackCDC();
		CFont f, *fp;
		f.CreatePointFont(200, "Microsoft JhengHei");
		fp = pDC->SelectObject(&f);
		pDC->SetBkColor(RGB(0, 0, 0));
		pDC->SetTextColor(RGB(0, 0, 0));
		pDC->SetBkMode(TRANSPARENT);

		/*-----------�s�W�F��--------------*/
		if (jumpStory)
		{
			//���L��ܰʵe
			pDC->TextOut(490, 80, "�A�O�q�p�N�ߧӭn�����i�̪��H");
			pDC->TextOut(590, 180, "���F�F���o�ӥؼ�");
			pDC->TextOut(507, 280, "�����n���q�L�ڸ̪��ǲλ���");
			pDC->TextOut(540, 380, "��X�����æb�P�򪺯���");
			pDC->TextOut(610, 480, "�ña�ۯ����q�L");
			pDC->TextOut(580, 580, "�����u�@��������a");
		}
		else
		{
			if (story >= 0)
			{
				if (story < 30)
					runText("�A�O�q�p�N�ߧӭn�����i�̪��H", t1, story);

				//�@�Ӧr�@�Ӧr�]�X��
				pDC->TextOut(490, 80, t1);
			}

			if (story >= 30)
			{
				if (story < 60)
					runText("���F�F���o�ӥؼ�", t2, story - 30);

				pDC->TextOut(590, 180, t2);
			}

			if (story >= 60)
			{
				if (story < 90)
					runText("�����n���q�L�ڸ̪��ǲλ���", t3, story - 60);

				pDC->TextOut(507, 280, t3);
			}

			if (story >= 90)
			{
				if (story < 120)
					runText("��X�����æb�P�򪺯���", t4, story - 90);

				pDC->TextOut(540, 380, t4);
			}

			if (story >= 120)
			{
				if (story < 150)
					runText("�ña�ۯ����q�L", t5, story - 120);

				pDC->TextOut(610, 480, t5);
			}

			if (story >= 150)
			{
				if (story < 180)
					runText("�����u�@��������a", t6, story - 150);

				pDC->TextOut(580, 580, t6);
			}
		}

		/*--------------------------------*/
		pDC->SelectObject(fp);
		CDDraw::ReleaseBackCDC();
		story >= 180 ? jumpStory = true : story++;
	}
}

void CGameStateInit::runText(char *a, char *b, int amount)
{
	char str[80] = "";
	sprintf(str, a);

	for (int i = 0; i < amount; i++)
		b[i] = str[i];
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����������A(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame *g)
	: CGameState(g)
{
}

void CGameStateOver::OnMove()
{
	counter--;

	if (counter < 0)
	{
		GotoGameState(GAME_STATE_INIT);
		CAudio::Instance()->Stop(AUDIO_DUTY_VICTORY);
	}
}

void CGameStateOver::OnBeginState()
{
	counter = 30 * 5; // 5 seconds
	CAudio::Instance()->Stop(AUDIO_BATTLE);
	CAudio::Instance()->Play(AUDIO_DUTY_VICTORY, true);
	CAudio::Instance()->Stop(AUDIO_WALK_THEME);
}

void CGameStateOver::OnInit()
{
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	// �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(66);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���66%
	//
	// �}�l���J���
	//
	Background.LoadBitmap(IDB_VICTORY);
	Sleep(300);				// ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �̲׶i�׬�100%
	//
	ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	if (result)
	{
		Background.SetTopLeft(0, 0);
		Background.ShowBitmap();
	}

	CDC *pDC = CDDraw::GetBackCDC();
	CFont f, *fp;
	f.CreatePointFont(400, "Times New Roman");
	fp = pDC->SelectObject(&f);
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 0, 0));
	pDC->SetBkMode(TRANSPARENT);

	if (result)
		pDC->TextOut(360, 350, "�P�¹C�� !");
	else
		pDC->TextOut(360, 350, "�U���A�V�O !");

	pDC->SelectObject(fp);
	CDDraw::ReleaseBackCDC();
}

/////////////////////////////////////////////////////////////////////////////
// �o��class���C�����C�����檫��A�D�n���C���{�����b�o��
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g)
	: CGameState(g)
{
	monster = NULL;
}

CGameStateRun::~CGameStateRun()
{
	delete monster;
}

void CGameStateRun::OnBeginState()
{
	hero.Initialize(&isBattling, &npc, &chest);
	gamemap.SetScreenXY(110, 110);
	isBattling = false;
	isCollision = false;
	playWalkTheme = true;
	end = false;
	CAudio::Instance()->Play(AUDIO_WALK_THEME, true);
	CAudio::Instance()->Stop(AUDIO_MAIN_MENU);

	for (size_t i = 0; i < chest.size(); i++)
		chest[i]->init();
}

bool CGameStateRun::DoingSomeing()
{
	for (size_t i = 0; i < npc.size(); i++)
		if (npc[i]->IsRespone())
			return true;

	for (size_t i = 0; i < chest.size(); i++)
		if (chest[i]->IsOpening())
			return true;

	return false;
}

void CGameStateRun::OnMove()
{
	// ���ʹC������
	//
	// ���ʥD��
	//
	hero.OnMove(&gamemap);

	if (!isBattling)
	{
		for (size_t i = 0; i < npc.size(); i++)
			npc[i]->OnMove(&gamemap);

		for (size_t i = 0; i < chest.size(); i++)
			chest[i]->OnMove(&hero);
	}

	OnBattle();
	OnAudio();

	if (hero.GetHp() <= 0)
	{
		hero.SetHp(100);
		CAudio::Instance()->Stop(AUDIO_BEHEMOTH_THEME);
		isBattling = false;
		GotoGameState(GAME_STATE_OVER);
	}

	End();
}

void CGameStateRun::OnBattle()
{
	if (hero.HasMeetMonster(&gamemap))
	{
		if (!hero.GetReadllyFight())
			CAudio::Instance()->Play(AUDIO_BATTLE, true);
		else
			CAudio::Instance()->Play(AUDIO_BEHEMOTH_THEME, true);

		hero.SetLastXY(hero.GetX1(), hero.GetY1());
		gamemap.SetLastScreenXY(gamemap.GetScreenX(), gamemap.GetScreenY());
		TRACE("LastPositionX = %d, LastPositionY = %d\n", hero.GetLastPositionX(), hero.GetLastPositionY());
		monster = RandomMonster();

		if (monster != NULL)
			battleUI.Initialize(&gamemap, &hero, monster, &isBattling, &playWalkTheme);
	}

	if (monster != NULL)
	{
		monster->OnMove();

		if (!isBattling)
		{
			delete monster;
			monster = NULL;
		}
	}
}

void CGameStateRun::OnAudio()
{
	if (playWalkTheme)
	{
		CAudio::Instance()->Play(AUDIO_WALK_THEME, true);
		playWalkTheme = false;
	}

	if (!isBattling)
		CAudio::Instance()->Stop(AUDIO_BATTLE);
	else
		CAudio::Instance()->Stop(AUDIO_WALK_THEME);
}

Monster *CGameStateRun::RandomMonster()
{
	srand((unsigned)time(NULL));
	int max = 4;
	int rd = (hero.GetTreasureAmount() == 3 && hero.GetReadllyFight()) ? 4 : rand() % max;

	switch (rd)
	{
		case MONSTER_ID::MONSTER_SKULL:
			skull = new Skull(-700, -400, hero.GetLevel());
			skull->LoadBitmap();
			return skull;

		case MONSTER_ID::MONSTER_FlyingEye:
			flyingEye = new FlyingEye(-700, -400, hero.GetLevel());
			flyingEye->LoadBitmap();
			return flyingEye;

		case MONSTER_ID::MONSTER_GOBLIN:
			goblin = new Goblin(-700, -400, hero.GetLevel());
			goblin->LoadBitmap();
			return goblin;

		case MONSTER_ID::MONSTER_MUSHSROOM:
			mushsroom = new Mushsroom(-700, -400, hero.GetLevel());
			mushsroom->LoadBitmap();
			return mushsroom;

		case MONSTER_ID::BOSS_BEHEMOTH:
			behemoth = new Behemoth();
			behemoth->LoadBitmap();
			return behemoth;

		default:
			return NULL;
	}
}

void CGameStateRun::OnInit()
{
	// �C������Ȥιϧγ]�w
	//
	// ��ϫܦh�ɡAOnInit���J�Ҧ����ϭn��ܦh�ɶ��C���קK���C�����H
	// �������@�СA�C���|�X�{�uLoading ...�v�A���Loading���i�סC
	//
	ShowInitProgress(33);	// ���ӫe�@�Ӫ��A���i�סA���B�i�׵���33%
	//
	// �}�l���J���
	//
	printNum.LoadBitmap();
	NumberUI.LoadBitmap();
	hero.LoadBitmap();
	// ���J�D��
	gamemap.LoadBitmap();
	// ���J�a��
	battleUI.LoadBitmap();
	// ���J�԰�UI
	npc.push_back(make_unique<Npc>(360, 1120, 1220, 0, &hero));
	npc.push_back(make_unique<Npc>(3820, 820, 4320, 1, &hero));
	npc.push_back(make_unique<Npc>(2420, 1965, 2830, 1, &hero));
	chest.push_back(make_unique<Chest>(500, 1415, 0));
	chest.push_back(make_unique<Chest>(740, 150, 1));
	chest.push_back(make_unique<Chest>(150, 900, 0));
	chest.push_back(make_unique<Chest>(175, 140, 1));
	chest.push_back(make_unique<Chest>(1220, 1235, 0));
	chest.push_back(make_unique<Chest>(5900, 150, 1));
	chest.push_back(make_unique<Chest>(5320, 990, 0));
	chest.push_back(make_unique<Chest>(5870, 1970, 1));
	chest.push_back(make_unique<Chest>(2140, 1500, 0));
	chest.push_back(make_unique<Chest>(460, 1995, 1));
	chest.push_back(make_unique<Chest>(5780, 1955, 0));
	chest.push_back(make_unique<Chest>(5685, 1955, 1));
	chest.push_back(make_unique<Chest>(5575, 1955, 0));

	for (size_t i = 0; i < npc.size(); i++)
		npc[i]->LoadBitmap();

	for (size_t i = 0; i < chest.size(); i++)
		chest[i]->LoadBitmap();

	//
	// ��������Loading�ʧ@�A�����i��
	//
	ShowInitProgress(50);
	Sleep(300); // ��C�A�H�K�ݲM���i�סA��ڹC���ЧR����Sleep
	//
	// �~����J��L���
	//
	CAudio::Instance()->Load(AUDIO_WALK_THEME, "sounds\\walk_theme.wav");
	CAudio::Instance()->Load(AUDIO_BATTLE, "sounds\\battle_theme.wav");
	CAudio::Instance()->Load(AUDIO_SWORD, "sounds\\sword.wav");
	CAudio::Instance()->Load(AUDIO_SPELL, "sounds\\heal.wav");
	CAudio::Instance()->Load(AUDIO_LIGHTNING, "sounds\\lightning.wav");
	CAudio::Instance()->Load(AUDIO_LASER, "sounds\\laser.wav");
	CAudio::Instance()->Load(AUDIO_HIT, "sounds\\hit.wav");
	CAudio::Instance()->Load(AUDIO_VICTORY_THEME, "sounds\\victory_theme.wav");
	CAudio::Instance()->Load(AUDIO_BEHEMOTH_THEME, "sounds\\behemoth_theme.wav");
	CAudio::Instance()->Load(AUDIO_DUTY_VICTORY, "sounds\\duty_complete_theme.wav");
	//
	// ��OnInit�ʧ@�|����CGameStaterOver::OnInit()�A�ҥH�i���٨S��100%
	//
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	const char KEY_ESC = 0x1B;
	nChar == KEY_ESC ? exit(0) : 0;

	//�������}�C��
	if (!isBattling)
	{
		if (!DoingSomeing())
			hero.OnKeyDown(nChar);

		// �D�����ʫ���
		for (size_t i = 0; i < npc.size(); i++)
			npc[i]->OnkeyDown(nChar);

		for (size_t i = 0; i < chest.size(); i++)
			chest[i]->OnKeyDown(nChar);
	}
	else
	{
		battleUI.OnkeyDown(nChar);
		// �԰�����
		CAudio::Instance()->Play(AUDIO_SELECT, false);
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (!isBattling)
		hero.OnKeyUp(nChar);
}

void CGameStateRun::End()
{
	if (battleUI.End() && hero.GetReadllyFight())
	{
		result = true;
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnShow()
{
	//
	//  �`�N�GShow�̭��d�U���n���ʥ��󪫥󪺮y�СA���ʮy�Ъ��u�@����Move���~��A
	//        �_�h��������sø�Ϯ�(OnDraw)�A����N�|���ʡA�ݰ_�ӷ|�ܩǡC���ӳN�y
	//        ���AMove�t�dMVC����Model�AShow�t�dView�A��View�������Model�C
	//
	//
	//  �K�W�I����
	//
	gamemap.OnShow();

	// �K�W�a��
	if (isBattling)
		battleUI.OnShow(&NumberUI, &printNum);

	// �K�W�԰�UI
	for (size_t i = 0; i < chest.size(); i++)
		chest[i]->OnShow(gamemap);

	hero.OnShow(&gamemap, &NumberUI, &printNum);

	// �K�W�D��
	for (size_t i = 0; i < chest.size(); i++)
		chest[i]->ShowItemGet(&printNum);

	if (!isBattling)
		for (size_t i = 0; i < npc.size(); i++)
			npc[i]->OnShow(&gamemap, &printNum);

	ShowHeroUi();

	//���I��ܤ~���|�Q�_�c�ANPC�צ�
	if (isBattling && monster != NULL && !monster->IsDead())
		monster->OnShow(&NumberUI, &printNum, &gamemap);

	// �K�W�v�ܩi
	hero.AnimationSkill(&gamemap);

	if (isBattling)
	{
		//���I��ܤ~���|�Q����j�����Ǫ��צ�
		battleUI.ShowAttackDamage(&NumberUI);
		battleUI.ShowEscapefailed();
	}
}
void CGameStateRun::ShowHeroUi()
{
	hero.ShowUI(&gamemap, &NumberUI);
	hero.ShowPotion(&gamemap, &NumberUI);
}
}