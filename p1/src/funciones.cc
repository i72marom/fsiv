#include "funciones.h"

void onMouse(int event, int x, int y, int flags, void *imagenes) {
	cv::Mat imagen_local = static_cast<cv::Mat *> (imagenes)[0].clone();
	static bool punto_a_ok = false, punto_b_ok = false;
	static bool levanta_boton = false, mueve_raton = false;
	static cv::Point punto_a, punto_b;

	if (punto_a_ok  && !punto_b_ok) {
		if (event == cv::EVENT_MOUSEMOVE) {
			cv::rectangle(imagen_local, punto_a, cv::Point(x, y), cv::Scalar(1));
			cv::imshow("IMG", imagen_local);
		}

		if (event == cv::EVENT_MOUSEMOVE && !levanta_boton) mueve_raton = true;
		else if (event == cv::EVENT_LBUTTONUP && !mueve_raton) levanta_boton = true;
		else if ((event == cv::EVENT_LBUTTONUP && mueve_raton) ||
			(event == cv::EVENT_LBUTTONDOWN && levanta_boton)) {
			punto_b_ok = true;
			punto_b.x = x;
			punto_b.y = y;
			cv::Rect plano_ab(punto_a, punto_b);
			cv::rectangle(imagen_local, plano_ab, cv::Scalar(1));
			setGrises(plano_ab, static_cast<cv::Mat *> (imagenes));
		}
	} else if (event == cv::EVENT_LBUTTONDOWN) {
		punto_a_ok = true;
		punto_a.x = x;
		punto_a.y = y;
	}
}

void onMousePoligono(int event, int x, int y, int flags, void *imagenes) {
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
	cv::Mat imagen_local = imagenes[0].clone();

	for (int i = 0; i < imagen_local.rows; ++i) {

		// cv::Mat::ptr<T>(int r): Forma eficiente y rápida de iterar sobre 
		// píxeles en un objeto para obtener un puntero al principio de la fila
		cv::Vec3b *ptr = imagen_local.ptr<cv::Vec3b>(i);

		for (int j = 0; j < imagen_local.cols; ++j) {
			if (!plano_ab.contains(cv::Point(j, i))) {
				uchar gris = (ptr[j][0] + ptr[j][1] + ptr[j][2]) / 3;

				ptr[j][0] = gris;
				ptr[j][1] = gris;
				ptr[j][2] = gris;
			}
		}
	}
	
	cv::imshow("IMG", imagen_local);
	imagenes[1] = imagen_local.clone();
}
