/**
 * @author Manuel Mariscal
 * @date 29/09/2020
 * @file funciones.cc
 * @brief Implementación de las funciones.
 * @version 1.0
 */

#include "funciones.h"

void onMouse(int event, int x, int y, int flags, void *imagenes) {
	cv::Mat imagen_local = static_cast<cv::Mat *> (imagenes)[0].clone();
	static bool punto_a_ok = false, punto_b_ok = false;
	static bool levanta_boton = false, mueve_raton = false;
	static cv::Point punto_a, punto_b;

	if (punto_a_ok  && !punto_b_ok) {
		if (event == cv::EVENT_MOUSEMOVE) {
			cv::rectangle(imagen_local, punto_a, cv::Point(x, y), cv::Scalar(5,252,116));
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
			cv::rectangle(imagen_local, plano_ab, cv::Scalar(5,252,116));
			setGrises(plano_ab, static_cast<cv::Mat *> (imagenes));
		}
	} else if (event == cv::EVENT_LBUTTONDOWN) {
		punto_a_ok = true;
		punto_a.x = x;
		punto_a.y = y;
	}
}

void onMousePoligono(int event, int x, int y, int flags, void *imagenes) {
	static cv::Mat imagen_local_estatica = static_cast<cv::Mat *> (imagenes)[0].clone();
	cv::Mat imagen_local = imagen_local_estatica.clone();
	static std::vector<cv::Point> puntos;
	static bool ok = false;

	if (!ok) {
		if (event == cv::EVENT_MOUSEMOVE && !puntos.empty()) {
			cv::line(imagen_local, puntos.back(), cv::Point(x,y), cv::Scalar(5,252,116));
			cv::imshow("IMG", imagen_local);
		}

		if (event == cv::EVENT_LBUTTONDOWN) {
			if (!puntos.empty()) 
				cv::line(imagen_local_estatica, puntos.back(), cv::Point(x,y), cv::Scalar(5,252,116));

			puntos.push_back(cv::Point(x,y));
		}

		if (event == cv::EVENT_RBUTTONUP && puntos.size() > 2) {
			setGrises(puntos, static_cast<cv::Mat *> (imagenes));
			ok = true;
		}
	}
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

void setGrises(std::vector<cv::Point> &puntos, cv::Mat *imagenes) {
	cv::Mat imagen_local = imagenes[0].clone();

	for (int i = 0; i < imagen_local.rows; ++i) {

		// cv::Mat::ptr<T>(int r): Forma eficiente y rápida de iterar sobre 
		// píxeles en un objeto para obtener un puntero al principio de la fila
		cv::Vec3b *ptr = imagen_local.ptr<cv::Vec3b>(i);

		for (int j = 0; j < imagen_local.cols; ++j) {
			if (cv::pointPolygonTest(cv::InputArray(puntos), cv::Point(j, i), 
				false) == -1) {
				
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
