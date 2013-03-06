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

//运动类使用到时间，调用系统时间
#include <sys/time.h>
#import <Foundation/Foundation.h>

#import "ccTypes.h"

enum {
	//! Default tag		默认标记 -1
	kCCActionTagInvalid = -1,
};

/** Base class for CCAction objects.
 * 运动类对象 基础类
 */
 
@interface CCAction : NSObject <NSCopying>
{
	id			originalTarget_;
	id			target_;
	NSInteger	tag_;
}

/** The "target". The action will modify the target properties.
 The target will be set with the 'startWithTarget' method.
 When the 'stop' method is called, target will be set to nil.
 The target is 'assigned', it is not 'retained'.
 关于目标：运动修改目标属性时，调用startWithTarget方法来设置，调用stop方法时，就将目标设置为nil.
 而目标是assigned属性，不是retained
 */
@property (nonatomic,readonly,assign) id target;

/** The original target, since target can be nil.
 Is the target that were used to run the action. Unless you are doing something complex, like CCActionManager, you should NOT call this method.
 @since v0.8.2
 原目标为nil。 该属性在运行中被使用。除了做一些复杂像CCActionManager时，才使用。通常不调用该方法
*/
@property (nonatomic,readonly,assign) id originalTarget;


/** The action tag. An identifier of the action 	
运动标记，用一个独一无二的值来标示动作*/
@property (nonatomic,readwrite,assign) NSInteger tag;

/** Allocates and initializes the action 	分配并初始化动作*/
+(id) action;

/** Initializes the action 初始化动作*/
-(id) init;

-(id) copyWithZone: (NSZone*) zone;

//! return YES if the action has finished	当一个动作完成时返回是
-(BOOL) isDone;
//! called before the action start. It will also set the target.	调用此方法开始运动，而目标被设置
-(void) startWithTarget:(id)target;
//! called after the action has finished. It will set the 'target' to nil.
//! IMPORTANT: You should never call "[action stop]" manually. Instead, use: "[target stopAction:action];"
// 懂运动结束时调用stop方法，并设置目标为nil 。 并且要记住不要调用[action stop] 方格，而是用[target stopAction:action]
-(void) stop;
//! called every frame with its delta time. DON'T override unless you know what you are doing.
//每个时间差调用。 不要重载，除非你知道你要做些什么
-(void) step: (ccTime) dt;
//! called once per frame. time a value between 0 and 1
//! For example:
//! * 0 means that the action just started
//! * 0.5 means that the action is in the middle
//! * 1 means that the action is over
// 每帧调用一次。如：0到1为一个时间差，0.5就是处于运动的中间时刻，而1则表示此运动结束，进行下一个
-(void) update: (ccTime) time;

@end

/** Base class actions that do have a finite time duration.
 Possible actions:
   - An action with a duration of 0 seconds
   - An action with a duration of 35.5 seconds
 Infitite time actions are valid
 运动都有时间长短的。 就是说一个运动的时间有长短。 有限的时间的运动是有效的
 */
@interface CCFiniteTimeAction : CCAction <NSCopying>
{
	//! duration in seconds		用秒而计算运动
	ccTime duration_;
}
//! duration in seconds of the action	属性时间长度
@property (nonatomic,readwrite) ccTime duration;

/** returns a reversed action	返回一个方向的运动 */
- (CCFiniteTimeAction*) reverse;
@end


@class CCActionInterval;
/** Repeats an action for ever. 
 To repeat the an action for a limited number of times use the Repeat action.
 @warning This action can't be Sequenceable because it is not an IntervalAction
 重复一个动作
 在限定的次数内重复运动。 此运动不能是Sequenceable,由于它不是IntervalAction类。
 */
@interface CCRepeatForever : CCAction <NSCopying>
{
	CCActionInterval *innerAction_;
}
/** Inner action	内在运动 */
@property (nonatomic, readwrite, retain) CCActionInterval *innerAction;

/** creates the action	创建一个运动 */
+(id) actionWithAction: (CCActionInterval*) action;
/** initializes the action 初始化一个运动 */
-(id) initWithAction: (CCActionInterval*) action;
@end

/** Changes the speed of an action, making it take longer (speed<1)
 or less (speed>1) time.
 Useful to simulate 'slow motion' or 'fast forward' effect.
 @warning This action can't be Sequenceable because it is not an CCIntervalAction
 改变一个运动的速度。使用慢镜头和快进效果。 同样不能设置为Sequenceable
 */
@interface CCSpeed : CCAction <NSCopying>
{
	CCActionInterval	*innerAction_;
	float speed_;
}
/** alter the speed of the inner function in runtime 改变内部函数运行时的速度*/
@property (nonatomic,readwrite) float speed;
/** Inner action of CCSpeed 	内在运动的CCSpeed*/
@property (nonatomic, readwrite, retain) CCActionInterval *innerAction;

/** creates the action	创建运动 */
+(id) actionWithAction: (CCActionInterval*) action speed:(float)value;
/** initializes the action 	初始化运动*/
-(id) initWithAction: (CCActionInterval*) action speed:(float)value;
@end

@class CCNode;
/** CCFollow is an action that "follows" a node.
跟随是一种运动，也是一个节点
 Eg:
	[layer runAction: [CCFollow actionWithTarget:hero]];

 Instead of using CCCamera as a "follower", use this action instead.
 替代CCCamera作为跟随者，使用此种运动
 @since v0.99.2
 */
@interface CCFollow : CCAction <NSCopying>
{
	/* node to follow	节点跟随 */
	CCNode	*followedNode_;

	/* whether camera should be limited to certain area  摄像是否限制在特定的区域里*/
	BOOL boundarySet;

	/* if screensize is bigger than the boundary - update not needed  如果屏幕大于边界，不用更新*/
	BOOL boundaryFullyCovered;

	/* fast access to the screen dimensions		快速访问屏幕尺寸 */
	CGPoint halfScreenSize;
	CGPoint fullScreenSize;

	/* world boundaries 	边界*/
	float leftBoundary;
	float rightBoundary;
	float topBoundary;
	float bottomBoundary;
}

/** alter behavior - turn on/off boundary 	改变行为，是否开启边界设置*/
@property (nonatomic,readwrite) BOOL boundarySet;

/** creates the action with no boundary set 创建一个运动没有边界设置*/
+(id) actionWithTarget:(CCNode *)followedNode;

/** creates the action with a set boundary 创建一个有边界的运动*/
+(id) actionWithTarget:(CCNode *)followedNode worldBoundary:(CGRect)rect;

/** initializes the action 从跟随节点来初始化一个运动 */
-(id) initWithTarget:(CCNode *)followedNode;

/** initializes the action with a set boundary 初始化一个带有边界的运动*/
-(id) initWithTarget:(CCNode *)followedNode worldBoundary:(CGRect)rect;

@end

