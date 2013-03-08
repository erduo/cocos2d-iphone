"										\n\
#ifdef GL_ES							\n\
precision lowp float;					\n\
#endif									\n\
										\n\
uniform		vec4 u_color;				\n\
										\n\
varying vec2 v_texCoord;				\n\
										\n\
uniform sampler2D u_texture;			\n\
//因为顶点着色器是管线中的第一个组件，我们传递属性至位置和颜色，并让其通过内部变量（改变v_color）传递颜色属性至片段着色器。\n\
void main()								\n\
{										\n\
	gl_FragColor =  texture2D(u_texture, v_texCoord) * u_color;	\n\
}										\n\
";
