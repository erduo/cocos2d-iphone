/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2011 Ricardo Quesada
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


#import "CCNode.h"
#import "CCAction.h"
#import "CCProtocols.h"

#include <sys/time.h>
//节点，运动，协议，系统时间
/** An interval action is an action that takes place within a certain period of time.
It has an start time, and a finish time. The finish time is the parameter
duration plus the start time.
间隔运动就是运动持续了一段时间。它具有开始时间，结束时间，而结束时间就是开始时间加上持续时间。
These CCActionInterval actions have some interesting properties, like:
 - They can run normally (default)
 - They can run reversed with the reverse method
 - They can run with the time altered with the Accelerate, AccelDeccel and Speed actions.
而间隔运动有意向特性：
可以正常运动；
可以反向运动；
可以在运行时改变速度，加速和减速；
For example, you can simulate a Ping Pong effect running the action normally and
then running it again in Reverse mode.
例如，你可以模拟一乒乓球运行效果可以是正常或逆向模式。
Example:

	CCAction * pingPongAction = [CCSequence actions: action, [action reverse], nil];
*/
@interface CCActionInterval: CCFiniteTimeAction <NSCopying>
{
	ccTime	elapsed_;
	BOOL	firstTick_;
}

/** how many seconds had elapsed since the actions started to run.  从运行开始持续的时间参数
*/
@property (nonatomic,readonly) ccTime elapsed;
//创建，初始化，是否完成，是否反向等方法
/** creates the action */
+(id) actionWithDuration: (ccTime) d;
/** initializes the action */
-(id) initWithDuration: (ccTime) d;
/** returns YES if the action has finished */
-(BOOL) isDone;
/** returns a reversed action */
- (CCActionInterval*) reverse;
@end

/** Runs actions sequentially, one after another
运行运动的序列，一个接一个
 */
@interface CCSequence : CCActionInterval <NSCopying>
{
	CCFiniteTimeAction *actions_[2];
	ccTime split_;
	int last_;
}
/** helper contructor to create an array of sequenceable actions  助手构造一个带有序列的运行 */
+(id) actions: (CCFiniteTimeAction*) action1, ... NS_REQUIRES_NIL_TERMINATION;
/** helper contructor to create an array of sequenceable actions given an array 
给定一个数组来构造
*/
+(id) actionWithArray: (NSArray*) arrayOfActions;
/** creates the action */
+(id) actionOne:(CCFiniteTimeAction*)actionOne two:(CCFiniteTimeAction*)actionTwo;
/** initializes the action */
-(id) initOne:(CCFiniteTimeAction*)actionOne two:(CCFiniteTimeAction*)actionTwo;
@end


/** Repeats an action a number of times. 重复一个运动 次数
 * To repeat an action forever use the CCRepeatForever action.
 */
@interface CCRepeat : CCActionInterval <NSCopying>
{
	NSUInteger times_;
	NSUInteger total_;
	ccTime nextDt_;
	BOOL isActionInstant_;
	CCFiniteTimeAction *innerAction_;
}

/** Inner action */
@property (nonatomic,readwrite,retain) CCFiniteTimeAction *innerAction;

/** creates a CCRepeat action. Times is an unsigned integer between 1 and MAX_UINT.   创建和初始化一个重复运动，次数为无符号整数从1到最大值
 */
+(id) actionWithAction:(CCFiniteTimeAction*)action times: (NSUInteger)times;
/** initializes a CCRepeat action. Times is an unsigned integer between 1 and MAX_UINT */
-(id) initWithAction:(CCFiniteTimeAction*)action times: (NSUInteger)times;
@end

/** Spawn a new action immediately  立即生产一个新的运动
 */
@interface CCSpawn : CCActionInterval <NSCopying>
{
	CCFiniteTimeAction *one_;
	CCFiniteTimeAction *two_;
}
/** helper constructor to create an array of spawned actions 
使用构造助手来创建和初始化一个运动；带指定数组的。   后面怎么使用待使用效果??
*/
+(id) actions: (CCFiniteTimeAction*) action1, ... NS_REQUIRES_NIL_TERMINATION;
/** helper contructor to create an array of spawned actions given an array */
+(id) actionWithArray: (NSArray*) arrayOfActions;
/** creates the Spawn action */
+(id) actionOne: (CCFiniteTimeAction*) one two:(CCFiniteTimeAction*) two;
/** initializes the Spawn action with the 2 actions to spawn */
-(id) initOne: (CCFiniteTimeAction*) one two:(CCFiniteTimeAction*) two;
@end

/**  Rotates a CCNode object to a certain angle by modifying it's
 rotation attribute.
 The direction will be decided by the shortest angle.
以特定角度转动来修改节点对象的旋转属性。 
而方向决定了最短角度
*/
@interface CCRotateTo : CCActionInterval <NSCopying>
{
	float dstAngle_;
	float startAngle_;
	float diffAngle_;
}
/** creates the action   创建和初始化*/
+(id) actionWithDuration:(ccTime)duration angle:(float)angle;
/** initializes the action */
-(id) initWithDuration:(ccTime)duration angle:(float)angle;
@end

/** Rotates a CCNode object clockwise a number of degrees by modiying its rotation attribute.
*/
@interface CCRotateBy : CCActionInterval <NSCopying>
{
	float angle_;
	float startAngle_;
}
/** creates the action */
+(id) actionWithDuration:(ccTime)duration angle:(float)deltaAngle;
/** initializes the action */
-(id) initWithDuration:(ccTime)duration angle:(float)deltaAngle;
@end

/** Moves a CCNode object to the position x,y. x and y are absolute coordinates by modifying its position attribute.
通过坐标来移动节点对象； 开始位置，结束位置，距离，要么是to,或by来定义
*/
@interface CCMoveTo : CCActionInterval <NSCopying>
{
	CGPoint endPosition_;
	CGPoint startPosition_;
	CGPoint delta_;
}
/** creates the action */
+(id) actionWithDuration:(ccTime)duration position:(CGPoint)position;
/** initializes the action */
-(id) initWithDuration:(ccTime)duration position:(CGPoint)position;
@end

/**  Moves a CCNode object x,y pixels by modifying its position attribute.
 x and y are relative to the position of the object.
 Duration is is seconds.  周期是秒
*/
@interface CCMoveBy : CCMoveTo <NSCopying>
{
}
/** creates the action */
+(id) actionWithDuration: (ccTime)duration position:(CGPoint)deltaPosition;
/** initializes the action */
-(id) initWithDuration: (ccTime)duration position:(CGPoint)deltaPosition;
@end

/** Skews a CCNode object to given angles by modifying its skewX and skewY attributes
 @since v1.0 
倾斜一个节点对象，使用给定的角度，修改倾斜属性
 */
@interface CCSkewTo : CCActionInterval <NSCopying>
{
	float skewX_;
	float skewY_;
	float startSkewX_;
	float startSkewY_;
	float endSkewX_;
	float endSkewY_;
	float deltaX_;
	float deltaY_;
}
/** creates the action */
+(id) actionWithDuration:(ccTime)t skewX:(float)sx skewY:(float)sy;
/** initializes the action */
-(id) initWithDuration:(ccTime)t skewX:(float)sx skewY:(float)sy;
@end

/** Skews a CCNode object by skewX and skewY degrees
 @since v1.0
 */
@interface CCSkewBy : CCSkewTo <NSCopying>
{
}
@end

/** Moves a CCNode object simulating a parabolic jump movement by modifying its position attribute.
移动节点对象模拟抛物线来修改其属性
*/
 @interface CCJumpBy : CCActionInterval <NSCopying>
{
	CGPoint startPosition_;
	CGPoint delta_;
	ccTime height_;
	NSUInteger jumps_;
}
/** creates the action */
+(id) actionWithDuration: (ccTime)duration position:(CGPoint)position height:(ccTime)height jumps:(NSUInteger)jumps;
/** initializes the action */
-(id) initWithDuration: (ccTime)duration position:(CGPoint)position height:(ccTime)height jumps:(NSUInteger)jumps;
@end

/** Moves a CCNode object to a parabolic position simulating a jump movement by modifying its position attribute.
*/
 @interface CCJumpTo : CCJumpBy <NSCopying>
{
}
@end

/** bezier configuration structure
贝塞尔配置结构
 */
typedef struct _ccBezierConfig {
	//! end position of the bezier
	CGPoint endPosition;
	//! Bezier control point 1  贝塞尔控制点
	CGPoint controlPoint_1;
	//! Bezier control point 2
	CGPoint controlPoint_2;
} ccBezierConfig;

/** An action that moves the target with a cubic Bezier curve by a certain distance.   移动目标带有贝塞尔曲线及特定距离，这个使用数学函数方法？？
 */
@interface CCBezierBy : CCActionInterval <NSCopying>
{
	ccBezierConfig config_;
	CGPoint startPosition_;
}

/** creates the action with a duration and a bezier configuration 使用周期和贝塞尔配置参数来创建和初始化方法 */
+(id) actionWithDuration: (ccTime) t bezier:(ccBezierConfig) c;

/** initializes the action with a duration and a bezier configuration */
-(id) initWithDuration: (ccTime) t bezier:(ccBezierConfig) c;
@end

/** An action that moves the target with a cubic Bezier curve to a destination point.
 @since v0.8.2
 */
@interface CCBezierTo : CCBezierBy
{
}
@end

/** Scales a CCNode object to a zoom factor by modifying its scale attribute.
 @warning This action doesn't support "reverse"
缩放属性的修改。 不支持方向
 */
@interface CCScaleTo : CCActionInterval <NSCopying>
{
	float scaleX_;
	float scaleY_;
	float startScaleX_;
	float startScaleY_;
	float endScaleX_;
	float endScaleY_;
	float deltaX_;
	float deltaY_;
}
/** creates the action with the same scale factor for X and Y  使用相同比例缩放x,y轴来创建和初始化方法
*/
+(id) actionWithDuration: (ccTime)duration scale:(float) s;
/** initializes the action with the same scale factor for X and Y */
-(id) initWithDuration: (ccTime)duration scale:(float) s;
/** creates the action with and X factor and a Y factor */
+(id) actionWithDuration: (ccTime)duration scaleX:(float) sx scaleY:(float)sy;
/** initializes the action with and X factor and a Y factor    x,y轴不同*/
-(id) initWithDuration: (ccTime)duration scaleX:(float) sx scaleY:(float)sy;
@end

/** Scales a CCNode object a zoom factor by modifying its scale attribute.
*/
@interface CCScaleBy : CCScaleTo <NSCopying>
{
}
@end

/** Blinks a CCNode object by modifying its visible attribute
闪烁一个节点对象，来修改其可见性。 创建和初始化方法
*/
@interface CCBlink : CCActionInterval <NSCopying>
{
	NSUInteger times_;
}
/** creates the action */
+(id) actionWithDuration: (ccTime)duration blinks:(NSUInteger)blinks;
/** initilizes the action */
-(id) initWithDuration: (ccTime)duration blinks:(NSUInteger)blinks;
@end

/** Fades In an object that implements the CCRGBAProtocol protocol. It modifies the opacity from 0 to 255.
 The "reverse" of this action is FadeOut
实现淡入和淡出属性。 从0到255为入，从255到0是出
 */
@interface CCFadeIn : CCActionInterval <NSCopying>
{
}
@end

/** Fades Out an object that implements the CCRGBAProtocol protocol. It modifies the opacity from 255 to 0.
 The "reverse" of this action is FadeIn
*/
@interface CCFadeOut : CCActionInterval <NSCopying>
{
}
@end

/** Fades an object that implements the CCRGBAProtocol protocol. It modifies the opacity from the current value to a custom one.
 @warning This action doesn't support "reverse"
给定一个值来修改淡出属性
 */
@interface CCFadeTo : CCActionInterval <NSCopying>
{
	GLubyte toOpacity_;
	GLubyte fromOpacity_;
}
/** creates an action with duration and opactiy */
+(id) actionWithDuration:(ccTime)duration opacity:(GLubyte)opactiy;
/** initializes the action with duration and opacity */
-(id) initWithDuration:(ccTime)duration opacity:(GLubyte)opacity;
@end

/** Tints a CCNode that implements the CCNodeRGB protocol from current tint to a custom one.
 @warning This action doesn't support "reverse"
 @since v0.7.2
着色节点。 不支持反向
*/
@interface CCTintTo : CCActionInterval <NSCopying>
{
	ccColor3B to_;
	ccColor3B from_;
}
/** creates an action with duration and color  使用周期参数和颜色参数来创建和初始化方法
*/
+(id) actionWithDuration:(ccTime)duration red:(GLubyte)red green:(GLubyte)green blue:(GLubyte)blue;
/** initializes the action with duration and color */
-(id) initWithDuration:(ccTime)duration red:(GLubyte)red green:(GLubyte)green blue:(GLubyte)blue;
@end

/** Tints a CCNode that implements the CCNodeRGB protocol from current tint to a custom one.
 @since v0.7.2
 */
@interface CCTintBy : CCActionInterval <NSCopying>
{
	GLshort deltaR_, deltaG_, deltaB_;
	GLshort fromR_, fromG_, fromB_;
}
/** creates an action with duration and color */
+(id) actionWithDuration:(ccTime)duration red:(GLshort)deltaRed green:(GLshort)deltaGreen blue:(GLshort)deltaBlue;
/** initializes the action with duration and color */
-(id) initWithDuration:(ccTime)duration red:(GLshort)deltaRed green:(GLshort)deltaGreen blue:(GLshort)deltaBlue;
@end

/** Delays the action a certain amount of seconds
给定时间长度来延迟运动
*/
@interface CCDelayTime : CCActionInterval <NSCopying>
{
}
@end

/** Executes an action in reverse order, from time=duration to time=0
反向执行时，从周期到0；
 @warning Use this action carefully. This action is not
 sequenceable. Use it as the default "reversed" method
 of your own actions, but using it outside the "reversed"
 scope is not recommended.
注意使用该运动时，没有序列。自身使用反向，外部使用时不推荐使用反向。
*/
@interface CCReverseTime : CCActionInterval <NSCopying>
{
	CCFiniteTimeAction * other_;
}
/** creates the action */
+(id) actionWithAction: (CCFiniteTimeAction*) action;
/** initializes the action */
-(id) initWithAction: (CCFiniteTimeAction*) action;
@end


@class CCAnimation;
@class CCTexture2D;
/** Animates a sprite given the name of an Animation
使用给定的动画来展示精灵
 */
@interface CCAnimate : CCActionInterval <NSCopying>
{
	NSMutableArray		*splitTimes_;
	NSInteger			nextFrame_;
	CCAnimation			*animation_;
	id					origFrame_;
	NSUInteger			executedLoops_;
}
/** animation used for the animage   动画*/
@property (readwrite,nonatomic,retain) CCAnimation * animation;

/** creates the action with an Animation and will restore the original frame when the animation is over   创建动画行动*/
+(id) actionWithAnimation:(CCAnimation*)animation;
/** initializes the action with an Animation and will restore the original frame when the animtion is over */
-(id) initWithAnimation:(CCAnimation*)animation;
@end

/** Overrides the target of an action so that it always runs on the target
 * specified at action creation rather than the one specified by runAction.
重载目标对象运动
 */
@interface CCTargetedAction : CCActionInterval <NSCopying>
{
	id forcedTarget_;
	CCFiniteTimeAction* action_;
}
/** This is the target that the action will be forced to run with  该目标是运动中是被强制的
 */
@property(readwrite,nonatomic,retain) id forcedTarget;

/** Create an action with the specified action and forced target   创建一个指定运动和强制目标*/
+ (id) actionWithTarget:(id) target action:(CCFiniteTimeAction*) action;

/** Init an action with the specified action and forced target */
- (id) initWithTarget:(id) target action:(CCFiniteTimeAction*) action;

@end
