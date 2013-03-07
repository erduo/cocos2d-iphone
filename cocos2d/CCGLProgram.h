//
// Copyright 2011 Jeff Lamarche
//
// Copyright 2012 Goffredo Marocchi
//
// Copyright 2012 Ricardo Quesada
//
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided
// that the following conditions are met:
//	1. Redistributions of source code must retain the above copyright notice, this list of conditions and
//		the following disclaimer.
//
//	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions
//		and the following disclaimer in the documentation and/or other materials provided with the
//		distribution.
//
//	THIS SOFTWARE IS PROVIDED BY THE FREEBSD PROJECT ``AS IS'' AND ANY EXPRESS OR IMPLIED
//	WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
//	FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE FREEBSD PROJECT
//	OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//	CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
//	OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
//	AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//	NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
//	ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//

#import <Foundation/Foundation.h>
#import "ccMacros.h"
#import "Platforms/CCGL.h"

enum {
	kCCVertexAttrib_Position,
	kCCVertexAttrib_Color,
	kCCVertexAttrib_TexCoords,

	kCCVertexAttrib_MAX,
};

enum {
	kCCUniformMVPMatrix,
	kCCUniformSampler,

	kCCUniform_MAX,
};

#define kCCShader_PositionTextureColor			@"ShaderPositionTextureColor"
#define kCCShader_PositionTextureColorAlphaTest	@"ShaderPositionTextureColorAlphaTest"
#define kCCShader_PositionColor					@"ShaderPositionColor"
#define kCCShader_PositionTexture				@"ShaderPositionTexture"
#define kCCShader_PositionTexture_uColor		@"ShaderPositionTexture_uColor"
#define kCCShader_PositionTextureA8Color		@"ShaderPositionTextureA8Color"
#define kCCShader_Position_uColor				@"ShaderPosition_uColor"

// uniform names   同一名称
#define kCCUniformMVPMatrix_s			"u_MVPMatrix"
#define kCCUniformSampler_s				"u_texture"
#define kCCUniformAlphaTestValue		"u_alpha_value"

// Attribute names  属性名称
#define	kCCAttributeNameColor			@"a_color"
#define	kCCAttributeNamePosition		@"a_position"
#define	kCCAttributeNameTexCoord		@"a_texCoord"


struct _hashUniformEntry;

/** CCGLProgram
 Class that implements a glProgram
 该类实现了一个glProgram
 
 @since v2.0.0
 */
@interface CCGLProgram : NSObject
{
	struct _hashUniformEntry	*hashForUniforms_;

@public
	GLuint          program_,
					vertShader_,
					fragShader_;

	GLint			uniforms_[kCCUniform_MAX];
}

/** Initializes the CCGLProgram with a vertex and fragment with bytes array  使用顶点和带有字节数组的碎片创建和初始化 */
- (id)initWithVertexShaderByteArray:(const GLchar*)vShaderByteArray fragmentShaderByteArray:(const GLchar*)fShaderByteArray;

/** Initializes the CCGLProgram with a vertex and fragment with contents of filenames  碎片是带有文件*/
- (id)initWithVertexShaderFilename:(NSString *)vShaderFilename fragmentShaderFilename:(NSString *)fShaderFilename;

/**  It will add a new attribute to the shader   增加一个属性给着色器*/
- (void)addAttribute:(NSString *)attributeName index:(GLuint)index;

/** links the glProgram  链接glProgram*/
- (BOOL)link;

/** it will call glUseProgram()  调用glProgram*/
- (void)use;

/** It will create 3 uniforms:  创建三种规格
	- kCCUniformPMatrix
	- kCCUniformMVMatrix
	- kCCUniformSampler

 And it will bind "kCCUniformSampler" to 0   给kCCUniformSampler赋值为0
 */
- (void) updateUniforms;

/** calls glUniform1i only if the values are different than the previous call for this same shader program.   值不同于上一次调用说色时，分别进行不同的调用根据输入的参数是整数，浮点数，不同： glUniform1i,glUniform1f,glUniform2f,glUniform3f ,glUniform4f*/
-(void) setUniformLocation:(NSUInteger)location withI1:(GLint)i1;

/** calls glUniform1f only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location withF1:(GLfloat)f1;

/** calls glUniform2f only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location withF1:(GLfloat)f1 f2:(GLfloat)f2;

/** calls glUniform3f only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location withF1:(GLfloat)f1 f2:(GLfloat)f2 f3:(GLfloat)f3;

/** calls glUniform4f only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location withF1:(GLfloat)f1 f2:(GLfloat)f2 f3:(GLfloat)f3 f4:(GLfloat)f4;

/** calls glUniform2fv only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location with2fv:(GLfloat*)floats count:(NSUInteger)numberOfArrays;

/** calls glUniform3fv only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location with3fv:(GLfloat*)floats count:(NSUInteger)numberOfArrays;

/** calls glUniform4fv only if the values are different than the previous call for this same shader program. */
-(void) setUniformLocation:(NSUInteger)location with4fv:(GLvoid*)floats count:(NSUInteger)numberOfArrays;

/** calls glUniformMatrix4fv only if the values are different than the previous call for this same shader program. 同上，只是参数不同时，进行不同调用gl函数*/
-(void) setUniformLocation:(NSUInteger)location withMatrix4fv:(GLvoid*)matrix_array count:(NSUInteger)numberOfMatrix;

/** will update the MVP matrix on the MVP uniform if it is different than the previous call for this same shader program.  更新mvp matrix */
-(void) setUniformForModelViewProjectionMatrix;

/** returns the vertexShader error log    返回顶点着色的错误信息*/
- (NSString *)vertexShaderLog;

/** returns the fragmentShader error log  返回碎片着色的错误信息*/
- (NSString *)fragmentShaderLog;

/** returns the program error log  返回程序或者说方案错误信息*/
- (NSString *)programLog;
@end
