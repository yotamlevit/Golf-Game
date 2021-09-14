#version 330 core

// Positions/Coordinates
layout (location = 0) in vec3 aPos;
// Colors
layout (location = 1) in vec3 aColor;

layout (location = 2) in vec2 aTex;

// Outputs the color for the Fragfment Shader
out vec3 color;

// Outputs the texture for the Fragfment Shader
out vec2 texCoord;

// Controles the scale of the vertices
uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   // Assigns the colors from the Vertex Data to "color"
   color = aColor;
   texCoord = aTex;
}