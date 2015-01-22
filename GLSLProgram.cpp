#include "GLSLProgram.h"
#include "BengineErrors.h"
#include <fstream>
#include <vector>

namespace Bengine {
  GLSLProgram::GLSLProgram() : m_numAttributes(0), m_programID(0), m_vertexShaderID(0), m_fragmentShaderID(0) {}

  GLSLProgram::~GLSLProgram() {}

  void GLSLProgram::compileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath) {
    m_programID = glCreateProgram();

    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    if (m_vertexShaderID == 0) {
      fatalError("vertex shader failed to be created");
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    if (m_fragmentShaderID == 0) {
      fatalError("fragment shader failed to be created");
    }

    compileShader(vertexShaderFilePath, m_vertexShaderID);
    compileShader(fragmentShaderFilePath, m_fragmentShaderID);
  }
  void GLSLProgram::linkShaders() {
    //Vertex and fragment shaders are successfully compiled.
    //Now time to link them together into a program
    glAttachShader(m_programID, m_vertexShaderID);
    glAttachShader(m_programID, m_fragmentShaderID);

    //Link our program
    glLinkProgram(m_programID);

    //Note the different functions hereL glGetProrgam instead of glGetShader
    GLint isLinked = 0;
    glGetProgramiv(m_programID, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
      GLint maxLength = 0;
      glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &maxLength);

      //The maxLength includes the NULL character
      std::vector<char> errorLog(maxLength);
      glGetProgramInfoLog(m_programID, maxLength, &maxLength, &errorLog[0]);

      //We don't need the program anymore.
      glDeleteProgram(m_programID);
      //Don't leak shaders either.
      glDeleteShader(m_vertexShaderID);
      glDeleteShader(m_fragmentShaderID);

      //Use the infoLog as you see fit.
      std::printf("%s\n", &(errorLog[0]));
      fatalError("Shaders failed to link!");
    }

    //Always detach shaders after a succesful link.
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);
    glDeleteShader(m_fragmentShaderID);
  }

  void GLSLProgram::compileShader(const std::string& filePath, GLuint id) {
    std::ifstream file(filePath);
    if (file.fail()) {
      perror(filePath.c_str());
      fatalError("failed to open " + filePath);
    }

    std::string fileContents = "";
    std::string line;

    while(std::getline(file,line)) {
      fileContents += line + "\n";
    }

    file.close();
    const char* contentsPtr = fileContents.c_str();
    glShaderSource(id, 1, &contentsPtr, nullptr);
    glCompileShader(id);

    GLint success = 0;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (success == GL_FALSE) {
      GLint maxLength = 0;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

      //The maxLength includes the NULL character
      std::vector<char> errorLog(maxLength);
      glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

      //Provide the infolog in whatever mano you deem best.
      //Exit with failure
      glDeleteShader(id);

      std::printf("%s\n", &(errorLog[0]));
      fatalError("Shader " + filePath + " failed to compile");
    }
  }

  void GLSLProgram::addAttribute(const std::string& attributeName) {
    glBindAttribLocation(m_programID, m_numAttributes++, attributeName.c_str());
  }

  GLint GLSLProgram::getUniformLocation(const std::string& uniformName) {
    GLint location = glGetUniformLocation(m_programID, uniformName.c_str());
    if (location == GL_INVALID_INDEX) {
      fatalError("Uniform " + uniformName + " not found in shader!");
    }
    return location;
  }

  void GLSLProgram::use() {
    glUseProgram(m_programID);
    for (int i = 0; i < m_numAttributes; ++i) {
      glEnableVertexAttribArray(i);
    }
  }

  void GLSLProgram::unuse() {
    glUseProgram(0);
    for (int i = 0; i < m_numAttributes; ++i) {
      glDisableVertexAttribArray(i);
    }
  }
}
