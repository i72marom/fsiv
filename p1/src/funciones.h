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
 * [onMouse description]
 * @param event    [description]
 * @param x        [description]
 * @param y        [description]
 * @param flags    [description]
 * @param imagenes [description]
 */
void onMouse(int event, int x, int y, int flags, void *imagenes);

void setGrises(cv::Rect plano_ab, cv::Mat *imagenes);

#endif