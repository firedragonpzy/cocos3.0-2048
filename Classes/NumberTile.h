#ifndef __NUMBER_TILE_H__
#define __NUMBER_TILE_H__

#include "cocos2d.h"

class NumberTile : public cocos2d::LayerColor
{
public:
    virtual bool init();  

    CREATE_FUNC(NumberTile);

	int getNumber() const { return _number; }

	void setNumber(int number);
private:
	int _number;
	cocos2d::Label* _scoreLabel;
};

#endif // __NUMBER_TILE_H__
