#ifndef __OLED_H
#define __OLED_H

void OLED_Init(void);   // 初始化
void OLED_Clear(void);	// 清屏
void OLED_ShowChar(uint8_t Line, uint8_t Column, char Char);	// 显示一个字符
void OLED_ShowString(uint8_t Line, uint8_t Column, char *String);	// 显示一个字符串
void OLED_ShowNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length); // 显示无符号十进制数
void OLED_ShowSignedNum(uint8_t Line, uint8_t Column, int32_t Number, uint8_t Length);   // 显示有符号十进制数
void OLED_ShowHexNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);	// 显示十六进制数字
void OLED_ShowBinNum(uint8_t Line, uint8_t Column, uint32_t Number, uint8_t Length);	// 显示二进制数字

#endif
