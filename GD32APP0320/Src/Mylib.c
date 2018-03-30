#include "Mylib.h"

#define MAX 128

void DeleteChars(char *str1,char *str2)
{
	if(str1==NULL || str2==NULL)
		return;

	bool hashtable[MAX];
	memset(hashtable,0,sizeof(hashtable));

	//��str2���ַ���Ӧ��hashtable�����е�λ���ϵ�ֵ��Ϊture
	while(*str2 != '\0')
	{
		//ASCIIֵ��128-255֮��ĵ��ַ���
		//��char���棬ת��Ϊint��,��-128--1֮��
		int index;
		if(*str2 >= 0)
			index = *str2;
		else
			index = *str2 + 256;

		hashtable[index] = 1;
		++str2;
	}

	char *pFast = str1;
	char *pSlow = str1;
	while(*pFast != '\0')
	{
		int index;
		if(*pFast >= 0)
			index = *pFast;
		else
			index = *pFast + 256;

		//�����Ƿ�����Ҫɾ�����ַ���pFast�����ƣ�
		//ֻ��û����Ҫɾ�����ַ�ʱ��pSlow�ź���
		if(!hashtable[index])
			*pSlow++ = *pFast;	
		++pFast;
	}
	*pSlow = '\0';
}

void GetAccount(char *data,char *account)
{
	char *p1,*p2;
	
	p1 = strstr ( (const char *) data, ";");
	p2 = strstr ( (const char *) data, "=");

	if(p1 == NULL || p2 == NULL)
	{
	    return;
	}
	
	
	strncpy (account, (const char *) p1+1, p2-p1-1);

}