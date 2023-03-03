#ifndef WORLD_H
#define WORLD_H
///----------------------------------------------------------------------------|
/// "world.h"
///----------------------------------------------------------------------------:
#include "world.h"

struct  Player
{       Player(std::wstring Name = L"...?") : name(Name)
        {   restart();
        }

    std::wstring name;

    void restart()
    {   if (nullptr != pworld) delete pworld; pworld = new World();
    }

    void show_my   () { pworld->show_my   (); }
    void show_enemy() { pworld->show_enemy(); }

    eStatusShoot       is_shoot(const Point2i p)
    {   return pworld->is_shoot(              p);
    }

    bool is_live() const { return pworld->is_live(); }
    
private:
    World* pworld = nullptr;
};

///--------------------------|
/// Тест.                    |
///--------------------------:
inline void testclass_Player()
{
    Player  player;
            player.show_my();
}

#endif // WORLD_H
