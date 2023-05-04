#include <ncurses.h>
#include <string>
#include "game.h"

int main()
{
    initscr();
    curs_set(0);
    noecho();
    start_color();
    keypad(stdscr, true);

    mvprintw(0,0, "Choose mode: ");
    const std::string choices[2] = {"1. Dialog mode", "2. Simulation mode"};

    int highlight = 0;
    int choice;
    while (true)
    {
        highlight = highlight % 2 + 1;
        for (int i = 1; i < 3; ++i)
        {
            if (highlight == i)
                wattron(stdscr, A_REVERSE);
            mvprintw(i, 0, "%s", choices[i - 1].c_str());
            wattroff(stdscr, A_REVERSE);
        }
        choice = getch();
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                highlight = (highlight + 2) % 2;
                break;
            case KEY_DOWN:
                highlight++;
                highlight = (highlight + 2) % 2;
                break;
        }
        if (choice == 10)
            break;        
    }


    halfdelay(1);

    if (highlight == 1)
    {
        clear();
        start_color();
        assume_default_colors(0,7);
        
        Game a(stdscr);
        a.InitMap();
        a.GameDraw();
        while(getch() != '`')
        {
            a.MakeNewGeneration();
            a.GameDraw();
        }
    }
    if (highlight == 2)
    {
        clear();
        mvprintw(0, 0, "Enter size:");
        echo();

        int height;
        mvprintw(1, 0, "Height: ");
        mvscanw(1, 8, "%i", &height);

        int width;
        mvprintw(2, 0, "Width: ");
        mvscanw(2, 7, "%i", &width);

        clear();
        mvprintw(0, 0, "Simulation in progress");
        mvprintw(1, 0, "Press '`' to stop");

        Game b(width, height);
        b.InitMap();
        while(getch() != '`')
        {
            b.MakeNewGeneration();
        }
        b.SaveState();    
    }
    endwin();
    return 0;
};
