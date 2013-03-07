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

#import "CCActionGrid.h"

/** CCShakyTiles3D action */
@interface CCShakyTiles3D : CCTiledGrid3DAction
{
	int		randrange;
	BOOL	shakeZ;
}

/** creates the action with a range, whether or not to shake Z vertices, a grid size, and duration   使用范围，是否z轴，大小，周期来创建和初始化方法 */
+(id)actionWithRange:(int)range shakeZ:(BOOL)shakeZ grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a range, whether or not to shake Z vertices, a grid size, and duration */
-(id)initWithRange:(int)range shakeZ:(BOOL)shakeZ grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCShatteredTiles3D action   破碎瓦片效果：参数有范围，是否立即，z轴方向 */
@interface CCShatteredTiles3D : CCTiledGrid3DAction
{
	int		randrange;
	BOOL	once;
	BOOL	shatterZ;
}

/** creates the action with a range, whether of not to shatter Z vertices, a grid size and duration */
+(id)actionWithRange:(int)range shatterZ:(BOOL)shatterZ grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration */
-(id)initWithRange:(int)range shatterZ:(BOOL)shatterZ grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCShuffleTiles action
 Shuffle the tiles in random order
拖拽：随机数，大小，周期
 */
@interface CCShuffleTiles : CCTiledGrid3DAction
{
	int	seed;
	NSUInteger tilesCount;
	int *tilesOrder;
	void *tiles;
}

/** creates the action with a random seed, the grid size and the duration */
+(id)actionWithSeed:(int)s grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a random seed, the grid size and the duration */
-(id)initWithSeed:(int)s grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCFadeOutTRTiles action
 Fades out the tiles in a Top-Right direction
从右上方淡出效果
 */
@interface CCFadeOutTRTiles : CCTiledGrid3DAction
{
}
@end

////////////////////////////////////////////////////////////

/** CCFadeOutBLTiles action.
 Fades out the tiles in a Bottom-Left direction
左下方
 */
@interface CCFadeOutBLTiles : CCFadeOutTRTiles
{
}
@end

////////////////////////////////////////////////////////////

/** CCFadeOutUpTiles action.
 Fades out the tiles in upwards direction
从上方
 */
@interface CCFadeOutUpTiles : CCFadeOutTRTiles
{
}
@end

////////////////////////////////////////////////////////////

/** CCFadeOutDownTiles action.
 Fades out the tiles in downwards direction
正下方
 */
@interface CCFadeOutDownTiles : CCFadeOutUpTiles
{
}
@end

////////////////////////////////////////////////////////////

/** CCTurnOffTiles action.
 Turn off the files in random order  关：种子，大小，周期
 */
@interface CCTurnOffTiles : CCTiledGrid3DAction
{
	int	seed;
	NSUInteger tilesCount;
	int *tilesOrder;
}

/** creates the action with a random seed, the grid size and the duration */
+(id)actionWithSeed:(int)s grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a random seed, the grid size and the duration */
-(id)initWithSeed:(int)s grid:(ccGridSize)gridSize duration:(ccTime)d;
@end

////////////////////////////////////////////////////////////

/** CCWavesTiles3D action.  波纹：波个数，幅度，频率*/
@interface CCWavesTiles3D : CCTiledGrid3DAction
{
	int waves;
	float amplitude;
	float amplitudeRate;
}

/** waves amplitude */
@property (nonatomic,readwrite) float amplitude;
/** waves amplitude rate */
@property (nonatomic,readwrite) float amplitudeRate;

/** creates the action with a number of waves, the waves amplitude, the grid size and the duration */
+(id)actionWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a number of waves, the waves amplitude, the grid size and the duration */
-(id)initWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCJumpTiles3D action. 跳跃：sin函数，抛物线；参数有次数，幅度，频率
 A sin function is executed to move the tiles across the Z axis
 */
@interface CCJumpTiles3D : CCTiledGrid3DAction
{
	int jumps;
	float amplitude;
	float amplitudeRate;
}

/** amplitude of the sin*/
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate */
@property (nonatomic,readwrite) float amplitudeRate;

/** creates the action with the number of jumps, the sin amplitude, the grid size and the duration */
+(id)actionWithJumps:(int)j amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with the number of jumps, the sin amplitude, the grid size and the duration */
-(id)initWithJumps:(int)j amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCSplitRows action   拆分：行数，大小，周期*/
@interface CCSplitRows : CCTiledGrid3DAction
{
	int		rows;
	CGSize	winSize;
}
/** creates the action with the number of rows to split and the duration */
+(id)actionWithRows:(int)rows duration:(ccTime)duration;
/** initializes the action with the number of rows to split and the duration */
-(id)initWithRows:(int)rows duration:(ccTime)duration;

@end

////////////////////////////////////////////////////////////

/** CCSplitCols action    拆分列： 列数，大小*/
@interface CCSplitCols : CCTiledGrid3DAction
{
	int		cols;
	CGSize	winSize;
}
/** creates the action with the number of columns to split and the duration */
+(id)actionWithCols:(int)cols duration:(ccTime)duration;
/** initializes the action with the number of columns to split and the duration */
-(id)initWithCols:(int)cols duration:(ccTime)duration;

@end
