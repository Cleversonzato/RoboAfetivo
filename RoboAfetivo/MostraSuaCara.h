#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2\imgproc.hpp"

#include "Camera.h" //inlcuido para debugar, ver depois se precisa no final

class MostraSuaCara
{
public:
	MostraSuaCara();
	~MostraSuaCara();
	std::vector<cv::Rect> pegaCara(cv::Mat&);
	void pegaAreas(cv::Mat& recorte, std::vector<cv::Rect>& coordenadasBoca, std::vector<cv::Rect>& coordenadasOlhoD, std::vector<cv::Rect>& coordenadasOlhoE, std::vector<cv::Rect>& coordenadasNariz);
	void pegaPontos();

private:
	std::string caraXml = "C:\\Users\\cleve\\Documents\\Bibliotecas\\OpenCV\\build\\install\\etc\\haarcascades\\haarcascade_frontalface_alt2.xml";
	std::string olhoDXml = "C:\\Users\\cleve\\Documents\\Bibliotecas\\OpenCV\\build\\install\\etc\\haarcascades\\haarcascade_righteye_2splits.xml";
	std::string olhoEXml = "C:\\Users\\cleve\\Documents\\Bibliotecas\\OpenCV\\build\\install\\etc\\haarcascades\\haarcascade_lefteye_2splits.xml";
	std::string bocaXml = "C:\\Users\\cleve\\Documents\\Bibliotecas\\OpenCV\\build\\install\\etc\\haarcascades\\Mouth.xml";
	std::string narizXml = "C:\\Users\\cleve\\Documents\\Bibliotecas\\OpenCV\\build\\install\\etc\\haarcascades\\Nariz.xml";
	cv::CascadeClassifier *cara;
	cv::CascadeClassifier *olhoD;
	cv::CascadeClassifier *olhoE;
	cv::CascadeClassifier *boca;
	cv::CascadeClassifier *nariz;
	cv::Point p1, p2;
	std::vector<cv::Rect> coordenadas;	
	std::vector<cv::Point> pontos;
	
	
};

