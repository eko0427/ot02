/* ------------------------------------------------------------------------- */
/* main.c																	 */
/* OT2B																		 */
/* 課題ソースファイル								 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	番号	更新内容								更新日		名前		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2018/05/08	中田　桂介	 */
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */
/* includeファイル															 */
/* ------------------------------------------------------------------------- */
#define _CRT_SECURE_NO_DEPRECATE
#include<windows.h>								/* ＯＳ機能関連				 */
#include<stdio.h>								/* 標準Ｉ／Ｏ				 */
#include<stdlib.h>

/* ------------------------------------------------------------------------- */
/* 定数定義																	 */
/* ------------------------------------------------------------------------- */
#define SIZE 101

/* ------------------------------------------------------------------------- */
/* typedef宣言																 */
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
/* 構造体定義																 */
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
/* プロトタイプ宣言															 */
/* ------------------------------------------------------------------------- */
void quicksort(struct Address *, int left, int right);

/* ------------------------------------------------------------------------- */
/* 関数名	: main			 												 */
/* 機能名	: エントリーポイント											 */
/* 機能概要	: 時間計測だけします。											 */
/* 作成日	: 2018/05/08		中田  桂介		新規作成					 */
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

	/* システム起動時間を取得 */
	dwStartTime = GetTickCount();

	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */

	quicksort(p, 1, SIZE - 1);					/* ソート関数の呼び出し		 */

	/* 既にファイルが存在しているか確認して存在した場合末尾の数値を増やす	 */
	/* なかったら新規作成													 */
	for (LoopCnt = 1; (fp = fopen(file_name, "r")) != NULL; LoopCnt++) {
		if (LoopCnt >= 100) {
			fclose(fp);
			return -1;
		}
		fclose(fp);
		sprintf(file_name, "%s\\Desktop\\ot\\ot02\\AddrBook%d.csv", getenv("USERPROFILE"), LoopCnt);
	}
	
	/* csvファイルとして出力												 */
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

	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */

	/* システム起動時間を取得 */
	dwEndTime = GetTickCount();

	/* 検索前と検索後の時間を引き、処理にかかった時間を表示 */
	printf("%dミリ秒かかりました！", (dwEndTime - dwStartTime));




	system("pause");
	return 0;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: quicksort			 											 */
/* 機能名	: クイックソート												 */
/* 機能概要	: クイックソートをして値を返します								 */
/* 作成日	: 2018/05/12		中田  桂介		新規作成					 */
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