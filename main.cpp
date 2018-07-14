/*
main.cpp

@	Author : 1조(한조)
@	Revised Date : 2018.04.04

*/

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

IplImage * test;
IplImage * binaryOutput;
IplImage * cutOutput;
IplImage * scaledOutput;

int getThreeOrNine()
{
	printf("\n5단계 진입- 중앙에서 부터 수직선을 긋고, 두번째 검은색이 나올 경우 그자리에서 부터 -10 위치의 y좌표로 부터 서쪽으로 검은색 유무 조사.\n");

	int flag = 0;															//flag 값이 0인경우 하얀부분을, 1인경우 검은색부분을 지나고 있다는 뜻.									
	int countBlackArea = 0;													//count 검은색 부분의 개수 확인
	int checkingPoint = 0;													//check를 시작할지 말지 결정

	CvPoint checkThreeOrNine;												//좌표 조사 3,9 조사를 위한

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x좌표 중앙 지점

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0 && checkingPoint == 1)
		{
			checkThreeOrNine.x = 50;
			checkThreeOrNine.y = j;
			break;
		}
		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0)
		{
			countBlackArea += 1;
			flag = 1;
		}
		else if ((temp.val[0] != 0 || temp.val[1] != 0 || temp.val[2] != 0) && flag == 1)
		{
			checkingPoint = 1;
			flag = 0;
		}
	}
	for (int i = checkThreeOrNine.x; i >= 0; i--)
	{
		CvScalar temp = cvGet2D(scaledOutput, checkThreeOrNine.y - 5, i);
		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)			//검은 부분이 존재할 경우 9
		{
			return 9;
		}
	}
	return 3;																	//검은 부분이 없는 경우 3;
}

int getThreeOrEightOrNine()													//y좌표50 위, 좌표 중앙을 시작으로 서쪽으로 직선을 그었을때, 검은색 유무 판단(4단계)
{
	printf("4단계 진입 -y좌표50 위, 좌표 중앙을 시작으로 서쪽으로 직선을 그었을때, 검은색 유무 판단, 검은색이 있으면 8, 한번이라도 검은색이 없었다면 3,9 \n");
	
	int continueFlag = 0;

	for (int j = 50; j < 100; j++)
	{
		for (int i = 50; i >= 0; i--)
		{
			CvScalar temp = cvGet2D(scaledOutput, j, i);

			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
			{
				continueFlag = 1;
				break;
			}
		}
		if (continueFlag == 0)
		{
			return getThreeOrNine();
		}
		continueFlag = 0;
	}
	return 8;
}
int getFiveOrSix()
{
	printf("4단계 진입 -y좌표50 위, 좌표 중앙을 시작으로 서쪽으로 직선을 그었을때, 검은색 유무 판단, 검은색이 있으면 6, 한번이라도 검은색이 없었다면 5 \n");

	int continueFlag = 0;

	for (int j = 50; j < 100; j++)
	{
		for (int i = 50; i >= 0; i--)
		{
			CvScalar temp = cvGet2D(scaledOutput, j, i);

			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
			{
				continueFlag = 1;
				break;
			}
		}
		if (continueFlag == 0)
		{
			return 5;
		}
		continueFlag = 0;
	}

	return 6;
}
int drawMiddleLineAndCheckEast()												// 중앙에서 부터 수직선을 긋고, 첫번째 검은색이 나올 경우 그자리에서 부터 +2 위치의 y좌표로 부터 동쪽 검은색 유무 조사(3단계)
{
	printf("\n3단계 진입 - 중앙에서 부터 수직선을 긋고, 두번째 검은색이 나올 경우 그자리에서 부터 -10 위치의 y좌표로 부터 동쪽 검은색 유무 조사.\n");

	int flag = 0;															//flag 값이 0인경우 하얀부분을, 1인경우 검은색부분을 지나고 있다는 뜻.									
	int countBlackArea = 0;													//count 검은색 부분의 개수 확인
	int checkingPoint = 0;													//check를 시작할지 말지 결정

	bool isFiveOrSix = true;
	CvPoint checkFiveOrSix;													//좌표 조사 5,6 조사를 위한

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x좌표 중앙 지점

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0 && checkingPoint ==1)
		{
			checkFiveOrSix.x = 50;
			checkFiveOrSix.y = j;
			break;
		}

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0)
		{
			countBlackArea += 1;
			flag = 1;
		}
		else if ((temp.val[0] != 0 || temp.val[1] != 0 || temp.val[2] != 0) && flag == 1)
		{
			checkingPoint = 1;
			flag = 0;
		}
	}

	for (int i = checkFiveOrSix.x; i < 100; i++)
	{
		CvScalar temp = cvGet2D(scaledOutput, checkFiveOrSix.y-10, i);

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
		{
			isFiveOrSix = false;
			break;
		}
	}

	if (isFiveOrSix)
	{
		return getFiveOrSix();
	}
	else
	{
		return getThreeOrEightOrNine();
	}
}

int isHardSixOrNine()			// 중앙에서 부터 수직선을 긋고, 첫번째 검은색이 나올 경우 그자리에서 부터 +2 위치의 y좌표로 부터 동쪽 검은색 유무 조사(3단계)
{
	printf("\n3단계 진입- 중앙에서 부터 수직선을 긋고, 두번째 검은색이 나올 경우 그자리에서 부터 -10 위치의 y좌표로 부터 동쪽 검은색 유무 조사.\n");

	int flag = 0;															//flag 값이 0인경우 하얀부분을, 1인경우 검은색부분을 지나고 있다는 뜻.									
	int countBlackArea = 0;													//count 검은색 부분의 개수 확인
	int checkingPoint = 0;													//check를 시작할지 말지 결정

	CvPoint checkSixOrNine;													//좌표 조사 6,9 조사를 위한

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x좌표 중앙 지점

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0 && checkingPoint == 1)
		{
			checkSixOrNine.x = 50;
			checkSixOrNine.y = j;
			break;
		}

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag == 0)
		{
			countBlackArea += 1;
			flag = 1;
		}
		else if ((temp.val[0] != 0 || temp.val[1] != 0 || temp.val[2] != 0) && flag == 1)
		{
			checkingPoint = 1;
			flag = 0;
		}
	}

	for (int i = checkSixOrNine.x; i < 100; i++)
	{
		CvScalar temp = cvGet2D(scaledOutput, checkSixOrNine.y - 10, i);

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)			//검은 부분이 존재할 경우 9
		{
			return 9;
		}
	}
	return 6;																	//존재하지 않을 경우 6
}
int drawNumberLineAndCheckThreeArea()										//전체에 수직선을 긋고 3개의 검은부분이 나오는지 확인 할것 (2단계)
{
	printf("\n2단계 진입-중앙에 수직선을 긋고 3개의 검은부분이 나오는지 확인 할것\n");

	int flag = 0;															//flag 값이 0인경우 하얀부분을, 1인경우 검은색부분을 지나고 있다는 뜻.									
	int countBlackArea = 0;													//count 검은색 부분의 개수 확인
	
	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);
		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && flag ==0)
		{
			countBlackArea += 1;
			flag = 1;
		}
		else if ((temp.val[0] != 0 && temp.val[1] != 0 && temp.val[2] != 0) && flag == 1)
		{
			flag = 0;
		}
	}

	if (countBlackArea == 3)
	{
		return drawMiddleLineAndCheckEast();									//검은부분이 3개이면 나머지 연산
	}
	else
	{
		return 0;												//검은부분이 3개가 아니면 0;
	}
}

int checkOneOrTwoOrSeven()										//2인지4인지 확인(2단계)
{
	printf("\n2단계 진입 1인지, 2인지, 4인지, 7인지, 견고딕 6, 견고딕9 인지 확인\n");

	bool isFour = false;
	int countPix = 0;

	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			CvScalar temp = cvGet2D(scaledOutput, j, i);

			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
			{
				countPix += 1;
			}
		}
		if (countPix >= 95)		//기존90이었음
		{
			isFour = true;
			break;
		}
		countPix = 0;
	}

	
	//혹시 1인지 아닌지 판단.
	CvScalar checkOne = cvGet2D(scaledOutput, 99, 94);										//우측 하단 검사
	CvScalar checkSix = cvGet2D(scaledOutput, 99, 5);									//좌측 하단 검사
	CvScalar checkSeven = cvGet2D(scaledOutput, 2, 97);									//우측 상단 검사

	if (checkOne.val[0] == 0 && checkOne.val[1] == 0 && checkOne.val[2] == 0 && isFour == true)		//1일 경우
	{
		return 1;
	}
	else if (isFour)
	{
		return 4;
	}
	else if (!isFour && checkSix.val[0] == 0 && checkSix.val[1] == 0 && checkSix.val[2] == 0)
	{
		return 2;
	}
	else if (!isFour && checkSeven.val[0] == 0 && checkSeven.val[1] == 0 && checkSeven.val[2] == 0)
	{
		return 7;
	}
	else
	{
		return isHardSixOrNine();
	}
}

int drawHorizontalLine()									//각 높이별 수평선 그림 (1단계 - 시작)
{
	printf("\n1단계 진입 -각 높이별 수평선 그림\n");

	bool isThereOneLine = false;
	bool isLastLineLong = false;

	int countPix = 0;
	int countLastPix = 0;

	for (int j = 0; j < 100; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			CvScalar temp = cvGet2D(scaledOutput, j, i);
			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
			{
				countPix += 1;
			}
		}
		if (countPix >= 90)			//총 100Pix에 임의의수 99를 잡음
		{
			isThereOneLine = true;
			
			break;
		}
		printf("countPix: %d  height: %d\n", countPix, j);

		countPix = 0;
	}

	for (int i = 0; i < 100; i++)
	{
		CvScalar temp = cvGet2D(scaledOutput, 99, i);
		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)
		{
			countLastPix += 1;
		}
	}

	if (countLastPix > 60)								//신명조의 특징때문에 새로지은 변수
	{
		isLastLineLong = true;
	}

	if (isThereOneLine ==true || isLastLineLong == true)
	{
		return checkOneOrTwoOrSeven();
	}
	else
	{
		return drawNumberLineAndCheckThreeArea();
	}
}

int main()
{
	char str[100];

	CvPoint originalPoint;
	CvPoint firstPoint;
	CvPoint lastPoint;

	int minX = 5000;												//x좌표 최저 위치
	int minY= 5000;													//y좌표 최저 위치

	int maxX = -100;												//x좌표 최고 위치
	int maxY = -100;												//y좌표 최고 위치

	//초기화 작업----------------------------------------------------------------------------------------------------

	printf("insert the directory of file: ");
	scanf("%s", str);


	test = cvLoadImage(str);
	binaryOutput = cvCreateImage(cvGetSize(test),8, 3);

	originalPoint.x = test->width;
	originalPoint.y = test->height;

	printf("Image Width: %d\n", originalPoint.x);
	printf("Image Height: %d\n", originalPoint.y);
	

	//이진화처리----------------------------------------------------------------------------------------
	for (int i = 0; i < test->width; i++)
	{
		for (int j = 0; j < test->height; j++)
		{
			CvScalar temp = cvGet2D(test, j, i);

			double avg = (temp.val[0] + temp.val[1] + temp.val[2]) / 3;

			if (avg > 128)
			{
				cvSet2D(binaryOutput, j, i, cvScalar(255, 255, 255));
			}
			else
			{
				cvSet2D(binaryOutput, j, i, cvScalar(0, 0, 0));
			}

		}
	}

	//이미지 자르기-------------------------------------------------------------------------------------------------
	//검은색의 첫점과 끝점찾기
	for (int i = 0; i < binaryOutput->width; i++)
	{
		for (int j = 0; j < binaryOutput->height; j++)
		{
			CvScalar temp = cvGet2D(binaryOutput, j, i);
			
			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && maxX < i)
			{
				maxX = i;
			}
			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && maxY < j)
			{
				maxY = j;
			}

			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && minX > i)
			{
				minX = i;
			}
			if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0 && minY > j)
			{
				minY = j;
			}
		}
	}

	printf("minX: %d minY: %d\n", minX, minY);
	printf("maxX: %d maxY: %d\n", maxX, maxY);

	CvSize cutSize;
	cutSize.width = maxX - minX +1;
	cutSize.height = maxY - minY + 1;

	cutOutput = cvCreateImage(cutSize,8, 3);
	cvSet(cutOutput, cvScalar(255, 255, 255));
	
	for (int i = minX; i <= maxX; i++)
	{
		for (int j = minY; j <= maxY; j++)
		{
			CvScalar insertColor = cvGet2D(binaryOutput, j, i);
			if (insertColor.val[0] == 0 && insertColor.val[1] == 0 && insertColor.val[2] == 0)
			{
				cvSet2D(cutOutput, j - minY, i - minX, insertColor);
			}
		}
	}

	printf("cutOutput width: %d\n", cutOutput->width);
	printf("cutOutput height: %d\n", cutOutput->height);

	//이미지 scaling-------------------------------------------------------------------------------------------
	scaledOutput = cvCreateImage(cvSize(100, 100),8, 3);
	cvResize(cutOutput, scaledOutput, CV_INTER_NN);


	//패턴분류-------------------------------------------------------------------------------------------------
	//... 미리 정의 해둔 함수 사용

	printf("The Number is %d\n\n\n", drawHorizontalLine());


	cvNamedWindow("Binary Image", 1);
	cvNamedWindow("Cut Image", 2);
	cvNamedWindow("100*100 Resized Image", 3);

	cvShowImage("Binary Image", binaryOutput);
	cvShowImage("Cut Image", cutOutput);
	cvShowImage("100*100 Resized Image", scaledOutput);

	cvWaitKey(0);

	cvDestroyWindow("Binary Image");
	cvDestroyWindow("Cut Image");
	cvDestroyWindow("100*100 Resized Image");

	return 0;
}