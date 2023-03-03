#include "flot_generator.h"

struct  World   : public std::vector< std::vector<Palub*>>
{       World() :        std::vector< std::vector<Palub*>>(cfg.R,
                                      std::vector<Palub*> (cfg.C)),
                         alloc(cfg.R, std::vector<Palub>  (cfg.C))
        {
            FlotGenerator gen(flot);

            auto& m = *this;

            for    (size_t r = 0; r < m   .size(); ++r)
            {   for(size_t c = 0; c < m[0].size(); ++c)
                {
                    m[r][c]            = &alloc[r][c];
                    m[r][c]->position  = {c, r};
                }
            }

            for    (const auto& ship  : flot.get())
            {   for(const auto& palub : ship.get())
                {
                    const Point2i&     p = palub.position;
                    m[p.y][p.x]          = const_cast<Palub*>(&palub);
                    m[p.y][p.x]->set_pship(const_cast<Ship* >(&ship));
                }
            }
        }

    eStatusShoot is_shoot(const Point2i p)
    {
        auto&  ppalub  = ((*this)[p.y][p.x]);
        auto&  pship   = ((*this)[p.y][p.x])->get_pship();

        auto   status  = ppalub->damage();
        if    (status == eStatusShoot::E_DEAD_PALUB) 
               status  = pship ->damage(status);
        return status;
    }

    void debug()
    {
        for    (const auto& r : *this)
        {   for(const auto& e :  r   )
            {   std::cout << (e->get_pship() == nullptr ? '.' : '*');
            }   std::cout << '\n';
        }       std::cout << '\n';
    }

    void show_my   () { show('O'); }
    void show_enemy() { show(' '); }

    bool is_live() const { return flot.is_live(); }

private:
    void show(char a)
    {   std::vector<std::string> map(cfg.R, std::string(cfg.C, '.'));

        auto& m = *this;

        for     (size_t r = 0; r < m   .size(); ++r)
        {   for (size_t c = 0; c < m[0].size(); ++c)
            {
                switch(m[r][c]->get_status())
                {
                    case E_LIVE_PALUB: map[r][c] =  a ; break;
                    case E_DEAD_PALUB: map[r][c] = 'X'; break;
                    case E_FAULT     : map[r][c] = '.'; break;
                    case E_NONE      : map[r][c] = ' '; break;
                }
            }
        }

        myl::info(map);
    }

    Flot flot;

    std::vector<std::vector<Palub>> alloc;
};

///--------------------------|
/// Тест.                    |
///--------------------------:
inline void testclass_World()
{
    World world;
          world.debug  ();
          world.show_my();
}
