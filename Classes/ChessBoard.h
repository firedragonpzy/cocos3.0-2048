#ifndef __CHESS_BOARD_H__
#define __CHESS_BOARD_H__

#include "cocos2d.h"

class NumberTile;
class ChessBoard : public cocos2d::Layer
{
public:

    virtual bool init();  
    CREATE_FUNC(ChessBoard);

	cocos2d::Point getTilePostion(int x, int y);
	void checkGameOver();
	void generateNewTile();

	bool isChessBoardFull();
	
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	//(x2, y2)合并到(x1, y1)
	void mergeTwoTile(int x1, int y1, int x2, int y2);
	//(x2, y2)移动到(x1, y1)
	void moveTileTo(int x1, int y1, int x2, int y2);
private:
	cocos2d::Label *_scoreLabel;
	cocos2d::Point _startPoint;
	cocos2d::Point _endPoint;
	std::map<int, NumberTile*> _tileMap;
	int _score;
	int _chess[4][4];
	std::vector<int> _emptyTiles;
};

#endif // __CHESS_BOARD_H__
