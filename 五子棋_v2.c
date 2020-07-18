#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getch.h>

// 棋盘
char board[15][15];
// 棋子坐标
char kx = 7 , ky = 7;
// 角色
char role = '@';

// 显示棋盘
void show_board(void)
{
	system("clear");
	for(int i=0; i<15; i++)
	{
		for(int j=0; j<15; j++)
		{
			if(board[i][j])
			{
				printf(" %c",board[i][j]);
			}
			else
			{
				printf(" *");
			}
		}
		printf("\n");
	}
}
// 落子
void get_key(void)
{
	printf(" -----------请%c落子-----------\n",role);
	for(;;)
	{
		printf("\33[%hhd;%hhdH",kx+1,(ky+1)*2);
		switch(getch())
		{
			case 183: kx>0 && kx--; break;
			case 184: kx<14 && kx++; break;
			case 185: ky<14 && ky++; break;
			case 186: ky>0 && ky--; break;
			case 10: if(!board[kx][ky])
			{
				board[kx][ky] = role;
				return;
			}
		}
	}
	
}

int count_eqkey(int ox,int oy)
{
	int count = 0;
	for(int x=kx+ox,y=ky+oy; x>=0 && x<15 && y>=0 && y<15 &&
		board[x][y]==board[kx][ky]; x+=ox,y+=oy)
	{
		count++;
	}
	return count;
}

// 检查五子
bool check_board(void)
{
	if(count_eqkey(0,-1)+count_eqkey(0,1) >= 4)
		return true;
	if(count_eqkey(-1,0)+count_eqkey(1,0) >= 4)
		return true;
	if(count_eqkey(-1,-1)+count_eqkey(1,1) >= 4)
		return true;
	if(count_eqkey(-1,1)+count_eqkey(1,-1) >= 4)
		return true;

	return false;
}
int main()
{
	for(;;)
	{
		show_board();

		get_key();
		
		if(check_board())
		{
			show_board();
			printf("恭喜%c胜利,游戏结束!\n",role);
			return 0;
		}

		role = '@'==role?'#':'@';
	}

}
