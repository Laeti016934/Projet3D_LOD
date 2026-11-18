#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "shader.h"

GLuint load_shaders(const char* vertex_file_path, const char* fragment_file_path)
{
    GLuint vertexShaderID, fragmentShaderID;
    vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Reads the Vertex Shader code from the vertex shader file. Check the documentation of ifstream and stringstream to learn more.
    // https://en.cppreference.com/cpp/io/basic_ifstream : input operations on files
    // https://en.cppreference.com/cpp/io/basic_stringstream : input and output operations on string based streams
    //std:: means that the type/function is from the std namespace.
    std::string vertexShaderCode;
    std::ifstream vertexShaderStream(vertex_file_path, std::ios::in); //"in" is an enum found in the "ios" class of the "std" namespace.
    if(vertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << vertexShaderStream.rdbuf(); // "<<" is a C++ operator that can be implemented in any class like a normal function.
        vertexShaderCode = sstr.str();
        vertexShaderStream.close();
    }
    else
    {
        //We can still use printf in c++, though we often prefer to use the object std::cout, check bellow
        printf("Impossible to open %s. Maybe you're reading from the wrong directory.\n", vertex_file_path);
        getchar();
        exit(1);
    }

    // Reads the Fragment Shader code from the file
    std::string fragmentShaderCode;
    std::ifstream fragmentShaderStream(fragment_file_path, std::ios::in);
    if(fragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << fragmentShaderStream.rdbuf();
        fragmentShaderCode = sstr.str();
        fragmentShaderStream.close();
    }
    else
    {
        //Note the lack of \n.
        std::cout << "You got the vertex shader correct. How did you open the wrong fragment shader file : " << fragment_file_path << "?" << std::endl;
        getchar();
        exit(1);
    }

    GLint compileResult = GL_FALSE;
    int infoLogLength;

    // Compile shaders. Did you know shaders are compiled at run time, and not compile time?
    // Modern video games either pre-compile them at launch,
    // or they compile them little by little whenever they are flagged as needed.

    // Compile Vertex Shader.
    printf("Compiling shader : %s\n", vertex_file_path);
    // You can cast a std string into a char * (or char const * if you don't modify the pointer) using c_str().
    char const * VertexSourcePointer = vertexShaderCode.c_str();

    glShaderSource(vertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(vertexShaderID);

    // Checks Vertex Shader compile output.
    // Like most programs, compiling shaders can fail. These lines fetch the compile output and display it in the standard output.
    // glGetShaderiv() gives infos about a given shader object: https://registry.khronos.org/OpenGL-Refpages/es3.0/html/glGetShaderiv.xhtml
    glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &compileResult);
    glGetShaderiv(vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 )
    {
        std::vector<char> VertexShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(vertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    else
    {
        printf("Vertex shader of ID %d compiled successfully\n", vertexShaderID);
    }

    // Compile Fragment Shader.
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = fragmentShaderCode.c_str();
    glShaderSource(fragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(fragmentShaderID);

    // Check Fragment Shader compile output.
    glGetShaderiv(fragmentShaderID, GL_COMPILE_STATUS, &compileResult);
    glGetShaderiv(fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 )
    {
        std::vector<char> FragmentShaderErrorMessage(infoLogLength+1);
        glGetShaderInfoLog(fragmentShaderID, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    else
    {
        printf("Fragment shader of ID %d compiled successfully\n", fragmentShaderID);
    }

    // Link the program
    printf("Linking program\n");

    // Create a program whose id gets stored in ProgramID using glCreateProgram:
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glCreateProgram.xhtml
    // What ID do you think it is going to get? 0? 1? Something else?
    GLuint ProgramID = 0;
    ProgramID = glCreateProgram();

    // Attach the shaders to the program using glAttachShader:
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glAttachShader.xhtml
    glAttachShader(ProgramID, vertexShaderID);
    glAttachShader(ProgramID, fragmentShaderID);

    // Get OpenGL to deal with linking all shaders to your GPU using glLinkProgram.
    // https://registry.khronos.org/OpenGL-Refpages/gl4/html/glLinkProgram.xhtml
    glLinkProgram(ProgramID);

    // Check the status of the link.
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &compileResult);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if ( infoLogLength > 0 )
    {
        std::vector<char> ProgramErrorMessage(infoLogLength+1);
        glGetProgramInfoLog(ProgramID, infoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    else
    {
        printf("Program of ID %d linked successfully\n", ProgramID);
    }

    // Now that the program is linked to the GPU, we do not need the shader objects anymore.
    // Detach them with glDetachShader: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDetachShader.xhtml
    glDetachShader(ProgramID, vertexShaderID);
    glDetachShader(ProgramID, fragmentShaderID);

    // And remove them with glDeleteShader: https://registry.khronos.org/OpenGL-Refpages/gl4/html/glDeleteShader.xhtml
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return ProgramID;
}


