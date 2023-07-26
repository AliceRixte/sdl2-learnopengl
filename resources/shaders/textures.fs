#version 330 core 

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main(){
    FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.8) * vec4(ourColor,1.0);
}
