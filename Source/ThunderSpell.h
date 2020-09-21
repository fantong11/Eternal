#ifndef THUNDERSPELL_H
#define THUNDERSPELL_H
#include "Skill.h"

namespace game_framework
{
class ThunderSpell : public Skill
{
public:
	ThunderSpell();
	void LoadBitmap();
};
}
#endif