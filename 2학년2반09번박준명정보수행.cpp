/*////////////////////////////////////////////////////////
���α׷� ����: ������ �������� ���� �ķ����ݿ��� ���α׷�
�ۼ���: 2209 ���ظ�
*������ ��ó : KREI �ؿܰ�������� 
===========================
version = 0.0.1
-�޴� ȭ�� ����
===========================
version = 0.0.2
-�ķ� ���� ������ �б� 
-�ķ� ���� ��ȭ �׷��� ���
===========================
version = 0.0.3
-�ķ� ���� �׷��� �ؼ� �����
-���α׷� ���� ����
===========================
version = 0.0.4
-�޴� �Է� ��� �籸��
-��ٸ��� �Լ� ����
-�׷��� ���� �Լ� ���� 
===========================
version = 0.0.5
-�׷��� �����ϴ� �Լ� ���� ����� �õ�
-���α׷� ���� ��� 
===========================
version = 0.0.6
-������ ���� �ķ� ���� ���� �˰��� �ۼ� 
-��ü���� ���� ���� �� UI���� 
///////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS
#define MAX 100000 //�޸� �Ҵ�ÿ� ���Ƿ� �ִ밪 �ֱ����� ���� 

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <math.h>

void GotoXY(int x, int y); //�ܼ�â���� ��ǥ �̵��ϴ� �Լ� 
void Title(); //���� �� �޴� ����ϴ� �Լ� 
void Menu(); //�޴� ���� �Է� �޴� �Լ� 
void Change_scene(); //�޴����� ���ý� ȭ�� �ٲٴ� �Լ� 
void Read_FDI(); //�ķ����� csv�д� �Լ� 
void Show_FDI(); //�ķ����� �׷��� �����ִ� �Լ�
void Make_chart(int x, int y, float data[]); //�׷����� �׷��ִ� �Լ� (x=x�� ����, y=y�� ����, data[]=�׷����� �׸� ��)
void Ip_chart(); //�ķ� ���� �׷��� �ؼ�
void Wait_input(); //�޴� ��� ���� �� �Է��� ���������� ����ϴ� �Լ� 
void Predict(); //�������� ���� ������ ����
int Predict_Input(); //�������� ���� ������ ���� ���� ���� �Է� �޴� �Լ�
void Program_Explain(); //���α׷� ���� ��� 
float Inc_rate(float a, float b); //a�� ���� b�� ������

float FDI_data[200]; //�ķ� ���� ������ �迭 
char* Date_data[200]; //�ķ� ���� ��¥ ������ �迭 
float dif_FDI[200]; //�ķ� ������ ��ȭ�� 
int fun=0; //�޴����� �� ���
int power; //������ ������ ������ ��Ÿ���� ��ġ

int main(){
	system("mode con cols=170 lines=105"); //�ܼ�â ũ��  
	
	Read_FDI(); //�����ϸ� csv���Ͽ��� �ķ����� �о���� 
	
	//�޴� ���� 
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
	system("cls"); //�ܼ� â �ʱ�ȭ 
	
	//�޴�ȭ�� ��� 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(8,2);
	printf("[[[[ ������ �������� ���� �ķ����� ���� ]]]]");
	GotoXY(0,5);
	printf(" [ �޴� ]");
	printf("\n\n>> 1.���ݱ����� �ķ����� ��ȭ �׷��� ����");
	printf("\n\n   2.�ķ����� �׷����� ���� ���� �߻� ���� Ȯ��");
	printf("\n\n   3.������ �������� ���� �ķ����� ����");
	printf("\n\n   4.���α׷� ���� ����");
	printf("\n\n   5.����");
	printf("\n\n\n- ��,�Ʒ� ����Ű�� ���� �޴��� ���� ���͸� ���� �޴��� ������ �� �� �ֽ��ϴ�.");
	printf("\n\n\n- ������:(2209)���ظ�");
}

void Menu()
{
	char key_code;
	
	while(1){
		key_code = _getch(); //Ű���� �Է��� �޾ƿ� 
		switch(key_code){
			case 72: //���� ����Ű �Է� 
				GotoXY(0,2*fun+7);
				printf("  ");
				fun--;
				break;
				
			case 80: //�Ʒ��� ����Ű �Է� 
				GotoXY(0,2*fun+7);
				printf("  ");
				fun++;
				break;
				
			case 13: //���� �Է�
				Change_scene();
				break; 
		}
		
		//�޴� �������� ����� ���� ��� �� ������ ó�� 
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
		case 0: //��Ʈ ���� ���ý� 
			system("cls");
			Show_FDI();
			break;
		case 1: //�ķ� ������ ���� ���� �߻����� Ȯ�� ���ý� 
			system("cls");
			Ip_chart();
			break;
		case 2: //���� �������� ���� �ķ����� ���� ���ý� 
			Predict();
			break;
		case 3: //���α׷� ���� ���ý� 
			Program_Explain(); 
			break; 
		case 4: //���α׷� ���� ���ý� 
			system("cls");
			printf("1���� ���α׷��� ����˴ϴ�...");
			_sleep(1000); 
			exit(0);
			break;
	}
}

void Read_FDI()
{
    float cnt, pre_cnt=0; //�ķ����� ����, ������ �ķ����� �� 
    char* date; //��¥ ���� ���� 
    int idx=0; //�迭�� �����ϱ� ���� ������ 
    FILE *pFile = NULL;

    pFile = fopen("FDI_Data.csv", "r"); //���� ���
    
    if( pFile == NULL ){ //�߸��� ���� �Է½�... 
		printf("�Է� ������ �߸� �����Ǿ��ų� ������ �ֽ��ϴ�.\n");
		exit(0); 
	}
		
	else
        while( !feof( pFile ) )
		{
            fscanf(pFile, "%f\n", &cnt);
            FDI_data[idx] = cnt-85; //�ķ� ���ݿ��� 85�� ���� ���� 
			dif_FDI[idx] = cnt-pre_cnt; //1�ް� �ķ� ������ ���� ���� 
			pre_cnt = cnt;
            idx++;
        }
        
	fclose(pFile);
	
	idx=0;
	
	pFile = fopen("Date_Data.csv", "r"); //���� ���  
    if( pFile == NULL ){ //�߸��� ���� �Է½� 
		printf("�Է� ������ �߸� �����Ǿ��ų� ������ �ֽ��ϴ�.\n");
		exit(0);
	}

	else
        while( !feof( pFile ) )
		{
        	date = (char*)malloc(sizeof(char) * MAX); //�޸� �Ҵ� 
        	fgets(date, MAX, pFile);
            Date_data[idx] = date;
            idx++;
        }
        
	fclose(pFile);
}

void Show_FDI()
{
	//�׷��� �׸��� 
	Make_chart(140,57, FDI_data); 
	
	GotoXY(1,60); 
	Wait_input();
}

void Make_chart(int x, int y, float data[])
{
	//�׷��� ����=============
	for(int i=0;i<y;i++){  //y�� �׸��� 
		GotoXY(5,i+1);
		printf("||"); 
	}
	for(int i=0; i<x;i++){  //x�� �׸��� 
		GotoXY(i,y+1);
		printf("=");
	}
	GotoXY(0,0);
	printf("(2002~2004����� ���� ����� 100������ ����ġ)");
	
	for(int i=0; i<=((y-5)/10); i++){ //y�� ����
		GotoXY(1,y-(i*10));
		printf("%d",i*10+85);
	}
	for(int i=0; Date_data[(i+1)*10]; i++){ //x�� ����
		GotoXY(8+(i*10),y+2);
		printf("%s",Date_data[i*10]);
	}
	
	//�׷��� �� ǥ��==========
	for(int i=0; data[i]; i++){
		GotoXY(i+8,y-data[i]);
		printf("#");
		_sleep(15);
	}
	//========================
} 

void Ip_chart()
{
	int Check = 1; //�׷����� ���°� �������� ���һ������� �Ǻ�
	
	Make_chart(140,57,FDI_data);
	
	for(int i=1; i<150; i++){ //���� ������ ��ȭ���� ���� �������� �������� �Ǻ� 
		if(Check && dif_FDI[i]>0 && dif_FDI[i-1]>0)
			if(Inc_rate(dif_FDI[i-1],dif_FDI[i])>200)
			{
				//���� �߻����� �����Ǵ� �� ���������� ǥ�� 
				GotoXY(i+7,57-FDI_data[i-1]);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				printf("#");
				//==========================================
				
				//���� �߻����� �����Ǵ� ��¥ ���
				GotoXY(i+7,56-FDI_data[i-1]);
				printf("|%s",Date_data[i-1]);  
				//================================
				
				Check=0;
				_sleep(40);
			}
		
		if(Inc_rate(dif_FDI[i-1],dif_FDI[i])>130 && dif_FDI[i-1]<0 && dif_FDI[i]<0) //�׷����� ���� ���¶�� Check �ٲٱ�
			Check=1;
	}
	
	//���� ���� �߻��� �� & �ٰ� ��� 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	GotoXY(0,61);
	printf(" ���� ������ �߻��� ��:\n");
	printf("  2012��:�޸��� | 2020��:�ڷγ�\n\n"); 
	printf("���� �߻��̶�� �Ǵ��� �ٰ�:\n");
	printf(" ������ �߻��ϰ� �Ǹ� �ķ������� �����ϰ� �Ǵ� ����� �����ݴϴ�.\n");
	printf(" ���� �ķ������� ������ ���Ͽ� �ް��ϰ� ����� ���� ������ �߻��� ������ �����Ͽ����ϴ�."); 
	
	//�����̽� �Է±��� ��� 
	Wait_input();
}

void Predict()
{
	float pre_FDI_data[200]; //���Ӱ� ������ �ķ� ���� ������ �迭  
	float pre_FDI; //������ �ķ� � ���� ���� �� 
	int idx=0, y=90;
	idx = Predict_Input(); //�����ϴµ� �ʿ��� ���� �Է¹޴� �Լ� 

	//���� �߻��� ���� �����ϴ� �ڵ�
	system("cls");
	for(int i=0; FDI_data[i]; i++){
		pre_FDI_data[i] = FDI_data[i]*1; //���� �߻������� ���� �״�� �־��� 
		
		if(power == '2'){ //���� ������ ���� 2�� ���.. 
			if(i>idx && i<idx+5){ //���� �߻� ���ķ� ���� 5���� ����.. 
				pre_FDI_data[i] = pre_FDI_data[i-1] + (2*((5-i+idx)*0.1f+1));	
			}
			
			else if(i>=idx+5 && i<idx+11){ //5���� ������ �ٽ� 5���� ���� ����ȭ 
				pre_FDI_data[i] = FDI_data[i-1] + ((1-((i-idx-5)*0.2))*(5*((i-idx)*0.1f+1)));
			}
		}
				
		else if(power == '3'){ //���� ������ ���� 3�� ���.. 
			if(i>idx && i<idx+12){ //���� �߻� ���ķ� ���� 12���� ����.. 
				pre_FDI = pre_FDI_data[i-1] + ((18-i+idx)*0.1f +1);
				pre_FDI_data[i] = pre_FDI_data[i-1] + ((12-i+idx)*0.1f +1); 
			}
			
			else if(i>=idx+12 && i<idx+23){ //12���� ������ 10���� ���� ����ȭ 
				pre_FDI = pre_FDI + ((18-i+idx)*0.1f+1);
				pre_FDI_data[i] = (1-((i-idx-12)*0.1f))*pre_FDI + ((i-idx-12)*0.1)*FDI_data[i];
			}
		}
	}

	//���� �߻��� �׷��� �׸��� ========================================
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); //���� �߻��� �׷����� ���������� 
	Make_chart(140,y,pre_FDI_data);
	GotoXY(9,3);
	printf("#:�����߻� �� ����");
	
	//���� �߻��� �׷��� �׸��� ========================================
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); //���� �߻��� �׷����� ������� 
	Make_chart(140,y,FDI_data);
	GotoXY(9,2);
	printf("#:���� ����");
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	GotoXY(idx+8,y-1-pre_FDI_data[idx]);
	printf("|�����߻��Ѱ�");
	GotoXY(idx+8,y-pre_FDI_data[idx]);
	printf("#");
	//==================================================================
	
	//�׷����� ����ó�� �׷����� �� ������ �������� ���⺰ ��� ========
	GotoXY(0,y+5);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf(" [ �׷����� ����ó�� �����Ǵ� �ٰ� ]\n\n");
	if(power == '1'){
		printf("- ����� ���� �������� ũ���� ������ ũ������ �Ϲ����� ������ ��� -\n\n");
		printf("����̳� �ķ� ���귮�� ū ������ ��ġ�� ���Ͽ� ��ȭ�� �����ϴ�.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("�׷��⿡ �����߻� ���� �İ� ���� �׷����� ����ϰ� �˴ϴ�.");
	}
	
	else if(power == '2'){	
		printf("- �������� ������ ������� ���� ��� -\n\n");
		printf("���� �߻��� �ణ���� ������ �����ϰ� �˴ϴ�.\n");
		printf("������� ���� ������ �ߵ��� �ʾ� ������ �ݹ� �����Ե˴ϴ�.\n");
		printf("���� �ణ�� �Ⱓ ���� ������ ��� �� �ٽ� ���� ���� �˴ϴ�.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("��������� ����ó�� �ణ�� ��� �� ������ �ٽ� ���ƿ��� �׷����� ��Ÿ���ϴ�.");
	}
	
	else if(power == '3'){
		printf("- �������� ũ�� ���ӽð��� ��� ������� �������� �� -\n\n");
		printf("�������� ū ���ο� ������ ��Ÿ���� �Ͻ������� �ķ��� ���귮�� �����մϴ�.\n");
		printf("�׷��⿡ ���� �߻� �� ������ ���������� ����ϰ� �˴ϴ�.\n"); 
		printf("���� �߻� �� �ð��� ���� ��Ű� ġ������ ���ߵǸ� ������ �����Ǳ� �����մϴ�.\n\n");
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		printf("��������� ����ó�� ���� �߻� �� �������� ������ ����� �� ���� ������ �ٽ� ����ȭ �Ǳ� �����մϴ�.");
	}
	//=================================================================
	
	//�����̽��� �Է±��� ���
	Wait_input();
	Title();
	Menu();
}

int Predict_Input()
{
	int year,month; //���� �߻� �⵵, �� 
	int idx=0; //���� �߻� �� �� �ε����� ǥ�� 
	
	system("cls");
	printf("������ �߻������� ���ڴ°�");
	
	//�⵵ �Է�
	while(1){  
		GotoXY(0,2);
		printf(" �⵵(13~22):        				 ");
		GotoXY(14,2);
		scanf("%d",&year);
		if(year>=13 && year<=22) break;
		fflush(stdin); //�̻��� �� �Է½� �Է� ���� ����
	}
	//�� �Է� 
	while(1){
		GotoXY(0,4);
		printf(" ��(1~12):        				  ");
		GotoXY(11,4);
		scanf("%d",&month);
		if(month>=1 && month<=12) break;
		fflush(stdin); //�̻��� �� �Է½� �Է� ���� ����
	}
	//������ ������ ���� �Է� 
	while(1){
		GotoXY(0,6);
		printf("������ ������ ����\n\n"); 
		printf(" [1.����ó�� �������� ������ ������� ������]\n\n");
		printf(" [2.�������� ������ ������� ������]\n\n");
		printf(" [3.�ڷγ�ó�� �������� ũ�� ���ӽð��� �� ��]\n\n");
		printf("1~3 �߿� �ϳ��� �Է����ּ���...");
		power = _getch();
		if(power<='3' && power>='1') break; 
	}
	
	idx = 12*year+month-150; //�Է��� ���� �߻� ���� ������ �ʱ� ���� ����
	
	return idx;
}

void Wait_input()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\n\n�޴��� ���ư����� [�����̹�]�� �����ּ���...");
	
	//�ƹ�Ű�� ���������� ��� 
	while(1)
		if(_getch() == 32)
			break;
	
	fun=0; //�޴� �Է� �ʱ�ȭ 
	
	Title(); //�޴��� ���ư� 
	Menu();
} 

void Program_Explain()
{
	//���α׷� ���� ���� 
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	printf("\n [[[ �ش����α׷��� ������ �������� �ķ� ���� ���� ���踦 ã�� �ķ������� �����ϴ� ���α׷��Դϴ�. ]]]");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n- �ķ� ���� ������?");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	printf("\n\n   �ķ� ��� �ⱸ(FAO)���� 1990����� ���������������������ǰ ��");
	printf("\n   55�� �ֿ� ��깰�� �������ݵ����� ������ �ſ� ��ǥ�ϰ� �ִ� ���������Դϴ�.");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
	printf("\n\n\n- 1���� �����ϸ� 2012����� ���ݱ����� �ķ����� �׷����� �� �� �ֽ��ϴ�."); 
	printf("\n\n\n- 2���� �����ϸ� �ķ����� �׷����� ���� �ֱٿ� ������ �߻����� ������ �����Ǵ� ���� Ȯ���� �����ֽ��ϴ�.");
	printf("\n\n\n- 3���� �����ϸ� �����߻��� ���� ���Ƿ� ���������� �ķ� ���� ��ȭ�� ������ ����� �����ֽ��ϴ�.");
	printf("\n\n\n- 4���� �����ϸ� ���α׷� ������ �����ֽ��ϴ�.");
	printf("\n\n\n- 5���� �����ϸ� ���α׷��� ����˴ϴ�.");
	
	//�����̽��� ���� �� ���� ��� 
	Wait_input();
	Title();
	Menu();
}
