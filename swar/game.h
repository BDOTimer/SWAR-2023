#ifndef GAME_H
#define GAME_H

///----------------------------------------------------------------------------|
/// "game.h"
///----------------------------------------------------------------------------:
#include "player.h"

struct  Game
{       Game() : what_player_for_show(0)
        {   players.emplace_back(Player(L"Player-01"));
            players.emplace_back(Player(L"Player-02"));

            loop();
        }

    ///------------------------|
    /// Для кого показываем?   |
    ///------------------------:
    size_t what_player_for_show;

    void loop()
    {
        ///--------------------|
        /// Чей первый ход?    |
        ///--------------------:
        size_t id = (size_t)myl::rrand(0, 2);

        int cnt_steps = 1;

        while(is_game())
        {
            l(cnt_steps) cnt_steps++;

            Point2i point  = Generator::rrand();
            auto    status = players[next(id)].is_shoot(point);
            auto    I      = id;

            switch (status)
            {
        case eStatusShoot::E_NONE      : throw(ERROR_("FATAL LOGIC")); break;
        case eStatusShoot::E_LIVE_PALUB: throw(ERROR_("FATAL LOGIC")); break;
        case eStatusShoot::E_DEAD_PALUB: ms(L"Корабль ПОТОПЛЕН!")    ; break;
        case eStatusShoot::E_FAULT     : ms(L"ПРОМАХ...");id=next(id); break;
        case eStatusShoot::E_HIT       : ms(L"Корабль горит...")     ; break;
        case eStatusShoot::E_ERROR     : ms(L"...E_ERROR...")        ; break;
            }

            if ( I     == what_player_for_show &&
                status != eStatusShoot::E_ERROR )
            {   show_console(what_player_for_show); //std::cin.get();
            }
        }

        gameover();
    }

private:
    std::vector<Player> players;

    size_t next(size_t id){ return 1 - id; }

    void show_console(size_t id)
    {
        std::cout << "\nmy:---------------:\n";
        players[             id ].show_my   ();
        players[        next(id)].show_enemy();

        std::cout << "\nenemy:-------(чит):\n";
        players[        next(id)].show_my   ();
        players[             id ].show_enemy();
    }

    bool is_game()
    {   return players[0].is_live() && players[1].is_live();
    }

    void gameover()
    {
        myl::BANNER(
        "     |---------------------------|",
        "     |        GAME OVER!         |",
        "     |---------------------------:");

        size_t id = players[0].is_live() ? 0 : 1;

        std::wcout  << L"      Игрок <"
                    << players[id].name
                    << L"> выиграл!\n\n";

        std::cout << "\n:---:" << 1 - id << "\n"; players[    id].show_my();
        std::cout << "\n:---:" << 2 - id << "\n"; players[1 - id].show_my();
    }

    void ms(const wchar_t* mess) { std::wcout << mess << '\n'; }
};

///--------------------------|
/// Тест.                    |
///--------------------------:
inline void testclass_Game()
{
    Game run;
}
#endif // GAME_H

