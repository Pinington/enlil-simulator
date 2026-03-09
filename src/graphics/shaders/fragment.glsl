#version 330 core
in vec3 fragNormal;
in vec3 fragPos;
in vec3 fragColor;

out vec4 color;

uniform vec3 lightPos = vec3(5.0,5.0,5.0);

void main() {
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * fragColor;

    vec3 ambient = 0.8 * fragColor;
    color = vec4(diffuse + ambient, 1.0);
}