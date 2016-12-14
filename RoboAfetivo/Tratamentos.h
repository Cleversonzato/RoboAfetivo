#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2\imgproc.hpp"

#include "camera.h" //para fim de debugar, pode ser retirado futuramente

class Tratamentos
{
public:
	Tratamentos();
	~Tratamentos();

	void paraPretoBranco(cv::Mat& cor, cv::Mat& peb);
	void pegaCaracteristicas(cv::Mat&, cv::String tipo);

};


