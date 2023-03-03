#ifndef FLOT_H
#define FLOT_H

#include "config.h"

enum eStatusShoot
{
    E_LIVE_PALUB,
    E_DEAD_PALUB,
    E_FAULT     ,
    E_NONE      ,
    E_ERROR     ,
    E_HIT       /// ???
};

struct  Ship;
struct  Palub
{
    Point2i position;

    void set_pship(Ship* p)
    {   pship       = p;
        STATUSSHOOT = E_LIVE_PALUB;
    }

    void debug() const
    {   position.debug();
    }

    eStatusShoot damage()
    {
        switch(STATUSSHOOT)
        {   case eStatusShoot::E_NONE      : STATUSSHOOT = E_FAULT      ; break;
            case eStatusShoot::E_LIVE_PALUB: STATUSSHOOT = E_DEAD_PALUB ; break;
            case eStatusShoot::E_DEAD_PALUB:
            case eStatusShoot::E_FAULT     : return        E_ERROR      ;
            case eStatusShoot::E_ERROR     : throw(ERROR_("damage fail"));
        }

        return STATUSSHOOT;
    }

    Ship*&       get_pship () { return pship      ; }
    eStatusShoot get_status() { return STATUSSHOOT; }

private:
    Ship*        pship       = nullptr;
    eStatusShoot STATUSSHOOT = E_NONE ;
};

struct  Ship
{       Ship(const size_t n) : npalubs(n)
        {
        }

    enum eStatus
    {   E_LIVE,
        E_DEAD
    };

    eStatus STATUS = E_LIVE;

    void debug  () const
    {   l(npalubs)
        for(const auto& palub : palubs)
        {   palub.debug();
        }
    }

    const std::vector<Palub>& get() const { return palubs; }

    eStatusShoot damage(eStatusShoot status)
    {
        if(STATUS == E_DEAD) return eStatusShoot::E_DEAD_PALUB;

        cnt_dead++;

        STATUS = cnt_dead == npalubs ? E_DEAD : E_LIVE;

        return STATUS == E_DEAD ? eStatusShoot::E_DEAD_PALUB
                                : eStatusShoot::E_HIT      ;
    }

    bool is_live() const { return STATUS == E_LIVE; }

private:
    const size_t       npalubs     ;
    std::vector<Palub> palubs      ;
    size_t             cnt_dead = 0;

    void set_palubs(std::vector<Point2i>& p)
    {   palubs.resize(p.size());
        for(size_t i = 0; i < p.size(); ++i)
        {   palubs[i].position = p[i];
        }
    }

    bool is_error() const
    {   return palubs.size() != npalubs;
    }

    friend struct Flot;
};

struct  Flot
{       Flot()
        {   m.reserve(cfg.rule.size());
        }

    void debug() const
    {   std::cout << "\n\n----------------:\n";
        for(const auto& ship : m) ship.debug();
    }

    void insert_palubs(std::vector<Point2i>& palubs)
    {   m.push_back(Ship(palubs.size()));
        m.back     ().set_palubs(palubs);
    }

    bool is_error() const
    {   bool error = m.size() != cfg.rule.size();
        for(const auto& ship : m)
        {   ship.is_error();
        }
        return error;
    }

    bool is_live() const
    {   for(const auto& ship : m) if(ship.is_live()) return true;
        return   false; 
    }

    const std::vector<Ship>& get() const { return m; }

private:
    std::vector<Ship> m;
};

inline void testclass_Flotilia()
{
    Flot flot;

    for(size_t i = 0; i < cfg.rule.size(); ++i)
    {   size_t n = cfg.rule[i];
        std::vector<Point2i> palubs(n, {77, 88});
        flot.insert_palubs  (palubs);
    }

    std::cout << (flot.is_error() ? "FAIL ...\a" : "SUCCESS.") << '\n';

    flot.debug();
}
#endif // FLOT_H

