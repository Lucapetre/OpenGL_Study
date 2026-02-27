#version 330 core

out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;

uniform vec3 testUniformColor;
uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
    FragColor = mix(texture(texture0, texCoord), texture(texture1, texCoord), 0.2f)  * vec4(ourColor * testUniformColor, 1.0f);
}
