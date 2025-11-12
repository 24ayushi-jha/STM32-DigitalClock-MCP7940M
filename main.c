/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#define MCP7940M_ADDRESS		(0x6f<<1)
void LCD_Send_8bit(uint8_t data)
{
    // D0
    if ((data & 0x01) == 0x01)
    {
        HAL_GPIO_WritePin(LCD_D0_7_GPIO_Port, LCD_D0_7_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D0_7_GPIO_Port, LCD_D0_7_Pin, GPIO_PIN_RESET);
    }

    // D1
    if ((data & 0x02) == 0x02)
    {
        HAL_GPIO_WritePin(LCD_D1_8_GPIO_Port, LCD_D1_8_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D1_8_GPIO_Port, LCD_D1_8_Pin, GPIO_PIN_RESET);
    }

    // D2
    if ((data & 0x04) == 0x04)
    {
        HAL_GPIO_WritePin(LCD_D2_9_GPIO_Port, LCD_D2_9_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D2_9_GPIO_Port, LCD_D2_9_Pin, GPIO_PIN_RESET);
    }

    // D3
    if ((data & 0x08) == 0x08)
    {
        HAL_GPIO_WritePin(LCD_D3_10_GPIO_Port, LCD_D3_10_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D3_10_GPIO_Port, LCD_D3_10_Pin, GPIO_PIN_RESET);
    }

    // D4
    if ((data & 0x10) == 0x10)
    {
        HAL_GPIO_WritePin(LCD_D4_11_GPIO_Port, LCD_D4_11_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D4_11_GPIO_Port, LCD_D4_11_Pin, GPIO_PIN_RESET);
    }

    // D5
    if ((data & 0x20) == 0x20)
    {
        HAL_GPIO_WritePin(LCD_D5_12_GPIO_Port, LCD_D5_12_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D5_12_GPIO_Port, LCD_D5_12_Pin, GPIO_PIN_RESET);
    }

    // D6
    if ((data & 0x40) == 0x40)
    {
        HAL_GPIO_WritePin(LCD_D6_13_GPIO_Port, LCD_D6_13_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D6_13_GPIO_Port, LCD_D6_13_Pin, GPIO_PIN_RESET);
    }

    // D7
    if ((data & 0x80) == 0x80)
    {
        HAL_GPIO_WritePin(LCD_D7_14_GPIO_Port, LCD_D7_14_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(LCD_D7_14_GPIO_Port, LCD_D7_14_Pin, GPIO_PIN_RESET);
    }
}
void LCD_Send_Command(uint8_t cmd)
{
	 HAL_GPIO_WritePin(LCD_RS_4_GPIO_Port,LCD_RS_4_Pin,GPIO_PIN_RESET);
	 HAL_GPIO_WritePin(LCD_RW_5_GPIO_Port,LCD_RW_5_Pin,GPIO_PIN_RESET);
	 LCD_Send_8bit(cmd);
	 HAL_GPIO_WritePin(LCD_EN_6_GPIO_Port,LCD_EN_6_Pin,GPIO_PIN_SET);
     HAL_Delay(2);
     HAL_GPIO_WritePin(LCD_EN_6_GPIO_Port,LCD_EN_6_Pin,GPIO_PIN_RESET);
}
void LCD_Init(void)
{
	 HAL_Delay(50);
	 LCD_Send_Command(0x38);
	 HAL_Delay(2);
	 LCD_Send_Command(0x38);
	 HAL_Delay(2);
	 LCD_Send_Command(0x0C);
	 HAL_Delay(2);
	 LCD_Send_Command(0x01);
	 HAL_Delay(2);
	 LCD_Send_Command(0x06);
	 HAL_Delay(2);
}
//function for printing any digit
void LCD_Print_Data(uint8_t data)
{
	 HAL_GPIO_WritePin(LCD_RS_4_GPIO_Port,LCD_RS_4_Pin,GPIO_PIN_SET);
	 HAL_GPIO_WritePin(LCD_RW_5_GPIO_Port,LCD_RW_5_Pin,GPIO_PIN_RESET);
	 LCD_Send_8bit(data);
	 HAL_GPIO_WritePin(LCD_EN_6_GPIO_Port,LCD_EN_6_Pin,GPIO_PIN_SET);
	 HAL_Delay(2);
	 HAL_GPIO_WritePin(LCD_EN_6_GPIO_Port,LCD_EN_6_Pin,GPIO_PIN_RESET);
}
//function for printing string
void Print_LCD_String(uint8_t *ptr)
{
	while(*ptr)
	{
		LCD_Print_Data(*ptr);
		ptr++;
    }
}
//function for printing of keypads
uint8_t keypressed=0;
void keycheck(void)
{
    keypressed = 0xFF;
    // LCD_Send_Command(0x80 | 0x41);

    // --- Row 1 ---
    HAL_GPIO_WritePin(KEY1_R1_GPIO_Port, KEY1_R1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY2_R2_GPIO_Port, KEY2_R2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY3_R3_GPIO_Port, KEY3_R3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY4_R4_GPIO_Port, KEY4_R4_Pin, GPIO_PIN_SET);

    if (HAL_GPIO_ReadPin(KEY5_C1_GPIO_Port, KEY5_C1_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '1';
    }
    else if (HAL_GPIO_ReadPin(KEY6_C2_GPIO_Port, KEY6_C2_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '2';
    }
    else if (HAL_GPIO_ReadPin(KEY7_C3_GPIO_Port, KEY7_C3_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '3';
    }
    else if (HAL_GPIO_ReadPin(KEY8_C4_GPIO_Port, KEY8_C4_Pin) == GPIO_PIN_RESET)
    {
        keypressed = 'A';
    }

    // --- Row 2 ---
    HAL_GPIO_WritePin(KEY1_R1_GPIO_Port, KEY1_R1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY2_R2_GPIO_Port, KEY2_R2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY3_R3_GPIO_Port, KEY3_R3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY4_R4_GPIO_Port, KEY4_R4_Pin, GPIO_PIN_SET);

    if (HAL_GPIO_ReadPin(KEY5_C1_GPIO_Port, KEY5_C1_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '4';
    }
    else if (HAL_GPIO_ReadPin(KEY6_C2_GPIO_Port, KEY6_C2_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '5';
    }
    else if (HAL_GPIO_ReadPin(KEY7_C3_GPIO_Port, KEY7_C3_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '6';
    }
    else if (HAL_GPIO_ReadPin(KEY8_C4_GPIO_Port, KEY8_C4_Pin) == GPIO_PIN_RESET)
    {
        keypressed = 'B';
    }

    // --- Row 3 ---
    HAL_GPIO_WritePin(KEY1_R1_GPIO_Port, KEY1_R1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY2_R2_GPIO_Port, KEY2_R2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY3_R3_GPIO_Port, KEY3_R3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(KEY4_R4_GPIO_Port, KEY4_R4_Pin, GPIO_PIN_SET);

    if (HAL_GPIO_ReadPin(KEY5_C1_GPIO_Port, KEY5_C1_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '7';
    }
    else if (HAL_GPIO_ReadPin(KEY6_C2_GPIO_Port, KEY6_C2_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '8';
    }
    else if (HAL_GPIO_ReadPin(KEY7_C3_GPIO_Port, KEY7_C3_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '9';
    }
    else if (HAL_GPIO_ReadPin(KEY8_C4_GPIO_Port, KEY8_C4_Pin) == GPIO_PIN_RESET)
    {
        keypressed = 'C';
    }
    // --- Row 4 ---
    HAL_GPIO_WritePin(KEY1_R1_GPIO_Port, KEY1_R1_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY2_R2_GPIO_Port, KEY2_R2_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY3_R3_GPIO_Port, KEY3_R3_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEY4_R4_GPIO_Port, KEY4_R4_Pin, GPIO_PIN_RESET);

    if (HAL_GPIO_ReadPin(KEY5_C1_GPIO_Port, KEY5_C1_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '*';
    }
    else if (HAL_GPIO_ReadPin(KEY6_C2_GPIO_Port, KEY6_C2_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '0';
    }
    else if (HAL_GPIO_ReadPin(KEY7_C3_GPIO_Port, KEY7_C3_Pin) == GPIO_PIN_RESET)
    {
        keypressed = '#';
    }
    else if (HAL_GPIO_ReadPin(KEY8_C4_GPIO_Port, KEY8_C4_Pin) == GPIO_PIN_RESET)
    {
        keypressed = 'D';
    }
}
uint8_t key_press_count=0;
uint8_t user_input[3];
uint8_t Index=0;
uint8_t one_time_enter=1;
uint8_t edit_count=0;
uint8_t current_field=0;
uint8_t set_mode=0;
uint8_t min;
uint8_t sec;
uint8_t hour;
void key_action(void)
{
    if (keypressed != 0xFF)
    {
        if (one_time_enter == 1)
        {
        	one_time_enter = 0;
            LCD_Send_Command(0xC0 + Index);
            user_input[Index] = keypressed;
            Index++;
            LCD_Send_Command(0x80|0x43);
            LCD_Print_Data(keypressed);
		}
				//            if (Index >= 3)
				//            {
				//                Index = 0;
				//                if (user_input[0] == '1' && user_input[1] == '2' && user_input[2] == '3')
				//                {
				//                    Print_LCD_String((uint8_t *)" : RIGHT");
				//                }
				//                else
				//                {
				//                    Print_LCD_String((uint8_t *)" : WRONG");
				//                }
				//                // LCD_Send_Command((0x80 | 0x40) >> 0x01);
				//                // LCD_Print_Data(keypressed);
				//            }
        else
        {
        	one_time_enter = 1;
        }
    }
}


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

/* USER CODE BEGIN PV */

//uint8_t seconds;
uint8_t weekday;
uint8_t date;
uint8_t month;
uint8_t year;
uint8_t decToBCD(uint8_t dec)
{
	uint8_t high,low,bcd;
	low=dec%10;
	dec=dec/10;
	high=dec%10;
	bcd=high;
	bcd=bcd<<4;
	bcd=bcd|low;
	return bcd;
//	return ((val/10)<<4) + (val%10);
}
uint8_t BCDToDec(uint8_t bcd)
{
	uint8_t high,low,dec;
	low=bcd & 0x0f;
	bcd=bcd>>4;
	high=bcd;
	dec=(high*10)+low;
	return dec;
//	return ((bcd>>4)*10)+(bcd & 0x0f);
}
void print_lcd_bcd(uint8_t bcd)
{
	LCD_Print_Data((bcd>>4)+0x30);
	LCD_Print_Data((bcd & 0x0f)+0x30);
}
void print_lcd_dec(uint8_t dec)
{
	uint8_t ones,tens;
	//uint8_t hund;
	ones=dec%10;//a=123,ones=3
	dec=dec/10;//a=12
	tens=dec%10;//a=12,tens=2
	dec=dec/10;//a=1;
//	hund=dec%10;
//	LCD_Print_Data(hund+0x30);
	LCD_Print_Data(tens+0x30);
	LCD_Print_Data(ones+0x30);
}
void check_RTC(void)
{
  uint8_t seconds;
  HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x00,I2C_MEMADD_SIZE_8BIT,&seconds,1,100);
  if((seconds & 0x80 )==0x80)
  {
	  LCD_Send_Command(0x80);
	  Print_LCD_String((uint8_t *)"Date:");
  }
  else
  {
	  seconds=(seconds|0x80);
	  HAL_I2C_Mem_Write(&hi2c1,MCP7940M_ADDRESS,0x00,I2C_MEMADD_SIZE_8BIT,&seconds,1,100);
	  HAL_Delay(100);
	  LCD_Send_Command(0x80);
	  Print_LCD_String((uint8_t *)"clock started");
	  HAL_Delay(1000);
  }
}
void check_weekday_rtc(void)
{
	uint8_t weekdays;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x03,I2C_MEMADD_SIZE_8BIT,&weekdays,1,100);
	if((weekdays & 0x20)==0x20)
	{
		LCD_Send_Command(0x80);
	    Print_LCD_String((uint8_t *)"weekdays ok");
	}
	else if((weekdays & 0x20)!=0x20)
	{
		weekdays=(weekdays|0x20);
		HAL_I2C_Mem_Write(&hi2c1,MCP7940M_ADDRESS,0x03,I2C_MEMADD_SIZE_8BIT,&weekdays,1,100);
		LCD_Send_Command(0x80);
	    Print_LCD_String((uint8_t *)"started wk clk");
	    HAL_Delay(1000);
	}
}
void Manual_Time_Update(void)
{
    sec++;
    //resettuing sec
    if (sec >= 60)
    {
        sec = 0;
        min++;
    }
   // min++;
    if (min >= 60)
    {
    	min = 0;
		hour++;
    }
    if(hour>=24)
    {
    	hour=0;
    }
    LCD_Send_Command(0x80);
    Print_LCD_String((uint8_t *)"TIME: ");
    LCD_Send_Command(0xc0);
    print_lcd_dec(hour);
    LCD_Print_Data(':');
    print_lcd_dec(min);
    LCD_Print_Data(':');
    //LCD_Send_Command(0xc2);
//   LCD_Send_Command(0xc7);
    print_lcd_dec(sec);
	if(hour<12)
	{
	  LCD_Send_Command(0x80|0x49);
	  Print_LCD_String((uint8_t *)"AM");
	}
	else
	{
	  LCD_Send_Command(0x80|0x49);
	  Print_LCD_String((uint8_t *)"PM");
	}
}
void Read_Seconds()
{
	uint8_t seconds_2;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x00,I2C_MEMADD_SIZE_8BIT,&seconds_2,1,100);
	seconds_2=seconds_2 & 0x7f;
	sec=BCDToDec(seconds_2);
	LCD_Send_Command(0x80|0x46);
	print_lcd_dec(sec);
}
void Read_minutes()
{
	uint8_t min_seg=0;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x01,I2C_MEMADD_SIZE_8BIT,&min_seg,1,100);
	min_seg=min_seg & 0x7f;
	min=BCDToDec(min_seg);
	//key_action();
	LCD_Send_Command(0x80|0x43);
	//LCD_Print_Data(keypressed);
	print_lcd_dec(min);
	LCD_Print_Data(':');
}
void Read_hour()
{
	uint8_t hour_seg=0;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x02,I2C_MEMADD_SIZE_8BIT,&hour_seg,1,100);
	if((hour_seg & 0x40) == 0x40)//bit5<-pm<-1
	{
		LCD_Send_Command(0x80|0x49);
		Print_LCD_String((uint8_t *)"PM");
	}
	else //bit5<-am<-0
	{
		LCD_Send_Command(0x80|0x49);
		Print_LCD_String((uint8_t *)"AM");
	}
	hour_seg=hour_seg & 0x1f;
	hour=BCDToDec(hour_seg);
	LCD_Send_Command(0xc0);
	print_lcd_dec(hour);
	LCD_Print_Data(':');
}
void Read_weekday()
{
	uint8_t week_seg=0;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x03,I2C_MEMADD_SIZE_8BIT,&week_seg,1,100);
	week_seg=week_seg & 0x07;//keeps only weekdays bit 0-2
	//week_seg=week_seg|0x20;
	if(week_seg==0x01)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"MON");
	}
	else if(week_seg==0x02)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"TUE");
	}
	else if(week_seg==0x03)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"WED");
	}
	else if(week_seg==0x04)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"THU");
	}
	else if(week_seg==0x05)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"FRI");
	}
	else if(week_seg==0x06)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"SAT");
	}
	else if(week_seg==0x07)
	{
		LCD_Send_Command(0x80|0x4d);
		Print_LCD_String((uint8_t *)"SUN");
	}
	weekday=BCDToDec(week_seg);
	//LCD_Send_Command(0xc0);
	print_lcd_dec(weekday);
}
void Read_date()
{
	uint8_t date_seg=0;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x04,I2C_MEMADD_SIZE_8BIT,&date_seg,1,100);
	date_seg=date_seg & 0x3f;
	date=BCDToDec(date_seg);
	LCD_Send_Command(0x80|0x05);
	print_lcd_dec(date);
	LCD_Print_Data(':');
}
void Read_month()
{
	uint8_t month_seg=0;

	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x05,I2C_MEMADD_SIZE_8BIT,&month_seg,1,100);
	if(month_seg & 0x20)//bit5<-leap year<-0             checking if ith bit set or not
	{
		LCD_Send_Command(0x80|0x0e);
		Print_LCD_String((uint8_t *)"leap");
	}

	else //bit5<-not a leap year<-1
	{
		LCD_Send_Command(0x80|0x0e);
		Print_LCD_String((uint8_t *)"norm");
	}
	month_seg= month_seg & 0x1f;//removing bit5=1<-leap year
	month=BCDToDec(month_seg);
	LCD_Send_Command(0x80|0x08);
	print_lcd_dec(month);
	LCD_Print_Data(':');
}
void Set_year(void)
{
    uint8_t year_seg = decToBCD(25);  //  2025
    HAL_I2C_Mem_Write(&hi2c1, MCP7940M_ADDRESS, 0x06,I2C_MEMADD_SIZE_8BIT, &year_seg, 1, 100);
}
void Set_month(void)
{
    uint8_t month_seg = decToBCD(11);  //  11
    month_seg=month_seg&0x1f; //removing bit5=1<-leap year
    HAL_I2C_Mem_Write(&hi2c1, MCP7940M_ADDRESS, 0x05,I2C_MEMADD_SIZE_8BIT, &month_seg, 1, 100);
}
void Set_date(void)
{
    uint8_t date_seg = decToBCD(12);  //
    date_seg=date_seg & 0x3f;
    HAL_I2C_Mem_Write(&hi2c1, MCP7940M_ADDRESS, 0x04,I2C_MEMADD_SIZE_8BIT, &date_seg, 1, 100);
}
void Set_weekday(void)
{
	uint8_t week_seg=decToBCD(3);
	week_seg=week_seg & 0x07;
	week_seg=week_seg|0x20;
	HAL_I2C_Mem_Write(&hi2c1,MCP7940M_ADDRESS,0x03,I2C_MEMADD_SIZE_8BIT,&week_seg,1,100);
}
void Read_year()
{
	uint8_t year_seg=0;
	HAL_I2C_Mem_Read(&hi2c1,MCP7940M_ADDRESS,0x06,I2C_MEMADD_SIZE_8BIT,&year_seg,1,100);
	year_seg=year_seg & 0xff;
	year=BCDToDec(year_seg);
	LCD_Send_Command(0x80|0x0b);
	print_lcd_dec(year);
}
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
uint8_t RTC_Buffer[22];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */
  LCD_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
//  check_RTC();
//  Read_Seconds();
//  LCD_Send_Command(0x80);
//  Print_LCD_String((uint8_t *)"seconds:");
  check_RTC();
 // check_weekday_rtc();
  Set_year();
  Set_month();
  Set_date();
  Set_weekday();
  while (1)
  {
	  HAL_Delay(1000);
	  key_action();
	  keycheck();
	  Read_year();
	  Read_month();
	  Read_date();
	  Read_weekday();
	  Read_hour();
	  Read_minutes();
	  Read_Seconds();
	  key_action();
	}
  }
    //HAL_Delay(1000);
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.Timing = 0x00201D2B;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Analogue filter
  */
  if (HAL_I2CEx_ConfigAnalogFilter(&hi2c1, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure Digital filter
  */
  if (HAL_I2CEx_ConfigDigitalFilter(&hi2c1, 0) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(KEY4_R4_GPIO_Port, KEY4_R4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_D7_14_Pin|LCD_D6_13_Pin|LCD_D5_12_Pin|LCD_D4_11_Pin
                          |LCD_D3_10_Pin|LCD_D2_9_Pin|LCD_D1_8_Pin|KEY1_R1_Pin
                          |KEY2_R2_Pin|KEY3_R3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LCD_D0_7_Pin|LCD_EN_6_Pin|LCD_RW_5_Pin|LCD_RS_4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : KEY4_R4_Pin */
  GPIO_InitStruct.Pin = KEY4_R4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(KEY4_R4_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY5_C1_Pin KEY6_C2_Pin */
  GPIO_InitStruct.Pin = KEY5_C1_Pin|KEY6_C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : KEY7_C3_Pin KEY8_C4_Pin */
  GPIO_InitStruct.Pin = KEY7_C3_Pin|KEY8_C4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D7_14_Pin LCD_D6_13_Pin LCD_D5_12_Pin LCD_D4_11_Pin
                           LCD_D3_10_Pin LCD_D2_9_Pin LCD_D1_8_Pin KEY1_R1_Pin
                           KEY2_R2_Pin KEY3_R3_Pin */
  GPIO_InitStruct.Pin = LCD_D7_14_Pin|LCD_D6_13_Pin|LCD_D5_12_Pin|LCD_D4_11_Pin
                          |LCD_D3_10_Pin|LCD_D2_9_Pin|LCD_D1_8_Pin|KEY1_R1_Pin
                          |KEY2_R2_Pin|KEY3_R3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_D0_7_Pin LCD_EN_6_Pin LCD_RW_5_Pin LCD_RS_4_Pin */
  GPIO_InitStruct.Pin = LCD_D0_7_Pin|LCD_EN_6_Pin|LCD_RW_5_Pin|LCD_RS_4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
}
  /* USER CODE END Error_Handler_Debug */
//}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
