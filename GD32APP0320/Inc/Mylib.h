#ifndef __MYLIB_H
#define __MYLIB_H
#include <stdio.h>
#include<string.h>
#include "gd32f1x0.h"

//ɾ������һ���ַ����г��ֵ��ַ�
/*****************************************************************************
 * Function      : DeleteChars
 * Description   : ɾ������һ���ַ����г��ֵ��ַ�
 * Input         : char *str1   Դ�ַ���
                   char *str2   ��Ҫɾ�����ַ�
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
 * Description   : ��ȡ����
 * Input         : char *data   ���ŵ�����  
                 char *account  ����
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
