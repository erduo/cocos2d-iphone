/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2009 On-Core
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


#import <Foundation/Foundation.h>

#import "CCNode.h"
#import "CCCamera.h"
#import "ccTypes.h"
#import "CCDirector.h"
#import "kazmath/mat4.h"
//节点，摄像，类型，导演
@class CCTexture2D;
@class CCGrabber;
@class CCGLProgram;

/** Base class for other
网格基类
 */
@interface CCGridBase : NSObject
{
	BOOL		active_;
	int			reuseGrid_;
	ccGridSize	gridSize_;
	CCTexture2D *texture_;
	CGPoint		step_;
	CCGrabber	*grabber_;
	BOOL		isTextureFlipped_;

	CCGLProgram	*shaderProgram_;

	ccDirectorProjection	directorProjection_;
}

/** wheter or not the grid is active   是否活动 */
@property (nonatomic,readwrite) BOOL active;
/** number of times that the grid will be reused  重用次数 */
@property (nonatomic,readwrite) int reuseGrid;
/** size of the grid   大小*/
@property (nonatomic,readonly) ccGridSize gridSize;
/** pixels between the grids 网格之间的像素*/
@property (nonatomic,readwrite) CGPoint step;
/** texture used  纹理 */
@property (nonatomic, retain) CCTexture2D *texture;
/** grabber used 采集器*/
@property (nonatomic, retain) CCGrabber *grabber;
/** is texture flipped 纹理翻转*/
@property (nonatomic, readwrite) BOOL isTextureFlipped;
/** shader program 着色方案 */
@property (nonatomic, readwrite, assign) CCGLProgram *shaderProgram;

+(id) gridWithSize:(ccGridSize)gridSize texture:(CCTexture2D*)texture flippedTexture:(BOOL)flipped;
+(id) gridWithSize:(ccGridSize)gridSize;

-(id) initWithSize:(ccGridSize)gridSize texture:(CCTexture2D*)texture flippedTexture:(BOOL)flipped;
-(id)initWithSize:(ccGridSize)gridSize;
-(void)beforeDraw;
-(void)afterDraw:(CCNode*)target;
-(void)blit;
-(void)reuse;

-(void)calculateVertexPoints;

@end

////////////////////////////////////////////////////////////

/**
 CCGrid3D is a 3D grid implementation. Each vertex has 3 dimensions: x,y,z
三维网格
 */
@interface CCGrid3D : CCGridBase
{
	GLvoid		*texCoordinates;
	GLvoid		*vertices;
	GLvoid		*originalVertices;
	GLushort	*indices;
}

/** returns the vertex at a given position  返回一个顶点*/
-(ccVertex3F)vertex:(ccGridSize)pos;
/** returns the original (non-transformed) vertex at a given position 返回一个非转化顶点*/
-(ccVertex3F)originalVertex:(ccGridSize)pos;
/** sets a new vertex at a given position 给定一个位置设置一耳光新顶点*/
-(void)setVertex:(ccGridSize)pos vertex:(ccVertex3F)vertex;

@end

////////////////////////////////////////////////////////////

/**
 CCTiledGrid3D is a 3D grid implementation. It differs from Grid3D in that
 the tiles can be separated from the grid.
瓦片网格，不同3D网格，它可以从网格中分离
*/
@interface CCTiledGrid3D : CCGridBase
{
	GLvoid		*texCoordinates;
	GLvoid		*vertices;
	GLvoid		*originalVertices;
	GLushort	*indices;
}

/** returns the tile at the given position   返回瓷砖 */
-(ccQuad3)tile:(ccGridSize)pos;
/** returns the original tile (untransformed) at the given position  返回非转化的瓷砖 */
-(ccQuad3)originalTile:(ccGridSize)pos;
/** sets a new tile  设定一个新的瓷砖 */
-(void)setTile:(ccGridSize)pos coords:(ccQuad3)coords;

@end
