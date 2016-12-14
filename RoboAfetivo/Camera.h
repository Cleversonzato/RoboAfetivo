#pragma once
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "MostraSuaCara.h"
#include "Tratamentos.h"


class Camera
{
public:
	Camera();
	~Camera();
	void gravando(); //o "main loop" do programa
	static void mostraFrame(cv::Mat&); //metodo static para mostra imagens em qualquer momento, util para debugar e ver o que acontece
	static const std::string janela; // nome da janela a ser aberta
	

private:
	void preparaCamera();
		
	cv::Mat frame;
	const int localCamera = 0; //camera a ser lida pelo programa. 0 é a camera padrão
	cv::VideoCapture captura;
		
};

