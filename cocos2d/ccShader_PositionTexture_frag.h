"																		\n\
#ifdef GL_ES															\n\
precision lowp float;													\n\
#endif																	\n\
																		\n\
varying vec2 v_texCoord;												\n\
uniform sampler2D u_texture;											\n\
//无论什么程序转换/效果，每个顶点的最终位置靠分配坐标至gl_Position进行设置；另一方面，每个像素的最终颜色通过指定颜色至gl_FragColor进行设置。	\n\
void main()							\n\
{																		\n\
	gl_FragColor =  texture2D(u_texture, v_texCoord);					\n\
}																		\n\
";
