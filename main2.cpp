//
//  main2.cpp
//  Sanke game
//
//  Created by Mani Kireeti on 08/04/20.
//  Copyright © 2020 Mani Kireeti. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


using namespace std;
int A[101][101];
int BX[200],BY[200];
int hi,hj;
int fi,fj;
int score=0;
int length=0;


int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void display(){
    cout<<"----------------------------------------------------"<<endl;
    for (int i=1; i<21; i++) {
        cout<<"|";
        for(int j=1;j<51;j++){
            if(A[i][j]==0) cout<<" ";
            if(A[i][j]==1 && !(i==hi && j==hj) && !(i==fi && j==fj)) cout<<"*";
            if(i==hi && j==hj)  cout<<"O";
            if(i==fi && j==fj)  cout<<"F";
        }
        cout<<"|"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;
    cout<<"SCORE: "<<score<<endl;
}

int direction(int a,int b,int c,int d){
    if(a==c && b==d){
        return 0;//initial
    }
    if((a-c)==0 && (b-d)==1){
        return 1;//right
    }
    if((a-c)==0 && (b-d)==-1){
        return 2;//left
    }
    if((a-c)==1 && (b-d)==0){
        return 3;//down
    }
    if((a-c)==-1 && (b-d)==0){
        return 4;//top
    }
    return -1;
}


void game(){
    for(int i=1;i<101;i++){
        for(int j=1;j<101;j++){
            A[i][j]=0;
        }
    }
    for(int i=0;i<200;i++){
        BX[i]=-1;
        BY[i]=-1;
    }
    hi=10;hj=25;
    A[hi][hj]=1;
    score=0;
    length=0;
    while(true){
            fi=rand()%20+1;
            fj=rand()%50+1;
            if(A[fi][fj]==0) break;
    }
    A[fi][fj]=1;
    display();
    int count=0;
    
    
    while(true){
        for(int i=0;i<length;i++){
            if(hi==BX[i] && hj==BY[i]){
                system("clear");
                cout<<"SORRY YOU LOST THE GAME"<<endl;
                cout<<"Your SCORE is: "<<score<<endl;
                cout<<"Press P to PLay another game or Q to quit"<<endl;
                char a;
                cin>>a;
                if(a=='p' || a=='P') game();
                else return;
            }
        }
        system("clear");
        if(kbhit()){
            char dir=getchar();
            if(dir=='w'){
                count=1;
            }
            if(dir=='s'){
                count=2;
            }
            if(dir=='a'){
                count=3;
            }
            if(dir=='d'){
                count=4;
            }
        }
        if(count==0){
            int count1=0;
            if(fi==hi && fj==hj+1){
                A[hi][hj]=0;
                count1=1;
                A[hi][hj+1]=0;
                length++;
                for(int i=length-1;i>0;i--){
                    BX[i]=BX[i-1];
                    BY[i]=BY[i-1];
                }
                BX[0]=hi;
                BY[0]=hj;
                A[BX[0]][BY[0]]=1;
                hi=fi;hj=fj;
                while(true){
                    fi=rand()%20+1;
                    fj=rand()%50+1;
                    if(A[fi][fj]==0)break;
                }
                A[fi][fj]=1;
                for(int i=0;i<length;i++){
                    A[BX[i]][BY[i]]=1;
                }
                A[hi][hj]=1;
                score=score+10;
            }
            if(count1==0){
                if(hj==50){
                    A[hi][hj]=0;
                    hj=0;
                }
                A[hi][hj]=0;
                hj++;
                A[hi][hj]=1;
                if(length>0){
                    for(int i=0;i<length;i++){
                            if(BY[i]==50){
                                A[BX[i]][BY[i]]=0;
                                BY[i]=0;
                            }
                            A[BX[i]][BY[i]]=0;
                            BY[i]++;
                            A[BX[i]][BY[i]]=1;
                    }
                }
            }
            display();
            usleep(1000000/20);
        }
       
//        --------------------------------------------------------
        
        
        if(count==1){
            int count1=0,count2=0;
            if(fi==hi-1 && fj==hj){
                A[hi][hj]=0;
                count1=1;
                A[hi-1][hj]=0;
                length++;
                for(int i=length-1;i>0;i--){
                        BX[i]=BX[i-1];
                        BY[i]=BY[i-1];
                }
                BX[0]=hi;
                BY[0]=hj;
                hi=fi;hj=fj;
                while(true){
                    fi=rand()%20+1;
                    fj=rand()%50+1;
                    if(A[fi][fj]==0)break;
                }
                A[fi][fj]=1;
                A[hi][hj]=1;
                score=score+10;
            }
            if(count1==0){
                if(length>0){
                     A[BX[length-1]][BY[length-1]]=0;
                    for(int i=length-1;i>0;i--){
                        BX[i]=BX[i-1];
                        BY[i]=BY[i-1];
                    }
                    BX[0]=hi;BY[0]=hj;
                    count2=1;
                    for(int i=0;i<length;i++){
                        A[BX[i]][BY[i]]=1;
                    }
                }
                if(hi==1){
                    if(count2==0) A[hi][hj]=0;
                    hi=21;
                }
                if(count2==0) A[hi][hj]=0;
                hi--;
                A[hi][hj]=1;
            }
            display();
            usleep(1000000/12);
        }
        
//        ------------------------------------------------------
        
        if(count==2){
            int count1=0,count2=0;
            if(fi==hi+1 && fj==hj){
                A[hi][hj]=0;
                count1=1;
                A[hi+1][hj]=0;
                length++;
                for(int i=length-1;i>0;i--){
                    BX[i]=BX[i-1];
                    BY[i]=BY[i-1];
                }
                BX[0]=hi;
                BY[0]=hj;
                hi=fi;hj=fj;
                while(true){
                    fi=rand()%20+1;
                    fj=rand()%50+1;
                    if(A[fi][fj]==0)break;
                }
                A[fi][fj]=1;
                A[hi][hj]=1;
                score=score+10;
            }
            if(count1==0){
                if(length>0){
                    A[BX[length-1]][BY[length-1]]=0;
                    for(int i=length-1;i>0;i--){
                        BX[i]=BX[i-1];
                        BY[i]=BY[i-1];
                    }
                    count2=1;
                    BX[0]=hi;BY[0]=hj;
                    for(int i=0;i<length;i++){
                        A[BX[i]][BY[i]]=1;
                    }
                }
                if(hi==20){
                    if(count2==0) A[hi][hj]=0;
                    hi=0;
                }
                if(count2==0) A[hi][hj]=0;
                hi++;
                A[hi][hj]=1;
            }
            display();
            usleep(1000000/12);
        }
//        -----------------------------------------------------
        
        if(count==3){
            int count1=0,count2=0;
            if(fi==hi && fj==hj-1){
                A[hi][hj]=0;
                count1=1;
                A[hi][hj-1]=0;
                length++;
                for(int i=length-1;i>0;i--){
                    BX[i]=BX[i-1];
                    BY[i]=BY[i-1];
                }
                BX[0]=hi;
                BY[0]=hj;
                hi=fi;hj=fj;
                while(true){
                        fi=rand()%20+1;
                        fj=rand()%50+1;
                        if(A[fi][fj]==0)break;
                }
                A[fi][fj]=1;
                A[hi][hj]=1;
                score=score+10;
            }
            if(count1==0){
                if(length>0){
                    A[BX[length-1]][BY[length-1]]=0;
                    for(int i=length-1;i>0;i--){
                        BX[i]=BX[i-1];
                        BY[i]=BY[i-1];
                    }
                    BX[0]=hi;BY[0]=hj;
                    count2=1;
                    for(int i=0;i<length;i++){
                        A[BX[i]][BY[i]]=1;
                    }
                }
                if(hj==1){
                     if(count2==0) A[hi][hj]=0;
                    hj=51;
                }
                 if(count2==0) A[hi][hj]=0;
                hj--;
                A[hi][hj]=1;
            }
            display();
            usleep(1000000/20);
        }
        
 //       -----------------------------------------------------------------------
        
        
        if(count==4){
            int count1=0,count2=0;
            if(fi==hi && fj==hj+1){
                count1=1;
                A[hi][hj]=0;
                A[hi][hj+1]=0;
                length++;
                for(int i=length-1;i>0;i--){
                    BX[i]=BX[i-1];
                    BY[i]=BY[i-1];
                }
                BX[0]=hi;
                BY[0]=hj;
                hi=fi;hj=fj;
                while(true){
                        fi=rand()%20+1;
                        fj=rand()%50+1;
                        if(A[fi][fj]==0)break;
                }
                A[fi][fj]=1;
                A[hi][hj]=1;
                
                score=score+10;
            }
            if(count1==0){
                if(length>0){
                    
                    A[BX[length-1]][BY[length-1]]=0;
                    for(int i=length-1;i>0;i--){
                        BX[i]=BX[i-1];
                        BY[i]=BY[i-1];
                    }
                    BX[0]=hi;BY[0]=hj;count2=1;
                    for(int i=0;i<length;i++){
                        A[BX[i]][BY[i]]=1;
                    }
                }
                if(hj==50){
                    if(count2==0)  A[hi][hj]=0;
                    hj=0;
                }
                 if(count2==0) A[hi][hj]=0;
                hj++;
                A[hi][hj]=1;
            }
            display();
            usleep(1000000/20);
        }
    }
}

int main() {
    srand( static_cast<unsigned int>(time(nullptr)));
    system("clear");
    cout<<"WELCOME TO THE SNAKE GAME"<<endl;
    cout<<"Instructiions: "<<endl;
    cout<<"w - up | a - left | s - down | d - right"<<endl;
    cout<<"Press P to play or q to Quit"<<endl;
    char a;
    cin>>a;
    if(a=='p' || a=='P') game();
    return 0;

}
