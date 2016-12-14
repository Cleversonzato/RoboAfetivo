#include "stdafx.h"
#include "Tratamentos.h"


Tratamentos::Tratamentos()
{
}


Tratamentos::~Tratamentos()
{
}


void Tratamentos::paraPretoBranco(cv::Mat& cor, cv::Mat& peb)
{
	cv::cvtColor(cor, peb, cv::COLOR_RGB2GRAY);
}

void Tratamentos::pegaCaracteristicas(cv::Mat& parte, cv::String tipo)
{
	
	int pos = 1;	
	cv::Mat temp, temp2;
	cv::putText(parte, tipo, cv::Point(5,5), cv::FONT_HERSHEY_COMPLEX, 0.25, cv::Scalar(255, 255, 255), 1, cv::LINE_AA);

	cv::createTrackbar("barra", Camera::janela, &pos, 255);
	do {
		double local = (double) pos;
		cv::threshold(parte, temp, local, 255, 0);
		
		pos = cvGetTrackbarPos("barra", "Reconhecimento Facial");		
		cv::hconcat(parte, temp, temp2);		
		cv::imshow(Camera::janela, temp2);
		
	} while (cv::waitKey(1)!=27); //pressione esc para continuar
}
