#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
COORD coord = {0,0};
DWORD bytes = 0;
class Snake{
	public :
		queue<int>pax;
		queue<int>pay;
		int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
		
		Snake(){
			pax = queue<int>(); pay = queue<int>();
			dx[0] = 0; dx[1] = 1; dx[2] = 0; dx[3] = -1;
			dy[0] = 1; dy[1] = 0; dy[2] = -1; dy[3] = 0;
		}
};
class Game : public Snake{
	public :
		char buttonChoice[3][3] = {"->","  ","  "}; int button_pos=0;         //72,80,75,77 上下左右  13回车，32空格 
		char **maze;
		int maze_n , maze_m;
		int fx,fy;
		int hx,hy,tx,ty;	
		int speed=500,eaten=0,score=0,level=0,length=0,od=0,nd=1; // 1 ,2 ,3 ,4代表右下左上 
		int mspeed=500,meaten=0,mscore=0,mlevel=0,mlength=0;
		
		Game(){
			maze_n = 20; maze_m = 40;
			fx = -1; fy = -1;
			speed=500;eaten=0;score=0;level=0;length=0;od=0;nd=1;
			mspeed=500;meaten=0;mscore=0;mlevel=0;mlength=0;
		}
		Game(int a, int b){
			maze_n = a; maze_m = b;
			fx = -1; fy = -1;
			speed=500;eaten=0;score=0;level=0;length=0;od=0;nd=1;
			mspeed=500;meaten=0;mscore=0;mlevel=0;mlength=0;
		}	
		void change(){                                            //改变图的大小 
		
			HANDLE hOutBuf = CreateConsoleScreenBuffer( GENERIC_WRITE , FILE_SHARE_WRITE,	NULL , CONSOLE_TEXTMODE_BUFFER , NULL );	
			CONSOLE_CURSOR_INFO cci; cci.bVisible = 0; cci.dwSize = 1;	
			SetConsoleCursorInfo(hOutBuf, &cci);
			
			char warn_msg[100] = " Waitting for building! Any key to back.";
			coord.X = 20; coord.Y = 2;
			WriteConsoleOutputCharacter(hOutBuf , warn_msg , strlen(warn_msg) , coord , &bytes);	  
			SetConsoleActiveScreenBuffer(hOutBuf);
			_getch();
			return;
		}         
		bool welcome(){                                           //欢迎界面 
		
			HANDLE hOutBuf = CreateConsoleScreenBuffer( GENERIC_WRITE , FILE_SHARE_WRITE,	NULL , CONSOLE_TEXTMODE_BUFFER , NULL );
			CONSOLE_CURSOR_INFO cci; cci.bVisible = 0; cci.dwSize = 1;	
			SetConsoleCursorInfo(hOutBuf, &cci);		
			
			char welcome_title[100] = "!!!!   Snake   !!!!";
			char welcome_start[10] = " Start" ;
			char chang_size[100] =  " change size of maze";
			char quit[10] = " Quit";
			coord.X = 40; coord.Y = 2;
			WriteConsoleOutputCharacter(hOutBuf , welcome_title , strlen(welcome_title) , coord , &bytes);	  //下一行 
			coord.X = 44; coord.Y = 3;
			WriteConsoleOutputCharacter(hOutBuf , buttonChoice[0] , 2, coord , &bytes);
			coord.X = 46; coord.Y = 3;
			WriteConsoleOutputCharacter(hOutBuf , welcome_start , strlen(welcome_start) , coord , &bytes);    //下一行 
			coord.X = 44; coord.Y = 4;
			WriteConsoleOutputCharacter(hOutBuf , buttonChoice[1] , 2 , coord , &bytes);
			coord.X = 46; coord.Y = 4;
			WriteConsoleOutputCharacter(hOutBuf , chang_size , strlen(chang_size) , coord , &bytes);    //下一行 
			coord.X = 44; coord.Y = 5;
			WriteConsoleOutputCharacter(hOutBuf , buttonChoice[2] , 2 , coord , &bytes);
			coord.X = 46; coord.Y = 5;
			WriteConsoleOutputCharacter(hOutBuf , quit , strlen(quit) , coord , &bytes);    //下一行 
			SetConsoleActiveScreenBuffer(hOutBuf);
			int choice = _getch();
			if(choice==13){
			    if(button_pos==0) return true;
				else if(button_pos==2) return false;
				else {
					change(); return welcome();
				}
			}
			else if(choice==72&&button_pos>0){
				buttonChoice[button_pos][0] = ' ';
				buttonChoice[button_pos][1] = ' ';
				buttonChoice[button_pos][2] = '\n';
				button_pos--;
				buttonChoice[button_pos][0] = '-';
				buttonChoice[button_pos][1] = '>';
				buttonChoice[button_pos][2] = '\n';
			}
			else if(choice==80&&button_pos<2){
				buttonChoice[button_pos][0] = ' ';
				buttonChoice[button_pos][1] = ' ';
				buttonChoice[button_pos][2] = '\n';
				button_pos++;
				buttonChoice[button_pos][0] = '-';
				buttonChoice[button_pos][1] = '>';
				buttonChoice[button_pos][2] = '\n';
			}
			return welcome();
		}
		void loading(){                          //加载界面 
		
			CONSOLE_CURSOR_INFO cci; cci.bVisible = false; cci.dwSize = 1;
			char load[50] = " LOADING...";
			char wait[100] = "Game is started after ";
			char second[2];
			char seconds[20] =  " seconds";
			for(int i = 3 ; i > 0 ; i--){
				second[0] =  i + '0';
				HANDLE hOutput = CreateConsoleScreenBuffer( GENERIC_WRITE , FILE_SHARE_WRITE , NULL , CONSOLE_TEXTMODE_BUFFER , NULL );
				SetConsoleCursorInfo( hOutput , &cci);
				coord.X = 40; coord.Y = 10;
				WriteConsoleOutputCharacter( hOutput , load , strlen(load) , coord , &bytes);
				coord.X = 33; coord.Y = 13;
				WriteConsoleOutputCharacter( hOutput , wait , strlen(wait) , coord , &bytes);
				coord.X = 33 + strlen(wait);
				WriteConsoleOutputCharacter( hOutput , second , 1 , coord , &bytes);
				coord.X = coord.X + 1;
				WriteConsoleOutputCharacter( hOutput , seconds , strlen(seconds) , coord , &bytes); 
				SetConsoleActiveScreenBuffer( hOutput );
				Sleep(800);
			}
			return;
		}
		void show_maze(){
			
			HANDLE hOutBuf = CreateConsoleScreenBuffer( GENERIC_WRITE , FILE_SHARE_WRITE,	NULL , CONSOLE_TEXTMODE_BUFFER , NULL );
			CONSOLE_CURSOR_INFO cci; cci.bVisible = 0; cci.dwSize = 1;	
			SetConsoleCursorInfo(hOutBuf, &cci);
					
			coord.X = 35;
			for(int i=0;i<maze_n;i++) {
				coord.Y = i+5;
				WriteConsoleOutputCharacter( hOutBuf , maze[i] , strlen(maze[i]) , coord , &bytes);
			}
			SetConsoleActiveScreenBuffer( hOutBuf );   
			return;
			
		} 
		bool game(){                          //主游戏 
			maze = new char *[maze_n];
			for(int i=0;i<maze_n;i++) maze[i] = new char [maze_m+1];
			for(int i=1;i<maze_n-1;i++)                                      //地图的初始化 
			    for(int j=1;j<maze_m-1;j++){
			    	    maze[i][j] = ' ';
				}
			for(int i=0;i<maze_n;i++){
				maze[i][0] = maze[i][maze_m-1] = '#';maze[i][maze_m] = '\0';
			}
			for(int i=0;i<maze_m;i++){
				maze[0][i] = maze[maze_n-1][i] = '#';
			}
			srand(time(0));
			tx = rand()%(maze_n-2)+1;ty = rand()%(maze_m-4)+1;
			hx = tx;hy = ty+2;
			nd = 1;
			for(int i = 0 ; i < 3 ; i++){
				pax.push( tx );pay.push( ty + i );
				maze[ tx ][ ty + i ] = 's';
			} 
			fx = rand() % ( maze_n - 2 ) + 1;
			fy = rand() % ( maze_m - 2 ) + 1;
			while(maze[ fx ][ fy ] == '#' || maze[fx][fy] == 's' || fx <= 0 || fx >= maze_n-1 || fy <= 0 || fy >= maze_m-1){
				fx = rand() % ( maze_n - 2 ) + 1;
			    fy = rand() % ( maze_m - 2 ) + 1;
			}
			maze[fx][fy] = 'F';                                                           //初始化结束 
			int sh = ( maze_n - 1 ) * ( maze_m - 1 ) - eaten;
			while( sh > 6 ) {
				od = nd;
				int start_time = clock();
				while(clock() - start_time < speed){   
					if(_kbhit()){ 
						int temp = _getch();
						int c = _getch();
						if(c == 72){
							if(od != 2 && od != 4) nd = 4;
							break;
						}
						else if(c == 80){
							if(od != 2 && od != 4) nd = 2;
							break;
						} 
						else if(c == 75){
							if(od != 1 && od != 3) nd = 3;
							break;
						}
						else if(c == 77){
							if(od != 1&& od != 3) nd = 1;
							break;
						}
						if(temp == 32) _getch();
					}
				} 
				if(nd == 1){
					hy++;
					if(hy == 0 || hy == maze_m-1 || maze[hx][hy] == 's') return false;
				}
				else if(nd == 2) {
					hx ++;
					if(hx == 0 || hx == maze_n-1 || maze[hx][hy] == 's') return false;
				}
				else if(nd == 3){
					hy--;
					if(hy == 0 || hy == maze_m-1 || maze[hx][hy] == 's') return false;
				} 
				else{
					hx--;
					if(hx == 0 || hx == maze_n-1 || maze[hx][hy] == 's') return false;
				} 
				maze[hx][hy] = 's';
				pax.push(hx); pay.push(hy);
				if(hx == fx && hy == fy) {
				//	eaten++; score+=10; length++;            成绩计算 
					fx = rand()%(maze_n-2)+1;
				    fy = rand()%(maze_m-2)+1;
					while(maze[fx][fy] == '#' || maze[fx][fy] == 's' || fx < 0 || fx >= maze_n-1 || fy < 0 || fy >= maze_m-1) {
						fx = rand()%maze_n+1;
				        fy = rand()%maze_m+1;
					}
					maze[fx][fy] = 'F';
				}
				else {
					tx=pax.front(),ty=pay.front();
					pax.pop();pay.pop();
					maze[tx][ty] = ' ';	
				}
				sh = (maze_n-1)*(maze_m-1)-eaten;
				show_maze();	
			}
			if(sh <= 6) return true; 
		}

		void start_game(){
				
			while(welcome()){
					
				this->pax = queue<int>();
				this->pay = queue<int>();
				
				HANDLE hOutBuf = CreateConsoleScreenBuffer( GENERIC_WRITE , FILE_SHARE_WRITE,	NULL , CONSOLE_TEXTMODE_BUFFER , NULL );    //建立缓冲区 
				CONSOLE_CURSOR_INFO cci; cci.bVisible = 0; cci.dwSize = 1;	//光标属性 
				SetConsoleCursorInfo(hOutBuf, &cci);                        //设置给缓冲区 
				
				loading();
				if(!game()) {
					coord.X = 40; coord.Y = 10;
					WriteConsoleOutputCharacter( hOutBuf , "game Over!" , 10 , coord , &bytes);
					coord.X = 35; coord.Y = 12;
					WriteConsoleOutputCharacter( hOutBuf , "any key to continue.." , 20 , coord , &bytes);
				}
				else {
					coord.X = 40; coord.Y = 10;
					WriteConsoleOutputCharacter( hOutBuf , "You Did It!!" , 12 , coord , &bytes);
				}
				SetConsoleActiveScreenBuffer( hOutBuf );
				_getch();
			}
		}			
};
int main(){
	Game gam;	
 	gam.start_game();
    return 0;
}

