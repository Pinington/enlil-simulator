#version 330 core

layout(location = 0) in vec3 posAttr;
layout(location = 1) in vec3 colAttr;
layout(location = 2) in vec3 normalAttr;

uniform mat4 matrix;

out vec3 fragNormal;
out vec3 fragPos;
out vec3 fragColor;

uniform vec3 offsets[64]; // Max spheres

void main() {
    vec3 offset = offsets[gl_InstanceID];
    vec4 worldPos = matrix * vec4(offset + posAttr, 1.0);
    fragPos = vec3(worldPos);

    // Transform normal for model/view (if no scaling, just pass through is fine)
    fragNormal = normalAttr;

    fragColor = colAttr;
    gl_Position = worldPos;
}