#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <iostream>
#include <exception>

//Includes para OpenCV, Descomentar según los módulo utilizados.
#include <opencv2/core/core.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/**
 * [onMouse Permite la selección de un rectangulo de dos formas distintas:
 * 				1. Seleccionando dos puntos sobre la imagen.
 * 				2. De forma interactiva arrastrando el ratón.
 * 			Una vez seleccionado el rectangulo, no se podrá cambiar la seleccion.
 * ]
 * @param event    [description]
 * @param x        [description]
 * @param y        [description]
 * @param flags    [description]
 * @param imagenes [description]
 */
void onMouse(int event, int x, int y, int flags, void *imagenes);


void onMousePoligono(int event, int x, int y, int flags, void *imagenes);

void setGrises(cv::Rect plano_ab, cv::Mat *imagenes);

#endif