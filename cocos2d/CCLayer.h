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



#import "ccMacros.h"

#ifdef __CC_PLATFORM_IOS
#import <UIKit/UIKit.h>									// Needed for UIAccelerometerDelegate
#import "Platforms/iOS/CCTouchDelegateProtocol.h"		// Touches only supported on iOS
#elif defined(__CC_PLATFORM_MAC)
#import "Platforms/Mac/CCEventDispatcher.h"
#endif

#import "CCProtocols.h"
#import "CCNode.h"

#pragma mark -
#pragma mark CCLayer

/** CCLayer is a subclass of CCNode that implements the CCTouchEventsDelegate protocol.
层是CCNode的子类，用来实现CCTouchEventsDelegate 协议
具有所有CCNode的特征，增加了可以接收触摸和加速计输入事件
 All features from CCNode are valid, plus the following new features:
 - It can receive iPhone Touches
 - It can receive Accelerometer input
*/
#ifdef __CC_PLATFORM_IOS
@interface CCLayer : CCNode <UIAccelerometerDelegate, CCStandardTouchDelegate, CCTargetedTouchDelegate>
{
	BOOL isTouchEnabled_;
	BOOL isAccelerometerEnabled_;
}
/** If isTouchEnabled, this method is called onEnter. Override it to change the
 way CCLayer receives touch events.
启用触摸，重载onEnter方法，改变接收触摸事件
 ( Default: [touchDispatcher addStandardDelegate:self priority:0] )
 Example:  注册触摸调度
     -(void) registerWithTouchDispatcher
     {
        [touchDispatcher addTargetedDelegate:self priority:INT_MIN+1 swallowsTouches:YES];
     }

 Valid only on iOS. Not valid on Mac.

 @since v0.8.0
 */
-(void) registerWithTouchDispatcher;

/** whether or not it will receive Touch events.
 You can enable / disable touch events with this property.
 Only the touches of this node will be affected. This "method" is not propagated to its children.

 Valid on iOS and Mac OS X v10.6 and later.
是否接收触摸事件。 
 @since v0.8.1
 */
@property(nonatomic,assign) BOOL isTouchEnabled;
/** whether or not it will receive Accelerometer events
 You can enable / disable accelerometer events with this property.

 Valid only on iOS. Not valid on Mac.
是否接收加速计事件
 @since v0.8.1
 */
@property(nonatomic,assign) BOOL isAccelerometerEnabled;

#elif defined(__CC_PLATFORM_MAC)


@interface CCLayer : CCNode <CCKeyboardEventDelegate, CCMouseEventDelegate, CCTouchEventDelegate>
{
	BOOL	isMouseEnabled_;//鼠标
	BOOL	isKeyboardEnabled_;//键盘
	BOOL	isTouchEnabled_;//触摸
}

/** whether or not it will receive mouse events.

 Valind only Mac. Not valid on iOS
 */
@property (nonatomic, readwrite) BOOL isMouseEnabled;

/** whether or not it will receive keyboard events.

 Valind only Mac. Not valid on iOS
 */
@property (nonatomic, readwrite) BOOL isKeyboardEnabled;

/** whether or not it will receive touch events.

 Valid on iOS and Mac OS X v10.6 and later.
 */
@property (nonatomic, readwrite) BOOL isTouchEnabled;

/** priority of the mouse event delegate.
 Default 0.
 Override this method to set another priority.
鼠标事件委托
 Valind only Mac. Not valid on iOS
 */
-(NSInteger) mouseDelegatePriority;

/** priority of the keyboard event delegate.
 Default 0.
 Override this method to set another priority.
键盘事件
 Valind only Mac. Not valid on iOS
 */
-(NSInteger) keyboardDelegatePriority;

/** priority of the touch event delegate.
 Default 0.
 Override this method to set another priority.

 Valind only Mac. Not valid on iOS
 */
-(NSInteger) touchDelegatePriority;

#endif // mac


@end

#pragma mark -
#pragma mark CCLayerColor

/** CCLayerColor is a subclass of CCLayer that implements the CCRGBAProtocol protocol.
颜色层是层的子类，实现CCRGBAProtocol协议。继承所有层的特征，增加了透明度和rgb颜色
 All features from CCLayer are valid, plus the following new features:
 - opacity
 - RGB colors
 */
@interface CCLayerColor : CCLayer <CCRGBAProtocol, CCBlendProtocol>
{
	GLubyte		opacity_;
	ccColor3B	color_;
	ccVertex2F	squareVertices_[4];
	ccColor4F	squareColors_[4];

	ccBlendFunc	blendFunc_;
}

/** creates a CCLayer with color, width and height in Points 使用颜色，宽和高来创建*/
+ (id) layerWithColor: (ccColor4B)color width:(GLfloat)w height:(GLfloat)h;
/** creates a CCLayer with color. Width and height are the window size. */
+ (id) layerWithColor: (ccColor4B)color;

/** initializes a CCLayer with color, width and height in Points.
 This is the designated initializer.  指定初始化
 */
- (id) initWithColor:(ccColor4B)color width:(GLfloat)w height:(GLfloat)h;
/** initializes a CCLayer with color. Width and height are the window size. */
- (id) initWithColor:(ccColor4B)color;

/** change width in Points  改变宽 */
-(void) changeWidth: (GLfloat)w;
/** change height in Points */
-(void) changeHeight: (GLfloat)h;
/** change width and height in Points
 @since v0.8
 */
-(void) changeWidth:(GLfloat)w height:(GLfloat)h;

/** Opacity: conforms to CCRGBAProtocol protocol 透明度：符合CCRGBAProtocol 协议*/
@property (nonatomic,readonly) GLubyte opacity;
/** Opacity: conforms to CCRGBAProtocol protocol */
@property (nonatomic,readonly) ccColor3B color;
/** BlendFunction. Conforms to CCBlendProtocol protocol */
@property (nonatomic,readwrite) ccBlendFunc blendFunc;
@end

#pragma mark -
#pragma mark CCLayerGradient

/** CCLayerGradient is a subclass of CCLayerColor that draws gradients across
the background.
是颜色层的子类，用来绘制梯度背景；继承了颜色层所有特征，增加了方向，最终颜色，插补模式
 All features from CCLayerColor are valid, plus the following new features:
 - direction
 - final color
 - interpolation mode

 Color is interpolated between the startColor and endColor along the given
 vector (starting at the origin, ending at the terminus).  If no vector is
 supplied, it defaults to (0, -1) -- a fade from top to bottom.
颜色是从开始色到结束色给定一个向量加上插补。默认向量为(0,-1）
 If 'compressedInterpolation' is disabled, you will not see either the start or end color for
 non-cardinal vectors; a smooth gradient implying both end points will be still
 be drawn, however.

 If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
如果compressedInterpolation此参数被禁用，看不到两端的颜色，及变化过程。没有禁用可以看到
 @since v0.99.5
 */
@interface CCLayerGradient : CCLayerColor
{
	ccColor3B endColor_;
	GLubyte startOpacity_;
	GLubyte endOpacity_;
	CGPoint vector_;
	BOOL	compressedInterpolation_;
}

/** Creates a full-screen CCLayer with a gradient between start and end. 使用开始和结束色来创建 ； 下面增加向量 */
+ (id) layerWithColor: (ccColor4B) start fadingTo: (ccColor4B) end;
/** Creates a full-screen CCLayer with a gradient between start and end in the direction of v. */
+ (id) layerWithColor: (ccColor4B) start fadingTo: (ccColor4B) end alongVector: (CGPoint) v;

/** Initializes the CCLayer with a gradient between start and end. */
- (id) initWithColor: (ccColor4B) start fadingTo: (ccColor4B) end;
/** Initializes the CCLayer with a gradient between start and end in the direction of v. */
- (id) initWithColor: (ccColor4B) start fadingTo: (ccColor4B) end alongVector: (CGPoint) v;

/** The starting color.  开始色 */
@property (nonatomic, readwrite) ccColor3B startColor;
/** The ending color.  结束色*/
@property (nonatomic, readwrite) ccColor3B endColor;
/** The starting opacity. 开始的透明度 */
@property (nonatomic, readwrite) GLubyte startOpacity;
/** The ending color.  结束的透明度 */
@property (nonatomic, readwrite) GLubyte endOpacity;
/** The vector along which to fade color.  渐变色的矢量 */
@property (nonatomic, readwrite) CGPoint vector;
/** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
 Default: YES
默认为是，压缩插值
 */
@property (nonatomic, readwrite) BOOL compressedInterpolation;

@end

#pragma mark -
#pragma mark CCLayerMultiplex

/** CCLayerMultiplex is a CCLayer with the ability to multiplex its children.
是层的子类，可以复合多个子类，支持多个子类，同一时刻只有一个是激活状态
 Features:
   - It supports one or more children
   - Only one children will be active a time
 */
@interface CCLayerMultiplex : CCLayer
{
	unsigned int enabledLayer_;
	NSMutableArray *layers_;
}

/** creates a CCMultiplexLayer with one or more layers using a variable argument list.   使用链表 */
+(id) layerWithLayers: (CCLayer*) layer, ... NS_REQUIRES_NIL_TERMINATION;
/** initializes a MultiplexLayer with one or more layers using a variable argument list. */
-(id) initWithLayers: (CCLayer*) layer vaList:(va_list) params;
/** switches to a certain layer indexed by n.
 The current (old) layer will be removed from its parent with 'cleanup:YES'.
转到指定的层。旧的层被删除和从父类中释放
 */
-(void) switchTo: (unsigned int) n;
/** release the current layer and switches to another layer indexed by n.
 The current (old) layer will be removed from its parent with 'cleanup:YES'.
释放当前层，转到n层
 */
-(void) switchToAndReleaseMe: (unsigned int) n;
@end

