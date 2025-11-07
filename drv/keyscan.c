 /* ---------------------------------------------------------------
** File name:		keyscan.c
** Brief:
** COPYRIGHT(C) ZXW 2020
** ---------------------------------------------------------------
*/

/* Includes -----------------------------------------------------*/
#include "type.h"
#include "sys.h"
#include "int.h"
#include "gpio.h"
#include "keyscan.h"
#include "uart.h"


/* Macro --------------------------------------------------------*/

const uint8_t KEY_TABLE_AREA3[55] = {
	10,  9,  8,  7,  6,  5,  4,  3,  2, 1,
	19, 18, 17, 16, 15, 14, 13, 12, 11,
	27, 26, 25, 24, 23, 22, 21, 20,
	34, 33, 32, 31, 30, 29, 28,
	40, 39, 38, 37, 36, 35,
	45, 44, 43, 42, 41,
	49, 48, 47, 46,
	52, 51, 50, 
	54, 53,
	55
};

/* Global Variables ---------------------------------------------*/
#ifdef MODULE_TEST
volatile uint32_t keyH = 0, keyL = 0;
volatile uint8_t area = 0;
volatile uint8_t key_scan_num = 0;

#endif

/* Extern -------------------------------------------------------*/
/* Functions ----------------------------------------------------*/

/** 
 * @brief Clear keyscan interrupt
 */ 
void keyscan_clear_int(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KSCAN_CTRL_REG);
	reg_temp &= ~KEYSCAN_KSCAN_INT_CLEAR_MASK;
	reg_temp |= 1 << KEYSCAN_KSCAN_INT_CLEAR_SHIFT;
	write_reg(KEYSCAN_KSCAN_CTRL_REG, KEYSCAN_KSCAN_INT_CLEAR_MASK);
}

/** 
 * @brief Start keyscan hardware module
 */ 
void keyscan_start(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KSCAN_CTRL_REG);
	reg_temp &= ~KEYSCAN_KSCAN_START_MASK;
	reg_temp |= 1 << KEYSCAN_KSCAN_START_SHIFT;
	write_reg(KEYSCAN_KSCAN_CTRL_REG, KEYSCAN_KSCAN_START_MASK);
}

/** 
 * @brief Enable keyscan interrupt
 */ 
void keyscan_int_enable(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KSCAN_INT_CFG_REG);
	reg_temp &= ~KEYSCAN_KSCAN_INT_ENABLE_MASK;
	reg_temp |= 0x1 << KEYSCAN_KSCAN_INT_ENABLE_SHIFT;
	write_reg(KEYSCAN_KSCAN_INT_CFG_REG, reg_temp);
}

/** 
 * @brief Disable keyscan interrupt
 */
void keyscan_int_disable(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KSCAN_INT_CFG_REG);
	reg_temp &= ~KEYSCAN_KSCAN_INT_ENABLE_MASK;
	write_reg(KEYSCAN_KSCAN_INT_CFG_REG, reg_temp);
}

/** 
 * @brief Enable keyscan hardware module
 */
void keyscan_enable(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_MODULE_MODE_REG);
	reg_temp &= ~KEYSCAN_KEY_SCAN_EN_MASK;
	reg_temp |= 0x1 << KEYSCAN_KEY_SCAN_EN_SHIFT;
	write_reg(KEYSCAN_MODULE_MODE_REG, reg_temp);
}

/** 
 * @brief Disable keyscan hardware module
 */
void keyscan_disable(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_MODULE_MODE_REG);
	reg_temp &= ~KEYSCAN_KEY_SCAN_EN_MASK;
	write_reg(KEYSCAN_MODULE_MODE_REG, reg_temp);
}

/** 
 * @brief Set keyscan period to be or not to be synchronized
 * @details The period will be widen to make it synchronized
 * @param[in] keyscan_area_scan_t  a bool value 1: enable pwiden 0:disable pwiden
 */
void keyscan_set_pwiden(keyscan_area_scan_t pwiden)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KEY_SCAN_CFG_REG);
	reg_temp &= ~KEYSCAN_KEY_PWIDEN_MASK;
	reg_temp |= pwiden << KEYSCAN_KEY_PWIDEN_SHIFT;
	write_reg(KEYSCAN_KEY_SCAN_CFG_REG, reg_temp);
}

/** 
 * @brief Set keyscan areas
 * @details Up to 3 areas are available 
 * @param[in] area  area[0]:A1  area[1]:A2  area[2]:A3
 */
void keyscan_set_area(uint8_t area)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KEY_SCAN_CFG_REG);
	reg_temp &= ~KEYSCAN_KSCAN_MODE_MASK;
	reg_temp |= area << KEYSCAN_KSCAN_MODE_SHIFT;
	write_reg(KEYSCAN_KEY_SCAN_CFG_REG, reg_temp);
}

/** 
 * @brief Set keyscan polarity - scan level of A3
 * @param[in] pol 1:high level 0:low level
 */
void keyscan_set_pol(uint8_t pol)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KEY_SCAN_CFG_REG);
	reg_temp &= ~KEYSCAN_KSCAN_IO_POL_MASK;
	reg_temp |= pol << KEYSCAN_KSCAN_IO_POL_SHIFT;
	write_reg(KEYSCAN_KEY_SCAN_CFG_REG, reg_temp);
}

/** 
 * @brief Set keyscan frequency 
 * @param[in] keyscan_frquency_t 0:32k  1:16k  2:8k  3:4k
 */
void keyscan_set_freq(keyscan_frquency_t freq)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KEY_SCAN_CFG_REG);
	reg_temp &= ~KEYSCAN_KSCAN_FREQ_MASK;
	reg_temp |= freq << KEYSCAN_KSCAN_FREQ_SHIFT;
	write_reg(KEYSCAN_KEY_SCAN_CFG_REG, reg_temp);
}

/** 
 * @brief Set keyscan cycle
 * @details Actually the scan cycles are twice the input parameter except when scan_cycle = 0.
 * 			If scan_cycle = 3,keyscan hardware module needs to sweep 6 times to get a available key value.
 * @param[in] scan_cycle 0:1 cycle  x(x>0): 2*x cycles
 */
void keyscan_set_cycle(uint8_t scan_cycle)
{
    write_reg(KEYSCAN_KEY_SCAN_CYCLE_REG, scan_cycle);
}

/** 
 * @brief Read out the area of ​​the key value just generated
 * @return reg_temp  0:null 1:A1  2:A2  4:A3
 */
uint8_t keyscan_read_kscan_area(void)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KEYSCAN_STATE_REG);
	reg_temp &= KEYSCAN_KSCAN_AREA_MASK;
	reg_temp = reg_temp >> KEYSCAN_KSCAN_AREA_SHIFT;
	return (uint8_t)reg_temp;
}

/** 
 * @brief Select the IO to participate in the keyscan module
 * @param[in] reg_bits reg_bits[10:0]:  GPIO10,GPIO9...GPIO0
 */
void keyscan_set_io_valid(uint16_t reg_bits)
{
	uint32_t reg_temp = read_reg(KEYSCAN_KSCAN_IO_VALID_H_REG);
	reg_temp &= ~KEYSCAN_KSCAN_IO_VALID_H_MASK;
	reg_temp |= (reg_bits & (KEYSCAN_KSCAN_IO_VALID_H_MASK<<8))>>8;
	write_reg(KEYSCAN_KSCAN_IO_VALID_H_REG, reg_temp);
	
	reg_temp = read_reg(KEYSCAN_KSCAN_IO_VALID_L_REG);
	reg_temp &= ~KEYSCAN_KSCAN_IO_VALID_L_MASK;
	reg_temp |= reg_bits & KEYSCAN_KSCAN_IO_VALID_L_MASK;
	write_reg(KEYSCAN_KSCAN_IO_VALID_L_REG, reg_temp);
}

/** 
 * @brief Set function for the IO participating in the keyscan module
 * @param[in] reg_bits reg_bits[10:0]:  GPIO10,GPIO9...GPIO0
 */
void keyscan_io_set(uint32_t gpio_bits)
{
	uint8_t i = 0;
	for(i = 0; i<11; i++){
		if(gpio_bits&(BIT0<<i)) sys_set_port_mux(PAD_GPIO_00+0x04*i, PAD_MUX_FUNCTION_2|2);
	}
}



void keyscan_io_set_before_sleep(uint32_t gpio_bits){
	uint8_t i = 0;
	for(i = 0; i<10; i++){
		if(gpio_bits&(BIT0<<i)) sys_set_port_mux(PAD_GPIO_00+0x04*i, PAD_MUX_FUNCTION_2|2); //keypad IO func2
		else        sys_set_port_mux(PAD_GPIO_00+0x04*i, PAD_MUX_FUNCTION_0|1);     //not used IO func0|1       
	}
	if(gpio_bits&BIT10) sys_set_port_mux(PAD_GPIO_10, PAD_MUX_FUNCTION_7);
	write_reg(0X40120194, 11); //select debug_io_group
	write_reg(0X40020078, 22); //select debug_io_func  22: all 0  21:all 1
}

void keyscan_pwr_ctrl_enable(void)
{
    uint8_t reg_val =read_reg(KEYSCAN_BASE_ADDR);

    reg_val &= ~KEYSCAN_KEY_SCAN_PWR_CTRL_EN_MASK;
    reg_val |= 1<<KEYSCAN_KEY_SCAN_PWR_CTRL_EN_SHIFT;

    write_reg(KEYSCAN_BASE_ADDR, reg_val);
}

void keyscan_pwr_ctrl_disable(void)
{
    uint8_t reg_val =read_reg(KEYSCAN_BASE_ADDR);

    reg_val &= ~KEYSCAN_KEY_SCAN_PWR_CTRL_EN_MASK;

    write_reg(KEYSCAN_BASE_ADDR, reg_val);
}


void get_keyscan_value(uint32_t *key_high,uint32_t *key_low)
{
    *key_high |= read_reg(KEYSCAN_KSCAN_VAL6_REG) << 16;
    *key_high |= read_reg(KEYSCAN_KSCAN_VAL5_REG) << 8;
    *key_high |= read_reg(KEYSCAN_KSCAN_VAL4_REG);
    *key_low |= read_reg(KEYSCAN_KSCAN_VAL3_REG) << 24;
    *key_low |= read_reg(KEYSCAN_KSCAN_VAL2_REG) << 16;
    *key_low |= read_reg(KEYSCAN_KSCAN_VAL1_REG) << 8;
    *key_low |= read_reg(KEYSCAN_KSCAN_VAL0_REG);
}


/*****************************************************************************************
 * @function get keyscan key sequence number
 *
 * @param[out] key sequence number    
 * @param
 * @param
 * @param
 *****************************************************************************************/

uint8_t get_keyscan_key_number(void){
    uint32_t tmp_key_value_high =0;
    uint32_t tmp_key_value_low =0;
    uint8_t i=0;
    uint8_t key_number =0;
    uint8_t tmp_area = keyscan_read_kscan_area();
	static uint8_t keys_buffer[3] = {0,0,0}, p_buffer = 0,from_wakeup_call_cnt = 0;
	from_wakeup_call_cnt++;
    get_keyscan_value(&tmp_key_value_high,&tmp_key_value_low);
    switch (tmp_area)
    {
        case 1:
        {
            for (i = 0; i < 11; i++)
            {
               if((tmp_key_value_low >> i)&0x01)
               {
                   key_number = 66-i;
               }
            }
            break;
        }
        case 2:
        {
            for (i = 0; i < 11; i++)
            {
               if((tmp_key_value_low >> i)&0x01)
               {
                    key_number = 77-i;
               }
            }
            break;
        }
        case 3:
        {
            for (i = 0; i < 55; i++)
            {
                if(i < 32)
                {
                   if((tmp_key_value_low >> i)&0x01)
                   {
                        key_number =  KEY_TABLE_AREA3[i];
                   }
                }
                else
                {
                    if((tmp_key_value_high >> (i-32))&0x01)
                    {
                        key_number =  KEY_TABLE_AREA3[i];
                    }
                }
            }
            break;
        }                      
    }

	keys_buffer[p_buffer] = key_number;
	p_buffer = ++p_buffer%3;
	if((keys_buffer[0] == keys_buffer[1])&&(keys_buffer[1] == keys_buffer[2])){
    	return keys_buffer[0];
	}
	else{
		if(from_wakeup_call_cnt < 3){
			return keys_buffer[from_wakeup_call_cnt-1];
		}
		else return 0;
	}
}


/*****************************************************************************************
 * @function init keyscan
 *
 * @param[in] reg_bits     	enabled keyscan io bits
 * @param[in] area      	set the key scan area, which can be set to KEYSCAN_AREA1/KEYSCAN_AREA2/KEYSCAN_AREA3
 * @param[in] scan_level 	keyscan level,hight/low,0x01:high;0x00:low
 * @param[in] scan_cycle   	keyscan cycle ,cannot be set to zero
 *****************************************************************************************/
void keyscan_init(uint32_t reg_bits,keyscan_area_t area,uint8_t scan_level,uint8_t scan_cycle)
{
    keyscan_io_set(reg_bits);
    keyscan_set_pwiden(KEYSCAN_EQUILONG);
    keyscan_set_pol(scan_level);
    keyscan_set_freq(KEYSCAN_FRQ_4K);
    keyscan_set_io_valid(reg_bits);
    keyscan_set_area(area);
    keyscan_set_cycle(scan_cycle);
    keyscan_enable();
    keyscan_pwr_ctrl_enable();
    int_enable_irq( INT_KSCAN_EN_MASK );
    keyscan_int_enable();
    keyscan_start();

}

volatile uint8_t key_valid_flag = 0;
uint8_t key_numbers[2] = {0};
void get_keyscan_keys_number(){

    uint32_t key_value_high =0;
    uint32_t key_value_low =0;
	uint8_t high_num_1_count = 0;
	uint8_t low_num_1_count = 0;
	uint8_t key_offset_low  = 0;
	uint8_t key_offset_high = 0;

	static uint32_t pro_key_value_high  = 0;
	static uint32_t pro_key_value_low = 0; 
    uint8_t i=0;
	static uint8_t key_buffer1[3] = {0};
	static uint8_t p_buffer1 = 0;
	static uint8_t key_buffer2[3] = {0};
	static uint8_t p_buffer2 = 0;

    uint8_t tmp_area = keyscan_read_kscan_area();
    get_keyscan_value(&key_value_high,&key_value_low);
	//print("%x,%x\n",key_value_high,key_value_low);
	for(uint8_t i = 0 ;i < 24; i++)
	{
		if((key_value_high >> i)&0x01)
		{
			high_num_1_count++;
		}
	}
	for(uint8_t i = 0 ;i < 32; i++)
	{
		if((key_value_low >> i)&0x01)
		{
			low_num_1_count++;
		}
	}
	
 	/*one key is pressed*/
	if(high_num_1_count + low_num_1_count  == 1)
	{
	 	switch (tmp_area)
		{
			case 1:
			{
	
				for (i = 0; i < 11; i++)
				{
					  if((key_value_low >> i)&0x01)
					  {
						  key_numbers[0] = 66-i;
					  }
				 }
				break;
	
			}
			case 2:
		   {
	
				 for (i = 0; i < 11; i++)
				{
				   if((key_value_low >> i)&0x01)
				   {
						key_numbers[0] = 77-i;
				   }
				}
				break;
			}
			case 3:
			{
				
				 for (i = 0; i < 55; i++)
				{
					if(i < 32)
					{
					   if((key_value_low >> i)&0x01)
					   {
							key_numbers[0] =  KEY_TABLE_AREA3[i];
					   }
					}
					else
					{
						if((key_value_high >> (i-32))&0x01)
						{
							key_numbers[0] =  KEY_TABLE_AREA3[i];
						}
					}
				}
				break;
			}	
			
		}
		key_buffer1[p_buffer1] = key_numbers[0];
		p_buffer1 = ++p_buffer1%3;
		if((key_buffer1[0] == key_buffer1[1]&&key_buffer1[1] == key_buffer1[2]))
		{
			key_valid_flag = 1;				
		}
		
	}
	/*two keys are pressed and in area3*/
	else if(high_num_1_count + low_num_1_count  == 2 && tmp_area == 3)
	{
				
		for (i = 0; i < 55; i++)
        {
            if(i < 32)
            {
            	/*key_value_low have two "1"*/
            	if(low_num_1_count > 1)
            	{
            		
            		if(((key_value_low >> i)&0x01) && (key_offset_low < low_num_1_count))
                	{
                    	key_numbers[key_offset_low] =  KEY_TABLE_AREA3[i];
						key_offset_low++;
                	}
            	}
				/*key_value_low have one "1"*/
				else if(((key_value_low >> i))&0x01 && (low_num_1_count == 1))
				{
					key_numbers[0] =  KEY_TABLE_AREA3[i];
				}	
            }
            else
            {
            	/*key_value_high have two "1"*/
            	if(high_num_1_count > 1)
            	{
					if(((key_value_high >> (i-32)))&0x01 &&( key_offset_high < high_num_1_count))
                	{
                    	key_numbers[key_offset_high] =  KEY_TABLE_AREA3[i];
						key_offset_high++;
                	}
            	}
				/*key_value_high have one "1"*/
				else if(((key_value_high >> (i-32))&0x01) && (high_num_1_count == 1))
				{
					key_numbers[1] =  KEY_TABLE_AREA3[i];
				}
                
            }
        }
		key_buffer1[p_buffer1] = key_numbers[0];
		p_buffer1 = ++p_buffer1%3;
		key_buffer2[p_buffer2] = key_numbers[1];
		p_buffer2 = ++p_buffer2%3;

		if((key_buffer1[0] == key_buffer1[1]&&key_buffer1[1] == key_buffer1[2])
			&&(key_buffer2[0] == key_buffer2[1]&&key_buffer2[1] == key_buffer2[2]))
		{

			if(pro_key_value_high == key_value_high&&pro_key_value_low == key_value_low)
			{
				key_valid_flag = 2;
			}
		}
	pro_key_value_high = key_value_high;
	pro_key_value_low = key_value_low;
	}
	/*Invalid keys*/
	else
	{
		key_valid_flag = 3;							
	}
}


ATTRIBUTE_ISR ATTRIBUTE_WEAK void kscan_isr()
{
#ifdef MODULE_TEST
	get_keyscan_keys_number();
	keyscan_clear_int();
	keyscan_start();
#endif

}


