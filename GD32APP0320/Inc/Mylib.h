#ifndef __MYLIB_H
#define __MYLIB_H
#include <stdio.h>
#include<string.h>
#include "gd32f1x0.h"

//删除在另一个字符串中出现的字符
/*****************************************************************************
 * Function      : DeleteChars
 * Description   : 删除在另一个字符串中出现的字符
 * Input         : char *str1   源字符串
                   char *str2   需要删除的字符
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180323
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void DeleteChars(char *str1,char *str2);


/*****************************************************************************
 * Function      : GetAccount
 * Description   : 获取卡号
 * Input         : char *data   二磁道数据  
                 char *account  卡号
 * Output        : None
 * Return        : 
 * Others        : 
 * Record
 * 1.Date        : 20180323
 *   Author      : surge
 *   Modification: Created function

*****************************************************************************/
void GetAccount(char *data,char *account);
#endif
