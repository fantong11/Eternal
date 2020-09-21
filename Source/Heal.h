#ifndef HEAL_H
#define HEAL_H
#include "Skill.h"

namespace game_framework
{
class Heal : public Skill
{
public:
	Heal();
	void LoadBitmap();
};
}
#endif