#include "stdafx.h"
#include "MostraSuaCara.h"


MostraSuaCara::MostraSuaCara()
{
	cara = new cv::CascadeClassifier;
	boca = new cv::CascadeClassifier;
	olhoD = new cv::CascadeClassifier;
	olhoE = new cv::CascadeClassifier;
	nariz = new cv::CascadeClassifier;
	cara->load(caraXml);
	olhoD->load(olhoDXml);
	olhoE->load(olhoEXml);
	boca->load(bocaXml);
	nariz->load(narizXml);
	if (cara->empty()) { "std::cout<< erro ao abrir caraXml"; }
	if (boca->empty()) { "std::cout<< erro ao abrir bocaXml"; }
	if (olhoD->empty()) { "std::cout<< erro ao abrir olhoDXml"; }
	if (olhoE->empty()) { "std::cout<< erro ao abrir olhoEXml"; }
	if (nariz->empty()) { "std::cout<< erro ao abrir narizXml"; }
}

MostraSuaCara::~MostraSuaCara()
{

}

std::vector<cv::Rect> MostraSuaCara::pegaCara(cv::Mat& pretoBranco)
{
	cara->detectMultiScale(pretoBranco, coordenadas, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));	
	return coordenadas;
}

void MostraSuaCara::pegaAreas(cv::Mat& recorte, std::vector<cv::Rect>& coordenadasBoca, std::vector<cv::Rect>& coordenadasOlhoD, std::vector<cv::Rect>& coordenadasOlhoE, std::vector<cv::Rect>& coordenadasNariz)
{

	boca->detectMultiScale(recorte, coordenadasBoca, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	olhoD->detectMultiScale(recorte, coordenadasOlhoD, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	olhoE->detectMultiScale(recorte, coordenadasOlhoE, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	nariz->detectMultiScale(recorte, coordenadasNariz, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
		
}

void MostraSuaCara::pegaAreas(int* densidade, int tamanho, std::vector<int>& coordenadas)
{
	int antes = densidade[0] + densidade[1] + densidade[2];
	int depois = densidade[3] +  densidade[3]+ densidade[4];
	bool continuidade = false;
	//para pegar áreas do histograma em que nos locais em que o histograma dos 3 posteriores é reduzido com relação aos 3 anteriores
	for (int i = 3; i < tamanho -2; i++) {
		if ((continuidade == false) && ((depois - antes) < 0)) {
			coordenadas.push_back(i);			
			continuidade = true;
		}
		else {
			if ((continuidade == true) && ((depois - antes) > 0)) {
				if (i + 7 < tamanho) {
					coordenadas.push_back(i + 7);
					continuidade = false;
				}
				else {
					coordenadas.push_back(i+2);
					continuidade = false;
				}
			}

			antes = antes + densidade[i] - densidade[i-3];
			depois = depois + densidade[i+3] - densidade[i];	
			
		}
	}
}

void MostraSuaCara::pegaAreas2(int* densidade, int tamanho, std::vector<int>& coordenadas)
{

	/*int antes = densidade[0] + densidade[1];
	int depois = densidade[2] + densidade[3];*/
	bool sobe = false;
	bool desce = false;
	//para pegar áreas do histograma em que nos locais em que o histograma dos 3 posteriores é reduzido com relação aos 3 anteriores
	for (int i = 1; i < tamanho; i++) {
		if ((desce == false) && ((densidade[i] - densidade[i - 1]) < 0) ) {
			coordenadas.push_back(i);
			coordenadas.push_back(i + 1);
			desce = true;
		} 
		if ((desce == true) && ((densidade[i] - densidade[i - 1]) > 0)) {				
			coordenadas.push_back(i);
			coordenadas.push_back(i + 1);
			desce = false;
		}
	
		if ((sobe == false) && ((densidade[i] - densidade[i - 1]) > 0) ) {
			coordenadas.push_back(i);
			coordenadas.push_back(i + 1);
			sobe = true;
		}
		if ((sobe == true) && ((densidade[i] - densidade[i - 1]) < 0)) {
			coordenadas.push_back(i);
			coordenadas.push_back(i + 1);
			sobe = false;
		}
		

				/*antes = antes + densidade[i] - densidade[i - 2];
				depois = depois + densidade[i + 2] - densidade[i];*/		
	}
}

void MostraSuaCara::pegaPontos()
{

}