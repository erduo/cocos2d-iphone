/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


/**
 @file
 cocos2d (cc) types    类型
*/

#import <Foundation/Foundation.h>
#import "ccMacros.h"

#ifdef __CC_PLATFORM_IOS
#import <CoreGraphics/CGGeometry.h>	// CGPoint 	几何坐标点
#endif

#import "Platforms/CCGL.h"

/** RGB color composed of bytes 3 bytes
 * RGB 颜色值有三个字节组成
@since v0.8
 */
typedef struct _ccColor3B
{
	GLubyte	r;
	GLubyte	g;
	GLubyte b;
} ccColor3B;

//! helper macro that creates an ccColor3B type
//使用宏定义 创建一个ccColor3B,用到内联函数
static inline ccColor3B
ccc3(const GLubyte r, const GLubyte g, const GLubyte b)
{
	ccColor3B c = {r, g, b};
	return c;
}
//ccColor3B predefined colors	预定义的颜色
//! White color (255,255,255)	白色
static const ccColor3B ccWHITE = {255,255,255};
//! Yellow color (255,255,0)	黄色
static const ccColor3B ccYELLOW = {255,255,0};
//! Blue color (0,0,255)	蓝色
static const ccColor3B ccBLUE = {0,0,255};
//! Green Color (0,255,0)	绿色
static const ccColor3B ccGREEN = {0,255,0};
//! Red Color (255,0,0,)	红色
static const ccColor3B ccRED = {255,0,0};
//! Magenta Color (255,0,255)	品红色
static const ccColor3B ccMAGENTA = {255,0,255};
//! Black Color (0,0,0)		黑色
static const ccColor3B ccBLACK = {0,0,0};
//! Orange Color (255,127,0)	橘黄色
static const ccColor3B ccORANGE = {255,127,0};
//! Gray Color (166,166,166)	灰色
static const ccColor3B ccGRAY = {166,166,166};

/** RGBA color composed of 4 bytes
 * RGBA 颜色值有四个字节构成
@since v0.8
*/
typedef struct _ccColor4B
{
	GLubyte	r;
	GLubyte	g;
	GLubyte	b;
	GLubyte a;
} ccColor4B;
//! helper macro that creates an ccColor4B type
//同样使用宏定义来创建一个ccColor4B类型的对象
static inline ccColor4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
	ccColor4B c = {r, g, b, o};
	return c;
}


/** RGBA color composed of 4 floats
 * 颜色值有4个浮点数组成
@since v0.8
*/
struct ccColor4F {
	GLfloat r;
	GLfloat g;
	GLfloat b;
	GLfloat a;
};
typedef struct ccColor4F ccColor4F;

//! helper that creates a ccColor4f type
//使用内联函数创建ccColor4f类型
static inline ccColor4F ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
	return (ccColor4F){r, g, b, a};
}

/** Returns a ccColor4F from a ccColor3B. Alpha will be 1.
 * 此方法从一个ccColor3B类型转换为ccColor4F类型，且阿尔法的值为1.
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc3B(ccColor3B c)
{
	return (ccColor4F){c.r/255.f, c.g/255.f, c.b/255.f, 1.f};
}

/** Returns a ccColor4F from a ccColor4B.
 * 从ccColor4B转换为ccColor4F方法
 @since v0.99.1
 */
static inline ccColor4F ccc4FFromccc4B(ccColor4B c)
{
	return (ccColor4F){c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f};
}

/** returns YES if both ccColor4F are equal. Otherwise it returns NO.
 * 如果两个ccColor4F的值相同，则返回是，否则返回否
 @since v0.99.1
 */
static inline BOOL ccc4FEqual(ccColor4F a, ccColor4F b)
{
	return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/** A vertex composed of 2 GLfloats: x, y
 * 一个顶点有两个浮点数组成
 @since v0.8
 */
typedef struct _ccVertex2F
{
	GLfloat x;
	GLfloat y;
} ccVertex2F;

/** A vertex composed of 2 floats: x, y
 * 同样定义三维顶点有三个浮点数组成
 @since v0.8
 */
typedef struct _ccVertex3F
{
	GLfloat x;
	GLfloat y;
	GLfloat z;
} ccVertex3F;

/** A texcoord composed of 2 floats: u, y
 @since v0.8   作用？
 */
typedef struct _ccTex2F {
	 GLfloat u;
	 GLfloat v;
} ccTex2F;


//! Point Sprite component 
//一个精灵组件有：顶点，颜色，大小
typedef struct _ccPointSprite
{
	ccVertex2F	pos;		// 8 bytes
	ccColor4B	color;		// 4 bytes
	GLfloat		size;		// 4 bytes
} ccPointSprite;

//!	A 2D Quad. 4 * 2 floats
// 一个2D的四个顶点
typedef struct _ccQuad2 {
	ccVertex2F		tl;
	ccVertex2F		tr;
	ccVertex2F		bl;
	ccVertex2F		br;
} ccQuad2;


//!	A 3D Quad. 4 * 3 floats
//同上来解释
typedef struct _ccQuad3 {
	ccVertex3F		bl;
	ccVertex3F		br;
	ccVertex3F		tl;
	ccVertex3F		tr;
} ccQuad3;

//! A 2D grid size
//一个2D坐标方格的大小
typedef struct _ccGridSize
{
	NSInteger	x;
	NSInteger	y;
} ccGridSize;

//! helper function to create a ccGridSize
//创建一个ccGridSize
static inline ccGridSize
ccg(const NSInteger x, const NSInteger y)
{
	ccGridSize v = {x, y};
	return v;
}

//! a Point with a vertex point, a tex coord point and a color 4B
//一个点和一个顶点，一个tex点和一个4B的颜色
typedef struct _ccV2F_C4B_T2F
{
	//! vertices (2F)	顶点
	ccVertex2F		vertices;
	//! colors (4B)		颜色
	ccColor4B		colors;
	//! tex coords (2F)	tex点
	ccTex2F			texCoords;
} ccV2F_C4B_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
//同上，颜色有变化
typedef struct _ccV2F_C4F_T2F
{
	//! vertices (2F)
	ccVertex2F		vertices;
	//! colors (4F)
	ccColor4F		colors;
	//! tex coords (2F)
	ccTex2F			texCoords;
} ccV2F_C4F_T2F;

//! a Point with a vertex point, a tex coord point and a color 4F
//顶点有些变化
typedef struct _ccV3F_C4F_T2F
{
	//! vertices (3F)
	ccVertex3F		vertices;
	//! colors (4F)
	ccColor4F		colors;
	//! tex coords (2F)
	ccTex2F			texCoords;
} ccV3F_C4F_T2F;

//! 4 ccV3F_C4F_T2F
typedef struct _ccV3F_C4F_T2F_Quad
{
	//! top left 	左上
	ccV3F_C4F_T2F	tl;
	//! bottom left	左下
	ccV3F_C4F_T2F	bl;
	//! top right	右上
	ccV3F_C4F_T2F	tr;
	//! bottom right	右下
	ccV3F_C4F_T2F	br;
} ccV3F_C4F_T2F_Quad;

//! a Point with a vertex point, a tex coord point and a color 4B
typedef struct _ccV3F_C4B_T2F
{
	//! vertices (3F)	顶点有变化
	ccVertex3F		vertices;			// 12 bytes
//	char __padding__[4];

	//! colors (4B)
	ccColor4B		colors;				// 4 bytes
//	char __padding2__[4];

	// tex coords (2F)
	ccTex2F			texCoords;			// 8 byts
} ccV3F_C4B_T2F;

//! 4 ccVertex2FTex2FColor4B Quad
typedef struct _ccV2F_C4B_T2F_Quad
{
	//! bottom left	使用ccV2F_C4B_T2F来定义四个点
	ccV2F_C4B_T2F	bl;
	//! bottom right
	ccV2F_C4B_T2F	br;
	//! top left
	ccV2F_C4B_T2F	tl;
	//! top right
	ccV2F_C4B_T2F	tr;
} ccV2F_C4B_T2F_Quad;

//! 4 ccVertex3FTex2FColor4B
//ccV3F_C4B_T2F来定义
typedef struct _ccV3F_C4B_T2F_Quad
{
	//! top left
	ccV3F_C4B_T2F	tl;
	//! bottom left
	ccV3F_C4B_T2F	bl;
	//! top right
	ccV3F_C4B_T2F	tr;
	//! bottom right
	ccV3F_C4B_T2F	br;
} ccV3F_C4B_T2F_Quad;

//! 4 ccVertex2FTex2FColor4F Quad
//同上使用ccV2F_C4F_T2F来定义
typedef struct _ccV2F_C4F_T2F_Quad
{
	//! bottom left
	ccV2F_C4F_T2F	bl;
	//! bottom right
	ccV2F_C4F_T2F	br;
	//! top left
	ccV2F_C4F_T2F	tl;
	//! top right
	ccV2F_C4F_T2F	tr;
} ccV2F_C4F_T2F_Quad;

//! Blend Function used for textures
//纹理的混合函数
typedef struct _ccBlendFunc
{
	//! source blend function	源点
	GLenum src;
	//! destination blend function	目标点
	GLenum dst;
} ccBlendFunc;

//! ccResolutionType	判断类型
typedef enum
{
	//! Unknonw resolution type	未知类型
	kCCResolutionUnknown,
#ifdef __CC_PLATFORM_IOS
	//! iPhone resolution type	iphone
	kCCResolutioniPhone,
	//! RetinaDisplay resolution type	像素超高的显示Iphone
	kCCResolutioniPhoneRetinaDisplay,
	//! iPad resolution type		iPad
	kCCResolutioniPad,
	//! iPad Retina Display resolution type	超清显示的iPad
	kCCResolutioniPadRetinaDisplay,
	
#elif defined(__CC_PLATFORM_MAC)
	//! Mac resolution type			mac类型
	kCCResolutionMac,

	//! Mac RetinaDisplay resolution type (???)	超清显示，有吗？
	kCCResolutionMacRetinaDisplay,
#endif // platform

} ccResolutionType;

// XXX: If any of these enums are edited and/or reordered, udpate CCTexture2D.m
//提示：这些条目任何一个被编辑或重新排序，都要更新CCTexture2D.m文件
//! Vertical text alignment type
//垂直文本的对齐方式
typedef enum
{
    kCCVerticalTextAlignmentTop,
    kCCVerticalTextAlignmentCenter,
    kCCVerticalTextAlignmentBottom,
} CCVerticalTextAlignment;

// XXX: If any of these enums are edited and/or reordered, udpate CCTexture2D.m
//! Horizontal text alignment type
//同上。 水平文本的对齐方式
typedef enum
{
	kCCTextAlignmentLeft,
	kCCTextAlignmentCenter,
	kCCTextAlignmentRight,
} CCTextAlignment;

// XXX: If any of these enums are edited and/or reordered, udpate CCTexture2D.m
//! Line break modes	换行模式	
typedef enum {
	kCCLineBreakModeWordWrap,
	kCCLineBreakModeCharacterWrap,
	kCCLineBreakModeClip,
	kCCLineBreakModeHeadTruncation,
	kCCLineBreakModeTailTruncation,
	kCCLineBreakModeMiddleTruncation
} CCLineBreakMode;

//! delta time type	时间差
//! if you want more resolution redefine it as a double
typedef float ccTime;
//typedef double ccTime; 定义一个double类型的ccTime

typedef float ccMat4[16];
