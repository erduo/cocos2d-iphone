/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (C) 2009 Matt Oswald
 *
 * Copyright (c) 2009-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
 * Copyright (c) 2011 Marco Tillemans
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

#import "CCNode.h"
@class CCTextureAtlas;
@class CCParticleSystem;

//don't use lazy sorting for particle systems  不用使用懒惰的粒子存储系统
@interface CCNode (extension)
-(void) setZOrder:(NSUInteger) z;
@end

/** CCParticleBatchNode is like a batch node: if it contains children, it will draw them in 1 single OpenGL call
 * (often known as "batch draw").
 *一个批量节点。单次调用opengl
 * A CCParticleBatchNode can reference one and only one texture (one image file, one texture atlas).只能引用一个只有一个纹理（图片，纹理地图）
 * Only the CCParticleSystems that are contained in that texture can be added to the CCSpriteBatchNode.  只有CCParticeSystem可以添加给精灵批量节点
 * All CCParticleSystems added to a CCSpriteBatchNode are drawn in one OpenGL ES draw call.  也是一次调用
 * If the CCParticleSystems are not added to a CCParticleBatchNode then an OpenGL ES draw call will be needed for each one, which is less efficient.
 *如果没有添加，每次回调用opengl，这样效率很低
 *
 * Limitations:限制：某时刻只有CCParticleSystemQuad 是被支持的；所有系统都要带有相同的参数
 * - At the moment only CCParticleSystemQuad is supported
 * - All systems need to be drawn with the same parameters, blend function, aliasing, texture
 *
 * Most efficient usage 高效使用：使用纹理和容量来初始化
 * - Initialize the ParticleBatchNode with the texture and enough capacity for all the particle systems
 * - Initialize all particle systems and add them as child to the batch node
 * @since v1.1
 */

@interface CCParticleBatchNode : CCNode <CCTextureProtocol> {

	CCTextureAtlas	*textureAtlas_;
	ccBlendFunc		blendFunc_;
}

/** the texture atlas used for drawing the quads   为绘制四边形*/
@property (nonatomic, retain) CCTextureAtlas* textureAtlas;
/** the blend function used for drawing the quads  都是为绘制四边形 */
@property (nonatomic, readwrite) ccBlendFunc blendFunc;

/** initializes the particle system with CCTexture2D, a default capacity of 500 默认容量为500，来初始化*/
+(id)batchNodeWithTexture:(CCTexture2D *)tex;

/** initializes the particle system with the name of a file on disk (for a list of supported formats look at the CCTexture2D class), a default capacity of 500 particles */
+(id)batchNodeWithFile:(NSString*) imageFile;

/** initializes the particle system with CCTexture2D, a capacity of particles, which particle system to use */
+(id)batchNodeWithTexture:(CCTexture2D *)tex capacity:(NSUInteger) capacity;

/** initializes the particle system with the name of a file on disk (for a list of supported formats look at the CCTexture2D class), a capacity of particles */
+(id)batchNodeWithFile:(NSString*)fileImage capacity:(NSUInteger)capacity;

/** initializes the particle system with CCTexture2D, a capacity of particles */
-(id)initWithTexture:(CCTexture2D *)tex capacity:(NSUInteger)capacity;

/** initializes the particle system with the name of a file on disk (for a list of supported formats look at the CCTexture2D class), a capacity of particles */
-(id)initWithFile:(NSString *)fileImage capacity:(NSUInteger)capacity;

/** Add a child into the CCParticleBatchNode */
-(void) addChild:(CCParticleSystem*)child z:(NSInteger)z tag:(NSInteger) aTag;

/** Inserts a child into the CCParticleBatchNode  插入子节点 */
-(void) insertChild:(CCParticleSystem*) pSystem inAtlasAtIndex:(NSUInteger)index;

/** remove child from the CCParticleBatchNode  删除 */
-(void) removeChild:(CCParticleSystem*) pSystem cleanup:(BOOL)doCleanUp;

/** disables a particle by inserting a 0'd quad into the texture atlas  是一个子节点失效*/
-(void) disableParticle:(NSUInteger) particleIndex;
@end
