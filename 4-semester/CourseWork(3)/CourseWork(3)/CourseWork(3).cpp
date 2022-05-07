#define MAIN_PROCESS 0
#define TASK 2
#define SCALE 4

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>

#include<mpi.h>
#include<iostream>
#include <cstdio>
#include <vector>
#include <math.h>
using namespace std;
using namespace cv;

Mat loadImage(String imageName)
{
	Mat image = imread(imageName, IMREAD_GRAYSCALE); //открытие и внутреннее преобразование в оттенки серого
	if (image.empty())
	{
		cout << "Невозможно открыть изображение!" << endl;
		cin.get();
		throw invalid_argument(imageName);
	}
	return image;
}


Mat filterRoberts(Mat srcImage)
{
	Mat dstImage = srcImage.clone();
	int t1 = 0, t2 = 0, B = 0, D = 0, E = 0, H = 0;

	for (int row = 1; row < srcImage.rows - 1; row++)
	{
		t1 = 0, t2 = 0, B = 0, D = 0, E = 0, H = 0;

		for (int col = 1; col < srcImage.cols - 1; col++)
		{
			H = srcImage.at<uchar>(row, col);
			D = srcImage.at<uchar>(row + 1, col);
			E = srcImage.at<uchar>(row + 1, col + 1);
			B = srcImage.at<uchar>(row, col + 1);

			t1 = abs(H - E);
			t2 = abs(D - B);

			dstImage.at<uchar>(row, col) = (uchar)(t1 + t2);
		}
	}

	// left & right boder
	for (size_t row = 0; row < srcImage.rows - 1; row++)
	{
		// left
		size_t leftCol = 0;
		B = srcImage.at<uchar>(row, leftCol);
		H = srcImage.at<uchar>(row, leftCol + 1);
		E = srcImage.at<uchar>(row + 1, leftCol);
		D = srcImage.at<uchar>(row + 1, leftCol + 1);

		t1 = abs(B - D);
		t2 = abs(H - E);
		dstImage.at<uchar>(row, leftCol) = (uchar)(t1 + t2);

		//right
		size_t rightCol = srcImage.cols - 1;
		B = srcImage.at<uchar>(row, rightCol);
		H = srcImage.at<uchar>(row, rightCol - 1);
		E = srcImage.at<uchar>(row + 1, rightCol);
		D = srcImage.at<uchar>(row + 1, rightCol - 1);

		t1 = abs(H - E);
		t2 = abs(B - D);
		dstImage.at<uchar>(row, rightCol) = (uchar)(t1 + t2);
	}

	// lower & upper border
	for (size_t col = 0; col < srcImage.cols - 1; col++)
	{
		// lower
		size_t lowerRow = srcImage.rows - 1;
		B = srcImage.at<uchar>(lowerRow, col);
		H = srcImage.at<uchar>(lowerRow, col + 1);
		E = srcImage.at<uchar>(lowerRow - 1, col);
		D = srcImage.at<uchar>(lowerRow - 1, col + 1);

		t1 = abs(E - H);
		t2 = abs(D - B);
		dstImage.at<uchar>(lowerRow, col) = (uchar)(t1 + t2);

		// upper
		size_t upperRow = 0;
		B = srcImage.at<uchar>(upperRow, col);
		H = srcImage.at<uchar>(upperRow, col + 1);
		E = srcImage.at<uchar>(upperRow + 1, col);
		D = srcImage.at<uchar>(upperRow + 1, col + 1);

		t1 = abs(B - D);
		t2 = abs(H - E);
		dstImage.at<uchar>(upperRow, col) = (uchar)(t1 + t2);
	}
	return dstImage;
}



Mat scaleLine(Mat sourceLine, int scale)
{
	Mat scaledLine = Mat(scale, sourceLine.cols * scale, CV_8U);
	for (size_t i = 0; i < sourceLine.cols; i++)
	{
		uchar pixel = sourceLine.at<uchar>(0, i);
		for (size_t j = 0; j < scale; j++)
		{
			scaledLine.at<uchar>(0, i * scale + j) = pixel;
		}
	}

	for (size_t j = 1; j < scale; j++)
	{
		scaledLine.row(0).copyTo(scaledLine.row(j));
	}
	return scaledLine;
}

Mat scaleImage(Mat sourceImage, int scale)
{
	Mat scaledImage;
	for (size_t i = 0; i < sourceImage.rows; i++)
	{
		scaledImage.push_back(scaleLine(sourceImage.row(i), scale));
	}
	return scaledImage;
}



/////////// параллельная /////////////////

int main(int argc, char** argv) {

	double t1, t2;

	Mat inputImage, outputImage;
	int rowsCount, colsCount;
	int bufferSize, imageSize;
	int processNumber, processesCount;
	uchar* partialBuffer;

	// Init MPI
	MPI_Init(&argc, &argv);
	t1 = MPI_Wtime();
	MPI_Comm_rank(MPI_COMM_WORLD, &processNumber); // определяет номер запущенного процесса
	MPI_Comm_size(MPI_COMM_WORLD, &processesCount); // количество запущенных процессов

	if (processNumber == MAIN_PROCESS)
	{
		cout << "Size: " << processesCount << endl;
		inputImage = loadImage("C://Users//Марина//Desktop//Univers//4 semestr//KS&S//CourseWork//CourseWork(3)//CourseWork(3)//image.jpg");

		if (inputImage.total() % processesCount)
		{
			std::cerr << "Cannot evenly divide the image between the processes. Choose a different number of processes!" << std::endl;
			return -2;
		}

		colsCount = inputImage.cols;
		imageSize = inputImage.rows * inputImage.cols;
		rowsCount = inputImage.rows / (processesCount - 1);
		bufferSize = rowsCount * inputImage.cols;
	}

	MPI_Barrier(MPI_COMM_WORLD);

	// отправляет от 0 процесса к другим процессам данные
	MPI_Bcast(&colsCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&imageSize, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&rowsCount, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast(&bufferSize, 1, MPI_INT, 0, MPI_COMM_WORLD);

	// выделяем частичный буфер, содержащий изображение
	partialBuffer = new uchar[bufferSize];

	// дожидается, чтобы все данные отправились процессам
	MPI_Barrier(MPI_COMM_WORLD);

	if (processNumber == MAIN_PROCESS) {
		for (size_t i = 1; i < processesCount; i++) {
			int shift = (i - 1) * bufferSize;
			MPI_Send(inputImage.data + shift, bufferSize, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD);
		}
	}

	if (processNumber != 0) {
		// принимает отправленные ему данные
		MPI_Recv(partialBuffer, bufferSize, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
		// конвертирует изображение
		Mat part(rowsCount, colsCount, CV_8UC1, partialBuffer);

		// Task 1: фильтр изображения
		if (TASK == 1) {
			Mat filteredPart = filterRoberts(part);
			MPI_Send(filteredPart.data, bufferSize, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
		}
		// Task 2: увеличение изображения
		else if (TASK == 2) {
			Mat scaledPart = scaleImage(part, SCALE);
			MPI_Send(scaledPart.data, scaledPart.cols * scaledPart.rows, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
		}
	}

	if (processNumber == MAIN_PROCESS) {
		uchar* output;

		if (TASK == 1) {
			output = new uchar[imageSize];

			for (size_t i = 1; i < processesCount; i++) {
				MPI_Recv(partialBuffer, bufferSize, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				copy(partialBuffer, partialBuffer + bufferSize, output + bufferSize * (i - 1));
			}
			outputImage = Mat(inputImage.rows, inputImage.cols, CV_8UC1, output);
		}
		else if (TASK == 2) {
			output = new uchar[imageSize * SCALE * SCALE];
			int bufSize = bufferSize * SCALE * SCALE;
			uchar* buffer = new uchar[bufSize];

			for (size_t i = 1; i < processesCount; i++) {
				MPI_Recv(buffer, bufSize, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUSES_IGNORE);
				copy(buffer, buffer + bufSize, output + bufSize * (i - 1));
			}
			outputImage = Mat(inputImage.rows * SCALE, inputImage.cols * SCALE, CV_8UC1, output);
		}

		namedWindow("Output");
		imshow("Output", outputImage);
		imwrite("C:\\Users\\Марина\\Desktop\\Univers\\4 semestr\\KS&S\\CourseWork\\CourseWork(3)\\CourseWork(3)\\outputImage.jpg", outputImage);
		waitKey(0);
	}

	delete[] partialBuffer;
	t2 = MPI_Wtime();
	cout << "Common sequential time: " << (t2 - t1) << " s" << "\n";
	MPI_Finalize();

	return 0;
}



/////////////// последовательная ////////////////////////////

//int main(int argc, char** argv) {
//	Mat srcImage = loadImage("C://Users//Марина//Desktop//Univers//4 semestr//KS&S//CourseWork//CourseWork(3)//CourseWork(3)//image.jpg");
//    Mat filteredImage = filterRoberts(srcImage);
//	Mat scaledImage = scaleImage(srcImage, SCALE);
//    
//	imshow("srcImage", srcImage);
//
//	imshow("filteredImage", filteredImage);
//	imwrite("C:\\Users\\Марина\\Desktop\\Univers\\4 semestr\\KS&S\\CourseWork\\CourseWork(3)\\CourseWork(3)\\filteredImage.jpg", filteredImage);
//
//	imshow("scaledImage", scaledImage);
//	imwrite("C:\\Users\\Марина\\Desktop\\Univers\\4 semestr\\KS&S\\CourseWork\\CourseWork(3)\\CourseWork(3)\\scaledImage.jpg", scaledImage);
//	
//	waitKey(0);
//    return 0;
//}



