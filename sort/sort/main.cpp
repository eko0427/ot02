/* ------------------------------------------------------------------------- */
/* main.c																	 */
/* OT2B																		 */
/* �ۑ�\�[�X�t�@�C��								 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	�ԍ�	�X�V���e								�X�V��		���O		 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬								2018/05/08	���c�@�j��	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* include�t�@�C��															 */
/* ------------------------------------------------------------------------- */
#define _CRT_SECURE_NO_DEPRECATE
#include<windows.h>								/* �n�r�@�\�֘A				 */
#include<stdio.h>								/* �W���h�^�n				 */
#include<stdlib.h>

/* ------------------------------------------------------------------------- */
/* �萔��`																	 */
/* ------------------------------------------------------------------------- */
#define SIZE 101

/* ------------------------------------------------------------------------- */
/* typedef�錾																 */
/* ------------------------------------------------------------------------- */
typedef char		   SCHR;
typedef unsigned char  UCHR;
typedef short		   SSHT;
typedef unsigned short USHT;
typedef long		   SLNG;
typedef unsigned long  ULNG;
typedef int			   SINT;
typedef unsigned int   UINT;
typedef float		   FLOT;
typedef double		   DBLE;

/* ------------------------------------------------------------------------- */
/* �\���̒�`																 */
/* ------------------------------------------------------------------------- */
struct Address {
	SCHR Number[4];
	SCHR Name[15];
	SCHR LastName[11];
	SCHR FirstName[15];
	SCHR Gender[2];
	SCHR BloodType[2];
	SCHR Birthday[11];
	SCHR PhoneNumber[14];
	SCHR MobilePhone[14];
	SCHR MailAddress[39];
	SCHR PostalCode[9];
	SCHR Address1[101];
	SCHR Address2[71];
};

/* ------------------------------------------------------------------------- */
/* �v���g�^�C�v�錾															 */
/* ------------------------------------------------------------------------- */
void quicksort(struct Address *, int left, int right);

/* ------------------------------------------------------------------------- */
/* �֐���	: main			 												 */
/* �@�\��	: �G���g���[�|�C���g											 */
/* �@�\�T�v	: ���Ԍv���������܂��B											 */
/* �쐬��	: 2018/05/08		���c  �j��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
	DWORD dwStartTime = 0;
	DWORD dwEndTime = 0;

	FILE *fp;
	SINT LoopCnt;
	SCHR file_name[256],buf[256],buf2[256];
	
	Address AddrBook[SIZE];
	Address *p = AddrBook;

	sprintf(file_name, "%s\\Desktop\\ot\\ot02\\AddrBook.csv", getenv("USERPROFILE"));

	fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("Not open %s\n",file_name);
	}
	
	fgets(buf2, 256, fp);

	for (LoopCnt = 1; LoopCnt < SIZE; LoopCnt++) {
		fgets(buf, 256, fp);
		sscanf(buf, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%s",
			AddrBook[LoopCnt].Number,
			AddrBook[LoopCnt].Name,
			AddrBook[LoopCnt].LastName,
			AddrBook[LoopCnt].FirstName,
			AddrBook[LoopCnt].Gender,
			AddrBook[LoopCnt].BloodType,
			AddrBook[LoopCnt].Birthday,
			AddrBook[LoopCnt].PhoneNumber,
			AddrBook[LoopCnt].MobilePhone,
			AddrBook[LoopCnt].MailAddress,
			AddrBook[LoopCnt].PostalCode,
			AddrBook[LoopCnt].Address1,
			AddrBook[LoopCnt].Address2);
	}
	fclose(fp);

	/* �V�X�e���N�����Ԃ��擾 */
	dwStartTime = GetTickCount();

	/* ��������������������������������������������������������������������  */

	quicksort(p, 1, SIZE - 1);					/* �\�[�g�֐��̌Ăяo��		 */

	/* ���Ƀt�@�C�������݂��Ă��邩�m�F���đ��݂����ꍇ�����̐��l�𑝂₷	 */
	/* �Ȃ�������V�K�쐬													 */
	for (LoopCnt = 1; (fp = fopen(file_name, "r")) != NULL; LoopCnt++) {
		if (LoopCnt >= 100) {
			fclose(fp);
			return -1;
		}
		fclose(fp);
		sprintf(file_name, "%s\\Desktop\\ot\\ot02\\AddrBook%d.csv", getenv("USERPROFILE"), LoopCnt);
	}
	
	/* csv�t�@�C���Ƃ��ďo��												 */
	fp = fopen(file_name, "w");
	fprintf(fp, "%s", buf2);
	for (LoopCnt = 1; LoopCnt < SIZE; LoopCnt++) {
		fprintf(fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
			LoopCnt,
			AddrBook[LoopCnt].Name,
			AddrBook[LoopCnt].LastName,
			AddrBook[LoopCnt].FirstName,
			AddrBook[LoopCnt].Gender,
			AddrBook[LoopCnt].BloodType,
			AddrBook[LoopCnt].Birthday,
			AddrBook[LoopCnt].PhoneNumber,
			AddrBook[LoopCnt].MobilePhone,
			AddrBook[LoopCnt].MailAddress,
			AddrBook[LoopCnt].PostalCode,
			AddrBook[LoopCnt].Address1,
			AddrBook[LoopCnt].Address2);
	}
	fclose(fp);

	/* ��������������������������������������������������������������������  */

	/* �V�X�e���N�����Ԃ��擾 */
	dwEndTime = GetTickCount();

	/* �����O�ƌ�����̎��Ԃ������A�����ɂ����������Ԃ�\�� */
	printf("%d�~���b������܂����I", (dwEndTime - dwStartTime));




	system("pause");
	return 0;
}

/* ------------------------------------------------------------------------- */
/* �֐���	: quicksort			 											 */
/* �@�\��	: �N�C�b�N�\�[�g												 */
/* �@�\�T�v	: �N�C�b�N�\�[�g�����Ēl��Ԃ��܂�								 */
/* �쐬��	: 2018/05/12		���c  �j��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void quicksort(struct Address *p, int left, int right)
{
	int LoopCnt, last;

	if (left >= right)
		return;

	last = left;
	for (LoopCnt = left+1; LoopCnt <= right; LoopCnt++) {
		if (strcmp(p[LoopCnt].BloodType , p[left].BloodType) < 0) {
			last++;
			p[0] = p[last];
			p[last] = p[LoopCnt];
			p[LoopCnt] = p[0];
		}
	}
	p[0] = p[left];
	p[left] = p[last];
	p[last] = p[0];

	quicksort(p, left, last - 1);
	quicksort(p, last + 1, right);
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */