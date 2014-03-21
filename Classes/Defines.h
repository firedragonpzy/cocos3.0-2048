USING_NS_CC;

const static Color4B Tile_Color[] = 
{
	Color4B(255, 255, 255, 255),	//1
	Color4B(255, 0, 0, 255),		//2
	Color4B(0, 255, 0, 255),		//4
	Color4B(0, 0, 255, 255),		//8
	Color4B(255, 255, 0, 255),		//16
	Color4B(255, 0, 255, 255),		//32
	Color4B(0, 255, 255, 255),		//64
	Color4B(120, 0, 0, 255),		//128
	Color4B(0, 120, 0, 255),		//256
	Color4B(0, 0, 120, 255),		//512
	Color4B(120, 120, 0, 255),		//1024
	Color4B(120, 0, 120, 255),		//2048
};

#define SPACE 10
#define TILE_LEN 80
#define CHESS_LEN (SPACE*5+TILE_LEN*4)

#define DESIGN_WIDTH 960
#define DESIGN_HEIGHT 640
#define MI(x) (1<<(x))
#define PI 3.1415926

#define MOVE_SPPED 2000