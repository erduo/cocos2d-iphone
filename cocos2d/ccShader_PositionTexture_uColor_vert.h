"									\n\
attribute vec4 a_position;			\n\
attribute vec2 a_texCoord;			\n\
									\n\
uniform	mat4 u_MVPMatrix;			\n\
									\n\
#ifdef GL_ES						\n\
varying mediump vec2 v_texCoord;	\n\
#else								\n\
varying vec2 v_texCoord;			\n\
#endif								\n\
//位置和颜色属性（a_position和a_color）是一个有4个坐标（X，Y，Z，W，用于确定位置）和 (r，g，b，a，用于确定颜色) 的矢量格式\n\
void main()							\n\
{									\n\
    gl_Position = u_MVPMatrix * a_position;		\n\
	v_texCoord = a_texCoord;		\n\
}									\n\
";
