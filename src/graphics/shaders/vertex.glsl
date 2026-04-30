#version 330 core

layout(location = 0) in vec3 posAttr;
layout(location = 1) in vec3 colAttr;
layout(location = 2) in vec3 normalAttr;
layout(location = 3) in vec3 offset;

uniform mat4 matrix;

out vec3 fragNormal;
out vec3 fragPos;
out vec3 fragColor;

void main() {
    vec3 worldPos = posAttr + offset;
    fragPos = worldPos;

    // Transform normal for model/view (if no scaling, just pass through is fine)
    fragNormal = normalAttr;
    fragColor = colAttr;

    gl_Position = matrix * vec4(worldPos, 1.0);
}