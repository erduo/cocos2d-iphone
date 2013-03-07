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


#import "CCAction.h"

/** Instant actions are immediate actions. They don't have a duration like
 the CCIntervalAction actions.
及时行动的方法，不具有时间周期
*/
@interface CCActionInstant : CCFiniteTimeAction <NSCopying>
{
}
@end

/** Show the node   展示
 */
 @interface CCShow : CCActionInstant
{
}
@end

/** Hide the node
 */
@interface CCHide : CCActionInstant
{
}
@end

/** Toggles the visibility of a node   切换可见性
 */
@interface CCToggleVisibility : CCActionInstant
{
}
@end

/** Flips the sprite horizontally  水平翻动 是否是
 @since v0.99.0
 */
@interface CCFlipX : CCActionInstant
{
	BOOL	flipX;
}
+(id) actionWithFlipX:(BOOL)x;
-(id) initWithFlipX:(BOOL)x;
@end

/** Flips the sprite vertically   垂直参数
 @since v0.99.0
 */
@interface CCFlipY : CCActionInstant
{
	BOOL	flipY;
}
+(id) actionWithFlipY:(BOOL)y;
-(id) initWithFlipY:(BOOL)y;
@end

/** Places the node in a certain position  指定位置参数
 */
@interface CCPlace : CCActionInstant <NSCopying>
{
	CGPoint position;
}
/** creates a Place action with a position 创建和初始化一个指定位置的及时运动 */
+(id) actionWithPosition: (CGPoint) pos;
/** Initializes a Place action with a position */
-(id) initWithPosition: (CGPoint) pos;
@end

/** Calls a 'callback'   响应一个回调
 */
@interface CCCallFunc : CCActionInstant <NSCopying>
{
	id targetCallback_;
	SEL selector_;
}

/** Target that will be called   回调的目标 */
@property (nonatomic, readwrite, retain) id targetCallback;

/** creates the action with the callback  创建和初始化方法 */
+(id) actionWithTarget: (id) t selector:(SEL) s;
/** initializes the action with the callback */
-(id) initWithTarget: (id) t selector:(SEL) s;
/** exeuctes the callback  执行回调 */
-(void) execute;
@end

/** Calls a 'callback' with the node as the first argument.
 N means Node   用节点作为第一参数的回调
 */
@interface CCCallFuncN : CCCallFunc
{
}
@end

typedef void (*CC_CALLBACK_ND)(id, SEL, id, void *);
/** Calls a 'callback' with the node as the first argument and the 2nd argument is data. 第二参数为数据
 * ND means: Node and Data. Data is void *, so it could be anything.
节点和数据，可以是任何对象
 */
@interface CCCallFuncND : CCCallFuncN
{
	void			*data_;
	CC_CALLBACK_ND	callbackMethod_;
}

/** Invocation object that has the target#selector and the parameters 
调用的对象具有 目标 选择器和参数
*/
@property (nonatomic,readwrite) CC_CALLBACK_ND callbackMethod;

/** creates the action with the callback and the data to pass as an argument
创建带有回调数据作为参数的运动 */
+(id) actionWithTarget: (id) t selector:(SEL) s data:(void*)d;
/** initializes the action with the callback and the data to pass as an argument */
-(id) initWithTarget:(id) t selector:(SEL) s data:(void*) d;
@end

/** Calls a 'callback' with an object as the first argument.
 O means Object.   对象作为参数的回调
 @since v0.99.5
 */
@interface CCCallFuncO : CCCallFunc
{
	id	object_;
}
/** object to be passed as argument  对象做为参数*/
@property (nonatomic, readwrite, retain) id object;

/** creates the action with the callback and the object to pass as an argument
创建和初始化一个带有对象参数的回调
 */
+(id) actionWithTarget: (id) t selector:(SEL) s object:(id)object;
/** initializes the action with the callback and the object to pass as an argument */
-(id) initWithTarget:(id) t selector:(SEL) s object:(id)object;

@end

#pragma mark Blocks Support

/** Executes a callback using a block.   使用块来执行一个回调
 */
@interface CCCallBlock : CCActionInstant<NSCopying>
{
	void (^block_)();
}

/** creates the action with the specified block, to be used as a callback.
 The block will be "copied".
使用指定的块来执行回调。该块是可复制的。 下面是初始化方法，以及执行方法
 */
+(id) actionWithBlock:(void(^)())block;

/** initialized the action with the specified block, to be used as a callback.
 The block will be "copied".
 */
-(id) initWithBlock:(void(^)())block;

/** executes the callback */
-(void) execute;
@end

@class CCNode;

/** Executes a callback using a block with a single CCNode parameter.
使用带有单个节点参数的块来执行回调
 */
@interface CCCallBlockN : CCActionInstant<NSCopying>
{
	void (^block_)(CCNode *);
}

/** creates the action with the specified block, to be used as a callback.
 The block will be "copied".
同上解释，块是指定的，是可复制的
 */
+(id) actionWithBlock:(void(^)(CCNode *node))block;

/** initialized the action with the specified block, to be used as a callback.
 The block will be "copied".
 */
-(id) initWithBlock:(void(^)(CCNode *node))block;

/** executes the callback */
-(void) execute;
@end

/** Executes a callback using a block with a single NSObject parameter.
 @since v2.0
执行带有单个对象参数的块的回调
 */
@interface CCCallBlockO : CCActionInstant<NSCopying>
{
	void (^block_)(id object);
	id object_;
}

/** object to be passed to the block 对象作为参数 */
@property (nonatomic,retain) id object;

/** creates the action with the specified block, to be used as a callback.
 The block will be "copied".
同上
 */
+(id) actionWithBlock:(void(^)(id object))block object:(id)object;

/** initialized the action with the specified block, to be used as a callback.
 The block will be "copied".
 */
-(id) initWithBlock:(void(^)(id object))block object:(id)object;

/** executes the callback */
-(void) execute;
@end
