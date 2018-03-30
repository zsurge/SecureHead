#ifndef _INI_H_
#define _INI_H_

#include "dev_eprom.h"	

//���������ַ
#define PARAM_START_ADD 0x800FC00

#define UPGRADE 1
#define NOTUPGRADE 2
#define READSUCESS 3
#define READFALSE 4
#define WRITESUCESS 5
#define WRITEFALSE 6



//#pragma pack(1)
typedef struct
{
 unsigned char UpgradeFlag[4];
}T_MagCardParam;

//#pragma pack()

extern T_MagCardParam gMagCardParam;				//������־λ

char ReadUpgradeFlag(void);
void WriteUpgradeFlag(void);
void WriteUpgradeCompleFlag(void);
void ClearMagCardParam(void);

#endif

