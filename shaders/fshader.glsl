#version 410

uniform sampler2D tex0;

in vec4 color;
in vec2 texCoord;

out vec4 fragColor;


void main() 
{ 
    fragColor = texture(tex0,texCoord);
    //fragColor = vec4(texCoord.x,texCoord.y,0,1.);
    //fragColor = color;
} 

