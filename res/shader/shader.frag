#version 330 core

in vec2 v_TexCoord;
out vec4 color;

uniform vec4 u_SpriteColor;
uniform sampler2D u_Sprite;

void main() 
{
    vec4 texColor = texture(u_Sprite, v_TexCoord);
    color = texColor * u_SpriteColor;
}
