"													\n\
attribute vec4 a_position;							\n\
attribute vec2 a_texCoord;							\n\
attribute vec4 a_color;								\n\
													\n\
uniform		mat4 u_MVPMatrix;						\n\
													\n\
#ifdef GL_ES										\n\
varying lowp vec4 v_fragmentColor;					\n\
varying mediump vec2 v_texCoord;					\n\
#else												\n\
varying vec4 v_fragmentColor;						\n\
varying vec2 v_texCoord;							\n\
#endif												\n\
//每个着色器都只有一个main()方法，并针对每个顶点和片段、像素执行代码				\n\
void main()											\n\
{													\n\
    gl_Position = u_MVPMatrix * a_position;			\n\
	v_fragmentColor = a_color;						\n\
	v_texCoord = a_texCoord;						\n\
}													\n\
";
