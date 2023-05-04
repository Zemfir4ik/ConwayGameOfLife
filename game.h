#include <ncurses.h>
#include <ctime>
#include <cstdlib>


class Game
{
    int **cells;
    int **newGen;
    WINDOW* window;
    int height, width;
public:
    Game(int x, int y);
    Game(WINDOW* window);
    void InitMap();
    void GameDraw() const;
    void MakeNewGeneration();
    int CheckNeighbours(int y, int x);
    void SaveState();
};
