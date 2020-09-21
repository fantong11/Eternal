#ifndef HERO_H
#define HERO_H
#include <vector>
#include "Skull.h"
#include "GameMap.h"
#include "Level.h"
#include "Item.h"
#include "Skill.h"
#include "Npc.h"
#include "Chest.h"
#include <memory>
namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// �o��class���ѥi�H����L�ηƹ�����D��
// �����N�i�H��g���ۤv���{���F
/////////////////////////////////////////////////////////////////////////////
typedef unsigned int UNIT;
class Hero
{
public:
	Hero();
	void Initialize(bool *, vector<unique_ptr<Npc>> *npc, vector<unique_ptr<Chest>> *chest);// �]�w�D������l��
	void LoadBitmap();										// ���J�ϧ�
	int  GetX1();											// �D�����W�� x �y��
	int  GetY1();											// �D�����W�� y �y��
	int  GetX2();											// �D���k�U�� x �y��
	int  GetY2();											// �D���k�U�� y �y��
	int  GetSizeX();
	int  GetSizeY();
	int  GetMaxHp();
	int  GetMaxMp();
	int  GetHp();
	int  GetMp();
	int  GetLastPositionX();								// �^�ǤW���y��
	int  GetLastPositionY();								// �^�ǤW���y��
	int  GetAttackDamage();									// �^�ǧ����ˮ`
	int  GetWeaponGrade();									// �^�ǪZ������
	int  GetArmorGrade();									// �^�Ǩ��㵥��
	int  GetShieldGrade();									// �^�Ǭ޵P����
	int  GetSkillDamage();									// �^�ǧޯ�ˮ`
	int  GetCurrentBattleState();							// �^�ǥثe���A�A���A�����m�A�����A���m�A�ޯ�
	int  GetGold();											// �^�Ǫ���
	int  GetLevel();										// �^�ǵ���
	int  GetItemAmount(int);								// �^�ǹD��ƶq
	int  GetSkillManaCost(int);								// �^�ǧޯ���]�q
	int  GetBlockDamage();									// �^�ǹj�׶ˮ`�q
	int  GetTreasureAmount();								// �^���_���ƶq
	int  GetFinallyChest();									// �^�ǫO����
	void SetXY(int nx, int ny);								// �]�w�D�����W���y��
	void SetLastXY(int nx, int ny);							// �����D�����ʫe�y��
	void SetHp(int HP);										// �]�w��q
	void SetMp(int MP);										// �]�w�]�q
	void SetMovingDown(bool flag);							// �]�w�O�_���b���U����
	void SetMovingLeft(bool flag);							// �]�w�O�_���b��������
	void SetMovingRight(bool flag);							// �]�w�O�_���b���k����
	void SetMovingUp(bool flag);							// �]�w�O�_���b���W����
	void SetAllMovingToFalse();								// �]�w����
	void SetMovingState(int flag);							// �]�w��V �� = 0, �k = 1, �W = 2, �U = 3
	void SetMoveDistance(int dst);							// �]�w���ʶZ��
	void SetRun(bool);										// �]�w�}�l�]�B
	void SetGuard(bool);									// �]�w���m
	void SetGold(int);										// �]�w��o����
	void SetXp(int xp);										// ��o�g���
	void SetLevel();										// ���ܵ���
	void SetItemAmount(int id, int amount);					// �]�w���~�ƶq
	void SetWeaponGrade(int);								// �]�w�Z������
	void SetArmorGrade(int);								// �]�w���㵥��
	void SetShieldGrade(int);								// �]�w�޵P����
	void SetTreasureAmount(int);							// �]�w�����ƶq
	void SetFinallyBattleEnd(bool flag);					// �԰���������
	void SetFinallyChest(int);								// �]�m�O����
	void OpenBossDoor();									// ���}�u�@�~��
	void LevelUp();											// ���Ŵ���
	bool NextStepIsEmpty(GameMap *map, bool movingState, int x1, int y1, int x2, int y2);	// �P�_�U�@��O�_�i�H��
	bool HasMeetMonster(GameMap *map);						// �J��Ǫ�
	bool isMoving();										// ���b����
	bool isGuarding();										// ���b���m
	bool IsCollisionNpc();									// �I����npc
	bool IsCollisionChest();								// �I�����_�c
	bool HasCollision(int x1, int y1, int x2, int y2, GameMap *map);		// �P�_�O�_�I����
	bool IsRespone();										// �b��ܤ�
	bool GetReadllyFight();
	void OnMove(GameMap *map);								// ���ʥD��
	void Moving(GameMap *map);								// ���ʰʵe
	void Attacking();										// �����ʵe
	void AttackMonster(Monster &);							// �����Ǫ�
	void SkillAttackMonster(Monster &, int);				// �ޯ�����Ǫ�
	void Guarding();										// ���m�ʵe
	void Healing();											// �^�_�ʵe
	void UseItem(int);										// ��J�n�ϥΪ��D��s��
	void Skilling();										// �ޯ�ʵe
	void OnKeyDown(UNIT nChar);
	void OnKeyUp(UNIT nChar);
	void OnShow(GameMap *map, AdjustableCInteger *printNum, CInteger *printNum2);// ��ܥD��
	void doStandingAnimation(GameMap *map);					// �����ʮ�
	void AnimationMove(GameMap *map);						// ��ܲ��ʰʵe
	void AnimationAttack(GameMap *map);						// ��ܧ����ʵe
	void AnimationGuard(GameMap *map);						// ��ܨ��m�ʵe
	void AnimationGuardReset();								// ��ܨ��m�ʵe���m
	void AnimationHeal(GameMap *map);						// ��ܦ^�_�ʵe
	void AnimationSkill(GameMap *map);						// ��ܧޯ�ʵe
	void ShowUI(GameMap *map, AdjustableCInteger *printNum);// ��ܶ��m����
	void ShowHeroUI(GameMap *map, AdjustableCInteger *printNum);// ��ܰ�¦�ƭȤ���
	void ShowGoldUI(GameMap *map, AdjustableCInteger *printNum);// ��ܪ�������
	void PrintNumber(GameMap *map, AdjustableCInteger *printNum, int number, int nx, int ny);// ��ܼƦr
	void ShowHp(int x1, int y1, int hp);					// ��ܦ�q
	void ShowMp(int x1, int y1, int mp);					// ����]�q
	void ShowXp(int x1, int y1, int xp, int requireXp);		// ��ܸg���
	void ShowPotion(GameMap *map, AdjustableCInteger *printNum);
protected:
	CAnimation animation_U;									// �D���W�����ʵe
	CAnimation animation_D;									// �D���U�����ʵe
	CAnimation animation_L;									// �D���������ʵe
	CAnimation animation_R;									// �D���k�����ʵe
	CAnimation animation_attack;
	CAnimation animation_guard;
	CMovingBitmap HP_UI;
	CMovingBitmap Gold_UI;
	CMovingBitmap BossDoorFailed;
	int  x, y;												// �D�����W���y��
	int _HP, MaxHp, _MP, MaxMp;
	int  lastPosition_x, lastPosition_y;					// �W�@�Ӧ�m
	int  STEP_SIZE;											// ���ʶZ��
	int  RUN_SIZE;											// �]�B�Z��
	int  lastMovingState;									// �W�Ӳ��ʤ�V
	int  currentBattleState;								// �ثe��ʪ��A
	int  weapon_grade;										// �Z������
	int  armor_grade;										// ���㵥��
	int  shield_grade;										// �޵P����
	int  AttackDamage;
	int  SkillDamage;
	int  blockDamage;										// ��׶ˮ`
	int  moveDistance;										// ���ʶZ��
	int  Gold;
	int  itemId, skillId;
	int  treasure;											// �_���ƶq
	int  finally_chest;										// �O��
	bool isMovingDown;										// �O�_���b���U����
	bool isMovingLeft;										// �O�_���b��������
	bool isMovingRight;										// �O�_���b���k����
	bool isMovingUp;										// �O�_���b���W����
	bool isRunning;
	bool *_isBattling;										// �O�_�԰���
	bool isAttack;
	bool isGuard;
	bool isHeal;
	bool isSkill;
	bool isPressEnter;										// ��ܶ}�_�c
	bool isInFrontOfBoss_door;								// �b�u�@�~���f�e
	bool readllyFight;										// �ǳƦn�̫�@��
	Level level;
	vector<unique_ptr<Item>> items;
	vector<unique_ptr<Skill>> skills;
	vector<unique_ptr<Npc>> *npc;
	vector<unique_ptr<Chest>> *chest;
};
}
#endif