#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"

#include "camera.h" //para fim de debugar, pode ser retirado futuramente

class Tratamentos
{
public:
	Tratamentos();
	~Tratamentos();

	void paraPretoBranco(cv::Mat& cor, cv::Mat& peb);
	void colocaBarraLimiar(cv::Mat&); //pega os pontos de interesse na face
	void pegaHistograma(cv::Mat&, int* histH, int* histV); //devolve dois vetores com os valores do histograma por linha e coluna
	void desenhaHistograma(cv::Mat&, int* histH, int* histV); //desenha o histograma na matriz
	void desenhaCirculo(cv::Mat& imagem, cv::Point coordenadas);

};

