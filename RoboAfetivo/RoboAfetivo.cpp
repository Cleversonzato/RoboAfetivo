// RoboAfetivo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
/* includes da utilização do programa com fotos
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/imgproc.hpp"
*/

#include "Camera.h"

int main()
{
	/*descomente abaixo para usar o programa com fotos*/

	/*apagar
	cv::Mat temp, tempPB;
	cv::namedWindow("janela", CV_WINDOW_NORMAL);
	temp = cv::imread("C:\\Users\\cleve\\OneDrive\\Documentos\\images3.jpg");
	Tratamentos *trat = new Tratamentos;
	trat->paraPretoBranco(temp, tempPB);
	trat->pegaHistograma(tempPB);
	cv::imshow("janela", tempPB);
	cv::waitKey();
	*/
	
	
	Camera webcam;
	webcam.gravando();

	
    return 0;
}

