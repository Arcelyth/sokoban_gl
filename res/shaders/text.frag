#version 330 core
in vec2 v_TexCoord;
out vec4 color;

uniform sampler2D u_Text;
uniform vec4 u_TextColor;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_Text, v_TexCoord).r);
    color = u_TextColor * sampled;
}  
