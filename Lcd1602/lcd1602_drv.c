#include "lcd1602_drv.h"


/************************************************
�������� �� Read_Busy
��    �� �� Lcd1602��дæ���
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
static void Read_Busy(void)         
{
    LCD1602_DB(0xFF);		// ׼˫����ڶ��ⲿ״̬ǰ��Ҫ������Ϊ��1��
    LCD1602_RS(LOW);
    LCD1602_RW(HIGH);
	LCD1602_EN(HIGH);
	while(LCD1602_D7_READ)
		;					// �ȴ���д��������
	LCD1602_EN(LOW);    	// �ͷ�����
}

/************************************************
�������� �� Lcd1602_Write_Cmd
��    �� �� Lcd1602д����
��    �� �� Cmd ---- ����
�� �� ֵ �� ��
*************************************************/
void Lcd1602_Write_Cmd( uint8_t Cmd )    
{
    Read_Busy();
    LCD1602_RS(LOW);
    LCD1602_RW(LOW);
    LCD1602_DB(Cmd);
    LCD1602_EN(HIGH);
    LCD1602_EN(LOW);
}

/************************************************
�������� �� Lcd1602_Write_Data
��    �� �� Lcd1602д����
��    �� �� Data ---- ����
�� �� ֵ �� ��
*************************************************/
static void Lcd1602_Write_Data( uint8_t Data ) 
{
	Read_Busy();
	LCD1602_RS(HIGH);
	LCD1602_RW(LOW);
	LCD1602_DB(Data);
	LCD1602_EN(HIGH);
	LCD1602_EN(LOW);
}

/************************************************
�������� �� Lcd_Coord
��    �� �� Lcd1602������ʾ
��    �� �� X ---- X��
			Y ---- Y��
�� �� ֵ �� ��
*************************************************/
static void Lcd_Coord( uint8_t X, uint8_t Y ) 
{
    uint8_t addr = 0;
    if(!Y)
        addr = 0x00 + X;
    else
        addr = 0x40 + X;
    
    Lcd1602_Write_Cmd(addr | 0x80);
}

/************************************************
�������� �� Lcd_Show_Str
��    �� �� Lcd1602��ʾ
��    �� �� Str ---- ����
			X ---- X��
			Y ---- Y��
			Len --- ����
�� �� ֵ �� ��
*************************************************/
void Lcd_Show_Str( const uint8_t *Str, uint8_t X, uint8_t Y, uint8_t Len )
{
    Lcd_Coord(X,Y);							//��ǰ�ַ�������
	
    while(Len--)
    {
        Lcd1602_Write_Data(*Str++);
    }
}

/************************************************
�������� �� Lcd_Printf
��    �� �� Lcd1602�ַ�����ʾ
��    �� �� Str ---- ����
			X ---- X��
			Y ---- Y��
�� �� ֵ �� ��
*************************************************/
void Lcd_Printf( const uint8_t *Str, uint8_t X, uint8_t Y )
{
    Lcd_Coord(X,Y);							//��ǰ�ַ�������
    while(*Str != '\0')
    {
        Lcd1602_Write_Data(*Str++);
    }
}

/************************************************
�������� �� Lcd1602_Config
��    �� �� Lcd1602����
��    �� �� ��
�� �� ֵ �� ��
*************************************************/
void Lcd1602_Config(void)
{
	P1_0 = 0;						// �ر������
	P1_1 = 0;
	P1_2 = 0;
	P1_3 = 0;
}

/************************************************
�������� �� Lcd1602_Init
��    �� �� Lcd1602��ʼ��
��    �� �� D ---- ��ʾ���� or �أ�
			C ---- �����ʾ
			B ---- �����˸
			N ---- ��ַ�ƶ�
			S ---- ��Ļ�ƶ�
�� �� ֵ �� ��
*************************************************/
void Lcd1602_Init( uint8_t D, uint8_t C, uint8_t B, uint8_t N, uint8_t S )
{
	uint8_t disp = 0x08;
	uint8_t offset = 0x04;
	
	Lcd1602_Config();
	
	disp |= ((D << 2) | (C << 1) | (B << 0));
	offset |= ((N << 1) | (S << 0));
	
    Lcd1602_Write_Cmd(0x38);    	//�򿪣�5*8,8λ����
    Lcd1602_Write_Cmd(disp);
    Lcd1602_Write_Cmd(offset);
    Lcd1602_Write_Cmd(LCD_CLEAR);   //����   	
}


/*---------------------------- END OF FILE ----------------------------*/

