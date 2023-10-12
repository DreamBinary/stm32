#include "stm32f4xx.h"
#include "Touch.h"
#include "spi.h"

extern Pen_Holder Pen_Point;

uint8_t rev_byte;
uint8_t CMD_X[3] = {0xD0, 0x00, 0x00};
uint8_t CMD_Y[3] = {0x90, 0x00, 0x00};
uint8_t SPI_RE[3] = {0};

extern SPI_HandleTypeDef hspi2;

/*SPI读写一字节*/
unsigned char SPI_SendByte(uint8_t byte) {
    uint8_t Tx_DATA[1] = {byte};
    uint8_t Rx_DATA[1] = {0};
//	HAL_SPI_TransmitReceive( &hspi2,Tx_DATA,Rx_DATA,1,0x1000);
    HAL_SPI_Transmit(&hspi2, Tx_DATA, 1, 10);
    HAL_Delay(5);
    HAL_SPI_Receive(&hspi2, Rx_DATA, 1, 10);
    return Rx_DATA[0];

}


//SPI读数据 
//从7846/7843/XPT2046/UH7843/UH7846读取adc值	  

uint16_t ADS_Read_AD(uint8_t *CMD) {
    uint16_t Date;
    uint8_t Num[3] = {0};
//	uint8_t send[3] ={CMD,0X00,0x00};
    HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);
    Date = 0;

    HAL_SPI_TransmitReceive(&hspi2, CMD, Num, 3, 10);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET);

    Date = 0;
    Date = Num[1] << 8;
    Date |= Num[2];
    Date >>= 4;
    Date &= 0XFFF;
    return Date;
}

//带滤波的坐标读取
//最小值不能少于100.
uint8_t Read_ADS(uint16_t *x, uint16_t *y) {
    uint16_t xtemp, ytemp;
//	xtemp=ADS_Read_XY(CMD_RDX);
//	ytemp=ADS_Read_XY(CMD_RDY);
    xtemp = ADS_Read_AD(CMD_X);
//	HAL_Delay(5);
    ytemp = ADS_Read_AD(CMD_Y);
//	xtemp=ADS_Read_AD(CMD_RDX);
//	ytemp=ADS_Read_AD(CMD_RDY);
//	printf("xtemp : %d \n",xtemp);
//  printf("ytemp : %d \n",ytemp);
//	if(xtemp<10||ytemp<10)  return 0;//读数失败
    *x = xtemp;
    *y = ytemp;
//	printf("xx=%d yy=%d \n",*x,*y);
    return 1;//读数成功
}


//2次读取ADS7846,连续读取2次有效的AD值,且这两次的偏差不能超过
//50,满足条件,则认为读数正确,否则读数错误.	   
//该函数能大大提高准确度
#define ERR_RANGE 10 //误差范围 

uint8_t Read_ADS2(uint16_t *x, uint16_t *y) {
    uint16_t x1, y1;
    uint16_t x2, y2;
    uint8_t flag;
    flag = Read_ADS(&x1, &y1);
    if (flag == 0)return 0;
    flag = Read_ADS(&x2, &y2);
    if (flag == 0)return 0;

//    if(( (x2<=x1&&x1<x2+ERR_RANGE) || (x1<=x2&&x2<x1+ERR_RANGE) )          //前后两次采样在+-50内
//        &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
//    {


    *x = (x1 + x2) / 2;
    *y = (y1 + y2) / 2;
//				printf("x1=%d y1=%d \n",*x,*y);
    return 1;
//    }else return 1;	  
}


//转换结果
//根据触摸屏的校准参数来决定转换后的结果,保存在X0,Y0中
uint8_t Convert_Pos(void) {
    HAL_Delay(8);
    if (Read_ADS2(&Pen_Point.X, &Pen_Point.Y)) {
//		Pen_Point.X0=Pen_Point.xfac*Pen_Point.X+Pen_Point.xoff;
//		Pen_Point.Y0=Pen_Point.yfac*Pen_Point.Y+Pen_Point.yoff;  
        Pen_Point.X0 = (float) (0.272074431) * Pen_Point.X + (short) 0xFFD2;
        Pen_Point.Y0 = (float) (0.1643653285) * Pen_Point.Y + (short) 0xFFDC;  //以把矫正过的数据写死，以后不用在矫正
//			if(Pen_Point.X0 == 0) 
//			{
//					return 0;
//			}
        return 1;
    } else return 0;
}


