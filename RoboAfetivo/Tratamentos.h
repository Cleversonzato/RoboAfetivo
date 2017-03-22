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
	void borrar(cv::Mat&);
	void colocaBarraLimiar(cv::Mat&); //pega os pontos de interesse na face com um limiar/treshold padrão do opencv
	void limiarOtsu(cv::Mat& imagem); //pega o limiar/treshold "Otsu"
	void Tratamentos::brilhoContraste(cv::Mat& imagem); //altera o brilho e contraste da imagem.
	void pegaDensidade(cv::Mat&, int* denH =0 , int* denV =0); //devolve dois vetores com os valores da densidade por linha e coluna, deixe zero para desenhar só uma direção
	void desenhaDensidade(cv::Mat&, int* denH =0, int* denV = 0 ); //desenha o histograma na matriz, deixe o int*=0 para não calcular a densidade em uma direção
	void desenhaCirculo(cv::Mat& imagem, cv::Point coordenadas);
	void desenhaRetangulo(cv::Mat& imagem, cv::Rect_<int> coordenadas);
	
};

