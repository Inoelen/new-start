#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
const int Max = 99999;
const int Min = 0;
const int inf = 1e6;
const int mod = 1e9+7;
#define M 1000
#define N 1000
#define ll long long
#define swap(x,y) x^=y^=x^=y
queue<int>pax;
queue<int>pay;
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
string buttonChoice[3] = {"->","  ","  "};int button_pos=0;         //72,80,75,77 上下左右  13回车，32空格 
int maze_n(20),maze_m(40);
int fx(-1),fy(-1);
int hx,hy,tx,ty;
int speed=500,eaten=0,score=0,level=0,length=0,od=0,nd=1; // 1 ,2 ,3 ,4代表右下左上 
int mspeed=500,meaten=0,mscore=0,mlevel=0,mlength=0;
void change(){                                            //改变图的大小 
	system("cls");
	cout << "input maze of length : > " ;cin >> maze_n;
	cout << "input maze of height : > " ;cin >> maze_m;
	if(maze_m<10||maze_n<5){
		cout << "Too small,please again!" << endl;
		system("pause");
	}
	return;
}         
bool welcome(){                                           //欢迎界面 
	system("cls");
	cout << endl << endl;
	cout << "\t\t\t\t\t    !!!!   Snake   !!!!" << endl << endl;
	cout << "\t\t\t\t\t\t" << buttonChoice[0] << " Start" << endl;
	cout << "\t\t\t\t\t\t" << buttonChoice[1] << " change size of maze" << endl;
	cout << "\t\t\t\t\t\t" << buttonChoice[2] << " Quit" << endl << endl << endl << endl << endl << endl << endl;
	cout << "\tbest level: " << mlevel << " \tbest eaten: " << meaten << " \tbest speed: " << mspeed << " \tbest length: " << mlength << " \tbest score: " << mscore << endl;
	int c = _getch();
	if(c==13){
		system("cls");
	    if(button_pos==0) return true;
		else if(button_pos==2) return false;
		else{
			change();return welcome();
		} 
	}
	int choice = _getch();
	if(choice==13){
		system("cls");
	    if(button_pos==0) return true;
		else if(button_pos==2) return false;
		else change();
	}
	else if(choice==72&&button_pos>0){
		buttonChoice[button_pos] = "  ";
		button_pos--;
		buttonChoice[button_pos] = "->";
	}
	else if(choice==80&&button_pos<2){
		buttonChoice[button_pos] = "  ";
		button_pos++;
		buttonChoice[button_pos] = "->";
	}
	return welcome();
}
void loading(){                          //加载界面 
	for(int i=3;i>0;i--){
		system("cls");
		cout << endl << endl;
		cout << "\t\t\t\t\t   LOADING..." << endl << endl;
		cout << "\t\t\t\tGame is started after " << i << " seconds" << endl; 
		Sleep(800);
	}
	return;
}
void waitting(){                        //未完成示意 
	system("cls");
	cout << "\n\n\n\n\t\t\t\tgame is waitting for programming!" << endl;
	cout << "\n\n\t\t\t\t\tlooking forward it!" << endl;
	system("pause");
	return;
}
bool build_show(char **maze){                   //求 
    int sh=(maze_n-1)*(maze_m-1)-eaten;
    if(sh<=6) return true;
    level = eaten/10+1;
	if(speed>=100) speed = 500-50*(level-1); 
	od = nd;
	system("cls");
	cout << "\tlevel: " << level << " \teaten: " << eaten << " \tspeed: " << speed << " \tlength: " << length << " \tscore: " << score << endl;
	cout << endl << endl;
	for(int i=0;i<maze_n;i++)
	    cout << "\t\t\t" << maze[i] << endl;
	int start_time=clock();
	while(clock()-start_time<speed){ 
		if(_kbhit()){
			int temp = _getch();
			int c = _getch();
			if(c==32){
				system("pause");
			} 
			else if(c==72){
				if(od!=2&&od!=4) nd = 4;
			}
			else if(c==80){
				if(od!=2&&od!=4) nd = 2;
			} 
			else if(c==75){
				if(od!=1&&od!=3) nd = 3;
			}
			else if(c==77){
				if(od!=1&&od!=3) nd = 1;
			}
			break;
		}
	} 
	if(nd==1){
		hy++;
		if(hy==0||hy==maze_m-1||maze[hx][hy]=='s') return false;
	}
	else if(nd==2){
		hx ++;
		if(hx==0||hx==maze_n-1||maze[hx][hy]=='s') return false;
	}
	else if(nd==3){
		hy--;
		if(hy==0||hy==maze_m-1||maze[hx][hy]=='s') return false;
	} 
	else{
		hx--;
		if(hx==0||hx==maze_n-1||maze[hx][hy]=='s') return false;
	} 
	maze[hx][hy] = 's';
	pax.push(hx);pay.push(hy);
	if(hx==fx&&hy==fy){
		eaten++;score+=10;length++;
		fx = rand()%(maze_n-2)+1;
	    fy = rand()%(maze_m-2)+1;
		while(maze[fx][fy]=='#'||maze[fx][fy]=='s'){
			fx = rand()%maze_n+1;
	        fy = rand()%maze_m+1;
		}
		maze[fx][fy] = 'F';
	}
	else{
		maze[tx][ty] = ' ';
		pax.pop();pay.pop();
		tx=pax.front(),ty=pay.front();
	}
	return build_show(maze);
}
bool game(){                          //主游戏 
	//cout << "input maze of length : > " ;cin >> maze_n;
	//cout << "input maze of height : > " ;cin >> maze_m;
	char **maze = new char *[maze_n];
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
	for(int i=0;i<3;i++){
		pax.push(tx);pay.push(ty+i);
		maze[tx][ty+i] = 's';
	} 
	fx = rand()%(maze_n-2)+1;
	fy = rand()%(maze_m-2)+1;
	while(maze[fx][fy]=='#'||maze[fx][fy]=='s'){
		fx = rand()%(maze_n-2)+1;
	    fy = rand()%(maze_m-2)+1;
	}
	maze[fx][fy] = 'F';                                                           //初始化结束 
	return build_show(maze); 
}
int main(){
	while(welcome()){
		speed=500,eaten=0,score=0,level=0,od=0,nd=1,length=0,button_pos=0;
		pax = queue<int>();
		pay = queue<int>();
		loading();//waitting();
		if(!game()) cout << "\n\n\n\n\t\t\t\tGame Over!" << endl;
		else cout << "\n\n\n\n\t\t\t\tYou Did It!!" << endl;
		cout << "\n\n\n\n\t\t\t\tlevel: " << level << endl;
		cout << " \n\n\n\n\t\t\t\teaten: " << eaten << endl;
		cout << " \n\n\n\n\t\t\t\tspeed: " << speed << endl;
		cout << " \n\n\n\n\t\t\t\tlength: " << length << endl;
		cout << " \n\n\n\n\t\t\t\tscore: " << score << endl;
		if(mscore<score){
			mlevel = level;meaten=eaten;mspeed=speed;mlength=length;mscore=score;
		}
		getchar();
		system("pause");
	} 
    return 0;
}

