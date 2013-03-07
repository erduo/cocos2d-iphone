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

/** CCWaves3D action  波形3D运动*/
@interface CCWaves3D : CCGrid3DAction
{
	int waves;
	float amplitude;
	float amplitudeRate;
}

/** amplitude of the wave 波的幅度 */
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate of the wave  幅度的频率*/
@property (nonatomic,readwrite) float amplitudeRate;
//使用周期大小以及幅度来创建和初始化方法
+(id)actionWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
-(id)initWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCFlipX3D action 以x轴进行翻动 */
@interface CCFlipX3D : CCGrid3DAction
{
}

/** creates the action with duration 使用周期参数来创建和初始化 */
+(id) actionWithDuration:(ccTime)d;
/** initizlies the action with duration */
-(id) initWithDuration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCFlipY3D action  以y轴进行翻动*/
@interface CCFlipY3D : CCFlipX3D
{
}

@end

////////////////////////////////////////////////////////////

/** CCLens3D action  镜像3D */
@interface CCLens3D : CCGrid3DAction
{
	CGPoint	position_;
	float	radius_;
	float	lensEffect_;
	BOOL	dirty_;
}

/** lens effect. Defaults to 0.7 - 0 means no effect, 1 is very strong effect 
    透镜的效果，默认为0.7    0标示没有效果，1为非常强烈
*/
@property (nonatomic,readwrite) float lensEffect;
/** lens center position in Points  透镜的中心位置 */
@property (nonatomic,readwrite) CGPoint position;

/** creates the action with center position in Points, radius, a grid size and duration   使用中心位置，角度，大小和周期创建和初始化 */
+(id)actionWithPosition:(CGPoint)pos radius:(float)r grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with center position in Points, radius, a grid size and duration */
-(id)initWithPosition:(CGPoint)pos radius:(float)r grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCRipple3D action   3D波纹*/
@interface CCRipple3D : CCGrid3DAction
{
	CGPoint	position_;
	float	radius_;
	int		waves_;
	float	amplitude_;
	float	amplitudeRate_;
}

/** center position in Points 中心位置点 */
@property (nonatomic,readwrite) CGPoint position;
/** amplitude 幅度 */
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate 频率*/
@property (nonatomic,readwrite) float amplitudeRate;

/** creates the action with a position in points, radius, number of waves, amplitude, a grid size and duration 
使用中心位置点，角度，波的个数，幅度，大小和周期来创建和初始化方法
*/
+(id)actionWithPosition:(CGPoint)pos radius:(float)r waves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a position in points, radius, number of waves, amplitude, a grid size and duration */
-(id)initWithPosition:(CGPoint)pos radius:(float)r waves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCShaky3D action  摇动3D*/
@interface CCShaky3D : CCGrid3DAction
{
	int		randrange;
	BOOL	shakeZ;
}

/** creates the action with a range, shake Z vertices, a grid and duration
使用范围，大小，周期和是否是z轴方向 参数来创建和初始化
 */
+(id)actionWithRange:(int)range shakeZ:(BOOL)shakeZ grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with a range, shake Z vertices, a grid and duration */
-(id)initWithRange:(int)range shakeZ:(BOOL)shakeZ grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCLiquid action  液体效果运动*/
@interface CCLiquid : CCGrid3DAction
{
	int waves;
	float amplitude;
	float amplitudeRate;

}

/** amplitude  幅度*/
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate  幅度频率 */
@property (nonatomic,readwrite) float amplitudeRate;

/** creates the action with amplitude, a grid and duration  使用波的个数，幅度，大小，周期参数来创建和初始化 */
+(id)actionWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with amplitude, a grid and duration */
-(id)initWithWaves:(int)wav amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCWaves action  波 */
@interface CCWaves : CCGrid3DAction
{
	int		waves;
	float	amplitude;
	float	amplitudeRate;
	BOOL	vertical;
	BOOL	horizontal;
}

/** amplitude 幅度*/
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate 幅度频率*/
@property (nonatomic,readwrite) float amplitudeRate;

/** initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration 参数有幅度，大小，周期，是否是水平或垂直方向 来创建和初始化*/
+(id)actionWithWaves:(int)wav amplitude:(float)amp horizontal:(BOOL)h vertical:(BOOL)v grid:(ccGridSize)gridSize duration:(ccTime)d;
/** creates the action with amplitude, horizontal sin, vertical sin, a grid and duration */
-(id)initWithWaves:(int)wav amplitude:(float)amp horizontal:(BOOL)h vertical:(BOOL)v grid:(ccGridSize)gridSize duration:(ccTime)d;

@end

////////////////////////////////////////////////////////////

/** CCTwirl action  捻*/
@interface CCTwirl : CCGrid3DAction
{
	CGPoint	position_;
	int		twirls_;
	float	amplitude_;
	float	amplitudeRate_;
}

/** twirl center 捻的中心位置点 */
@property (nonatomic,readwrite) CGPoint position;
/** amplitude 幅度*/
@property (nonatomic,readwrite) float amplitude;
/** amplitude rate 频率*/
@property (nonatomic,readwrite) float amplitudeRate;

/** creates the action with center position, number of twirls, amplitude, a grid size and duration 使用中心位置，捻的个数，幅度，大小，周期参数来创建和初始化*/
+(id)actionWithPosition:(CGPoint)pos twirls:(int)t amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;
/** initializes the action with center position, number of twirls, amplitude, a grid size and duration */
-(id)initWithPosition:(CGPoint)pos twirls:(int)t amplitude:(float)amp grid:(ccGridSize)gridSize duration:(ccTime)d;

@end
