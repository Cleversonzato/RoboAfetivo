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

void Tratamentos::borrar(cv::Mat& imagem) {
	cv::blur(imagem, imagem, cv::Size(7, 7));

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
	} while (cv::waitKey(1)!=13); //pressione enter para continuar
	//Para remover a barra é necessário reiniciar a janela:
    //cv::destroyWindow(Camera::janela);
	//cv::namedWindow(Camera::janela, CV_WINDOW_NORMAL);

}

void Tratamentos::limiarOtsu(cv::Mat& imagem)
{
	cv::threshold(imagem, imagem, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	//cv::adaptiveThreshold(imagem, imagem, 255, CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 5, 3); 
	//Treshold adaptativo, para fins de comparação.
	
}

void Tratamentos::brilhoContraste(cv::Mat& imagem)
{
	//constantes da alteração do brilho e contraste da imagem.
	const double alfa= 10.0 ;
	const int beta = -50;


	cv::MatIterator_<uchar> it, end;
	for (it = imagem.begin<uchar>(), end = imagem.end<uchar>(); it != end; ++it) {
		*it = cv::saturate_cast<uchar>(alfa*(*it) + beta );
	}

}

void Tratamentos::pegaDensidade(cv::Mat& imagem, int* denH, int* denV )
{
	/*Note que é necessário inicializar os vetores deste método de acordo com a mat inicial,
	caso queira fazer dinamicamente, utilizar:
		int *denH, *denV;
		denH = new int[mat.rows];
		denV = new int[mat.cols]
	e lembrar de depois limpar os vetores
		delete[] denH;
		delete[] denV;
	*/
	int colunas = imagem.cols;
	int linhas = imagem.rows;

	uchar* p;	//ponteiro para a imagem
	p = imagem.ptr<uchar>(0);
	int y = 0;
	
	if (denH != 0) {
		//pega o histograma horizontal, visualizado na vertical
		for (int i = 0; i < linhas; i++) {
			denH[i] = 0;
			for (int j = 0; j < colunas; j++) {
				denH[i] = (int(p[y + j]) + denH[i]);
			}
			denH[i] = denH[i] / 255;
			y = y + colunas;
		}
	}

	if (denV != 0) {
		//pega o histograma vertical, visualizado na horizontal
		for (int i = 0; i < colunas; i++) {
			denV[i] = 0;
			y = i;			
			for (int j = 0; j < linhas; j++) {
				denV[i] = int(p[y]) + denV[i];
				y = y + colunas;
			}
			denV[i] = denV[i] / 255;
		}
	}
	
}

void Tratamentos::desenhaDensidade(cv::Mat& imagem, int* denH, int* denV )
{
	int colunas = imagem.cols;
	int linhas = imagem.rows;		
	//para comparar a densidade colorindo diferentemente

	if (denH != 0) {
		

		for (int i = 1; i < linhas; i++) {
	
			//aqui são consideradas as variações da densidade para atribuir cores. branco = redução com relação ao ultimo valor, preto = o resto.
			if ((denH[i-1] - denH[i]) > 0) {
				cv::line(imagem, cv::Point(denH[i], i), cv::Point(denH[i + 1], i + 1), cv::Scalar(255, 255, 255));
			}
			else {
				cv::line(imagem, cv::Point(denH[i], i), cv::Point(denH[i + 1], i + 1), cv::Scalar(0, 0, 0));
			}
			
		}
	}

	if (denV != 0) {
		
		for (int i = 1; i < colunas ; i++) {
						
			if ((denV[i-1] - denV[i]) > 0) {
				cv::line(imagem, cv::Point(i, linhas - denV[i]), cv::Point(i + 1, linhas - denV[i + 1]), cv::Scalar(255, 255, 255));
			}
			else {
				cv::line(imagem, cv::Point(i, linhas - denV[i]), cv::Point(i + 1, linhas - denV[i + 1]), cv::Scalar(0, 0, 0));
			}

		}
	}
}


void Tratamentos::desenhaCirculo(cv::Mat& imagem, cv::Point coordenadas)
{
	cv::circle(imagem, coordenadas, 3, cv::Scalar(0, 0, 0), -1, 8);		
}

void Tratamentos::desenhaRetangulo(cv::Mat& imagem, cv::Rect_<int> coordenadas)
{
	cv::rectangle(imagem, coordenadas, cv::Scalar(0, 250, 0, 4), 2);
}

