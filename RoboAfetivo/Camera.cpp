#include "stdafx.h"
#include "Camera.h"

const std::string Camera::janela = "Reconhecimento Facial";

void Camera::mostraFrame(cv::Mat& frame)
{
	cv::imshow(janela, frame);
	cv::waitKey(-1);
}


Camera::Camera()
{	
}

Camera::~Camera()
{
	captura.release();
	cv::destroyAllWindows();
}

void Camera::preparaCamera()
{
	captura.open(localCamera);
	if (!captura.isOpened()) 
	{ std::cout << "problemas na camera"; }
	
}


void Camera::gravando()
{
	MostraSuaCara *identificador = new MostraSuaCara;
	Tratamentos *alteracao = new Tratamentos;

	std::vector<cv::Rect> coordenadas, coordenadasOlhoD, coordenadasOlhoE, coordenadasBoca, coordenadasNariz;
	cv::Mat pretoBranco, caracteristicas;
		
	cv::namedWindow(janela, CV_WINDOW_NORMAL);
	preparaCamera();

	do {	
		captura >> frame;
		//tratamento inicial das imagens
		alteracao->paraPretoBranco(frame, pretoBranco);

		//reconhecimento facial
		coordenadas = identificador->pegaCara(pretoBranco);

		for (size_t i = 0; i < coordenadas.size(); i++) {
			cv::rectangle(frame, coordenadas[i], cv::Scalar(250, 0, 0, 2)); //desenha o quadro azul na face
			
			identificador->pegaPontos(pretoBranco(coordenadas[i]), coordenadasBoca, coordenadasOlhoD, coordenadasOlhoE, coordenadasNariz);			
			
			for (size_t y = 0; y < coordenadasBoca.size(); y++) {
				coordenadasBoca[y].x = coordenadasBoca[y].x + coordenadas[i].x;
				coordenadasBoca[y].y = coordenadasBoca[y].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasBoca[y], cv::Scalar(0, 250, 0, 4)); //desenha o quadro verde na boca
				alteracao->pegaCaracteristicas(pretoBranco(coordenadasBoca[y]), "boca");
			}
			for (size_t j = 0; j < coordenadasOlhoD.size(); j++) {
				coordenadasOlhoD[j].x = coordenadasOlhoD[j].x + coordenadas[i].x;
				coordenadasOlhoD[j].y = coordenadasOlhoD[j].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasOlhoD[j], cv::Scalar(0, 0, 250, 4)); //desenha o quadro vermelho no olhoD
				alteracao->pegaCaracteristicas(pretoBranco(coordenadasOlhoD[j]), "olho Direito");
			}
			for (size_t w = 0; w < coordenadasOlhoE.size(); w++) {
				coordenadasOlhoE[w].x = coordenadasOlhoE[w].x + coordenadas[i].x;
				coordenadasOlhoE[w].y = coordenadasOlhoE[w].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasOlhoE[w], cv::Scalar(0, 0, 250, 4)); //desenha o quadro vermelho no olhoE
				alteracao->pegaCaracteristicas(pretoBranco(coordenadasOlhoE[w]), "olho Esquerdo");
			}
			for (size_t z = 0; z < coordenadasNariz.size(); z++) {
				coordenadasNariz[z].x = coordenadasNariz[z].x + coordenadas[i].x;
				coordenadasNariz[z].y = coordenadasNariz[z].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasNariz[z], cv::Scalar(100, 100, 100, 4)); //desenha o quadro cinza no nariz
				alteracao->pegaCaracteristicas(pretoBranco(coordenadasNariz[z]), "nariz");
			}

		}
		cv::imshow(janela, frame);
	} while (cvWaitKey(1) != 13);
	delete identificador;
	
	
}



