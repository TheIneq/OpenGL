#version 460

layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 cameraMatrix;
uniform vec3 cameraPos;

void main() {
    TexCoords = aPos;
    vec3 worldPos = aPos + cameraPos;
    gl_Position = cameraMatrix * vec4(worldPos, 1.0);
}