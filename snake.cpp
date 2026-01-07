#include "snake.h"
#include "screen.h"
#include <stdlib.h>

CSnake::CSnake(CRect r, char _c /*=' '*/) : CFramedWindow(r, _c)
{
    resetGame();
}

void CSnake::resetGame()
{
    body.clear();
    int startX = geom.size.x/2;
    int startY = geom.size.y/2;
    body.push_front(CPoint(startX, startY));
    dir = RIGHT;       
    paused = true;     
    help = true;       
    game_over = false;
    level = 1;
    points = 0;
    speed_counter = 0;
    food.x = geom.size.x/2;
    food.y = geom.size.y/2+2;
}

void CSnake::generateFood()
{
    bool colision;
    do {
        colision = false;
        food.x = 1 + rand() % (geom.size.x - 2);
        food.y = 1 + rand() % (geom.size.y - 2);
        for (std::list<CPoint>::iterator temp = body.begin(); temp != body.end(); temp++) {
            if (temp->x == food.x && temp->y == food.y) {
                colision = true;
                break;
            }
        }
    } while (colision);
}

bool CSnake::checkColision(CPoint p)
{
    for (std::list<CPoint>::iterator it = body.begin(); it != body.end(); ++it)
        if (it->x == p.x && it->y == p.y) return true;
    return false;
}

void CSnake::moveSnake()
{
    if (paused || game_over) return;

    CPoint head = body.front();
    if (dir == UP) head.y--;
    else if (dir == DOWN) head.y++;
    else if (dir == LEFT) head.x--;
    else if (dir == RIGHT) head.x++;

    if (head.x <= 0) head.x = geom.size.x - 2;
    else if (head.x >= geom.size.x - 1) head.x = 1;
    if (head.y <= 0) head.y = geom.size.y - 2;
    else if (head.y >= geom.size.y - 1) head.y = 1;

    if (checkColision(head))
    {
        game_over = true;
        return;
    }

    body.push_front(head);
    if (head.x == food.x && head.y == food.y)
    {
        points++;
        level = (points / 15) + 1;
        generateFood();
    }
    else
    {
        body.pop_back();
    }
}

void CSnake::paint()
{
    CFramedWindow::paint();
    gotoyx(geom.topleft.y, geom.topleft.x + 2);
    if (!game_over)
        printl("| LEVEL: %d |", level);
    else
        printl("| GAME OVER, result: %d |", points);
    bool isHead = true;
    for (std::list<CPoint>::iterator p = body.begin(); p != body.end(); p++)
    {
        gotoyx(geom.topleft.y + p->y, geom.topleft.x + p->x);
        if (isHead) {
            printl("*");
            isHead = false;
        } else {
            printl("+");
        }
    }
    gotoyx(geom.topleft.y + food.y, geom.topleft.x + food.x);
    printl("O");

    if (help)
    {
        int midY = geom.topleft.y + 5;
        int midX = geom.topleft.x + 2;
        gotoyx(midY, midX);
        printl("h - toggle help");
        gotoyx(midY + 1, midX);
        printl("p - toggle pause/play");
        gotoyx(midY + 2, midX);
        printl("r - restart game");
        gotoyx(midY + 3, midX);
        printl("arrows - move snake/window");
    }
}

bool CSnake::handleEvent(int key)
{
    if (key == 'h' || key == 'H') 
    {
		help = !help;
		return true;
	}
    if (key == 'p' || key == 'P') 
    {
		paused = !paused;
		return true;
	}
    if (key == 'r' || key == 'R') 
    {
		resetGame();
		return true;
	}

    if (paused && (key == KEY_UP || key == KEY_DOWN || key == KEY_LEFT || key == KEY_RIGHT))
        return CFramedWindow::handleEvent(key);
    if (!paused && !game_over)
    {
        bool moved = false;
        if (key == KEY_UP && dir != DOWN)
        { 
			dir = UP;
			moved = true;
		}
        else if (key == KEY_DOWN && dir != UP)
        {
			dir = DOWN;
			moved = true;
		}
        else if (key == KEY_LEFT && dir != RIGHT) 
        {
			dir = LEFT; 
			moved = true; 
		}
        else if (key == KEY_RIGHT && dir != LEFT) 
        { 
			dir = RIGHT;
			moved = true;
		}
        if (moved) 
        {
            moveSnake();
            speed_counter = 0;
            return true;
        }
    }
    speed_counter++;
    int limit = 15 - level; 
    if (speed_counter >= limit)
    {
        moveSnake();
        speed_counter = 0;
        return true; 
    }

    return false;
}
