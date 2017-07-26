#pragma once
#include <stdint.h>
#include <vector>
#include <string>
#include <fstream>
#include <streambuf>

#if defined(_WIN64)
#define ASSET_SHADER_PATH "../../assets/shaders/"
#elif defined(BACK_ASSETS_PATH)
#define ASSET_SHADER_PATH "../assets/shaders/"
#else
#define ASSET_SHADER_PATH "assets/shaders/"
#endif

const std::vector<std::string> _paths = 
{
    "assets/shaders/",
    "../assets/shaders/",
    "../../assets/shaders/"
};

int32_t _create_program(std::string vs_shader, std::string fs_shader) {

    std::string vs_str = "";
    std::string fs_str = "";

    for( auto path : _paths ){
	    std::string vs_path = path + vs_shader;

	    std::ifstream vs_ifstream(vs_path);
        vs_str = std::string((std::istreambuf_iterator<char>(vs_ifstream)),
		    std::istreambuf_iterator<char>());

	    if (vs_str.size() != 0) break;
    }

    for( auto path : _paths ) {
	    std::string fs_path = path + fs_shader;
	    std::ifstream fs_ifstream(fs_path);
        fs_str = std::string((std::istreambuf_iterator<char>(fs_ifstream)),
		    std::istreambuf_iterator<char>());

	    if (fs_str.size() != 0) break;
    }

    if( vs_str.size() == 0 || fs_str.size() == 0 ){
        std::cout << "Shader not found! \n";
        return -1;
    }

	GLint vs = glCreateShader(GL_VERTEX_SHADER);
	GLint v_size = (GLint)strlen(vs_str.c_str());
	const char *vs_char = vs_str.c_str();
	glShaderSource(vs, 1, &vs_char, &v_size);
	glCompileShader(vs);

	GLchar* vs_shader_log = new GLchar[1024];
	glGetShaderInfoLog(vs, 1024, nullptr, vs_shader_log);
	if (strlen(vs_shader_log) != 0) {
		std::cout << "VS shader error: \n" << vs_shader_log << std::endl;
		delete[] vs_shader_log;
		return -1;
	}

	GLint fs = glCreateShader(GL_FRAGMENT_SHADER);
	GLint f_size = (GLint)strlen(fs_str.c_str());
	const char *fs_char = fs_str.c_str();
	glShaderSource(fs, 1, &fs_char, &f_size);
	glCompileShader(fs);

	GLchar* fs_shader_log = new GLchar[1024];
	glGetShaderInfoLog(fs, 1024, nullptr, fs_shader_log);
	if (strlen(fs_shader_log) != 0) {
		std::cout << "FS shader error: \n" << fs_shader_log << std::endl;
		delete[] vs_shader_log;
		delete[] fs_shader_log;
		return -1;
	}

	GLint program = glCreateProgram();
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);

	GLchar* info_log = new GLchar[1024];
	glGetProgramInfoLog(program, 1024, nullptr, info_log);
	if (strlen(info_log) != 0) {
		std::cout << "Program link error: \n" << info_log << std::endl;
		delete[] vs_shader_log;
		delete[] fs_shader_log;
		delete[] info_log;
		return -1;
	}

	delete[] vs_shader_log;
	delete[] fs_shader_log;
	delete[] info_log;

	return program;
}

void GLAPIENTRY opengl_error_callback(
	GLenum source,
	GLenum type,
	GLuint id,
	GLenum severity,
	GLsizei length,
	const GLchar* message,
	const void* userParam ) {
	std::string s_source = "";
	std::string s_type = "";
	std::string s_severity = "";
	std::string s_message = std::string( ( char* ) message );

	switch( source ) {
	case GL_DEBUG_SOURCE_API:             s_source += "GL_DEBUG_SOURCE_API";             break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   s_source += "GL_DEBUG_SOURCE_WINDOW_SYSTEM";   break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: s_source += "GL_DEBUG_SOURCE_SHADER_COMPILER"; break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     s_source += "GL_DEBUG_SOURCE_THIRD_PARTY";     break;
	case GL_DEBUG_SOURCE_APPLICATION:     s_source += "GL_DEBUG_SOURCE_APPLICATION";     break;
	case GL_DEBUG_SOURCE_OTHER:           s_source += "GL_DEBUG_SOURCE_OTHER";           break;
	default:                              s_source += "UNKNOWN SOURCE!";                 break;
	}

	switch( type ) {
	case GL_DEBUG_TYPE_ERROR:               s_source += "GL_DEBUG_TYPE_ERROR";               break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:	s_source += "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR"; break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  s_source += "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR";  break;
	case GL_DEBUG_TYPE_PORTABILITY:         s_source += "GL_DEBUG_TYPE_PORTABILITY";         break;
	case GL_DEBUG_TYPE_PERFORMANCE:         s_source += "GL_DEBUG_TYPE_PERFORMANCE";         break;
	case GL_DEBUG_TYPE_MARKER:              s_source += "GL_DEBUG_TYPE_MARKER";              break;
	case GL_DEBUG_TYPE_PUSH_GROUP:          s_source += "GL_DEBUG_TYPE_PUSH_GROUP";          break;
	case GL_DEBUG_TYPE_POP_GROUP:           s_source += "GL_DEBUG_TYPE_POP_GROUP";           break;
	case GL_DEBUG_TYPE_OTHER:               s_source += "GL_DEBUG_TYPE_OTHER";               break;
	}

	switch( severity ) {
	case GL_DEBUG_SEVERITY_HIGH:         s_severity = "ERROR";          break;
	case GL_DEBUG_SEVERITY_MEDIUM:       s_severity = "WARNING";        break;
	case GL_DEBUG_SEVERITY_LOW:          s_severity = "SOFT WARNING";           break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: s_severity = "NOTIFICATION";  break;
	}

	std::string out_log = "[OPENGL][" + s_severity + "][" + s_type + "][" + s_source + "]: " + message;
	std::cout << out_log << "\n";
}