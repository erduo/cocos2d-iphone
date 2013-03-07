/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
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


#import "CCTextureAtlas.h"
#import "CCNode.h"
#import "CCProtocols.h"

/** CCAtlasNode is a subclass of CCNode that implements the CCRGBAProtocol and
 CCTextureProtocol protocol
主要要实现上面连个协议
 It knows how to render a TextureAtlas object.
 If you are going to render a TextureAtlas consider subclassing CCAtlasNode (or a subclass of CCAtlasNode)
如何程序纹理地图对象
 All features from CCNode are valid, plus the following features:
 - opacity and RGB colors
继承所有节点基类的属性，增加了透明度和颜色值属性
 */
@interface CCAtlasNode : CCNode <CCRGBAProtocol, CCTextureProtocol>
{
	// texture atlas 纹理地图
	CCTextureAtlas	*textureAtlas_;

	// chars per row 行
	NSUInteger		itemsPerRow_;
	// chars per column  柱
	NSUInteger		itemsPerColumn_;

	// width of each char  宽度
	NSUInteger		itemWidth_;
	// height of each char  高度
	NSUInteger		itemHeight_;

	// quads to draw    四边
	NSUInteger		quadsToDraw_;

	// blend function   混合功能
	ccBlendFunc		blendFunc_;

	// texture RGBA. 纹理  RGBA为red green+blue+alpha组成
	GLubyte		opacity_;
	ccColor3B	color_;
	ccColor3B	colorUnmodified_;
	BOOL opacityModifyRGB_;

	// color uniform  颜色均匀
	GLint	uniformColor_;
}

/** conforms to CCTextureProtocol protocol  符合纹理协议 */
@property (nonatomic,readwrite,retain) CCTextureAtlas *textureAtlas;

/** conforms to CCTextureProtocol protocol */
@property (nonatomic,readwrite) ccBlendFunc blendFunc;

/** conforms to CCRGBAProtocol protocol */
@property (nonatomic,readwrite) GLubyte opacity;
/** conforms to CCRGBAProtocol protocol */
@property (nonatomic,readwrite) ccColor3B color;

/** how many quads to draw   个数参数 */
@property (nonatomic,readwrite) NSUInteger quadsToDraw;

/** creates a CCAtlasNode  with an Atlas file the width and height of each item measured in points and the quantity of items to render 使用地图文件创建对象和初始化
*/
+(id) atlasWithTileFile:(NSString*)tile tileWidth:(NSUInteger)w tileHeight:(NSUInteger)h itemsToRender: (NSUInteger) c;

/** initializes an CCAtlasNode  with an Atlas file the width and height of each item measured in points and the quantity of items to render*/
-(id) initWithTileFile:(NSString*)tile tileWidth:(NSUInteger)w tileHeight:(NSUInteger)h itemsToRender: (NSUInteger) c;

/** updates the Atlas (indexed vertex array).
 * Shall be overriden in subclasses
更新地图；要在子类中重载该方法
 */
-(void) updateAtlasValues;
@end
