"													\n\
#ifdef GL_ES										\n\
precision lowp float;								\n\
#endif												\n\
													\n\
varying vec4 v_fragmentColor;						\n\
//还不知道怎么用的,片段颜色													\n\
void main()											\n\
{													\n\
	gl_FragColor = v_fragmentColor;					\n\
}													\n\
";
