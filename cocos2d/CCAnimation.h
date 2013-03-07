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

#import <Foundation/Foundation.h>
#ifdef __CC_PLATFORM_IOS
#import <CoreGraphics/CoreGraphics.h>
#endif // IPHONE
//iphone平台用到核心绘图
@class CCSpriteFrame;
@class CCTexture2D;
@class CCSpriteFrame;

/** CCAnimationFrame
 A frame of the animation. It contains information like:
	- sprite frame name
	- # of delay units.
	- offset
 一个动画边框包括：精灵边框，延迟单元，偏移量
 @since v2.0
 */
@interface CCAnimationFrame : NSObject <NSCopying>
{
    CCSpriteFrame* spriteFrame_;
    float delayUnits_;
    NSDictionary *userInfo_;
}
/** CCSpriteFrameName to be used  精灵边框 */
@property (nonatomic, readwrite, retain) CCSpriteFrame* spriteFrame;

/**  how many units of time the frame takes 多少单元被使用 */
@property (nonatomic, readwrite) float delayUnits;

/**  A CCAnimationFrameDisplayedNotification notification will be broadcasted when the frame is displayed with this dictionary as UserInfo. If UserInfo is nil, then no notification will be broadcasted.  
当宽框架显示时注册一个通知，作为用户信息；如用户信息为Nil，则不用广播通知
 */
@property (nonatomic, readwrite, retain) NSDictionary *userInfo;

/** initializes the animation frame with a spriteframe, number of delay units and a notification user info */
-(id) initWithSpriteFrame:(CCSpriteFrame*)spriteFrame delayUnits:(float)delayUnits userInfo:(NSDictionary*)userInfo;
@end

/** A CCAnimation object is used to perform animations on the CCSprite objects.
一个动画对象被精灵对象来使用；
 The CCAnimation object contains CCAnimationFrame objects, and a possible delay between the frames.
 You can animate a CCAnimation object by using the CCAnimate action. 
可以使用CCAnimate 动作来标示动画对象
Example:

  [sprite runAction:[CCAnimate actionWithAnimation:animation]];

 */
@interface CCAnimation : NSObject <NSCopying>
{
	NSMutableArray	*frames_;
	float			totalDelayUnits_;
	float			delayPerUnit_;
	BOOL			restoreOriginalFrame_;
	NSUInteger		loops_;
}

/** total Delay units of the CCAnimation  所有延迟单元. */
@property (nonatomic, readonly) float totalDelayUnits;
/** Delay in seconds of the "delay unit"  以秒来计算的延迟单元 */
@property (nonatomic, readwrite) float delayPerUnit;
/** duration in seconds of the whole animation. It is the result of totalDelayUnits * delayPerUnit  周期 */
@property (nonatomic,readonly) float duration;
/** array of CCAnimationFrames   数组*/
@property (nonatomic,readwrite,retain) NSMutableArray *frames;
/** whether or not it shall restore the original frame when the animation finishes 
是否存储原框架
*/
@property (nonatomic,readwrite) BOOL restoreOriginalFrame;
/** how many times the animation is going to loop. 0 means animation is not animated. 1, animation is executed one time, ...   动画循环次数 */
@property (nonatomic, readwrite) NSUInteger loops;

/** Creates an animation 创建动画
 @since v0.99.5
 */
+(id) animation;

/** Creates an animation with an array of CCSpriteFrame.
 The frames will be created with one "delay unit".
使用一组CCSpriteFrame来创建
 @since v0.99.5
 */
+(id) animationWithSpriteFrames:(NSArray*)arrayOfSpriteFrameNames;

/* Creates an animation with an array of CCSpriteFrame and a delay between frames in seconds.
 The frames will be added with one "delay unit".
 @since v0.99.5
 */
+(id) animationWithSpriteFrames:(NSArray*)arrayOfSpriteFrameNames delay:(float)delay;

/* Creates an animation with an array of CCAnimationFrame, the delay per units in seconds and and how many times it should be executed.
 @since v2.0
 */
+(id) animationWithAnimationFrames:(NSArray*)arrayOfAnimationFrames delayPerUnit:(float)delayPerUnit loops:(NSUInteger)loops;


/** Initializes a CCAnimation with an array of CCSpriteFrame.
 The frames will be added with one "delay unit".
 @since v0.99.5
*/
-(id) initWithSpriteFrames:(NSArray*)arrayOfSpriteFrameNames;

/** Initializes a CCAnimation with an array of CCSpriteFrames and a delay between frames in seconds.
 The frames will be added with one "delay unit".
 @since v0.99.5
 */
-(id) initWithSpriteFrames:(NSArray *)arrayOfSpriteFrameNames delay:(float)delay;

/* Initializes an animation with an array of CCAnimationFrame and the delay per units in seconds.
 @since v2.0
 */
-(id) initWithAnimationFrames:(NSArray*)arrayOfAnimationFrames delayPerUnit:(float)delayPerUnit loops:(NSUInteger)loops;

/** Adds a CCSpriteFrame to a CCAnimation.
 The frame will be added with one "delay unit".
增加方法
*/
-(void) addSpriteFrame:(CCSpriteFrame*)frame;

/** Adds a frame with an image filename. Internally it will create a CCSpriteFrame and it will add it.
 The frame will be added with one "delay unit".
 Added to facilitate the migration from v0.8 to v0.9.
 */
-(void) addSpriteFrameWithFilename:(NSString*)filename;

/** Adds a frame with a texture and a rect. Internally it will create a CCSpriteFrame and it will add it.
 The frame will be added with one "delay unit".
 Added to facilitate the migration from v0.8 to v0.9.
不同的增加方法，都是增加一个延迟单元，不过是参数不同
 */
-(void) addSpriteFrameWithTexture:(CCTexture2D*)texture rect:(CGRect)rect;

@end
