/**

 * */

#ifndef _Native_Render_GL_UTILS_H_
#define _Native_Render_GL_UTILS_H_

#include <GLES3/gl3.h>
#include <string>
#include <glm.hpp>
#include <opencv2/opencv.hpp>
#include "../util/LogUtil.h"


#define SHADER_TO_STRING(s) #s

#define MATH_PI 3.1415926535897932384626433832802

class GLUtils {
public:
    static GLuint LoadShader(GLenum shaderType, const char *pSource);

    static GLuint CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource,
                                GLuint &vertexShaderHandle,
                                GLuint &fragShaderHandle);

    static GLuint CreateProgram(const char *pVertexShaderSource, const char *pFragShaderSource);

    static GLuint CreateProgramWithFeedback(
            const char *pVertexShaderSource,
            const char *pFragShaderSource,
            GLuint &vertexShaderHandle,
            GLuint &fragShaderHandle,
            const GLchar **varying,
            int varyingCount);

    static void DeleteProgram(GLuint &program);

    static void CheckGLError(const char *pGLOperation);

    static void setBool(GLuint programId, const std::string &name, bool value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), (int) value);
    }

    static void setInt(GLuint programId, const std::string &name, int value) {
        glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    }

    static void setFloat(GLuint programId, const std::string &name, float value) {
        glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    }

    static void setVec2(GLuint programId, const std::string &name, const glm::vec2 &value) {
        glUniform2fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec2(GLuint programId, const std::string &name, float x, float y) {
        glUniform2f(glGetUniformLocation(programId, name.c_str()), x, y);
    }

    static void setVec3(GLuint programId, const std::string &name, const glm::vec3 &value) {
        glUniform3fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void setVec3(GLuint programId, const std::string &name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(programId, name.c_str()), x, y, z);
    }

    static void setVec4(GLuint programId, const std::string &name, const glm::vec4 &value) {
        glUniform4fv(glGetUniformLocation(programId, name.c_str()), 1, &value[0]);
    }

    static void
    setVec4(GLuint programId, const std::string &name, float x, float y, float z, float w) {
        glUniform4f(glGetUniformLocation(programId, name.c_str()), x, y, z, w);
    }

    static void setMat2(GLuint programId, const std::string &name, const glm::mat2 &mat) {
        glUniformMatrix2fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static void setMat3(GLuint programId, const std::string &name, const glm::mat3 &mat) {
        glUniformMatrix3fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static void setMat4(GLuint programId, const std::string &name, const glm::mat4 &mat) {
        glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    static glm::vec3 texCoordToVertexCoord(glm::vec2 &texCoord) {
        return glm::vec3(2 * texCoord.x - 1, 1 - 2 * texCoord.y, 0);
    }

    /**
     *  将model加载图像纹理方法抽象为公共方法
     * @param path  图片路径
     * @param directory  图片文件夹
     * @param isHasTexture 是否包含图片用于选择着色器
     * @param gamma
     * @return
     */
    static unsigned int
    TextureFromFile(const char *path, const std::string &directory, int &isHasTexture,
                    bool gamma = false) {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = nullptr;

        // load the texture using OpenCV ,with blend color must read & set texture diff prams
        // LOGCATE("TextureFromFile Loading texture %s", filename.c_str());
        cv::Mat textureImage;
        GLenum format;
        int color2Format = CV_BGR2RGB;
        GLint textureUVMode = GL_REPEAT;
        if (isWindowAlphaTextrue(filename.c_str())) {
            textureImage = cv::imread(filename, -1);
            format = GL_RGBA;
            color2Format = CV_BGRA2RGBA;
            textureUVMode = GL_CLAMP_TO_EDGE;
        } else {
            textureImage = cv::imread(filename);
            format = GL_RGB;
            color2Format = CV_BGR2RGB;
            textureUVMode = GL_REPEAT;
        }

        if (!textureImage.empty()) {
            isHasTexture = 1;
            // opencv reads textures in BGR format, change to RGB for GL
            cv::cvtColor(textureImage, textureImage, color2Format);
            // opencv reads image from top-left, while GL expects it from bottom-left
            // vertically flip the image
            //cv::flip(textureImage, textureImage, 0);
            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, textureImage.cols,
                         textureImage.rows, 0, format, GL_UNSIGNED_BYTE,
                         textureImage.data);
            glGenerateMipmap(GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, textureUVMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, textureUVMode);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            GO_CHECK_GL_ERROR();
        } else {
            LOGCATE("TextureFromFile Texture failed to load at path: %s", path);
        }

        return textureID;
    }


    //TODO alpha 图片记得在这里加名字
    static bool isWindowAlphaTextrue(const char *_textureName) {
        if (strstr(_textureName, "window.png") != NULL ||
            strstr(_textureName, "headlight_open.png") != NULL ||
            strstr(_textureName, "headlight_open_right.png") != NULL ||
            strstr(_textureName, "headflashlight.png") != NULL ||
            strstr(_textureName, "headflashlight_right.png") != NULL ||
            strstr(_textureName, "light_weideng_break.png") != NULL ||
            strstr(_textureName, "light_weideng_break_left.png") != NULL ||
            strstr(_textureName, "light_weideng_flash.png") != NULL ||
            strstr(_textureName, "light_weideng_flash_left.png") != NULL ||
            strstr(_textureName, "img_y_left_alert.png") != NULL ||
            strstr(_textureName, "img_r_left_alert.png") != NULL ||
            strstr(_textureName, "img_o_left_alert.png") != NULL)
            return true;
        return false;
    }

};

#endif // _Native_Render_GL_UTILS_H_