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

void Tratamentos::colocaBarraLimiar(cv::Mat& parte)
{		
	int pos = 1;	
	cv::Mat temp, temp2;
	cv::createTrackbar("barra", Camera::janela, &pos, 255);
		
	do {
		double local = (double) pos;
		cv::threshold(parte, temp, local, 255, 0);
		pos = cvGetTrackbarPos("barra", "Reconhecimento Facial");	
		cv::hconcat(parte, temp, temp2);
		cv::imshow(Camera::janela, temp2);
	} while (cv::waitKey(1)!=27); //pressione esc para continuar
	
}

void Tratamentos::pegaHistograma(cv::Mat& imagem, int* histH, int* histV)
{
	/*Note que é necessário inicializar os vetores deste método de acordo com a mat inicial,
	caso queira fazer dinamicamente, utilizar:
		int *histH, *histV;
		histH = new int[mat.rows];
		histV = new int[mat.cols]
	e lembrar de depois limpar os vetores
		delete[] histH;
		delete[] histV;
	*/
	int colunas = imagem.cols;
	int linhas = imagem.rows;

	uchar* p;	//ponteiro para a imagem
	p = imagem.ptr<uchar>(0);
	int y = 0;
	
	//pega o histograma horizontal, visualizado na vertical
	for (int i = 0; i < linhas; i++) {
		histH[i] = 0;
		for (int j = 0; j < colunas; j++) {
			histH[i] = (int(p[y + j]) + histH[i]);					
		}
		histH[i] = histH[i] / 255;		
		y = y + colunas;
	}

	//pega o histograma vertical, visualizado na horizontal
	for (int i = 0; i < colunas; i++) {
		histV[i] = 0;
		y = i;
		//p = imagem.ptr<uchar>(i,0);
		for (int j = 0; j < linhas; j++) {
			histV[i] = int(p[y]) + histV[i];
			y = y + colunas;
		}
		histV[i] = histV[i] / 255;		
	}
		
}

void Tratamentos::desenhaHistograma(cv::Mat& imagem, int* histH, int* histV)
{
	int colunas = imagem.cols;
	int linhas = imagem.rows;
	const int limiar = 1; //variavel que define quanto de variação do histograma será considerado como "ponto"	

/*	for (int i = 0; i < linhas -1; i++) {
		cv::line(imagem, cv::Point(histH[i], i),cv::Point(histH[i+1], i+1), cv::Scalar(255,255,255) );
		if (std::abs(histH[i] - histH[i+1]) > limiar) {			
			desenhaCirculo(imagem, cv::Point(histH[i+1], i+1));
		}		
	}*/
	
	int antes, depois;//para comparar o histograma de acordo com os 3 pixels anteriores e os 3 posteriores

	antes = histH[0] + histH[1] + histH[2];
	depois = histH[3] + histH[4] + histH[5];
	for (int i = 3; i < linhas - 3; i++) {
		cv::line(imagem, cv::Point(histH[i], i), cv::Point(histH[i + 1], i + 1), cv::Scalar(255, 255, 255));
		/* Para marcar qualquer variação no histograma
		if (std::abs(histV[i] - histV[i + 1]) > limiar) {
		desenhaCirculo(imagem, cv::Point(i + 1, linhas - histV[i + 1]));  */

		if ((antes - depois) > 1) {
			desenhaCirculo(imagem, cv::Point(histH[i], i));
		}
		antes = antes - histH[i - 3] + histH[i];
		depois = depois - histH[i] + histH[i + 3];
	}


	antes = histV[0] + histV[1] + histV[2];
	depois = histV[3] + histV[4] + histV[5];
	for (int i = 3; i < colunas - 3; i++) {
		cv::line(imagem, cv::Point(i, linhas - histV[i]), cv::Point(i+1, linhas - histV[i + 1]), cv::Scalar(255, 255, 255));
		/* Para qualquer marcar qualquer variação no histograma
		if (std::abs(histV[i] - histV[i + 1]) > limiar) {
			desenhaCirculo(imagem, cv::Point(i + 1, linhas - histV[i + 1]));  */	
		
		if ((antes - depois) > 1 ) {
			desenhaCirculo(imagem, cv::Point(i, linhas - histV[i]));		
		}
		antes = antes - histV[i - 3] + histV[i];
		depois = depois - histV[i] + histV[i + 3];
	}		
}

void Tratamentos::desenhaCirculo(cv::Mat& imagem, cv::Point coordenadas)
{
	cv::circle(imagem, coordenadas, 3, cv::Scalar(0, 0, 0), -1, 8);		
}