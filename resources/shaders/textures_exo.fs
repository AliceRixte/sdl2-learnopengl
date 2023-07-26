#version 330 core 

in vec3 ourColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform float direction;

void main(){
    FragColor = mix(texture(texture0, texCoord), texture(texture1, vec2(direction + texCoord.x - 2.0 * direction * texCoord.x, texCoord.y)), 0.8) * vec4(ourColor,1.0);
}
