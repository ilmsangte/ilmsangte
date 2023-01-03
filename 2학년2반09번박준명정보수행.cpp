/*////////////////////////////////////////////////////////
프로그램 제목: 질병의 전염성에 따른 식량가격예측 프로그램
작성자: 2209 박준명
*데이터 출처 : KREI 해외곡물시장정보 
===========================
version = 0.0.1
-메뉴 화면 구성
===========================
version = 0.0.2
-식량 가격 데이터 읽기 
-식량 가격 변화 그래프 출력
===========================
version = 0.0.3
-식량 가격 그래프 해석 만들기
-프로그램 종료 구현
===========================
version = 0.0.4
-메뉴 입력 방식 재구성
-기다리는 함수 변경
-그래프 예측 함수 구성 
===========================
version = 0.0.5
-그래프 생성하는 함수 따로 만들기 시도
-프로그램 설명 출력 
===========================
version = 0.0.6
-질병에 따른 식량 가격 예측 알고리즘 작성 
-전체적인 오류 수정 및 UI개선 
///////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX 100000 //메모리 할당시에 임의로 최대값 주기위해 선언 

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

void GotoXY(int x, int y); //콘솔창에서 좌표 이동하는 함수 
void Title(); //제목 및 메뉴 출력하는 함수 
void Menu(); //메뉴 선택 입력 받는 함수 
void Change_scene(); //메뉴에서 선택시 화면 바꾸는 함수 
void Read_FDI(); //식량가격 csv읽는 함수 
void Show_FDI(); //식량가격 그래프 보여주는 함수
void Make_chart(int x, int y, float data[]); //그래프를 그려주는 함수 (x=x축 길이, y=y축 길이, data[]=그래프에 그릴 값)
void Ip_chart(); //식량 가격 그래프 해석
void Wait_input(); //메뉴 기능 실행 후 입력이 있을때까지 대기하는 함수 
void Predict(); //전염성에 따른 증가율 예측
int Predict_Input(); //전염성에 따른 증가율 예측 관련 변수 입력 받는 함수
void Program_Explain(); //프로그램 설명 출력 
float Inc_rate(float a, float b); //a에 대한 b의 증가량

float FDI_data[200]; //식량 가격 데이터 배열 
char* Date_data[200]; //식량 가격 날짜 데이터 배열 
float dif_FDI[200]; //식량 가격의 변화량 
int fun=0; //메뉴에서 고른 기능
int power; //질병의 전염성 정도를 나타내는 수치

int main(){
	system("mode con cols=170 lines=105"); //콘솔창 크기  
	
	Read_FDI(); //시작하면 csv파일에서 식량가격 읽어오기 
	
	//메뉴 실행 
	Title();
	Menu();
	
	return 0;
}

float Inc_rate(float a, float b)
{
	float aa = fabs(a);
	float bb = fabs(b);
	return bb/aa *100;
}

void GotoXY(int x, int y)
{ 
	COORD pos;
	HANDLE ghOutput;
	pos.X = x;
	pos.Y = y;
	ghOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(ghOutput, pos);
}

void Title()
{
	system("cls"); //콘솔 창 초기화 
	
	//메뉴화면 출력 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(8,2);
	printf("[[[[ 질병의 전염성에 따른 식량가격 예측 ]]]]");
	GotoXY(0,5);
	printf(" [ 메뉴 ]");
	printf("\n\n>> 1.지금까지의 식량가격 변화 그래프 보기");
	printf("\n\n   2.식량가격 그래프를 통한 질병 발생 여부 확인");
	printf("\n\n   3.질병의 전염성에 따른 식량가격 예측");
	printf("\n\n   4.프로그램 설명 보기");
	printf("\n\n   5.종료");
	printf("\n\n\n- 위,아래 방향키를 통해 메뉴를 고르고 엔터를 눌러 메뉴를 선택을 할 수 있습니다.");
	printf("\n\n\n- 제작자:(2209)박준명");
}

void Menu()
{
	char key_code;
	
	while(1){
		key_code = _getch(); //키보드 입력을 받아옴 
		switch(key_code){
			case 72: //위쪽 방향키 입력 
				GotoXY(0,2*fun+7);
				printf("  ");
				fun--;
				break;
				
			case 80: //아래쪽 방향키 입력 
				GotoXY(0,2*fun+7);
				printf("  ");
				fun++;
				break;
				
			case 13: //엔터 입력
				Change_scene();
				break; 
		}
		
		//메뉴 범위에서 벗어나는 값일 경우 끝 값으로 처리 
		if(fun<0)
			fun=0;
		
		else if(fun>4)
			fun=4;
		
		GotoXY(0,2*fun+7);
		printf(">>");
	}
}

void Change_scene()
{
	switch(fun)
	{
		case 0: //차트 보기 선택시 
			system("cls");
			Show_FDI();
			break;
		case 1: //식량 가격을 통해 질병 발생여부 확인 선택시 
			system("cls");
			Ip_chart();
			break;
		case 2: //질병 전염성에 따른 식량가격 예측 선택시 
			Predict();
			break;
		case 3: //프로그램 설명 선택시 
			Program_Explain(); 
			break; 
		case 4: //프로그램 종료 선택시 
			system("cls");
			printf("1초후 프로그램이 종료됩니다...");
			_sleep(1000); 
			exit(0);
			break;
	}
}

void Read_FDI()
{
    float cnt, pre_cnt=0; //식량가격 값과, 이전의 식량가격 값 
    char* date; //날짜 저장 변수 
    int idx=0; //배열에 저장하기 위한 인젝스 
    FILE *pFile = NULL;

    pFile = fopen("FDI_Data.csv", "r"); //파일 경로
    
    if( pFile == NULL ){ //잘못된 파일 입력시... 
		printf("입력 파일이 잘못 지정되었거나 문제가 있습니다.\n");
		exit(0); 
	}
		
	else
        while( !feof( pFile ) )
		{
            fscanf(pFile, "%f\n", &cnt);
            FDI_data[idx] = cnt-85; //식량 가격에서 85뺀 값을 저장 
			dif_FDI[idx] = cnt-pre_cnt; //1달간 식량 가격의 차이 저장 
			pre_cnt = cnt;
            idx++;
        }
        
	fclose(pFile);
	
	idx=0;
	
	pFile = fopen("Date_Data.csv", "r"); //파일 경로  
    if( pFile == NULL ){ //잘못된 파일 입력시 
		printf("입력 파일이 잘못 지정되었거나 문제가 있습니다.\n");
		exit(0);
	}

	else
        while( !feof( pFile ) )
		{
        	date = (char*)malloc(sizeof(char) * MAX); //메모리 할당 
        	fgets(date, MAX, pFile);
            Date_data[idx] = date;
            idx++;
        }
        
	fclose(pFile);
}

void Show_FDI()
{
	//그래프 그리기 
	Make_chart(140,57, FDI_data); 
	
	GotoXY(1,60); 
	Wait_input();
}

void Make_chart(int x, int y, float data[])
{
	//그래프 생성=============
	for(int i=0;i<y;i++){  //y축 그리기 
		GotoXY(5,i+1);
		printf("||"); 
	}
	for(int i=0; i<x;i++){  //x축 그리기 
		GotoXY(i,y+1);
		printf("=");
	}
	GotoXY(0,0);
	printf("(2002~2004년까지 가격 평균을 100으로한 상대수치)");
	
	for(int i=0; i<=((y-5)/10); i++){ //y축 범위
		GotoXY(1,y-(i*10));
		printf("%d",i*10+85);
	}
	for(int i=0; Date_data[(i+1)*10]; i++){ //x축 범위
		GotoXY(8+(i*10),y+2);
		printf("%s",Date_data[i*10]);
	}
	
	//그래프 값 표시==========
	for(int i=0; data[i]; i++){
		GotoXY(i+8,y-data[i]);
		printf("#");
		_sleep(15);
	}
	//========================
} 

void Ip_chart()
{
	int Check = 1; //그래프의 상태가 증가인지 감소상태인지 판별
	
	Make_chart(140,57,FDI_data);
	
	for(int i=1; i<150; i++){ //증가 비율과 변화량을 통해 증가인지 감소인지 판별 
		if(Check && dif_FDI[i]>0 && dif_FDI[i-1]>0)
			if(Inc_rate(dif_FDI[i-1],dif_FDI[i])>200)
			{
				//질병 발생으로 예측되는 곳 빨간색으로 표현 
				GotoXY(i+7,57-FDI_data[i-1]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("#");
				//==========================================
				
				//질병 발생으로 예측되는 날짜 출력
				GotoXY(i+7,56-FDI_data[i-1]);
				printf("|%s",Date_data[i-1]);  
				//================================
				
				Check=0;
				_sleep(40);
			}
		
		if(Inc_rate(dif_FDI[i-1],dif_FDI[i])>130 && dif_FDI[i-1]<0 && dif_FDI[i]<0) //그래프가 감소 상태라면 Check 바꾸기
			Check=1;
	}
	
	//실제 질병 발생한 곳 & 근거 출력 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(0,61);
	printf(" 실제 질병이 발생한 곳:\n");
	printf("  2012년:메르스 | 2020년:코로나\n\n"); 
	printf("질병 발생이라고 판단한 근거:\n");
	printf(" 질병이 발생하게 되면 식량가격이 증가하게 되는 모습을 보여줍니다.\n");
	printf(" 따라서 식량가격이 이전과 비교하여 급격하게 상승한 곳을 질병이 발생한 곳으로 예측하였습니다."); 
	
	//스페이스 입력까지 대기 
	Wait_input();
}

void Predict()
{
	float pre_FDI_data[200]; //새롭게 예측한 식량 가격 데이터 배열  
	float pre_FDI; //예측한 식량 곡물 가격 이전 값 
	int idx=0, y=90;
	idx = Predict_Input(); //에측하는데 필요한 변수 입력받는 함수 

	//질병 발생후 가격 예측하는 코드
	system("cls");
	for(int i=0; FDI_data[i]; i++){
		pre_FDI_data[i] = FDI_data[i]*1; //질병 발생전에는 값을 그대로 넣어줌 
		
		if(power == '2'){ //질병 전염성 강도 2인 경우.. 
			if(i>idx && i<idx+5){ //질병 발생 이후로 부터 5개월 동안.. 
				pre_FDI_data[i] = pre_FDI_data[i-1] + (2*((5-i+idx)*0.1f+1));	
			}
			
			else if(i>=idx+5 && i<idx+11){ //5개월 지나고 다시 5개월 동안 안정화 
				pre_FDI_data[i] = FDI_data[i-1] + ((1-((i-idx-5)*0.2))*(5*((i-idx)*0.1f+1)));
			}
		}
				
		else if(power == '3'){ //질병 전염성 강도 3인 경우.. 
			if(i>idx && i<idx+12){ //질병 발생 이후로 부터 12개월 동안.. 
				pre_FDI = pre_FDI_data[i-1] + ((18-i+idx)*0.1f +1);
				pre_FDI_data[i] = pre_FDI_data[i-1] + ((12-i+idx)*0.1f +1); 
			}
			
			else if(i>=idx+12 && i<idx+23){ //12개월 지나고 10개월 동안 안정화 
				pre_FDI = pre_FDI + ((18-i+idx)*0.1f+1);
				pre_FDI_data[i] = (1-((i-idx-12)*0.1f))*pre_FDI + ((i-idx-12)*0.1)*FDI_data[i];
			}
		}
	}

	//질병 발생후 그래프 그리기 ========================================
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //질병 발생후 그래프는 빨간색으로 
	Make_chart(140,y,pre_FDI_data);
	GotoXY(9,3);
	printf("#:질병발생 후 가격");
	
	//질병 발생전 그래프 그리기 ========================================
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //질병 발생전 그래프는 흰색으로 
	Make_chart(140,y,FDI_data);
	GotoXY(9,2);
	printf("#:원래 가격");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	GotoXY(idx+8,y-1-pre_FDI_data[idx]);
	printf("|질병발생한곳");
	GotoXY(idx+8,y-pre_FDI_data[idx]);
	printf("#");
	//==================================================================
	
	//그래프가 다음처럼 그려지게 된 이유를 전염성의 세기별 출력 ========
	GotoXY(0,y+5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(" [ 그래프가 다음처럼 예측되는 근거 ]\n\n");
	if(power == '1'){
		printf("- 감기와 같은 전염성은 크지만 증상이 크지않은 일반적인 질병의 경우 -\n\n");
		printf("산업이나 식량 생산량에 큰 영향을 미치지 못하여 변화가 없습니다.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("그렇기에 질병발생 전과 후가 같은 그래프를 출력하게 됩니다.");
	}
	
	else if(power == '2'){	
		printf("- 전염성은 낮지만 사망률이 높은 경우 -\n\n");
		printf("질병 발생후 약간동안 가격이 증가하게 됩니다.\n");
		printf("사망률이 높아 전염이 잘되지 않아 질병이 금방 끝나게됩니다.\n");
		printf("따라서 약간의 기간 동안 가격이 상승 후 다시 원상 복귀 됩니다.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("결과적으로 다음처럼 약간의 상승 후 가격이 다시 돌아오는 그래프가 나타납니다.");
	}
	
	else if(power == '3'){
		printf("- 전염성이 크며 지속시간이 길고 사망률이 낮지않을 때 -\n\n");
		printf("전염성이 큰 새로운 질병이 나타나면 일시적으로 식량의 생산량이 감소합니다.\n");
		printf("그렇기에 질병 발생 후 가격이 지속적으로 상승하게 됩니다.\n"); 
		printf("질병 발생 후 시간이 지나 백신과 치료제가 개발되면 가격이 안정되기 시작합니다.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("결과적으로 다음처럼 질병 발생 후 오랫동안 가격이 상승한 후 점차 가격이 다시 안정화 되기 시작합니다.");
	}
	//=================================================================
	
	//스페이스바 입력까지 대기
	Wait_input();
	Title();
	Menu();
}

int Predict_Input()
{
	int year,month; //질병 발생 년도, 월 
	int idx=0; //질병 발생 한 날 인덱스로 표현 
	
	system("cls");
	printf("질병이 발생했으면 좋겠는곳");
	
	//년도 입력
	while(1){  
		GotoXY(0,2);
		printf(" 년도(13~22):        				 ");
		GotoXY(14,2);
		scanf("%d",&year);
		if(year>=13 && year<=22) break;
		fflush(stdin); //이상한 값 입력시 입력 버퍼 비우기
	}
	//월 입력 
	while(1){
		GotoXY(0,4);
		printf(" 월(1~12):        				  ");
		GotoXY(11,4);
		scanf("%d",&month);
		if(month>=1 && month<=12) break;
		fflush(stdin); //이상한 값 입력시 입력 버퍼 비우기
	}
	//질병의 전염성 정도 입력 
	while(1){
		GotoXY(0,6);
		printf("질병의 전염성 정도\n\n"); 
		printf(" [1.감기처럼 전염성은 높지만 사망률을 낮을때]\n\n");
		printf(" [2.전염성은 낮지만 사망률이 높을떄]\n\n");
		printf(" [3.코로나처럼 전염성이 크고 지속시간이 길 때]\n\n");
		printf("1~3 중에 하나를 입력해주세요...");
		power = _getch();
		if(power<='3' && power>='1') break; 
	}
	
	idx = 12*year+month-150; //입력한 질병 발생 날과 데이터 초기 값의 차이
	
	return idx;
}

void Wait_input()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\n\n메뉴로 돌아가려면 [스페이바]를 눌러주세요...");
	
	//아무키나 눌릴때까지 대기 
	while(1)
		if(_getch() == 32)
			break;
	
	fun=0; //메뉴 입력 초기화 
	
	Title(); //메뉴로 돌아감 
	Menu();
} 

void Program_Explain()
{
	//프로그램 설명 문구 
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\n [[[ 해당프로그램은 질병의 전염성과 식량 가격 간의 관계를 찾아 식량가격을 예측하는 프로그램입니다. ]]]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n- 식량 가격 지수란?");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\n\n   식량 농업 기구(FAO)에서 1990년부터 곡물·유지류·육류·낙농품 등");
	printf("\n   55개 주요 농산물의 국가가격동향을 점검해 매월 발표하고 있는 가격지수입니다.");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n\n- 1번을 선택하면 2012년부터 지금까지의 식량가격 그래프를 볼 수 있습니다."); 
	printf("\n\n\n- 2번을 선택하면 식량가격 그래프를 통해 최근에 질병이 발생했을 것으로 예측되는 곳을 확인해 볼수있습니다.");
	printf("\n\n\n- 3번을 선택하면 질병발생한 곳을 임의로 정했을때의 식량 가격 변화를 예측한 결과를 볼수있습니다.");
	printf("\n\n\n- 4번을 선택하면 프로그램 설명을 볼수있습니다.");
	printf("\n\n\n- 5번을 선택하면 프로그램이 종료됩니다.");
	
	//스페이스바 눌릴 때 까지 대기 
	Wait_input();
	Title();
	Menu();
}
