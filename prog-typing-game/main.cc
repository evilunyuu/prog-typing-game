#include <iostream>

int main(int argc, char **argv)
{
	try {


	} catch (const std::exception& e) {
		std::cout <<
				"An exception has occured:" << std::endl <<
				e.what() << std::endl;
		return 1;
	} catch (...) {
		std::cout <<
				"An unknown exception has occured!" << std::endl;
		return 2;
	}

	return 0;
}
