#include "texturetextwindow.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	try
	{
		ogl::Initialize(argc, argv, {} /*default context*/);
		ogl::CreateWindow("test title", 800, 600, false);

		const string imageFilename = argc == 1 ?
					"./" + string{"resources/test.dds"} : string{argv[1]};

		TextureTestWindow window(imageFilename);
		ogl::RunMainLoop(window);
		ogl::Terminate();

		return EXIT_SUCCESS;
	}
	catch (const std::exception& exc)
	{
		cerr << exc.what() << endl;
		ogl::Terminate();
		return EXIT_FAILURE;
	}
}
