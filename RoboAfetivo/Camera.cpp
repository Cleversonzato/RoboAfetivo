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
	//objetos
	MostraSuaCara *identificador = new MostraSuaCara;
	Tratamentos *alteracao = new Tratamentos;

	//cascade classifier
	std::vector<cv::Rect> coordenadas, coordenadasOlhoD, coordenadasOlhoE, coordenadasBoca, coordenadasNariz;
	cv::Mat pretoBranco, caracteristicas;

	//iniciando a captura e janela
	cv::namedWindow(janela, CV_WINDOW_NORMAL);
	preparaCamera();
	captura >> frame;

	//variaveis do calculo de densidade
	int *denH, *denV;
	denH = new int[frame.rows];	
	denV = new int[frame.cols];

	cv::Mat tep;	//apagar ou melhorar
	std::vector<int> partesH, partesV;
	
	do {	
		captura >> frame;
		//tratamento inicial das imagens
		alteracao->paraPretoBranco(frame, pretoBranco);		

		//reconhecimento facial
		coordenadas = identificador->pegaCara(pretoBranco);	 

		for (int i = 0; i < coordenadas.size(); i++) {

			mostraFrame(pretoBranco);			
			//apagar
			tep = pretoBranco(coordenadas[i]).clone();			
			alteracao->brilhoContraste(tep);
			alteracao->borrar(tep);									
							
			//alteracao->colocaBarraLimiar(pretoBranco(coordenadas[i]));
			// alteracao->limiarOtsu(tep);			
			alteracao->pegaDensidade(tep, denH,0);	
			//alteracao->desenhaDensidade(tep, denH, 0);
			identificador->pegaAreas(denH, tep.rows, partesH);
			
			mostraFrame(tep);

			for (int j = 0; j < (partesH.size() - 1); j = j + 2) {				
				alteracao->pegaDensidade(tep(cv::Rect_<int>(0, partesH[j], tep.cols, (partesH[j + 1] - partesH[j]))), 0, denV);
				alteracao->desenhaDensidade(tep(cv::Rect_<int>(0, partesH[j], tep.cols, (partesH[j + 1] - partesH[j]))), 0, denV);
				identificador->pegaAreas2(denV, tep.cols, partesV);

				std::cout << j << " tamanho do array H: " << partesH.size() << " quadrado: " << cv::Rect_<int>(0, partesH[j], tep.cols, (partesH[j + 1] - partesH[j])) << '\n';

				for (int y = 0; y < (partesV.size() - 1); y = y + 2) {					
					std::cout << j << " tamanho do array V: " << partesV.size() << " quadrado: " << cv::Rect_<int>(partesV[y], partesH[j], partesV[y + 1] - partesV[y], (partesH[j + 1] - partesH[j])) << '\n';
					alteracao->desenhaRetangulo(tep, cv::Rect_<int>(partesV[y], partesH[j], partesV[y+1]-partesV[y], (partesH[j + 1] - partesH[j])));
				}
				partesV.erase(partesV.begin(), partesV.end());
			}
			
			partesH.erase(partesH.begin(), partesH.end());
		/*
			for (int j = 0; j < (partesH.size() - 1); j = j + 2) {
				std::cout << j << " tamanho do array H: " << partesH.size() << " quadrado: " << cv::Rect_<int>(0, partesH[j], tep.cols, (partesH[j + 1] - partesH[j])) << '\n';
				alteracao->desenhaRetangulo(tep, cv::Rect_<int>(0, partesH[j], tep.cols, (partesH[j + 1] - partesH[j])));
			}
			partesH.erase(partesH.begin(), partesH.end());
			
			for (int y = 0; y < partesV.size() -1; y = y + 2) {	
				std::cout << y << " tamanho do array V: " << partesV.size() << " quadrado: " << cv::Rect_<int>(partesV[y], 0, (partesV[y + 1] - partesV[y]), tep.rows) << '\n';
				alteracao->desenhaRetangulo(tep, cv::Rect_<int>(partesV[y], 0, (partesV[y + 1] - partesV[y]), tep.rows ));
			}
			partesV.erase(partesV.begin(), partesV.end());								
			*/
			mostraFrame(tep);

			//fim apagar

			/*
			identificador->pegaAreas(pretoBranco(coordenadas[i]), coordenadasBoca, coordenadasOlhoD, coordenadasOlhoE, coordenadasNariz);			
			
			for (size_t y = 0; y < coordenadasBoca.size(); y++) {
				coordenadasBoca[y].x = coordenadasBoca[y].x + coordenadas[i].x;
				coordenadasBoca[y].y = coordenadasBoca[y].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasBoca[y], cv::Scalar(0, 250, 0, 4)); //desenha o quadro verde na boca
				alteracao->colocaBarraLimiar(pretoBranco(coordenadasBoca[y]));
			}
			for (size_t j = 0; j < coordenadasOlhoD.size(); j++) {
				coordenadasOlhoD[j].x = coordenadasOlhoD[j].x + coordenadas[i].x;
				coordenadasOlhoD[j].y = coordenadasOlhoD[j].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasOlhoD[j], cv::Scalar(0, 0, 250, 4)); //desenha o quadro vermelho no olhoD
				alteracao->colocaBarraLimiar(pretoBranco(coordenadasOlhoD[j]));
			}
			for (size_t w = 0; w < coordenadasOlhoE.size(); w++) {
				coordenadasOlhoE[w].x = coordenadasOlhoE[w].x + coordenadas[i].x;
				coordenadasOlhoE[w].y = coordenadasOlhoE[w].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasOlhoE[w], cv::Scalar(0, 0, 250, 4)); //desenha o quadro vermelho no olhoE
				alteracao->colocaBarraLimiar(pretoBranco(coordenadasOlhoE[w]));
			}
			for (size_t z = 0; z < coordenadasNariz.size(); z++) {
				coordenadasNariz[z].x = coordenadasNariz[z].x + coordenadas[i].x;
				coordenadasNariz[z].y = coordenadasNariz[z].y + coordenadas[i].y;
				//cv::rectangle(frame, coordenadasNariz[z], cv::Scalar(100, 100, 100, 4)); //desenha o quadro cinza no nariz
				alteracao->colocaBarraLimiar(pretoBranco(coordenadasNariz[z]));
			}			*/
		}
		cv::imshow(janela, frame);
	} while (cvWaitKey(1) != 13);
	
	//limpeza
	delete identificador;
	delete alteracao;
	delete[] denH;
	delete[] denV;
	
		
}

void Camera::salvaMat(std::string destino, cv::Mat& imagem)
{
	cv::imwrite(destino,imagem);
}


