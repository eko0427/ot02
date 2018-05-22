/* ------------------------------------------------------------------------- */
/* main.cpp																	 */
/* OT2B																		 */
/* 課題ソースファイル								 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	番号	更新内容								更新日		名前		 */
/* ------------------------------------------------------------------------- */
/* 000000	新規作成								2018/05/08	中田　桂介	 */
/* 000001	関数Strtok作成							2018/05/16	中田　桂介	 */
/* 000002	関数MergeSort作成						2018/05/20	中田　桂介	 */
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
#define SIZE 105000

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
struct AddrBook {
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
void QuickSort(struct AddrBook *, SINT iLeft, SINT iRight);
void MergeSort(struct AddrBook *, struct AddrBook *, SINT iLeft, SINT iRight, SINT, SINT);
SCHR *Strtok(SCHR *cStr, const SCHR cChar);

/* ------------------------------------------------------------------------- */
/* 関数名	: main			 												 */
/* 機能名	: エントリーポイント											 */
/* 機能概要	: csvファイルの読み込み出力、ソートの選択、ソート時間の計測		 */
/* 作成日	: 2018/05/08		中田  桂介		新規作成					 */
/* ------------------------------------------------------------------------- */
int main(int argc, char* argv[])
{
	DWORD dwStartTime = 0;
	DWORD dwEndTime = 0;

	FILE *fPtr;
	SINT iLoopCnt = 0,Cnt = 0;
	SINT iChoice[6];
	SCHR cFileName[256],cBuf[sizeof(AddrBook)],cBuf2[sizeof(AddrBook)];
	SCHR *cTemp;
	AddrBook Book[SIZE];
	AddrBook *cPtr = Book;
	AddrBook temp[SIZE];
	AddrBook *pTemp = temp;

	/* 読み込む構造体分メモリの確保メモリの確保								 */
	cPtr = (AddrBook*)malloc(SIZE * sizeof(AddrBook));
	pTemp = (AddrBook*)malloc(SIZE * sizeof(AddrBook));

	/* 元のcsvファイルの場所を指定											 */
	sprintf(cFileName, "%s\\Desktop\\ot\\ot02\\AddrBook.csv", getenv("USERPROFILE"));

	/* ファイルが開けなかった場合エラー										 */
	fPtr = fopen(cFileName, "r");
	if (fPtr == NULL) {
		printf("Not open %s\n",cFileName);
		return -1;
	}
	printf("Now Loading\n");

	/* 項目名をcBuf2へ格納													 */
	fgets(cBuf2, sizeof(AddrBook), fPtr);
	/* csvファイルから読み込んで構造体へ代入								 */
	for (iLoopCnt = 0; iLoopCnt < SIZE;  iLoopCnt++) {
		fgets(cBuf, sizeof(AddrBook), fPtr);
		cTemp = Strtok(cBuf, ',');				/* Noの分をトークン分割		 */
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].Name, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].LastName, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].FirstName, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].Gender, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].BloodType, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].Birthday, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].PhoneNumber, cTemp);
		/* 中が空欄だった場合\0を代入										*/
		cTemp = Strtok(0, ',');
		if (cTemp != NULL) {
			strcpy(cPtr[iLoopCnt].MobilePhone, cTemp);
		}
		else {
			strcpy(cPtr[iLoopCnt].MobilePhone, "\0");
		}
		cTemp = Strtok(0, ',');
		if (cTemp != NULL) {
			strcpy(cPtr[iLoopCnt].MailAddress, cTemp);
		}
		else {
			strcpy(cPtr[iLoopCnt].MailAddress, "\0");
		}
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].PostalCode, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].Address1, cTemp);
		cTemp = Strtok(0, ',');
		strcpy(cPtr[iLoopCnt].Address2, cTemp);
		//printf("%d\n",iLoopCnt);
	}
	fclose(fPtr);

	/* 既にファイルが存在しているか確認して存在した場合末尾の数値を増やす	 */
	/* なかった場合新規作成													 */
	for (iLoopCnt = 0; (fPtr = fopen(cFileName, "r")) != NULL; iLoopCnt++) {
		if (iLoopCnt >= 100) {
			fclose(fPtr);
			return -1;
		}
		fclose(fPtr);
		sprintf(cFileName, "%s\\Desktop\\ot\\ot02\\AddrBook%02d.csv", getenv("USERPROFILE"), iLoopCnt+1);
	}

	system("cls");

	printf("ソートを行いますキーを選択してください(最大3段階)\n");
	for (Cnt = 0; Cnt < 3; Cnt++) {
		printf("\n|1.氏名　　|2.カナ(苗字)|3.カナ(名前)　　| 4.性別　　| 5.血液型| 6.生年月日  |\n");
		printf("|7.電話番号|8.携帯電話　|9.メールアドレス|10.郵便番号|11.住所　|12.住所(カナ)|\n");
		printf("|END(999)  |\n\n");
		while (1) {
			printf("数値でを入力してください\n >");
			rewind(stdin);
			scanf("%d", &iChoice[Cnt]);
			if (((iChoice[Cnt] > 0) && (iChoice[Cnt] < 13)) || (iChoice[Cnt] == 999)) {
				break;
			}
			else {
				printf("入力ミスがありました再度入力をお願いします\n\n");
			}
		}
		if (iChoice[Cnt] == 999) {
			break;
		}
		printf("\n|1.昇順|2.降順|\n\n");
		while (1) {
			printf("数値でを入力してください\n >");
			rewind(stdin);
			scanf("%d", &iChoice[Cnt + 3]);
			if ((iChoice[Cnt + 3] == 1) || (iChoice[Cnt + 3] == 2)) {
				break;
			}
			else{
				printf("入力ミスがありました再度入力をお願いします\n\n");
			}
		}
	}

	/* システム起動時間を取得 */
	dwStartTime = GetTickCount();

	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */
	/* ソート関数の呼び出し													 */
	//QuickSort(cPtr, 0, SIZE - 1);
	for (; Cnt > 0; Cnt--) {
		MergeSort(cPtr, pTemp, 0, SIZE - 1, iChoice[Cnt-1], iChoice[Cnt+2]);
	}
	
	/* ■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■■  */

	/* システム起動時間を取得 */
	dwEndTime = GetTickCount();

	/* 検索前と検索後の時間を引き、処理にかかった時間を表示					 */
	printf("\n%d ミリ秒かかりました！\n", (dwEndTime - dwStartTime));

	/* csvファイルとして出力												 */
	fPtr = fopen(cFileName, "w");
	fprintf(fPtr, "%s", cBuf2);
	for (iLoopCnt = 0; iLoopCnt < SIZE; iLoopCnt++) {
		fprintf(fPtr, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s",
			iLoopCnt + 1,
			cPtr[iLoopCnt].Name,
			cPtr[iLoopCnt].LastName,
			cPtr[iLoopCnt].FirstName,
			cPtr[iLoopCnt].Gender,
			cPtr[iLoopCnt].BloodType,
			cPtr[iLoopCnt].Birthday,
			cPtr[iLoopCnt].PhoneNumber,
			cPtr[iLoopCnt].MobilePhone,
			cPtr[iLoopCnt].MailAddress,
			cPtr[iLoopCnt].PostalCode,
			cPtr[iLoopCnt].Address1,
			cPtr[iLoopCnt].Address2);
	}

	fclose(fPtr);
	system("pause");
	return 0;
}

/* ------------------------------------------------------------------------- */
/* 関数名	: MergeSort			 											 */
/* 機能名	: マージソート													 */
/* 機能概要	: 配列cPtr[]のiLeftからiRightの要素のマージソートを行う			 */
/* 作成日	: 2018/05/20		中田  桂介		新規作成					 */
/* ------------------------------------------------------------------------- */
void MergeSort(struct AddrBook *cPtr, struct AddrBook *pTemp, SINT iLeft, SINT iRight, SINT iChoice, SINT iChoice2)
{
	SINT mid, i, j, k;

	if (iLeft >= iRight) {						/* 配列の要素がひとつなら	 */
		return;									/* 何もしないで戻る			 */
	}
	/* 分割する																 */
	mid = (iLeft + iRight) / 2;
	/* 再帰呼び出し															 */
	MergeSort(cPtr, pTemp, iLeft, mid, iChoice, iChoice2);
	MergeSort(cPtr, pTemp, mid + 1, iRight, iChoice, iChoice2);

	/* cPtr[iLeft]からcPtr[mid]を作業領域にコピー							 */
	for (i = iLeft; i <= mid; i++) {
		pTemp[i] = cPtr[i];
	}
	/* cPtr[mid + 1] から cPtr[right] は逆順にコピー						 */
	for (i = mid + 1, j = iRight; i <= iRight; i++, j--) {
		pTemp[i] = cPtr[j];
	}
	/* iとjは作業領域のデータを、kは配列の要素を指している */
	i = iLeft;
	j = iRight;

	for (k = iLeft; k <= iRight; k++)			/* 小さい方から配列に戻す	 */
		/* ここでソートされる												 */
		switch (iChoice)
		{
		case 1:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].Name, pTemp[j].Name) <= 0 : strcmp(pTemp[i].Name, pTemp[j].Name) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 2:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].LastName, pTemp[j].LastName) <= 0 : strcmp(pTemp[i].LastName, pTemp[j].LastName) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 3:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].FirstName, pTemp[j].FirstName) <= 0 : strcmp(pTemp[i].FirstName, pTemp[j].FirstName) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 4:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].Gender, pTemp[j].Gender) <= 0 : strcmp(pTemp[i].Gender, pTemp[j].Gender) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 5:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].BloodType, pTemp[j].BloodType) <= 0 : strcmp(pTemp[i].BloodType, pTemp[j].BloodType) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 6:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].Birthday, pTemp[j].Birthday) <= 0 : strcmp(pTemp[i].Birthday, pTemp[j].Birthday) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 7:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].PhoneNumber, pTemp[j].PhoneNumber) <= 0 : strcmp(pTemp[i].PhoneNumber, pTemp[j].PhoneNumber) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 8:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].MobilePhone, pTemp[j].MobilePhone) <= 0 : strcmp(pTemp[i].MobilePhone, pTemp[j].MobilePhone) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 9:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].MailAddress, pTemp[j].MailAddress) <= 0 : strcmp(pTemp[i].MailAddress, pTemp[j].MailAddress) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 10:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].PostalCode, pTemp[j].PostalCode) <= 0 : strcmp(pTemp[i].PostalCode, pTemp[j].PostalCode) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 11:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].Address1, pTemp[j].Address1) <= 0 : strcmp(pTemp[i].Address1, pTemp[j].Address1) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		case 12:
			if ((iChoice2 == 1) ? strcmp(pTemp[i].Address2, pTemp[j].Address2) <= 0 : strcmp(pTemp[i].Address2, pTemp[j].Address2) >= 0) {
				cPtr[k] = pTemp[i++];
			} else {
				cPtr[k] = pTemp[j--];
			}
			break;
		default:
			break;
		}
}


/* ------------------------------------------------------------------------- */
/* 関数名	: QuickSort			 											 */
/* 機能名	: クイックソート												 */
/* 機能概要	: クイックソートをして値を返します								 */
/* 作成日	: 2018/05/12		中田  桂介		新規作成					 */
/* ------------------------------------------------------------------------- */
void QuickSort(struct AddrBook *cPtr, SINT iLeft, SINT iRight)
{
	struct AddrBook num;
	SINT iLoopCnt, iLast;

	if (iLeft >= iRight)
		return;

	iLast = iLeft;
	for (iLoopCnt = iLeft+1; iLoopCnt <= iRight; iLoopCnt++) {
		if (strcmp(cPtr[iLoopCnt].PostalCode , cPtr[iLeft].PostalCode) > 0) {
			iLast++;
			num = cPtr[iLast];
			cPtr[iLast] = cPtr[iLoopCnt];
			cPtr[iLoopCnt] = num;
		}
	}
	num = cPtr[iLeft];
	cPtr[iLeft] = cPtr[iLast];
	cPtr[iLast] = num;

	QuickSort(cPtr, iLeft, iLast - 1);
	QuickSort(cPtr, iLast + 1, iRight);
}

/* ------------------------------------------------------------------------- */
/* 関数名	: Strtok			 											 */
/* 機能名	: Strtok														 */
/* 機能概要	: 文字列を区切り文字で分解する									 */
/* 作成日	: 2018/05/16		中田  桂介		新規作成					 */
/* ------------------------------------------------------------------------- */
SCHR *Strtok(SCHR *cStr, const SCHR cChar) {
	static char *cPtr = 0;
	static char *cRetPtr = NULL;

	if (cStr != 0) {
		cPtr = cStr;
	}
	if (cPtr == 0) {
		return 0;
	}

	cRetPtr = cPtr;

	if (*cRetPtr == '\0') {
		cPtr = 0;
		return 0;
	}

	cPtr = cRetPtr + 1;
	if (*cRetPtr == cChar) {
		return NULL;
	}
	while (*cPtr != cChar) {
		if (*cPtr == '\0') {
			break;
		}
		cPtr++;
	}
	if (*cPtr != '\0') {
		*cPtr++ = '\0';
	}
	return cRetPtr;
}

/* ------------------------------------------------------------------------- */
/*              Copyright HAL Collage of Technology & Design                 */
/* ------------------------------------------------------------------------- */