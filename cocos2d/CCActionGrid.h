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


#import "CCActionInterval.h"
#import "CCActionInstant.h"
#import "CCGrid.h"

@class CCGridBase;

/** Base class for Grid actions 网格基类 */
@interface CCGridAction : CCActionInterval
{
	ccGridSize gridSize_;
}

/** size of the grid  大小参数*/
@property (nonatomic,readwrite) ccGridSize gridSize;

/** creates the action with size and duration    使用大小和周期参数来创建和初始化*/
+(id) actionWithSize:(ccGridSize)size duration:(ccTime)d;
/** initializes the action with size and duration */
-(id) initWithSize:(ccGridSize)gridSize duration:(ccTime)d;
/** returns the grid  返回一个基类*/
-(CCGridBase *)grid;

@end

////////////////////////////////////////////////////////////

/** Base class for CCGrid3D actions.
 Grid3D actions can modify a non-tiled grid.
3D网格，非平面的
 */
@interface CCGrid3DAction : CCGridAction
{
}

/** returns the vertex than belongs to certain position in the grid  返回一个顶点*/
-(ccVertex3F)vertex:(ccGridSize)pos;
/** returns the non-transformed vertex than belongs to certain position in the grid  返回一个非转化顶点 */
-(ccVertex3F)originalVertex:(ccGridSize)pos;
/** sets a new vertex to a certain position of the grid  设置一个特定位置的顶点*/
-(void)setVertex:(ccGridSize)pos vertex:(ccVertex3F)vertex;

@end

////////////////////////////////////////////////////////////

/** Base class for CCTiledGrid3D actions 基于瓦片或者瓷砖的3D */
@interface CCTiledGrid3DAction : CCGridAction
{
}

/** returns the tile that belongs to a certain position of the grid 返回的瓦属于网格的特定位置 */
-(ccQuad3)tile:(ccGridSize)pos;
/** returns the non-transformed tile that belongs to a certain position of the grid 
返回一个非转化的
*/
-(ccQuad3)originalTile:(ccGridSize)pos;
/** sets a new tile to a certain position of the grid  设置一个新的 */
-(void)setTile:(ccGridSize)pos coords:(ccQuad3)coords;

@end

////////////////////////////////////////////////////////////

/** CCAccelDeccelAmplitude action */
@interface CCAccelDeccelAmplitude : CCActionInterval
{
	float			rate_;
	CCActionInterval *other_;
}

/** amplitude rate  幅度频率*/
@property (nonatomic,readwrite) float rate;

/** creates the action with an inner action that has the amplitude property, and a duration time 使用幅度频率和周期创建方法 和下面的初始化方法 */
+(id)actionWithAction:(CCAction*)action duration:(ccTime)d;
/** initializes the action with an inner action that has the amplitude property, and a duration time */
-(id)initWithAction:(CCAction*)action duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCAccelAmplitude action 加速幅度运动 */
@interface CCAccelAmplitude : CCActionInterval
{
	float			rate_;
	CCActionInterval *other_;
}

/** amplitude rate 幅度频率 */
@property (nonatomic,readwrite) float rate;

/** creates the action with an inner action that has the amplitude property, and a duration time  解释同上 */
+(id)actionWithAction:(CCAction*)action duration:(ccTime)d;
/** initializes the action with an inner action that has the amplitude property, and a duration time */
-(id)initWithAction:(CCAction*)action duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCDeccelAmplitude action  减速幅度运动，后面的注释如上*/
@interface CCDeccelAmplitude : CCActionInterval
{
	float			rate_;
	CCActionInterval *other_;
}

/** amplitude rate */
@property (nonatomic,readwrite) float rate;

/** creates the action with an inner action that has the amplitude property, and a duration time */
+(id)actionWithAction:(CCAction*)action duration:(ccTime)d;
/** initializes the action with an inner action that has the amplitude property, and a duration time */
-(id)initWithAction:(CCAction*)action duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCStopGrid action.  停止网格运动
 Don't call this action if another grid action is active.
 Call if you want to remove the the grid effect. Example:
 [Sequence actions:[Lens ...], [StopGrid action], nil];
如果你要删除此网格，不要调用此运动当它是活动的时候
 */
@interface CCStopGrid : CCActionInstant
{
}
@end

////////////////////////////////////////////////////////////

/** CCReuseGrid action   重用 */
@interface CCReuseGrid : CCActionInstant
{
	int t_;
}
/** creates an action with the number of times that the current grid will be reused 
创建和初始化一个可以带有重用次数的网格运动
*/
+(id) actionWithTimes: (int) times;
/** initializes an action with the number of times that the current grid will be reused */
-(id) initWithTimes: (int) times;
@end
