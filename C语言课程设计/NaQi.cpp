#include<conio.h>
int IsLeapYear(int); 
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
# include <io.h>

#define I 8
#define R 150

//# include "student.h" 
typedef struct dbf1 {
	char ver;     //�汾�� 
	char date[3];    //����������
	unsigned long record_num;//��¼���� 
	unsigned short stru_byte_num;//�ṹ˵�����ֶ�˵��,��ռ���ֽ���+1
	unsigned short record_byte_num;//��¼�ֽڸ���
	char unse[20];//���� 
}DBFH;

typedef struct dbf2 {
	char field_name[11]; //�ֶ���ASCII�� 
	char field_type; //�ֶ����� 
	long unse1; //�ֶ��ڼ�¼�е�λ�� 
	char field_len; //�ֶγ��ȵĶ������� 
	char decimal;//С�����λ����2������ 
	char unse2[2];//���� 
	char work_area;//��������־ 
	char unse3[11];//���� 

}DBFSTRU;
void appe_rec();
void key_read();
void create_dbf();
void insert_rec();
void display();
void delete_rec();
void find_rec();
void print();
void qj();
void hj();
void rili();
void qingp();
void time();
int menu_select();
HWND GetConsoleHwnd(void);

DBFH dbf_head;
DBFSTRU fields[128];
FILE *dbfp;
char *cc;
#define MAX 68
#define MIN 70
void print(int n)
{
 int m = n;
 while(m--)
  printf(" ");
 printf("       (___)\n");
 m = n;
 while(m--)
  printf(" ");
 printf(" \\_____(o o)\n");
m = n;
 while(m--)
  printf(" ");
 printf("/      ` @@\n");
m = n;
 while(m--)
  printf(" ");
 printf("\\ ,____ /\n");
m = n;
 while(m--)
  printf(" ");
 printf(" \\\\    \\\\\n");
m = n;
 while(m--)
  printf(" ");
 printf("  ^^    ^^");
}
HWND GetConsoleHwnd(void)
{
#define MY_BUFSIZE 1024 // Buffer size for console window titles.
HWND hwndFound; // This is what is returned to the caller.
char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
char pszOldWindowTitle[MY_BUFSIZE]; // Contains original

GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);//��ȡ����̨�������pszOldWindowTitle��
//���ÿ���̨�ı���Ϊ ʱ���� ����ID
wsprintf(pszNewWindowTitle,"%d/%d",//�ѻ�ȡ����Ŀ���͵�ǰ����ID�����������pszNewwindowtitle��
GetTickCount(),//���ڻ�ȡ����ϵͳ������ĺ�����
GetCurrentProcessId());//��ȡ��ǰ����ID

SetConsoleTitle(pszNewWindowTitle);//���Ŀ���̨�ı���Ϊ������

Sleep(40);

hwndFound=FindWindow(NULL, pszNewWindowTitle);//��ȡ����̨��HWND��

SetConsoleTitle(pszOldWindowTitle);//���Ŀ���̨�ı���Ϊԭʼ����

return(hwndFound);//���ؾ��
}


void drawXY()//����X��Y��
{
HWND hWnd=GetConsoleHwnd();//��ȡ����̨���ھ�����������û�����ɫ
HDC hDC=GetDC(hWnd);
COORD dwSize;//��¼�����С�������趨������Զ��
HPEN hNewPen=CreatePen(PS_SOLID,1,RGB(255,0,0));//�������ʶ���
HPEN hOldPen=(HPEN)SelectObject(hDC,hNewPen);//ѡȡ���ʶ�����л�ͼ
CONSOLE_SCREEN_BUFFER_INFO bInfo; // ������Ϣ
HANDLE Hout=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
GetConsoleScreenBufferInfo(Hout, &bInfo );//��ȡ����̨��Ϣ
dwSize=bInfo.dwMaximumWindowSize ;//��ȡ���ڴ�С,��ʱ��õ����ַ�ģʽ��
//���ַ���ͼ��Ŵ�������8��
dwSize.X *=8;
dwSize.Y*=8;
SetBkMode(hDC, TRANSPARENT);SetTextColor(hDC,255*255);
//����X�������������
TextOut(hDC,dwSize.X-15,dwSize.Y/2-15,"X",1);
//Arc(hDC,100,100,300,300,350,500,350,500);//��Բ ����hDC��ʾ��ͼ�����100��100��300��300��ʾ��ʹ�õľ�������350��500��ʾ�����ߵ���㣬350��500���������ߵ��յ� ;
//����Y�������������
TextOut(hDC,dwSize.X/2,0,"Y",1);
MoveToEx(hDC,0,dwSize.Y /2,NULL);
LineTo(hDC,dwSize.X,dwSize.Y/2);
MoveToEx(hDC,dwSize.X/2,0,NULL);
LineTo(hDC,dwSize.X/2,dwSize.Y);
ReleaseDC(hWnd,hDC);
}
void draw(double p)
{
int i;
double x,y;
HWND hWnd=GetConsoleHwnd();//��ȡ����̨���ھ�����������û�����ɫ
HDC hDC=GetDC(hWnd);
COORD dwSize;//��¼�����С�������趨������Զ��
HPEN hNewPen=CreatePen(PS_SOLID,1,RGB(255,0,0));//�������ʶ���
HPEN hOldPen=(HPEN)SelectObject(hDC,hNewPen);//ѡȡ���ʶ�����л�ͼ
CONSOLE_SCREEN_BUFFER_INFO bInfo; // ������Ϣ
HANDLE Hout=GetStdHandle(STD_OUTPUT_HANDLE);//��ȡ����̨���
GetConsoleScreenBufferInfo(Hout, &bInfo );//��ȡ����̨��Ϣ
dwSize=bInfo.dwMaximumWindowSize ;//��ȡ���ڴ�С,��ʱ��õ����ַ�ģʽ��
//���ַ���ͼ��Ŵ�������8��
dwSize.X *=8;
dwSize.Y*=8;
//MoveToEx(hDC,0,dwSize.Y/2,NULL);
for(i=-180;i<=180;i++)
{
x=16*pow(sin(i*3.1415926/180),3.0)*p;
y=(13*cos(i*3.1415926/180)-5*cos(2*i*3.1415926/180)-2*cos(3*i*3.1415926/180)-cos(4*i*3.1415926/180))*p;


x=(x+16)*dwSize.X/32/2+dwSize.X/4;
y=-y/16*dwSize.Y/2.3+dwSize.Y/2;


x=x;
y=y;
MoveToEx(hDC,x,y,NULL);
LineTo(hDC,x+1,y+1);


}
}
void time()
{  
time_t rawtime;  
struct tm * timeinfo;  
time ( &rawtime );  
timeinfo = localtime ( &rawtime );  
printf ( "The current date/time is: %s", asctime (timeinfo) );  
}
int main()
{	system("color 0b");
//printf("\n");
	int i = 2;
 for(;i<MAX;i=i+1)
 {
  system("cls");
  print(i);
 }printf("            201441010107        �ƿ�1��            ����          \n");
      printf("\n");	
 printf("           �� ɫ �� �� ̬ �� �� �� �� չ �֣��� �� �� �� !!!!  \n");
  printf("              _______�r(�s���t)�q________\n");//���鴿������.......

 Sleep(2000);
 double p;
drawXY();
for(p=0.6;p<=1;p=p+0.01)
draw(p);
system("PAUSE");
system("cls");
system("color 0b");
printf("               �ƿ�һ��   ����   ����       \n");
 for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
            float a = x * x + y * y - 1;system("color 0d");
            putchar(a * a * a - x * x * y * y * y <= 0.0f ? '*' : ' ');
        }
        putchar('\n');
    }
	
	/* for (float y = 1.5f; y > -1.5f; y -= 0.1f) {
        for (float x = -1.5f; x < 1.5f; x += 0.05f) {
			system("color 0D");
            float z = x * x + y * y - 1;
            float f = z * z * z - x * x * y * y * y;
            putchar(f <= 0.0f ? "C+++++++"[(int)(f * -8.0f)] : ' ');
        }
        putchar('\n');
    }*/
system("cls");
   int i1,j,e; 
    int a; 
    int t1;
    for(i1=1,a=I;i1<=I/2;i1++,a--){ 
        t1=6;	system("color 0D");
        while(t1--)printf(" ");
        
        for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
            printf(" "); 
        for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*"); 
   for(j=(int) (   2*( I-sqrt(I*I-(a-i1)*(a-i1)) )   );j>0;j--) 
            printf(" ");
   for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*");
   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
            printf(" ");
   
   t1= (int) (   I-sqrt(I*I-(a-i1)*(a-i1))   ) ;
   t1= 2*t1;
   t1+=(int) ( 2*sqrt(I*I-(a-i1)*(a-i1)) );
   t1=20-t1;
  
   while(t1--){ 	system("color 0D");printf(" ");}

   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
   {	system("color 0b");printf(" "); }
        for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*"); 
   for(j=(int) (   2*( I-sqrt(I*I-(a-i1)*(a-i1)) )   );j>0;j--) 
   {	system("color 0b");printf(" "); }
   for(e=1;e<=2*sqrt(I*I-(a-i1)*(a-i1));e++) 
            printf("*");
   for(j=(int) (   I-sqrt(I*I-(a-i1)*(a-i1))   );j>0;j--) 
   {	system("color 0c");printf(" "); }
   
        printf("\n"); 
    } 
    
    for(i1=11;i1<=R/2;i1++){ 
  	system("color 0a");
        if(i1%2||i1%3)continue;
        
        t1=6;
        if(i1==6)printf(">>----");
        else while(t1--)printf(" ");
      	system("color 0b");
        for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
   {	system("color 0a");printf(" "); }
        for(e=1;e<=2*( sqrt(R*R-i1*i1) - (R-2*I) );e++) 
            printf("*"); 	system("color 0c");
   for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 	system("color 0b");
            
        t1= (int)(   R-sqrt(R*R-i1*i1)   );
        t1=2*t1;	system("color 0c");
        t1+= (int)(2*( sqrt(R*R-i1*i1) - (R-2*I) ));
        t1=35-t1;	system("color 0b");
   
   if(i1==6){printf("LOVE");}
   else if(i1==48){printf("\b\b\b C����!!");	system("color 0b");}
   else 
               while(t1--) printf(" "); 
       for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 	system("color 0c");
        for(e=1;e<=2*( sqrt(R*R-i1*i1) - (R-2*I) );e++) 
            printf("*"); 	system("color 0c");
   for(j=(int) (   R-sqrt(R*R-i1*i1)   );j>0;j--) 
            printf(" "); 
   
   if(i1==6)printf("----->"); 
        printf("\n"); 
    }       
	Sleep(1000);
      system("cls");
	printf("\n");
  	printf("\n");
	printf("\n");
	system("color 0b");
	printf("                      10 �� �� �� C �� �� ѧ ϰ             \n");
	printf("\n");
	printf("\n");
	printf("\n");
    printf("                  ��  �� ѧ  �� �� ��  �� ֪  ʶ   ^U^        \n ");
	system("color 0e");
	printf("\n\n\n\n\n\n\n\n\t\t\t");
	printf("C");
	system("color 0c");
	Sleep(500);
	printf("��");
	system("color 0b");
	Sleep(1000);
	printf("��");
	system("color 0c");
	Sleep(1000);
	printf("���");
	system("color 0f");
	Sleep(1000);
	printf("��");
	system("color 0a");
	Sleep(1000);
	printf("��");
	system("color 0d");
	Sleep(1000);
	printf("��");
	system("color 0f");
	Sleep(1000);
	printf("!!!");
	Sleep(1000);
	printf("ʲô");
	system("color 0b");
	Sleep(1000);
	printf("����");
	system("color 0c");
	Sleep(1000);
	printf("��");
	system("color 0f");
	Sleep(1000);
	printf("��");
	system("color 0a");
	Sleep(1000);
	printf("��");
	system("color 0d");
	Sleep(1000);
	printf("��");
	system("color 0f");
	Sleep(1000);
	printf("!!!");
	Sleep(1000);
	system("cls");
//	heartFlashOne();
//	paintHeart(6);
	system("cls");
	printf("\n\n\n\n");
	printf("\t\t\t");
	Sleep(200);
	printf("��");
	system("color 0a");
	Sleep(200);
	printf("��");
	system("color 0b");
	Sleep(200);
	printf("��");
	system("color 0c");
	Sleep(200);
	printf("��");
	system("color 0d");
	Sleep(200);
	printf("��");
	system("color 0e");
	Sleep(200);
	printf("��");
	system("color 0f");
	Sleep(200);
	printf("��");
	system("color 0c");
	Sleep(200);
	printf("��");
	system("color 0d");
	Sleep(200);
	printf("Ӱ");
	system("color 0e");
	Sleep(200);
	printf("!");
	system("color 0f");
	Sleep(200);
	printf("��");
	system("color 0a");
	Sleep(200);
	printf("��");
	system("color 0b");
	Sleep(200);
	printf("��");
	system("color 0c");
	Sleep(200);
	printf("��\n\n");
	system("color 0c");
	Sleep(200);
	printf("��Ҫ");
	system("color 0b");
	Sleep(200);
	printf("Ŭ��");
	system("color 0c");
	Sleep(200);
	printf(",");
	system("color 0d");
	Sleep(200);
	printf("����");
	system("color 0e");
	Sleep(200);
	printf("Ҫ��!!!");
	system("color 0f");
	Sleep(200);
	printf("-----");
	system("color 0c");
	Sleep(200);
	printf("Ҫ���Լ����Լ�!!!!");
	system("color 0b");
	Sleep(200);
	printf("�׸�");
	system("color 0c");
	Sleep(200);
	printf("����");
	system("color 0d");
	Sleep(200);
	printf("Ŭ��");
	system("color 0e");
	Sleep(200);
	printf("��");
	system("color 0f");
	Sleep(200);
	printf("�Լ�!!!");
	system("color 0d");
	Sleep(200);
	printf("����");
	system("color 0e");
	Sleep(200);
	printf("!!!");
	system("color 0f");
	Sleep(200);
	printf(" ���� !");
	system("color 0c");
	Sleep(200);
	system("color 0d");
	Sleep(200);
	system("color 0e");
	Sleep(200);
	system("color 0f");
	Sleep(500);
	system("color 0a");
	printf("\n");
/* printf("****************************************************************************\n");
 printf("**                                                                        **\n");
 time();
 printf("**                                                                        **\n");
 printf("****************************************************************************\n");
 system("color 0e");
printf("\n");
printf("\n");*/
 system("cls");
 printf("\n");
 printf("*********************��ӭ����C����ģ�����ݿ�ϵͳ***************************\n");
 printf("   *********************************************************************\n");
 	system("color 1e");
	for (;;)
	switch(menu_select()) {
		case 1:
			create_dbf();
			break;
		case 2:
			insert_rec();
			break;
		case 3:
			display();
			break;
		case 4:
			delete_rec();
			break;
		case 5:
			find_rec();
			break;
		case 6:
			appe_rec();
			break;
		case 7:
			printf("�˳����У��ټ���\n");
			exit(0);
		case 8:
			qj();
			break;
        case 9:
			hj();
			break;
		case 10:
			{
				printf("****************************************************************************\n");
                printf("**                                                                        **\n");
				time();
				printf("**                                                                        **\n");
                printf("****************************************************************************\n");
			}
			break;
        case 11:
			rili();
			break;
			}
	return 0;
}

int menu_select()
{
	char s[2];
	int cn;
//system("cls");
	printf("      ****************************************************************\n");
	printf("        ��-------------- 1.�������ݿ�ṹ--------       C        ��\n");
	printf("        ��-------------- 2.�����¼--------------      ��    O O ��\n");
	printf("        ��-------------- 3.��ʾ��¼--------------      ��     V  ��\n");
	printf("        ��-------------- 4.ɾ����¼--------------      ��        ��\n");
	printf("        ��-------------- 5.���Ҽ�¼--------------      ��    O O ��\n");	
	printf("        ��-------------- 6.׷�Ӽ�¼--------------      ��     -  ��\n");	
	printf("        ��-------------- 7.�˳����У�------------      ˼        ��\n");
   	printf("        ��-------------- 8.�ı�ǰ����ɫ��------------  ,         ��\n");
   	printf("        ��-------------- 9.�ı����ɫ��------------  ��    O O ��\n");
	printf("        ��-------------- 10.��ʾ��ǰ���ڣ�------------ ��     V  ��\n");
    printf("        ��-------------- 11.��ѡ����������^v^-----------     ��\n");
	printf("     ***************************************************************\n");
	printf("\n");
	printf("        ��-------------------��ѡ��1-11:----------------------    ��\n");
   //system("color 0D");
	for (;;)
	{
		gets(s);
		cn=atoi(s);
		if (cn<1||cn>11) printf("\nѡ�������ѡ1-11��");
		else break;
	}system("color 0a"); system("cls");
	printf("                       *******     C    *******\n");
    printf("                      *******     ��     *******\n");
	printf("                       *********  ��  ******** \n");
    printf("                        *******   ��   *******\n");
	printf("                         ******   ��   ******   \n");
    printf("                             ***  ��  ***\n");
    printf("                                ******\n");
    printf("                                  **\n");
		return cn;
}
 	
void create_struct() //�������ݿ�ṹ 
{

	int i=0,field_num;
	for(;;)
	{
		memset(&fields[i],0,32);
		printf("�ֶ�����10���ַ������ֶ����ͣ��ֶγ��ȣ�С��λ��\n");
		scanf("%s",fields[i].field_name); //�ֶ���ASCII��
		if (strcmp(fields[i].field_name,"!")==0) break;
			
		getchar();
		scanf("%c",&fields[i].field_type); //�ֶ�����

		scanf("%d",&fields[i].field_len);  //�ֶγ��ȵĶ�������
		
		if (i==0) fields[i].unse1=1;
		else  fields[i].unse1=fields[i-1].unse1+fields[i-1].field_len;   //�ֶ��ڼ�¼�е�λ�� 
		
		dbf_head.record_byte_num+=fields[i].field_len;             //��¼���� 
		
		scanf("%d",&fields[i].decimal);    //С�����λ����2������
		fseek(dbfp,32+i*32,0);
		fwrite(&fields[i],32,1,dbfp);
		i++;
	}
		field_num=i;
		fseek(dbfp,32+i*32,0);
		fputc(13,dbfp);
		for (i=0;i<263;i++)
			fputc(0,dbfp);
	
/*		printf("%s","������Ӽ�¼�𣿣�y/n��");
		char ch=getchar();
		if (ch=='y'||ch=='Y') 
		{
			appe_rec();
			return;
		}*/
		fputc(0x1A,dbfp);
		dbf_head.stru_byte_num=32+32*field_num+1+263;//�ֶ��������ڴ��еĵ�ַ32���ļ�ͷ��+32*�ֶθ���+1��������־��+263
		dbf_head.record_byte_num++;  //��¼���� 
		return ;

}

void create_dbf() // �������ݿ��ļ�ͷ��Ϣ�����ݿ�ṹ 
{	system("color 0b");

	char fname[20];
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"wb");
	dbf_head.ver=48;                  //�汾 
	dbf_head.date[0]=15; //�� 
	dbf_head.date[1]=9;	 //�� 
	dbf_head.date[2]=8;  //�� 
	dbf_head.record_num=0; //��¼�� 
	dbf_head.stru_byte_num=32+32*0+1+263;//�ֶ��������ڴ��еĵ�ַ=32���ļ�ͷ��+32*�ֶθ���+1��������־0D��+263
	dbf_head.record_byte_num=0;//��¼���� 

	for(int i=0;i<20;i++)            //20�ֽڱ��� 
		dbf_head.unse[i]=0;
	dbf_head.unse[17]=0x7A;
	
	fwrite(&dbf_head,32,1,dbfp);  //д���ݿ��ļ����ļ�ͷ��Ϣ��32���ֽ� 
	
	create_struct();

	fseek(dbfp,0,0);             
	fwrite(&dbf_head,32,1,dbfp);   //�ر��ļ�ǰ��д�ļ�ͷ��Ϣ 

	fclose(dbfp);
}

void key_read()  // ��¼���ݴ����ڴ�ռ�cc�� 
{
	int i,j,field_num,k;
	char ccc[255];

	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //�ֶ��� 	
	cc=(char *)malloc(dbf_head.record_byte_num);  //�ݴ��¼ 
	memset(cc,32,dbf_head.record_byte_num);  //��¼��������Ϊ�ո� 
	gets(ccc);
	for (i=0;i<field_num;i++)
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //��ȡ�ֶ�������Ϣ 
		printf("�ֶ�����%s,���ͣ�%c,���ȣ�%d,С��λ��%d\n",	fields[i].field_name,fields[i].field_type,fields[i].field_len,fields[i].decimal);
		if (gets(ccc)==NULL)
		{
			printf("�������ݴ���");
			exit(0);
		}
		if (strlen(ccc)>fields[i].field_len)
		{
			printf("��������̫��������һ��!!\n");
			i--;
		}
		else 
			if (fields[i].field_type=='I')
			{
                int n;
                n=atoi(ccc);
                *((int *)(cc+fields[i].unse1))=n;   //����ΪI�����ݴ���cc�� 
			}
			else if (fields[i].field_type=='N') 
			{
				memcpy(cc+(fields[i].unse1+fields[i].field_len-strlen(ccc)),ccc,strlen(ccc));
			}
			else
			{
				memcpy(cc+fields[i].unse1,ccc,strlen(ccc)); //�ֶ����ݸ��Ƶ����ֶ��ڼ�¼�е�λ�ô�
			}
		
	}
}
void appe_rec() //׷�Ӽ�¼  
{
	system("color 0a");

	char fname[20];   //���ļ����ļ�������ʱ��
	char yn;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	//fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("������Ӽ�¼��(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
	fclose(dbfp);
	return; 
} 

void insert_rec()//��������
{
	int n1,i,field_num;
	char fname[20];   //���ļ����ļ�������ʱ��
	char yn;
	char *records,*rec_i;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");//�����ݿ�
	fread(&dbf_head,32,1,dbfp);//��ȡͷ�ļ���Ϣ
	//fseek(dbfp,0,SEEK_SET);
    printf("����������λ��\n");
    scanf("%d",&n1);
	printf("�������������\n");
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //�ֶ��� 
    fseek(dbfp,dbf_head.stru_byte_num+n1*32,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
    for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("������Ӽ�¼��(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
   
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
    
	fclose(dbfp);
	return; 
	}


void display()
{
	char fname[20];   //���ļ����ļ�������ʱ��
	char yn;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	
	int i,j,field_num,k;
	char *records,*rec_i;
	int offset;
	char ccc[255];
	fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //�ֶ��� 
	fseek(dbfp,dbf_head.stru_byte_num,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
	
	printf("��¼��\t");
	for (i=0;i<field_num;i++)    
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //��ȡ�ֶ�������Ϣ 
		printf("%s\t",	fields[i].field_name); //��ʾ�ֶ��� 
	}
	printf("\n");
	
	offset=0;
	for (j=0;j<dbf_head.record_num;j++ )
	{
		memcpy(rec_i,records+offset,dbf_head.record_byte_num);

		printf("%3d   ",j+1);
		printf("%c",*rec_i);
		for (i=0;i<field_num;i++)
		{

			if (fields[i].field_type=='C')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("%s",ccc);
			}
			if (fields[i].field_type=='L')
			{
				printf("%c",*(rec_i+fields[i].unse1));
			}
			if (fields[i].field_type=='I')
			{
				printf("%4d",*(rec_i+fields[i].unse1));
			}			
			if (fields[i].field_type=='N')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("%s",ccc);
			}
			
		}
		printf("\n");
		offset+=dbf_head.record_byte_num;
	}
}

void delete_rec()
{
/*	int n1,i,field_num;
	char fname[20];   //���ļ����ļ�������ʱ��
	char yn;
	char *records,*rec_i;
	printf("\n");
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");//�����ݿ�
	fread(&dbf_head,32,1,dbfp);//��ȡͷ�ļ���Ϣ
	//fseek(dbfp,0,SEEK_SET);
    printf("����ɾ����λ��\n");
    scanf("%d",&n1);
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //�ֶ��� 
    fseek(dbfp,dbf_head.stru_byte_num+n1*32,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
    for (;;)
	{
		key_read();
		dbf_head.record_num++;
	    fseek(dbfp,-1,SEEK_END);
	    if (fgetc(dbfp)==0x1A)	fseek(dbfp,-1,SEEK_END);
	    else fseek(dbfp,0,SEEK_END);
		fwrite(cc,dbf_head.record_byte_num,1,dbfp);
	
		printf("����ɾ����¼��(Y/N)");
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
   
	fputc(0x1A,dbfp);
	fseek(dbfp,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfp);
    
	fclose(dbfp);
	return; */
		char fname[20],fnamels[7]="00.dbf";   //���ļ����ļ�������ʱ��
	char yn,*xx,*yy;
	int dp,field_num;
	FILE*dbfpls;
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	fread(&dbf_head,32,1,dbfp);//��ȡ�ļ�ͷ��Ϣ��32�ֽڵ��ļ�ͷ�����ݿ�ṹ��
	yy=(char*)malloc(dbf_head.stru_byte_num-32);//����һ��(�ֶ���Ϣ��263)�ڴ�ռ�yy������malloc���䣩
	fseek(dbfp,32,0);//�ļ�ָ��ָ����һ���ֶ�
    fread(yy,dbf_head.stru_byte_num-32,1,dbfp);//�ݴ��¼ //���ֶμ�¼��263���Ƶ�yy��
	for (;;)
	{	
		printf("����Ҫɾ���ڼ�����¼");
     	scanf("%d",&dp);
        xx=(char*)malloc(dbf_head.record_byte_num*dbf_head.record_num); //����һ������¼��ռ���ֽڣ��ڴ�ռ�xx������malloc���䣩
		fseek(dbfp,dbf_head.stru_byte_num,0);//�ļ�ָ��ָ����һ����¼
		fread(xx,dbf_head.record_byte_num,dp-1,dbfp); //�ݴ��¼ //��1��i����¼�ĸ��Ƶ�xx��
		dbfpls=fopen(fnamels,"wb+");
        fseek(dbfpls,dbf_head.stru_byte_num,0);//���ļ�ָ��ָ����һ����¼����λ��
        fwrite(xx,dbf_head.record_byte_num,dp-1,dbfpls);//�ڴ�ռ�xx�е����ݣ�1��i����¼��д�����ļ�
		fseek(dbfp,dbf_head.stru_byte_num+dbf_head.record_byte_num*dp,0);//�ļ�ָ��ָ����i+1����¼����λ��
        fread(xx,dbf_head.record_byte_num,dbf_head.record_num-dp,dbfp);//��i+1��n����¼���Ƶ�xx��
		fseek(dbfpls,dbf_head.stru_byte_num+dbf_head.record_byte_num*(dp-1),0);//���ļ�ָ��ָ����i+1����¼����λ��
		fwrite(xx,dbf_head.record_byte_num,dbf_head.record_num-dp,dbfpls);//�ڴ�ռ�xx�е����ݣ�i+1��n����¼��д�����ļ�
        free(xx);
		dbf_head.record_num--;
		printf("����ɾ����¼��(Y/N)");
   		getchar();
		scanf("%c",&yn);
		if (yn=='Y'||yn=='y') continue;
		else break;
	}
	fputc(0x1A,dbfpls);
	fseek(dbfpls,0,SEEK_SET);
	fwrite(&dbf_head,32,1,dbfpls); //�ر��ļ�ǰ��д�ļ�ͷ��Ϣ 
	fwrite(yy,dbf_head.stru_byte_num-32,1,dbfpls);//�ڴ�ռ�yy�е����ݣ��ֶμ�¼��263��д�����ļ�
	free(yy);
	fclose(dbfp);
	fclose(dbfpls);
	if( access(fname,0 )== -1 )
		printf( "�ļ�������\n");
	else
	{
		remove(fname);//����system()����ɾ��ԭ���Ŀ��ļ�
		rename(fnamels,fname);//����system�����������µĿ��ļ�����Ϊԭ���Ŀ��ļ�
	}  
    system("pause");
	getchar();
    return;
}

void find_rec()
{
char fname[20];   //���ļ����ļ�������ʱ��
	char yn;
	printf("please input file name:" );
	scanf("%s",fname);
	dbfp=fopen(fname,"rb+");
	
	int num;
	printf("�������¼�ţ�");
	scanf("%d",&num);

	int i,field_num,k;
	char *records,*rec_i;
	int offset;
	char ccc[255];
	fseek(dbfp,0,SEEK_SET);
	fread(&dbf_head,32,1,dbfp);
	
	records=(char *)malloc(dbf_head.record_num*dbf_head.record_byte_num);
	rec_i=(char*)malloc(dbf_head.record_byte_num);
	field_num=(dbf_head.stru_byte_num-32-1-263)/32; //�ֶ��� 
	fseek(dbfp,dbf_head.stru_byte_num,SEEK_SET);
	fread(records,dbf_head.record_byte_num,dbf_head.record_num,dbfp);
	
	printf("��¼��\t");
	for (i=0;i<field_num;i++)    
	{
		fseek(dbfp,(i+1)*32,0);
		fread(&fields[i],32,1,dbfp); //��ȡ�ֶ�������Ϣ 
		printf("%s\t",	fields[i].field_name); //��ʾ�ֶ��� 
	}
	printf("\n");
	
	offset=dbf_head.record_byte_num*(num-1);
		memcpy(rec_i,records+offset,dbf_head.record_byte_num);

		printf("%3d   ",num);
		printf("%c",*rec_i);
		for (i=0;i<field_num;i++)
		{

			if (fields[i].field_type=='C')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf(" %s",ccc);
			}
			if (fields[i].field_type=='L')
			{
				printf("%c",*(rec_i+fields[i].unse1));
			}
			if (fields[i].field_type=='I')
			{
				printf("%8d",*(rec_i+fields[i].unse1));
			}			
			if (fields[i].field_type=='N')
			{
				memcpy(ccc,rec_i+fields[i].unse1,fields[i].field_len);
				ccc[fields[i].field_len]=0;
				printf("    %s",ccc);
			}
		
	}
	printf("\n");
	system("pause");
	getchar();
	return;
	
	
}
void qj()
{
	system("color 9b");
}
void hj()
{
    system("color 07");

}

void rili()
{
 int i;
 int day;
 int year;
 int temp;
 int temp_i;
 long int Year_days = 0;
 int Year_Start = 1;
 int Per_Year_Days;
 int month_day[]={31,28,31,30,31,30,31,31,30,31,30,31,29};
 printf("Please enter the year: ");
 scanf("%d",&year);
 while(Year_Start < year)
 {
  if( IsLeapYear( Year_Start ) )
   Per_Year_Days = 366;
  else
   Per_Year_Days = 365;
  Year_days = Year_days + Per_Year_Days;
  Year_Start++;
 }
 for( temp = 1; temp <=12; temp++ )
 {
  switch( temp )
  {
   case 1:
    printf("    January(%d)\n",year);
    break;
   case 2:
    printf("    February(%d)\n",year);
    break;
   case 3:
    printf("    March(%d)\n",year);
    break;
   case 4:
    printf("    April(%d)\n",year);
    break;
   case 5:
    printf("    May(%d)\n",year);
    break;
   case 6:
    printf("    June(%d)\n",year);
    break;
   case 7:
    printf("    July(%d)\n",year);
    break;
   case 8:
    printf("    August(%d)\n",year);
    break;
   case 9:
    printf("    September(%d)\n",year);
    break;
   case 10:
    printf("    October(%d)\n",year);
    break;
   case 11:
    printf("   November(%d)\n",year);
    break;
   case 12:
    printf("   December(%d)\n",year);
    break;
  }
  i = Year_days % 7;
  printf("Mon Tue Wed Thu Fri Sat Sun\n");
  if( i != 0 )
   for( temp_i = 0; temp_i < i; temp_i++)
    printf("    ");
  day = 1;
  if( IsLeapYear(year) && temp == 2)
   while( day <= month_day[12] )
   {
    if( day >1 )
     if( Year_days % 7 == 0 )
      printf("\n");
    if( day >= 10 )
     printf("%d  ",day);
    else
     printf("%d   ",day);
    Year_days++;
    day++;
   }
  else
   while (day <= month_day[temp-1])
   {
    if( day > 1 )
     if( Year_days % 7 == 0 )
      printf("\n");
    if( day >=10 )
     printf("%d  ",day);
    else
     printf("%d   ",day);
    Year_days++;
    day++;
   }
  printf("\n");
  if( getch() == 'q' )
   exit(0);
 }
 getch();
}

int IsLeapYear( int year )
{
 if ((year %4 == 0) && (year % 100 != 0) ||
    (year % 400 == 0) )
  return 1;
 else
  return 0;
}
void clear()
{
	system("cls");
	printf("  %c�������%c\n\n",2,2);
	main();
}
