#include <stdio.h>
#include <stdlib.h>
#include "getch.h" // linux 에서 getch 함수

#define W_SIZE 10 // 오목판 가로 사이즈
#define H_SIZE 10 // 오목판 세로 사이즈
#define X 0
#define Y 1
char turn = 0,
	bwin = 0,
	wwin = 0;
int check = 0;
int board[W_SIZE+2][H_SIZE+2] = {0};
int cursor[2] = {W_SIZE / 2, H_SIZE / 2};

void DrawingBoard(void); // 오목칸 그리기 함수
void CheckingWin(void); // 승리 판정 함수
void MovingCursor(void); // 키 입력 - 커서 이동
void FinalSelect(void); // 키 입력 - 커서 이동, 재시작, 종료
void Reset(void); // 초기화

int main(void)
{
	while(1)
	{
		if(check == 1) Reset();
		DrawingBoard();
		CheckingWin();
		if(bwin > 0 || wwin > 0) // 판정
		{
			while(check == 0)
			{
				cursor[X] = 99;
				DrawingBoard();
				if(wwin == 99 && bwin == 99) printf("　승부가 나지 않았습니다!!.\n\n");

				else if(turn == 1) printf("　● 흑의 승리! ●\n\n");
				else printf("　○ 백의 승리! ○\n\n");
				printf("　(다시 시작 : r, R)\n　(종료 　　 : q, Q)\n");

				FinalSelect();
				if(check > 0) break;
			}
			Reset();
			DrawingBoard();
		}
		if(check == 2) break; // 종료 시 반복문 밖으로 탈출
		check = 0;

		if(turn == 0) printf("　● 흑의 차례 ●\n\n");
		else printf("　○ 백의 차례 ○\n\n");
    printf("  (UP           : w)\n  (DOWN         : s)\n  (LEFT         : a)\n  (RIGHT        : d)\n");
    printf("  (ENTER        : z)\n  (SPACE        : x)\n");
		printf("　(다시 시작 : r, R)\n　(종료 　　 : q, Q)\n");

		MovingCursor();
	}
	return 0;
}

/* 칸 사이의 공백이 없는 오목판 */
void DrawingBoard(void)
{
	int board_x, board_y, i;

	system("clear");
	for(board_y = 1 ; board_y <= H_SIZE ; board_y++)
	{
		printf("　");
		for(board_x = 1 ; board_x <= W_SIZE ; board_x++)
		{
			if(cursor[X] == board_x && cursor[Y] == board_y) // 커서 표시
			{
				if(board_y != 1 && board_y != H_SIZE)
				{
					switch(board[board_y][board_x])
					{
						case 0 :
							printf("▒");
							break;
						case 1 :
							printf("□");
							break;
						case 2 :
							printf("■");
							break;
					}
				} else if(board_y == H_SIZE) {
					switch(board[board_y][board_x])
					{
						case 0 :
							printf("▒");
							break;
						case 1 :
							printf("□");
							break;
						case 2 :
							printf("■");
							break;
					}
				} else {
					switch(board[board_y][board_x])
					{
						case 0 :
							printf("▒");
							break;
						case 1 :
							printf("□");
							break;
						case 2 :
							printf("■");
							break;
					}
				}
			} else {
				if(board_y != 1 && board_y != H_SIZE)
				{
					switch(board[board_y][board_x]) // 오목알 표시
					{
						case 0 :
							if(board_x == 1) printf("┠");
							else if(board_x == W_SIZE)  printf("┨");
							else printf("┼");
							break;
						case 1 :
							printf("○");
							break;
						case 2 :
							printf("●");
							break;
					}
				} else if(board_y == H_SIZE) {
					switch(board[board_y][board_x])
					{
						case 0 :
							if(board_x == 1) printf("┗");
							else if(board_x == W_SIZE)  printf("┛");
							else printf("┷");
							break;
						case 1 :
							printf("○");
							break;
						case 2 :
							printf("●");
							break;
					}
				} else {
					switch(board[board_y][board_x])
					{
						case 0 :
							if(board_x == 1) printf("┏");
							else if(board_x == W_SIZE)  printf("┓");
							else printf("┯");
							break;
						case 1 :
							printf("○");
							break;
						case 2 :
							printf("●");
							break;
					}
				}
			}
		}
		printf("\n");
	}
}
//*/

void CheckingWin(void)
{
	int fullcount = 0;
	int i, j;

	bwin = 0;
	wwin = 0;

	for(j = 1 ; j < H_SIZE+1 ; j++) // 오목판 꽉참
	{
		for(i = 1 ; i < W_SIZE+1 ; i++)
		{
			if(board[j][i] != 0) fullcount++;
		}
	}

	if(fullcount == W_SIZE * H_SIZE)
	{
		bwin = 99;
		wwin = 99;
	}

	for(j = 1 ; j < H_SIZE+1 ; j++) // ㅡ 모양 오목
	{
		for(i = 1 ; i < W_SIZE-3 ; i++)
		{
			if(board[j][i] == 1
			&& board[j][i+1] == 1
			&& board[j][i+2] == 1
			&& board[j][i+3] == 1
			&& board[j][i+4] == 1

			&& board[j][i-1] != 1
			&& board[j][i+5] != 1) bwin = 1;

			else if(board[j][i] == 2
				 && board[j][i+1] == 2
				 && board[j][i+2] == 2
				 && board[j][i+3] == 2
				 && board[j][i+4] == 2

				 && board[j][i-1] != 2
				 && board[j][i+5] != 2) wwin = 1;
		}
	}

	for(i = 1 ; i < W_SIZE+1 ; i++) // ㅣ 모양 오목
	{
		for(j = 1 ; j < H_SIZE-3 ; j++)
		{
			if(board[j][i] == 1
			&& board[j+1][i] == 1
			&& board[j+2][i] == 1
			&& board[j+3][i] == 1
			&& board[j+4][i] == 1

			&& board[j-1][i] != 1
			&& board[j+5][i] != 1) bwin = 1;

			else if(board[j][i] == 2
				 && board[j+1][i] == 2
				 && board[j+2][i] == 2
				 && board[j+3][i] == 2
				 && board[j+4][i] == 2

				 && board[j-1][i] != 2
				 && board[j+5][i] != 2) wwin = 1;
		}
	}

	for(j = 1 ; j < H_SIZE-3 ; j++) // ＼ 모양 오목
	{
		for(i = 1 ; i < W_SIZE-3 ; i++)
		{
			if(board[j][i] == 1
			&& board[j+1][i+1] == 1
			&& board[j+2][i+2] == 1
			&& board[j+3][i+3] == 1
			&& board[j+4][i+4] == 1

			&& board[j-1][i-1] != 1
			&& board[j+5][i+5] != 1) bwin = 1;

			else if(board[j][i] == 2
				 && board[j+1][i+1] == 2
				 && board[j+2][i+2] == 2
				 && board[j+3][i+3] == 2
				 && board[j+4][i+4] == 2

				 && board[j-1][i-1] != 2
				 && board[j+5][i+5] != 2) wwin = 1;
		}
	}

	for(i = 1 ; i < W_SIZE-3 ; i++) // / 모양 오목
	{
		for(j = 5 ; j < H_SIZE+1 ; j++)
		{
			if(board[j][i] == 1
			&& board[j-1][i+1] == 1
			&& board[j-2][i+2] == 1
			&& board[j-3][i+3] == 1
			&& board[j-4][i+4] == 1

			&& board[j-5][i+5] != 1
			&& board[j+1][i-1] != 1) bwin = 1;

			else if(board[j][i] == 2
				 && board[j-1][i+1] == 2
				 && board[j-2][i+2] == 2
				 && board[j-3][i+3] == 2
				 && board[j-4][i+4] == 2

				 && board[j-5][i+5] != 2
				 && board[j+1][i-1] != 2) wwin = 1;
		}
	}
}

void MovingCursor(void)
{
	char ch;

	ch = getch();
	switch(ch) // 화살표키 인식
	{
	case 'w': // UP
		if(cursor[Y] != 1) cursor[Y]--;
		else cursor[Y] = H_SIZE;
		break;
	case 'a' : // Left
		if(cursor[X] != 1) cursor[X]--;
		else cursor[X] = W_SIZE;
		break;
	case 'd' : // Right
		if(cursor[X] != W_SIZE) cursor[X]++;
		else cursor[X] = 1;
		break;
	case 's' : // Down
		if(cursor[Y] != H_SIZE) cursor[Y]++;
		else cursor[Y] = 1;
		break;
	case 'x' : //Space
		if(turn == 0 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 1;
			turn = 1;
		}
		else if(turn == 1 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 2;
			turn = 0;
		}
		break;
	case 'z' : //Enter
		if(turn == 0 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 1;
			turn = 1;
		}
		else if(turn == 1 && board[cursor[Y]][cursor[X]] == 0)
		{
			board[cursor[Y]][cursor[X]] = 2;
			turn = 0;
		}
		break;
	case 'r':
		check = 1;
		break;
	case 'R':
		check = 1;
		break;
	case 'q' :
		check = 2;
		break;
	case 'Q' :
		check = 2;
		break;
	default :
		check = 0;
		break;
	}
}

void FinalSelect(void)
{
	char ch;

	ch = getch();
	switch(ch) // 재시작, 종료 여부
	{
	case 'r':
		check = 1;
		break;
	case 'R':
		check = 1;
		break;
	case 'q' :
		check = 2;
		break;
	case 'Q' :
		check = 2;
		break;
	default :
		check = 0;
		break;
	}
}

void Reset(void)
{
	int i, j;

	turn = 0;
	wwin = 0;
	bwin = 0;
	cursor[X] = W_SIZE / 2;
	cursor[Y] = H_SIZE / 2;
	for(i = 1 ; i < W_SIZE ; i++)
	{
		for(j = 1 ; j < H_SIZE ; j++) board[j][i] = 0;
	}
}
