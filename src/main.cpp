/**
 *
 *
 *
**/
extern void test_maths();
extern void test_sockets();
extern void test_opengl_window();
extern void test_opengl_bonerig();

#include <iostream>

int main(void)
{
	/////////////////////////////////////////////////////////
	std::cout << "//                 //" << std::endl;
	std::cout << "// Framework tests //" << std::endl;
	std::cout << "//                 //" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_maths();
	return 0;
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: OpenGL window" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	//test_opengl_window();
	
	/////////////////////////////////////////////////////////
	std::cout << "**** Test completed: OpenGL window" << std::endl;
	/////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: OpenGL animated bone rig" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	test_opengl_bonerig();
	
	/////////////////////////////////////////////////////////
	std::cout << "**** Test completed: OpenGL window" << std::endl;
	/////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	std::cout << "****" << std::endl;
	std::cout << "**** TEST: Sockets" << std::endl;
	std::cout << "****" << std::endl;
	std::cout << "" << std::endl;
	/////////////////////////////////////////////////////////
	
	//test_sockets();
	
	/////////////////////////////////////////////////////////
	std::cout << "**** Test completed: Sockets" << std::endl;
	/////////////////////////////////////////////////////////
	
	/////////////////////////////////////////////////////////
	std::cout << "//                 //" << std::endl;
	std::cout << "// Tests completed //" << std::endl;
	std::cout << "//                 //" << std::endl;
	/////////////////////////////////////////////////////////
	
	std::cout << "Press enter to exit" << std::endl;
	std::getchar();
	return 0;
}
