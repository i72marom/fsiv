/*!
  Esto es un esqueleto de programa para usar en las prácticas
  de Visión Artificial.

  Se supone que se utilizará OpenCV.

  Para compilar, puedes ejecutar:
	g++ -Wall -o esqueleto esqueleto.cc `pkg-config opencv --cflags --libs`

*/

#include "funciones.h"

const cv::String keys =
	"{help h usage ? |      | print this message   }"
	"{p 			 |      | ejecuta onMousePoligono   }"
	"{@image1        |      | image1 for compare   }"
	"{@image2        |<none>| image2 for compare   }"
	;

int main (int argc, char* const* argv) {
	int retCode=EXIT_SUCCESS;

	try {    

		cv::CommandLineParser parser(argc, argv, keys);
		parser.about("Application name v1.0.0");
		if (parser.has("help")) {
			parser.printMessage();
			return 0;
		}
		
		cv::String img1 = parser.get<cv::String>("@image1");
		cv::String img2 = parser.get<cv::String>("@image2");
		
		if (!parser.check()) {
			parser.printErrors();
			return 0;
		}

		// leo la imagen
		cv::Mat imagenes[2];
		imagenes[0] = cv::imread(img1, cv::IMREAD_COLOR);

		if (imagenes[0].empty()) {
			std::cerr << "Error: no he podido abrir el fichero '" << img1 << "'." << std::endl;
			return EXIT_FAILURE;
		}

		// creo la ventana
		cv::namedWindow("IMG");

		// visualizo la imagen
		cv::imshow("IMG", imagenes[0]);

		if (parser.has("p"))
			cv::setMouseCallback("IMG", onMousePoligono, (void *)&imagenes);
		else
			cv::setMouseCallback("IMG", onMouse, (void *)&imagenes);

		// Si se recibe una entrada distinta a ESC se guarda la imagen.
		if (cv::waitKey(0) != 27)
			cv::imwrite(img2, imagenes[1]); 

	}
	
	catch (std::exception& e)
	{
		std::cerr << "Capturada excepcion: " << e.what() << std::endl;
		retCode = EXIT_FAILURE;
	}
	
	return retCode;
}
