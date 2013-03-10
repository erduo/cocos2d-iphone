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
 *
 */

#import "CCTexture2D.h"
#import "ccTypes.h"
#import "ccConfig.h"

/** A class that implements a Texture Atlas. 实现纹理集；
 * 具有属性：可以是pvr,png任意格式的纹理；更新，增加，移除，排序在运行中，容量变化，opengl组件；
 Supported features:
   * The atlas file can be a PVRTC, PNG or any other fomrat supported by Texture2D
   * Quads can be udpated in runtime
   * Quads can be added in runtime
   * Quads can be removed in runtime
   * Quads can be re-ordered in runtime
   * The TextureAtlas capacity can be increased or decreased in runtime
   * OpenGL component: V3F, C4B, T2F.
 The quads are rendered using an OpenGL ES VBO. 是使用vbo方式渲染呈现
 To render the quads using an interleaved vertex array list, you should modify the ccConfig.h file
 呈现quads使用在一个交错顶点数组列表，可以在配置文件中修改；
 */
@interface CCTextureAtlas : NSObject
{
	NSUInteger			totalQuads_;
	NSUInteger			capacity_;
	ccV3F_C4B_T2F_Quad	*quads_;	// quads to be rendered
	GLushort			*indices_;
	CCTexture2D			*texture_;
	
	GLuint				buffersVBO_[2]; //0: vertex  1: indices
	BOOL				dirty_;			//indicates whether or not the array buffer of the VBO needs to be updated

#if CC_TEXTURE_ATLAS_USE_VAO
	GLuint				VAOname_;
#endif
}

/** quantity of quads that are going to be drawn  个数*/
@property (nonatomic,readonly) NSUInteger totalQuads;
/** quantity of quads that can be stored with the current texture atlas size 容量*/
@property (nonatomic,readonly) NSUInteger capacity;
/** Texture of the texture atlas 纹理地图 */
@property (nonatomic,retain) CCTexture2D *texture;
/** Quads that are going to be rendered */
@property (nonatomic,readwrite) ccV3F_C4B_T2F_Quad *quads;

/** creates a TextureAtlas with an filename and with an initial capacity for Quads.
 * The TextureAtlas capacity can be increased in runtime.
 * 容量和文件名称作为参数来创建纹理地图
 */
+(id) textureAtlasWithFile:(NSString*)file capacity:(NSUInteger)capacity;

/** initializes a TextureAtlas with a filename and with a certain capacity for Quads.
 * The TextureAtlas capacity can be increased in runtime.
 *初始化。不用重复初始化！
 * WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
 */
-(id) initWithFile: (NSString*) file capacity:(NSUInteger)capacity;

/** creates a TextureAtlas with a previously initialized Texture2D object, and
 * with an initial capacity for n Quads.
 * The TextureAtlas capacity can be increased in runtime.
 * 纹理和容量创建和初始化方法
 */
+(id) textureAtlasWithTexture:(CCTexture2D *)tex capacity:(NSUInteger)capacity;

/** initializes a TextureAtlas with a previously initialized Texture2D object, and
 * with an initial capacity for Quads.
 * The TextureAtlas capacity can be increased in runtime.
 *
 * WARNING: Do not reinitialize the TextureAtlas because it will leak memory (issue #706)
 */
-(id) initWithTexture:(CCTexture2D *)tex capacity:(NSUInteger)capacity;

/** updates a Quad (texture, vertex and color) at a certain index
 * index must be between 0 and the atlas capacity - 1
 @since v0.8 更新（纹理，顶点，颜色） 带有指定序号的参数
 */
-(void) updateQuad:(ccV3F_C4B_T2F_Quad*)quad atIndex:(NSUInteger)index;

/** Inserts a Quad (texture, vertex and color) at a certain index
 index must be between 0 and the atlas capacity - 1
 @since v0.8 插入
 */
-(void) insertQuad:(ccV3F_C4B_T2F_Quad*)quad atIndex:(NSUInteger)index;

/** Inserts a c array of quads at a given index
 index must be between 0 and the atlas capacity - 1
 this method doesn't enlarge the array when amount + index > totalQuads
 @since v1.1 
*/
-(void) insertQuads:(ccV3F_C4B_T2F_Quad*)quads atIndex:(NSUInteger)index amount:(NSUInteger)amount;

/** Removes the quad that is located at a certain index and inserts it at a new index
 This operation is faster than removing and inserting in a quad in 2 different steps
 @since v0.7.2 移除方法
*/
-(void) insertQuadFromIndex:(NSUInteger)fromIndex atIndex:(NSUInteger)newIndex;

/** removes a quad at a given index number.
 The capacity remains the same, but the total number of quads to be drawn is reduced in 1
 @since v0.7.2
 */
-(void) removeQuadAtIndex:(NSUInteger) index;

/** removes a amount of quads starting from index
	@since 1.1
 */
- (void) removeQuadsAtIndex:(NSUInteger) index amount:(NSUInteger) amount;

/** removes all Quads.
 The TextureAtlas capacity remains untouched. No memory is freed.
 The total number of quads to be drawn will be 0
 @since v0.7.2
 */
-(void) removeAllQuads;

/** resize the capacity of the CCTextureAtlas.
 * The new capacity can be lower or higher than the current one
 * It returns YES if the resize was successful.
 * If it fails to resize the capacity it will return NO with a new capacity of 0.
 */
-(BOOL) resizeCapacity: (NSUInteger) n;

/**
 Used internally by CCParticleBatchNode
 don't use this unless you know what you're doing
 @since 1.1
*/
- (void) increaseTotalQuadsWith:(NSUInteger) amount;

/** Moves an amount of quads from oldIndex at newIndex
 @since v1.1
 */
-(void) moveQuadsFromIndex:(NSUInteger)oldIndex amount:(NSUInteger) amount atIndex:(NSUInteger)newIndex;

/**
 Moves quads from index till totalQuads to the newIndex
 Used internally by CCParticleBatchNode
 This method doesn't enlarge the array if newIndex + quads to be moved > capacity
 @since 1.1 移动
*/
- (void) moveQuadsFromIndex:(NSUInteger) index to:(NSUInteger) newIndex;

/**
 Ensures that after a realloc quads are still empty
 Used internally by CCParticleBatchNode
 @since 1.1
*/
- (void) fillWithEmptyQuadsFromIndex:(NSUInteger) index amount:(NSUInteger) amount;

/** draws n quads 绘制方法
 * n can't be greater than the capacity of the Atlas
 */

-(void) drawNumberOfQuads: (NSUInteger) n;

/** draws n quads from an index (offset).
 n + start can't be greater than the capacity of the atlas

 @since v1.0
 */
-(void) drawNumberOfQuads: (NSUInteger) n fromIndex: (NSUInteger) start;

/** draws all the Atlas's Quads
 */
-(void) drawQuads;

@end
