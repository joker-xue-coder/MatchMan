#ifndef __COMMON_H__
#define __COMMON_H__
#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#define PrintLog(log) std::cout<<std::endl<<"Log:"<<(log)<<std::endl<<"Line:"<<__LINE__<<std::endl<<"File:"<<__FILE__<<std::endl<<std::endl;


#endif // !__COMMON_H__
