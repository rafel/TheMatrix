#version 120
attribute vec3 position;
attribute vec2 textureCoord;
varying vec2 fragTextureCoord;
uniform mat4 MVP;

void main(void)
{
    fragTextureCoord = textureCoord;
	gl_Position =  MVP* vec4(position,1);
}