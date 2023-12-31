#pragma once 

#include <string>

class Shader
{
public:
    // the program ID
    unsigned int ID;
  
    // constructor reads and builds the shader
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    void set4Float(const std::string &name, float value1, float value2, float value3 ,float value4) const;

    ~Shader();
};