#include "opencv2/highgui/highgui.hpp"
#include<stdio.h>
#include<stdlib.h>
#include "Header.h"

using namespace cv;
using namespace std;

int main(void){
	
	int numFeatures=13;
	int testSetSize=37;
	int trainingSetSize=110;
		
	cancerDetect detector(trainingSetSize,numFeatures,testSetSize);
	string yTrainFileName="trainY.txt";//set this
	string yTestFileName="yTestActual.txt";

	vector<string> imgNames(trainingSetSize);
	for(int i=0;i<trainingSetSize;i++){
		string str="img2 (";
		str.append(to_string(i+1));
		str.append(").bmp");
		imgNames[i]=str;
	}


	/*detector.setKernel();
	detector.setType();
	detector.setTermCriteria();
	detector.loadTrainingImages(imgNames);
	detector.setTrainingYLabels(yTrainFileName);
	detector.train();*/

	VideoCapture videoStream1("vid2 (2).mp4");
	if (videoStream1.isOpened() == false){
		printf("Video File NOT Found\n");
		system("pause");
		exit(0);
	}
	detector.loadTrainedModel();
	Mat frame;
	while(true){
		videoStream1.read(frame);
		if(frame.empty()){
			exit(0);
		}
		imshow("Live Stream",frame);
		int x=waitKey(30);
		if(x=='f'){
			imwrite("imgLiveStream.jpg",frame);
			printf("Image Taken ---->>");
			float yPred=detector.predictIndividual("imgLiveStream.jpg");
			if(yPred>0.5){
				printf("Cancerous\n");
			}
			else{
				printf("Non-Cancerous\n");
			}
		}
		else if(x=='e'){
			exit(0);
		}
	}

	//float x=detector.predictIndividual("test.jpg");
	//printf("%lf\n",x);
	

	system("pause");
	return 0;


}
