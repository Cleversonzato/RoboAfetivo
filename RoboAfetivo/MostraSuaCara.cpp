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

void MostraSuaCara::pegaPontos(cv::Mat& recorte, std::vector<cv::Rect>& coordenadasBoca, std::vector<cv::Rect>& coordenadasOlhoD, std::vector<cv::Rect>& coordenadasOlhoE, std::vector<cv::Rect>& coordenadasNariz)
{
	
	boca->detectMultiScale(recorte, coordenadasBoca, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	olhoD->detectMultiScale(recorte, coordenadasOlhoD, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	olhoE->detectMultiScale(recorte, coordenadasOlhoE, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	nariz->detectMultiScale(recorte, coordenadasNariz, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));
	
}
