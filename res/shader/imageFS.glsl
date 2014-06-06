#version 120
varying vec2 fragTextureCoord;
uniform sampler2D textureWallpaper;

void main(void)
{
	 //  gl_FragColor = vec4 (1.0, 0.0, 0.0, 0.0);
	 gl_FragColor = texture2D(textureWallpaper,fragTextureCoord);
}
