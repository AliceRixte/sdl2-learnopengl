#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;
out vec4 position;

uniform float offset;

void main (){
    gl_Position = vec4(aPos.x + offset, -aPos.y, aPos.z, 1.0);
    position = vec4((gl_Position.x + 1.0)/2.0
        ,(gl_Position.y + 1.0)/2.0
        ,(gl_Position.z + 1.0)/2.0
        , 1.0);
    ourColor = aColor;
}