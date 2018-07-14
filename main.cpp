/*
main.cpp

@	Author : 1��(����)
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
	printf("\n5�ܰ� ����- �߾ӿ��� ���� �������� �߰�, �ι�° �������� ���� ��� ���ڸ����� ���� -10 ��ġ�� y��ǥ�� ���� �������� ������ ���� ����.\n");

	int flag = 0;															//flag ���� 0�ΰ�� �Ͼ�κ���, 1�ΰ�� �������κ��� ������ �ִٴ� ��.									
	int countBlackArea = 0;													//count ������ �κ��� ���� Ȯ��
	int checkingPoint = 0;													//check�� �������� ���� ����

	CvPoint checkThreeOrNine;												//��ǥ ���� 3,9 ���縦 ����

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x��ǥ �߾� ����

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
		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)			//���� �κ��� ������ ��� 9
		{
			return 9;
		}
	}
	return 3;																	//���� �κ��� ���� ��� 3;
}

int getThreeOrEightOrNine()													//y��ǥ50 ��, ��ǥ �߾��� �������� �������� ������ �׾�����, ������ ���� �Ǵ�(4�ܰ�)
{
	printf("4�ܰ� ���� -y��ǥ50 ��, ��ǥ �߾��� �������� �������� ������ �׾�����, ������ ���� �Ǵ�, �������� ������ 8, �ѹ��̶� �������� �����ٸ� 3,9 \n");
	
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
	printf("4�ܰ� ���� -y��ǥ50 ��, ��ǥ �߾��� �������� �������� ������ �׾�����, ������ ���� �Ǵ�, �������� ������ 6, �ѹ��̶� �������� �����ٸ� 5 \n");

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
int drawMiddleLineAndCheckEast()												// �߾ӿ��� ���� �������� �߰�, ù��° �������� ���� ��� ���ڸ����� ���� +2 ��ġ�� y��ǥ�� ���� ���� ������ ���� ����(3�ܰ�)
{
	printf("\n3�ܰ� ���� - �߾ӿ��� ���� �������� �߰�, �ι�° �������� ���� ��� ���ڸ����� ���� -10 ��ġ�� y��ǥ�� ���� ���� ������ ���� ����.\n");

	int flag = 0;															//flag ���� 0�ΰ�� �Ͼ�κ���, 1�ΰ�� �������κ��� ������ �ִٴ� ��.									
	int countBlackArea = 0;													//count ������ �κ��� ���� Ȯ��
	int checkingPoint = 0;													//check�� �������� ���� ����

	bool isFiveOrSix = true;
	CvPoint checkFiveOrSix;													//��ǥ ���� 5,6 ���縦 ����

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x��ǥ �߾� ����

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

int isHardSixOrNine()			// �߾ӿ��� ���� �������� �߰�, ù��° �������� ���� ��� ���ڸ����� ���� +2 ��ġ�� y��ǥ�� ���� ���� ������ ���� ����(3�ܰ�)
{
	printf("\n3�ܰ� ����- �߾ӿ��� ���� �������� �߰�, �ι�° �������� ���� ��� ���ڸ����� ���� -10 ��ġ�� y��ǥ�� ���� ���� ������ ���� ����.\n");

	int flag = 0;															//flag ���� 0�ΰ�� �Ͼ�κ���, 1�ΰ�� �������κ��� ������ �ִٴ� ��.									
	int countBlackArea = 0;													//count ������ �κ��� ���� Ȯ��
	int checkingPoint = 0;													//check�� �������� ���� ����

	CvPoint checkSixOrNine;													//��ǥ ���� 6,9 ���縦 ����

	for (int j = 0; j < 100; j++)
	{
		CvScalar temp = cvGet2D(scaledOutput, j, 50);						//x��ǥ �߾� ����

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

		if (temp.val[0] == 0 && temp.val[1] == 0 && temp.val[2] == 0)			//���� �κ��� ������ ��� 9
		{
			return 9;
		}
	}
	return 6;																	//�������� ���� ��� 6
}
int drawNumberLineAndCheckThreeArea()										//��ü�� �������� �߰� 3���� �����κ��� �������� Ȯ�� �Ұ� (2�ܰ�)
{
	printf("\n2�ܰ� ����-�߾ӿ� �������� �߰� 3���� �����κ��� �������� Ȯ�� �Ұ�\n");

	int flag = 0;															//flag ���� 0�ΰ�� �Ͼ�κ���, 1�ΰ�� �������κ��� ������ �ִٴ� ��.									
	int countBlackArea = 0;													//count ������ �κ��� ���� Ȯ��
	
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
		return drawMiddleLineAndCheckEast();									//�����κ��� 3���̸� ������ ����
	}
	else
	{
		return 0;												//�����κ��� 3���� �ƴϸ� 0;
	}
}

int checkOneOrTwoOrSeven()										//2����4���� Ȯ��(2�ܰ�)
{
	printf("\n2�ܰ� ���� 1����, 2����, 4����, 7����, �߰�� 6, �߰��9 ���� Ȯ��\n");

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
		if (countPix >= 95)		//����90�̾���
		{
			isFour = true;
			break;
		}
		countPix = 0;
	}

	
	//Ȥ�� 1���� �ƴ��� �Ǵ�.
	CvScalar checkOne = cvGet2D(scaledOutput, 99, 94);										//���� �ϴ� �˻�
	CvScalar checkSix = cvGet2D(scaledOutput, 99, 5);									//���� �ϴ� �˻�
	CvScalar checkSeven = cvGet2D(scaledOutput, 2, 97);									//���� ��� �˻�

	if (checkOne.val[0] == 0 && checkOne.val[1] == 0 && checkOne.val[2] == 0 && isFour == true)		//1�� ���
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

int drawHorizontalLine()									//�� ���̺� ���� �׸� (1�ܰ� - ����)
{
	printf("\n1�ܰ� ���� -�� ���̺� ���� �׸�\n");

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
		if (countPix >= 90)			//�� 100Pix�� �����Ǽ� 99�� ����
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

	if (countLastPix > 60)								//�Ÿ����� Ư¡������ �������� ����
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

	int minX = 5000;												//x��ǥ ���� ��ġ
	int minY= 5000;													//y��ǥ ���� ��ġ

	int maxX = -100;												//x��ǥ �ְ� ��ġ
	int maxY = -100;												//y��ǥ �ְ� ��ġ

	//�ʱ�ȭ �۾�----------------------------------------------------------------------------------------------------

	printf("insert the directory of file: ");
	scanf("%s", str);


	test = cvLoadImage(str);
	binaryOutput = cvCreateImage(cvGetSize(test),8, 3);

	originalPoint.x = test->width;
	originalPoint.y = test->height;

	printf("Image Width: %d\n", originalPoint.x);
	printf("Image Height: %d\n", originalPoint.y);
	

	//����ȭó��----------------------------------------------------------------------------------------
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

	//�̹��� �ڸ���-------------------------------------------------------------------------------------------------
	//�������� ù���� ����ã��
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

	//�̹��� scaling-------------------------------------------------------------------------------------------
	scaledOutput = cvCreateImage(cvSize(100, 100),8, 3);
	cvResize(cutOutput, scaledOutput, CV_INTER_NN);


	//���Ϻз�-------------------------------------------------------------------------------------------------
	//... �̸� ���� �ص� �Լ� ���

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