#include <ncurses.h>
#include <fstream>
#include "game.h"

Game::Game(int x, int y)
{
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    srand(time(NULL));

    height = y;
    width = x;

    cells = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        cells[i] = new int[width];
    }

    newGen = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        newGen[i] = new int[width];
    }
}

Game::Game(WINDOW* window)
{
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    srand(time(NULL));
    this->window = window;
    height = getmaxy(window);
    width = getmaxx(window);
    
    cells = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        cells[i] = new int[width];
    }

    newGen = new int*[height];
    for (int i = 0; i < height; ++i)
    {
        newGen[i] = new int[width];
    }
}

void Game::InitMap()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {           
            if (rand() % 2 == 1)
                cells[y][x] = 1;
            else 
                cells[y][x] = 0;
        }
    }
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            newGen[y][x] = cells[y][x];
        }
    }
}

void Game::GameDraw() const
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if(cells[y][x] == 1)
            {               
                attron(COLOR_PAIR(1));
                mvwprintw(window, y, x, "*");
                attroff(COLOR_PAIR(1));
            }
            else 
            {
                mvwprintw(window, y, x, " ");
            }
        }
    }
}

void Game::MakeNewGeneration()
{
    int neighbours = 0;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            neighbours = CheckNeighbours(y, x);    

            if (neighbours == 3 && cells[y][x] == 0)
            {
                newGen[y][x] = 1;
                continue;
            }
            
            if ((neighbours == 2 || neighbours == 3 ) && cells[y][x] == 1)
            {
                newGen[y][x] = 1;
                continue;
            }
            newGen[y][x] = 0;
        }
    }
    
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            cells[y][x] = newGen[y][x];
        }
    }
}

int Game::CheckNeighbours(int posY, int posX)
{
    int neighbours = 0;
    int x, y;
    for (int i = -1; i < 2; ++i)
    {
        for (int j = -1; j < 2; ++j)
        {
            y = posY + i;
            x = posX + j;

            if (y < 0)
                y = height - 1;
            if (y >= height)
                y = 0;

            if (x < 0)
                x = width - 1;
            if (x >= width)
                x = 0;
            
            neighbours += cells[y][x];
        }
    }

    if (cells[posY][posX] == 1)
        neighbours -= 1;

    return neighbours;
}

void Game::SaveState()
{
    std::ofstream out;
    out.open("Save.txt"); 
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (cells[y][x] == 1)
                out << 1;
            else
                out << 0;
        }
        out << std::endl;
    }
    out.close();
}
