#include "funciones.h"

void onMouse(int event, int x, int y, int flags, void *imagenes) {
	cv::Mat imagen_local = static_cast<cv::Mat *> (imagenes)[0].clone();
	static bool punto_a_ok = false;
	static cv::Point punto_a, punto_b;

	if (event == cv::EVENT_LBUTTONDOWN && punto_a_ok) {
		punto_b.x = x;
		punto_b.y = y;
		cv::Rect plano_ab(punto_a, punto_b);
		cv::rectangle(imagen_local, plano_ab, cv::Scalar(1));
		setGrises(plano_ab, static_cast<cv::Mat *> (imagenes));
	} else if (event == cv::EVENT_LBUTTONDOWN) {
		punto_a_ok = true;
		punto_a.x = x;
		punto_a.y = y;
	} 
}

void onMouseMove(int event, int x, int y, int flags, void *imagenes) {
	cv::Mat imagen_local = static_cast<cv::Mat *> (imagenes)[0].clone();
	static bool punto_a_ok = false;
	static cv::Point punto_a, punto_b;

	if (event == cv::EVENT_LBUTTONDOWN) {
		punto_a_ok = true;
		punto_a.x = x;
		punto_a.y = y;
	} 

	if (event == cv::EVENT_MOUSEMOVE && punto_a_ok) {
		punto_b.x = x;
		punto_b.y = y;
		cv::rectangle(imagen_local, punto_a, punto_b, cv::Scalar(129));
		cv::imshow("Imagen", imagen_local);
	}

	/*if (event == cv::EVENT_LBUTTONUP) {
		if (event == cv::EVENT_LBUTTONDOWN) {
			std::cout << "2" << std::endl;
			punto_b.x = x;
			punto_b.y = y;
			cv::Rect box(punto_a, punto_b);
			cv::rectangle(imagen_local, box, cv::Scalar(129));
		}
	}*/
}

void setGrises(cv::Rect plano_ab, cv::Mat *imagenes) {
	cv::Mat localImg = imagenes[0].clone();

	for (int i = 0; i < localImg.rows; i++)
	{

		//Vector de 3 bytes
		cv::Vec3b *imgrow = localImg.ptr<cv::Vec3b>(i);
		for (int j = 0; j < localImg.cols; j++)
		{
			/*
			Con esta comprobación le hacemos el cambio a solo las partes que no están en el área
			seleccionada

			la función cv::Rect.contains() recibe un punto y define si ese punto está o no
			dentro del rectángulo definido
			*/
			if (!plano_ab.contains(cv::Point(j, i)))
			{
				/*
				El uchar es un unsigned char en el cual está definido el valor de cada
				uno de los canales de la imagen, en este caso BGR
				*/
				uchar B = imgrow[j][0];
				uchar G = imgrow[j][1];
				uchar R = imgrow[j][2];

				uchar gray = (B + G + R) / 3;

				imgrow[j][0] = gray;
				imgrow[j][1] = gray;
				imgrow[j][2] = gray;
			}
		}
	}
	cv::imshow("Imagen", localImg);
	imagenes[1] = localImg.clone();
}
