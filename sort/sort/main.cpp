/* ------------------------------------------------------------------------- */
/* main.cpp																	 */
/* OT2B																		 */
/* �ۑ�\�[�X�t�@�C��								 						 */
/*																			 */
/* ------------------------------------------------------------------------- */
/* 	�ԍ�	�X�V���e								�X�V��		���O		 */
/* ------------------------------------------------------------------------- */
/* 000000	�V�K�쐬								2018/05/08	���c�@�j��	 */
/* 000001	�֐�Strtok�쐬							2018/05/16	���c�@�j��	 */
/* 000002	�֐�MergeSort�쐬						2018/05/20	���c�@�j��	 */
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
#define SIZE 105000

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
/* �v���g�^�C�v�錾															 */
/* ------------------------------------------------------------------------- */
void QuickSort(struct AddrBook *, SINT iLeft, SINT iRight);
void MergeSort(struct AddrBook *, struct AddrBook *, SINT iLeft, SINT iRight, SINT, SINT);
SCHR *Strtok(SCHR *cStr, const SCHR cChar);

/* ------------------------------------------------------------------------- */
/* �֐���	: main			 												 */
/* �@�\��	: �G���g���[�|�C���g											 */
/* �@�\�T�v	: csv�t�@�C���̓ǂݍ��ݏo�́A�\�[�g�̑I���A�\�[�g���Ԃ̌v��		 */
/* �쐬��	: 2018/05/08		���c  �j��		�V�K�쐬					 */
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

	/* �ǂݍ��ލ\���̕��������̊m�ۃ������̊m��								 */
	cPtr = (AddrBook*)malloc(SIZE * sizeof(AddrBook));
	pTemp = (AddrBook*)malloc(SIZE * sizeof(AddrBook));

	/* ����csv�t�@�C���̏ꏊ���w��											 */
	sprintf(cFileName, "%s\\Desktop\\ot\\ot02\\AddrBook.csv", getenv("USERPROFILE"));

	/* �t�@�C�����J���Ȃ������ꍇ�G���[										 */
	fPtr = fopen(cFileName, "r");
	if (fPtr == NULL) {
		printf("Not open %s\n",cFileName);
		return -1;
	}
	printf("Now Loading\n");

	/* ���ږ���cBuf2�֊i�[													 */
	fgets(cBuf2, sizeof(AddrBook), fPtr);
	/* csv�t�@�C������ǂݍ���ō\���֑̂��								 */
	for (iLoopCnt = 0; iLoopCnt < SIZE;  iLoopCnt++) {
		fgets(cBuf, sizeof(AddrBook), fPtr);
		cTemp = Strtok(cBuf, ',');				/* No�̕����g�[�N������		 */
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
		/* �����󗓂������ꍇ\0����										*/
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

	/* ���Ƀt�@�C�������݂��Ă��邩�m�F���đ��݂����ꍇ�����̐��l�𑝂₷	 */
	/* �Ȃ������ꍇ�V�K�쐬													 */
	for (iLoopCnt = 0; (fPtr = fopen(cFileName, "r")) != NULL; iLoopCnt++) {
		if (iLoopCnt >= 100) {
			fclose(fPtr);
			return -1;
		}
		fclose(fPtr);
		sprintf(cFileName, "%s\\Desktop\\ot\\ot02\\AddrBook%02d.csv", getenv("USERPROFILE"), iLoopCnt+1);
	}

	system("cls");

	printf("�\�[�g���s���܂��L�[��I�����Ă�������(�ő�3�i�K)\n");
	for (Cnt = 0; Cnt < 3; Cnt++) {
		printf("\n|1.�����@�@|2.�J�i(�c��)|3.�J�i(���O)�@�@| 4.���ʁ@�@| 5.���t�^| 6.���N����  |\n");
		printf("|7.�d�b�ԍ�|8.�g�ѓd�b�@|9.���[���A�h���X|10.�X�֔ԍ�|11.�Z���@|12.�Z��(�J�i)|\n");
		printf("|END(999)  |\n\n");
		while (1) {
			printf("���l�ł���͂��Ă�������\n >");
			rewind(stdin);
			scanf("%d", &iChoice[Cnt]);
			if (((iChoice[Cnt] > 0) && (iChoice[Cnt] < 13)) || (iChoice[Cnt] == 999)) {
				break;
			}
			else {
				printf("���̓~�X������܂����ēx���͂����肢���܂�\n\n");
			}
		}
		if (iChoice[Cnt] == 999) {
			break;
		}
		printf("\n|1.����|2.�~��|\n\n");
		while (1) {
			printf("���l�ł���͂��Ă�������\n >");
			rewind(stdin);
			scanf("%d", &iChoice[Cnt + 3]);
			if ((iChoice[Cnt + 3] == 1) || (iChoice[Cnt + 3] == 2)) {
				break;
			}
			else{
				printf("���̓~�X������܂����ēx���͂����肢���܂�\n\n");
			}
		}
	}

	/* �V�X�e���N�����Ԃ��擾 */
	dwStartTime = GetTickCount();

	/* ��������������������������������������������������������������������  */
	/* �\�[�g�֐��̌Ăяo��													 */
	//QuickSort(cPtr, 0, SIZE - 1);
	for (; Cnt > 0; Cnt--) {
		MergeSort(cPtr, pTemp, 0, SIZE - 1, iChoice[Cnt-1], iChoice[Cnt+2]);
	}
	
	/* ��������������������������������������������������������������������  */

	/* �V�X�e���N�����Ԃ��擾 */
	dwEndTime = GetTickCount();

	/* �����O�ƌ�����̎��Ԃ������A�����ɂ����������Ԃ�\��					 */
	printf("\n%d �~���b������܂����I\n", (dwEndTime - dwStartTime));

	/* csv�t�@�C���Ƃ��ďo��												 */
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
/* �֐���	: MergeSort			 											 */
/* �@�\��	: �}�[�W�\�[�g													 */
/* �@�\�T�v	: �z��cPtr[]��iLeft����iRight�̗v�f�̃}�[�W�\�[�g���s��			 */
/* �쐬��	: 2018/05/20		���c  �j��		�V�K�쐬					 */
/* ------------------------------------------------------------------------- */
void MergeSort(struct AddrBook *cPtr, struct AddrBook *pTemp, SINT iLeft, SINT iRight, SINT iChoice, SINT iChoice2)
{
	SINT mid, i, j, k;

	if (iLeft >= iRight) {						/* �z��̗v�f���ЂƂȂ�	 */
		return;									/* �������Ȃ��Ŗ߂�			 */
	}
	/* ��������																 */
	mid = (iLeft + iRight) / 2;
	/* �ċA�Ăяo��															 */
	MergeSort(cPtr, pTemp, iLeft, mid, iChoice, iChoice2);
	MergeSort(cPtr, pTemp, mid + 1, iRight, iChoice, iChoice2);

	/* cPtr[iLeft]����cPtr[mid]����Ɨ̈�ɃR�s�[							 */
	for (i = iLeft; i <= mid; i++) {
		pTemp[i] = cPtr[i];
	}
	/* cPtr[mid + 1] ���� cPtr[right] �͋t���ɃR�s�[						 */
	for (i = mid + 1, j = iRight; i <= iRight; i++, j--) {
		pTemp[i] = cPtr[j];
	}
	/* i��j�͍�Ɨ̈�̃f�[�^���Ak�͔z��̗v�f���w���Ă��� */
	i = iLeft;
	j = iRight;

	for (k = iLeft; k <= iRight; k++)			/* ������������z��ɖ߂�	 */
		/* �����Ń\�[�g�����												 */
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
/* �֐���	: QuickSort			 											 */
/* �@�\��	: �N�C�b�N�\�[�g												 */
/* �@�\�T�v	: �N�C�b�N�\�[�g�����Ēl��Ԃ��܂�								 */
/* �쐬��	: 2018/05/12		���c  �j��		�V�K�쐬					 */
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
/* �֐���	: Strtok			 											 */
/* �@�\��	: Strtok														 */
/* �@�\�T�v	: ���������؂蕶���ŕ�������									 */
/* �쐬��	: 2018/05/16		���c  �j��		�V�K�쐬					 */
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