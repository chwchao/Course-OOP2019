#ifndef CLYDE_H
#define CLYDE_H

#include "character.h"
#include <QObject>
#include <QWidget>

class Clyde : public Character
{
public:
    Clyde(int x, int y, QLabel *character,QGraphicsItem *parent = nullptr);
    virtual void pic_change();
    virtual bool direction_controlled(QChar key, Character* pacman = nullptr, Character* ghost = nullptr);
    virtual bool move(Character* pacman = nullptr);

private:
    int order[4] = {X_POSITIVE, X_NEGATIVE, Y_POSITIVE, Y_NEGATIVE};
    bool take_another_way = false;
};

#endif // BLINKY_H
