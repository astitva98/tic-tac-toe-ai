#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int win2(char* arr){

	//for player 1
	//cout<<3<<endl;
	for(int i=0;i<3;i++){
		if(arr[i]== '0' && arr[i+3]== '0' && arr[i+6]=='0')
			return 1;
		if(arr[i]== '1' && arr[i+3]== '1' && arr[i+6]=='1')
			return 2;
		int y=3*i;
		if(arr[y]=='0' && arr[y+1]== '0' && arr[y+2]=='0')
			return 1;
		if(arr[y]== '1' && arr[y+1]== '1' && arr[y+2]=='1')
			return 2;
	}
	if(arr[0]=='0' && arr[4]== '0' && arr[8]=='0')
		return 1;
	if(arr[2]== '1' && arr[4]== '1' && arr[6]=='1')
		return 2;
	if(arr[0]=='1' && arr[4]== '1' && arr[8]=='1')
		return 2;
	if(arr[2]== '0' && arr[4]== '0' && arr[6]=='0')
		return 1;
	for(int i=0;i<9;i++){
		if(i==8 && arr[i] != ' ' )	return -1;
		if(arr[i] == ' ')	break;
	}
	return 0;

}


int drawBoard(char* arr){
printf(" %c | %c | %c \n ---------\n %c | %c | %c \n ---------\n %c | %c | %c \n",arr[0],arr[1],arr[2],arr[3],arr[4],arr[5],arr[6],arr[7],arr[8]);
return win2(arr);

}
char human = '0';
char ai = '1';

int minimax(char* board , int deapth, bool maxx){
	int win = win2(board);
	if(win == 1)	return -10;
	if(win == 2)	return 10;
	if(win == -1)	return 0;

	if(maxx){
		int choice = -1;
		int bestscore = -1000000;
		for(int i=0;i<9;i++){
			if(board[i] == ' '){
				board[i] = ai;
				int score = minimax(board , deapth+1 , false);
				board[i] = ' ';
				if(score > bestscore){
					choice = i;
					bestscore = score;
				}
			}
		}
		// board[choice] = ai;
		return bestscore;
	}
	else{
		int choice = -1;
		int bestscore = 1000000;
		for(int i=0;i<9;i++){
			if(board[i] == ' '){
				board[i] = human;
				int score = minimax(board , deapth+1 , true);
				board[i] = ' ';
				if(score < bestscore){
					choice = i;
					bestscore = score;
				}
			}
		}
		// board[choice] = ai;
		return bestscore;
	}
}

int helper(char* board , int deapth , bool maxx){
	int bestscore = -10000;
	int choice = -1;
	for(int i=0;i<9;i++){
		if(board[i] == ' '){
			board[i] = ai;
			int score = minimax(board , 0 , false);
			board[i] = ' ';
			if(score > bestscore){
				bestscore = score;
				choice = i;
			}
		}
	}
	cout<<choice<<endl;
	return choice;
}

int main(){

	char play='y';
	while(play=='y')
	{
		cout<<"Welcome to Tic-Tac-Toe\n\nPress 1 for new game\nPress 2 for stats\nPress 3 to reset stats\nPress 4 to quit\nPress 5 to play against ai\n\n";
		int choice;
		cin>>choice;
		switch (choice){

			case 1 :	{
							char arr[]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
							int win=drawBoard(arr);
							int move;
							while (!win){
				
								cout<<"Player 1 turn\n\n";
								int ui=1;
								while(ui)
								{
									cin>>move;
									if(arr[move]!=' '){
									cout<<"Wrong move!!!\nTry again\n\n";
													
									}else
									ui=0;
								}
								arr[move]='0';
								win=drawBoard(arr);
								if(win==0){
									cout<<"Player 2 turn\n\n";
									//cin>>move;
									ui=1;
									while(ui)
									{
										cin>>move;
										if(arr[move]!=' '){
										cout<<"Wrong move!!!\nTry again\n\n";
														
										}else
										ui=0;
									}
									arr[move]='1';
									win=drawBoard(arr);
								}
							}
						
							if(win==1){
								string line1;
								string line2;
								string line3;
								fstream fio;
								fio.open("../data/stats.txt");
								getline(fio,line1);
								getline(fio,line2);
								getline(fio,line3);
								//cout<<"TEST"<<line2<<endl<<endl;				
								int t=stoi(line1);
								t++;
								line1=to_string(t);
								fio.seekg(0,ios::beg);
								fio<<line1<<endl;
								fio<<line2<<endl;
								fio<<line3<<endl;
								fio.close();
								//write to file
							}
							if(win==2){
								cout<<"Player 2 wins\n\n!!";
								fstream fio;
								fio.open("../data/stats.txt");
								string line1;
								string line2;
								string line3;
								getline(fio,line1);
								getline(fio,line2);
								getline(fio,line3);
								//cout<<"TEST"<<line2<<endl<<endl;				
								int t=stoi(line2);
								t++;
								line2=to_string(t);
								fio.seekg(0,ios::beg);
								fio<<line1<<endl;
								fio<<line2<<endl;
								fio<<line3<<endl;
								fio.close();
								//write to file
					
							}
							if(win==-1){
								cout<<"Tie\n\n!!";
								fstream fio;
								fio.open("../data/stats.txt");
								string line1;
								string line2;
								string line3;
								getline(fio,line1);
								getline(fio,line2);
								getline(fio,line3);
								//cout<<"TEST"<<line2<<endl<<endl;				
								int t=stoi(line3);
								t++;
								line3=to_string(t);
								fio.seekg(0,ios::beg);
								fio<<line1<<endl;
								fio<<line2<<endl;
								fio<<line3<<endl;
								fio.close();
							}
							cout<<"Play again? (y/n)";
							cin>>play;
							if(!(play=='y'||play=='n')){
								cout<<"\nWrong input\n\n";
								return 0;
							}
							break;
						}
		
				case 2 : 
				{
					ifstream fin;
					fin.open("../data/stats.txt");
					if(!fin){
						ofstream fop;
						fop.open("../data/stats.txt");
						fop<<'0'<<endl;
						fop<<'0'<<endl;
						fop.close();
						fin.open("../data/stats.txt");
					}
					string line1;
					string line2;
					
					getline(fin,line1);
					getline(fin,line2);
					cout<<"Player 1 has won "<<line1 <<" games\nPlayer 2 has won "<<line2<<" games\n\n";
					
		
					fin.close();
					//show stats
					cout<<"--------------------------\n\n";
					break;
		
				}
				case 3 : 
				{
					ofstream fop;
					fop.open("../data/stats.txt");
					fop<<'0'<<endl;
					fop<<'0'<<endl;
					fop.close();
					cout<<"\n\n------------------------\nStats have been reset!\n------------------------\n\n";
					break;
				}
				case 4:
				{
					play='n';
					break;
				}
				case 5:
				{
							char arr[]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
							cout<<"TEST YOUR SKILLS AGAINST THE BEST\n\nPress 1 to start.\nPress 2 for AI to start\n\n\n";
							int fm;
							cin>>fm;
							int win=drawBoard(arr);
							int move;
							// int fm;
							
							if(fm==1){
								while (!win){
					
									cout<<"Your turn\n\n";
									int ui=1;
									while(ui)
									{
										cin>>move;
										if(arr[move]!=' '){
										cout<<"Wrong move!!!\nTry again\n\n";
														
										}else
										ui=0;
									}
									arr[move]='0';
									win=drawBoard(arr);
									if(win==0){
										cout<<"AI turn\n\n";
										//cin>>move;
										ui=1;
										// while(ui)
										// {
										move = helper(arr , 0 , true);
											//cin>>move;
											// if(arr[move]!=' '){
											// cout<<"Wrong move!!!\nTry again\n\n";
															
											// }else
											// ui=0;
										// }
										arr[move]='1';
										win=drawBoard(arr);
									}
								}
							
								if(win==1){
									cout<<"Player 1 wins\n\n!!";
									fstream fio;
									fio.open("../data/stats.txt");
									string line1;
									string line2;
									string line3;
									getline(fio,line1);
									getline(fio,line2);
									getline(fio,line3);				
									int t=stoi(line1);
									t++;
									line1=to_string(t);
									fio.seekg(0,ios::beg);
									fio<<line1<<endl;
									fio<<line2<<endl;
									fio.close();
									//write to file
								}
								if(win==2){
									cout<<"Player 2 wins\n\n!!";
									fstream fio;
									fio.open("../data/stats.txt");
									string line1;
									string line2;
									string line3;
									getline(fio,line1);
									getline(fio,line2);
									getline(fio,line3);
									//cout<<"TEST"<<line2<<endl<<endl;				
									int t=stoi(line2);
									t++;
									line2=to_string(t);
									fio.seekg(0,ios::beg);
									fio<<line1<<endl;
									fio<<line2<<endl;
									fio.close();
									//write to file
						
								}
							}
							else{
								while (!win){
					
									cout<<"AI Turn\n\n";
									int ui=1;
									move = helper(arr , 0 , true);
									arr[move]='1';
									win=drawBoard(arr);
									// while(ui)
									// {
									// 	cin>>move;
									// 	if(arr[move]!=' '){
									// 	cout<<"Wrong move!!!\nTry again\n\n";
														
									// 	}else
									// 	ui=0;
									// }
									// arr[move]='0';
									// win=drawBoard(arr);
									if(win==0){
										while(ui)
										{
											cin>>move;
											if(arr[move]!=' '){
											cout<<"Wrong move!!!\nTry again\n\n";
															
											}else
											ui=0;
										}
										arr[move]='0';
										win=drawBoard(arr);
										// cout<<"AI turn\n\n";
										//cin>>move;
										// ui=1;
										// while(ui)
										// {
										// move = helper(arr , 0 , true);
											//cin>>move;
											// if(arr[move]!=' '){
											// cout<<"Wrong move!!!\nTry again\n\n";
															
											// }else
											// ui=0;
										// }
										// arr[move]='1';
										// win=drawBoard(arr);
									}
								}
							
								if(win==1){
									cout<<"Player 1 wins\n\n!!";
									fstream fio;
									fio.open("../data/stats.txt");
									string line1;
									string line2;
									string line3;
									getline(fio,line1);
									getline(fio,line2);
									getline(fio,line3);				
									int t=stoi(line1);
									t++;
									line1=to_string(t);
									fio.seekg(0,ios::beg);
									fio<<line1<<endl;
									fio<<line2<<endl;
									fio.close();
									//write to file
								}
								if(win==2){
									cout<<"Player 2 wins\n\n!!";
									fstream fio;
									fio.open("../data/stats.txt");
									string line1;
									string line2;
									string line3;
									getline(fio,line1);
									getline(fio,line2);
									getline(fio,line3);
									//cout<<"TEST"<<line2<<endl<<endl;				
									int t=stoi(line2);
									t++;
									line2=to_string(t);
									fio.seekg(0,ios::beg);
									fio<<line1<<endl;
									fio<<line2<<endl;
									fio.close();
									//write to file
						
								}
							}
							cout<<"Play again? (y/n)";
							cin>>play;
							if(!(play=='y'||play=='n')){
								cout<<"\nWrong input\n\n";
								return 0;
							}
							break;
				}
		
		}
	}

}