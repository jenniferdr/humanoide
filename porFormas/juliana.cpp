#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "cv.h"
#include "highgui.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <sstream>
using namespace cv;
using namespace std;
bool plotSupportVectors=true;
int numTrainingPoints=1000;
int numTestPoints=500;
int size=200;
int eq=0;

// accuracy
float evaluate(cv::Mat& predicted, cv::Mat& actual) {
	assert(predicted.rows == actual.rows);
	int t = 0;
	int f = 0;
	for(int i = 0; i < actual.rows; i++) {
		float p = predicted.at<float>(i,0);
		float a = actual.at<float>(i,0);
		if((p >= 0.0 && a >= 0.0) || (p <= 0.0 &&  a <= 0.0)) {
			t++;
		} else {
			f++;
		}
	}
	return (t * 1.0) / (t + f);
}

// plot data and class
void plot_binary(cv::Mat& data, cv::Mat& classes, string name) {
	cv::Mat plot(size, size, CV_8UC3);
	plot.setTo(cv::Scalar(255.0,255.0,255.0));
	for(int i = 0; i < data.rows; i++) {

		float x = data.at<float>(i,0) * size;
		float y = data.at<float>(i,1) * size;

		if(classes.at<float>(i, 0) > 0) {
			cv::circle(plot, Point(x,y), 2, CV_RGB(255,0,0),1);
		} else {
			cv::circle(plot, Point(x,y), 2, CV_RGB(0,255,0),1);
		}
	}
	cv::imshow(name, plot);
}


void svm(cv::Mat& trainingData, cv::Mat& trainingClasses, cv::Mat& testData, cv::Mat& testClasses) {
	CvSVMParams param = CvSVMParams();

	param.svm_type = CvSVM::C_SVC;
	param.kernel_type = CvSVM::RBF; //CvSVM::RBF, CvSVM::LINEAR ...
	param.degree = 0; // for poly
	param.gamma = 20; // for poly/rbf/sigmoid
	param.coef0 = 0; // for poly/sigmoid

	param.C = 7; // for CV_SVM_C_SVC, CV_SVM_EPS_SVR and CV_SVM_NU_SVR
	param.nu = 0.0; // for CV_SVM_NU_SVC, CV_SVM_ONE_CLASS, and CV_SVM_NU_SVR
	param.p = 0.0; // for CV_SVM_EPS_SVR

	param.class_weights = NULL; // for CV_SVM_C_SVC
	param.term_crit.type = CV_TERMCRIT_ITER +CV_TERMCRIT_EPS;
	param.term_crit.max_iter = 1000;
	param.term_crit.epsilon = 1e-6;

	// SVM training (use train auto for OpenCV>=2.0)
	CvSVM svm(trainingData, trainingClasses, cv::Mat(), cv::Mat(), param);

	cv::Mat predicted(testClasses.rows, 1, CV_32F);

	for(int i = 0; i < testData.rows; i++) {
		cv::Mat sample = testData.row(i);

		float x = sample.at<float>(0,0);
		float y = sample.at<float>(0,1);

		predicted.at<float>(i, 0) = svm.predict(sample);
	}

	cout << "Accuracy_{SVM} = " << evaluate(predicted, testClasses) << endl;
	plot_binary(testData, predicted, "Predictions SVM");

	// plot support vectors
	if(plotSupportVectors) {
		cv::Mat plot_sv(size, size, CV_8UC3);
		plot_sv.setTo(cv::Scalar(255.0,255.0,255.0));

		int svec_count = svm.get_support_vector_count();
		for(int vecNum = 0; vecNum < svec_count; vecNum++) {
			const float* vec = svm.get_support_vector(vecNum);
			cv::circle(plot_sv, Point(vec[0]*size, vec[1]*size), 3 , CV_RGB(0, 0, 0));
		}
	cv::imshow("Support Vectors", plot_sv);
	}
}

char *cvtInt( char *str, int num)
{
        sprintf( str, "%d", num );
}


int main (int argc , char* argv[]){

	cv::Mat data = Mat(numTrainingPoints,2,CV_8UC1);
	cv::Mat testdata = Mat(numTestPoints,2,CV_8UC1);
	
	vector< vector < cv::Mat > > trainingData;
	vector< vector < cv::Mat> > testData;

	//int testData[numTestPoints][2];
	//int labelData[numTrainingPoints];

	Mat training_mat(1000,180*120,CV_32FC1);
	Mat trainingTest_mat(1000,180*120,CV_32FC1);

	cv::Mat labels = Mat(1000,1,CV_32FC1);
	cv::Mat labelstest = Mat(data.rows,1,CV_32FC1);

	char str[30];
	char str1[40];
	
	cv::Mat input;
	cv::Mat output;

	Mat tmp_dst( 180, 120, CV_8UC1 );
// leer los positivos
	Mat  descriptors_1;
	for (int i = 1; i < 100;i++ ){
		///////////////////////// LEEMOS POSITIVOS /////////////
		if (i < 500){
			char num[10];
			strcpy (str,"ball/ball");
			sprintf(num, "%d", i);
			strcat (str,num);
			strcat (str,".jpg");	  
			//puts (str);
			input  = imread(str, 0); //Load as grayscale
			cv::SiftFeatureDetector detector;
			std::vector<cv::KeyPoint> keypoints;
			detector.detect(input, keypoints);
			cv::SiftDescriptorExtractor extractor;
			
			extractor.compute( data, keypoints, descriptors_1);
			
			

			trainingData.push_back(data);
			labels.at<float>(i,0) = 1.0;
			/////////////////////// LEEMOS TEST DATA ///////////////7
			if (i < 250){
				char num[10];
				strcpy (str,"ball/ball");
				sprintf(num, "%d", i+500);
				strcat (str,num);
				strcat (str,".jpg");	  
				//	puts (str);
				input  = imread(str, 0); //Load as grayscale
				cv::SiftFeatureDetector detector;
				std::vector<cv::KeyPoint> keypoints;
				cv::SiftDescriptorExtractor extractor;
				detector.detect(input, keypoints);
				extractor.compute( testdata, keypoints, descriptors_1);
			
				testData.push_back(data);
				labelstest.at<float>(i,0) = 1.0;

 
    
			}
				
		}else {
			////// LEEMOS NEGATIVOS/////////////////////////////
			char num[10];
			strcpy (str1,"non-ball/img");
			sprintf(num, "%d", i);
			strcat (str1,num);
			strcat (str1,".jpg");	  
			//puts (str1);
			
			input  = cv::imread(str1, 0); //Load as grayscale
			cv::SiftFeatureDetector detector;
			std::vector<cv::KeyPoint> keypoints;
			detector.detect(input, keypoints);
			cv::SiftDescriptorExtractor extractor;
			detector.detect(input, keypoints);
			extractor.compute( data, keypoints, descriptors_1);
			
		   
			trainingData.push_back(data);
			labels.at<float>(i,0) = 0.0;	
//////////////////// LEEMOS TEST DATA ////////////////////////////

			//char num[10];
			strcpy (str1,"non-ball/img");
			sprintf(num, "%d", i);
			strcat (str1,num);
			strcat (str1,".jpg");	  
			//			puts (str1);
			
			input  = cv::imread(str1, 0); //Load as grayscale
				
			if (i > 750){
				cv::SiftFeatureDetector detector;
				std::vector<cv::KeyPoint> keypoints;
				detector.detect(input, keypoints);
				cv::SiftDescriptorExtractor extractor;
				detector.detect(input, keypoints);
				extractor.compute( tmp_dst, keypoints, descriptors_1);
				
				testData.push_back(testdata);
				labelstest.at<float>(i,0) = 0.0;
			}
			else {
				cv::SiftFeatureDetector detector;
				std::vector<cv::KeyPoint> keypoints;
				detector.detect(input, keypoints);
				cv::SiftDescriptorExtractor extractor;
				detector.detect(input, keypoints);
				extractor.compute( testdata, keypoints, descriptors_1);
				
				//	testData.push_back(keypoints);
				labelstest.at<float>(i,0) = 0.0;


			}
			
		}
		data.convertTo( training_mat.row(i), CV_32FC1 );
		//cv::drawKeypoints(input,trainingData.at(i-1), output);
	}

	cout << "por aqui"<<endl;
		
		// Add results to image and save.
	




		// cv::Mat trainingClasses (aux[i].rows,1, CV_32FC1);
 	  
	
	data = Mat(trainingData);
//	data.cv::Mat::convertTo(data, CV_32FC1);
	testdata = Mat(testData);
//	testdata.cv::Mat::convertTo(testdata, CV_32FC1);
	cv::Mat trainingClasses = labels;
	cv::Mat testClasses = labelstest;
	
	
	cv::imwrite("sift_result.jpg", output);



	plot_binary( training_mat, trainingClasses, "Training Data");
	plot_binary( trainingTest_mat, testClasses, "Test Data");


	svm( training_mat, trainingClasses,  trainingTest_mat, testClasses);


	cv::waitKey();







	///////////////////////////////////////////////


	
    return 0;

   


}
