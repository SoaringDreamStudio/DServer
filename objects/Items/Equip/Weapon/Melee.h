#include "../Weapon.h"
#include "../../../../struct.h"
class Melee : public Weapon
{
public:
    Melee(int ID,
            int AD,
            int Range,
            std::string AttackAnimationName,
            Rect hitBox);

	~Melee(void);
protected:
    Rect hitBox;
};
