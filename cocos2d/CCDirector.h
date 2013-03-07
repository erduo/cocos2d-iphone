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
 */


#import "ccConfig.h"
#import "ccTypes.h"
#import "ccMacros.h"

#import "CCProtocols.h"
#import "Platforms/CCGL.h"
#import "kazmath/mat4.h"
//配置，类型，宏，协议，GL,矩阵
/** @typedef ccDirectorProjection
 Possible OpenGL projections used by director
可能用到openGL的投影功能
 */
typedef enum {
	/// sets a 2D projection (orthogonal projection). 设置2D投影，正投影
	kCCDirectorProjection2D,

	/// sets a 3D projection with a fovy=60, znear=0.5f and zfar=1500. 3D投影
	kCCDirectorProjection3D,

	/// it calls "updateProjection" on the projection delegate. 更新投影
	kCCDirectorProjectionCustom,

	/// Detault projection is 3D projection  默认3D投影
	kCCDirectorProjectionDefault = kCCDirectorProjection3D,

} ccDirectorProjection;


@class CCLabelAtlas;
@class CCScene;
@class CCScheduler;
@class CCActionManager;
//标签，场景，调度，动作管理类

#ifdef __CC_PLATFORM_IOS
#define CC_VIEWCONTROLLER UIViewController
#elif defined(__CC_PLATFORM_MAC)
#define CC_VIEWCONTROLLER NSObject
#endif

/**Class that creates and handle the main Window and manages how
and when to execute the Scenes.
该类主要是创建和调用主窗口，执行如何在屏幕显示
而导演类负责下面的功能：
初始化opengl es上下文；设定opengl像素格式；设定opengl的缓冲深度；设置投影；
 The CCDirector is also resposible for:
  - initializing the OpenGL ES context
  - setting the OpenGL pixel format (default on is RGB565)
  - setting the OpenGL buffer depth (default one is 0-bit)
  - setting the projection (default one is 3D)
导演类是单例，标准被使用的方法：[[CCDirector shareDirector] methodName];
 Since the CCDirector is a singleton, the standard way to use it is by calling:
  - [[CCDirector sharedDirector] methodName];
一些默认设置的openGL参数：
 The CCDirector also sets the default OpenGL context:
  - GL_TEXTURE_2D is enabled
  - GL_VERTEX_ARRAY is enabled
  - GL_COLOR_ARRAY is enabled
  - GL_TEXTURE_COORD_ARRAY is enabled
*/
@interface CCDirector : CC_VIEWCONTROLLER
{
	// internal timer   间隔时间
	NSTimeInterval animationInterval_;
	NSTimeInterval oldAnimationInterval_;

	/* stats  统计？*/
	BOOL	displayStats_;

	NSUInteger frames_;
	NSUInteger totalFrames_;
	ccTime secondsPerFrame_;

	ccTime		accumDt_;
	ccTime		frameRate_;
	CCLabelAtlas *FPSLabel_;
	CCLabelAtlas *SPFLabel_;
	CCLabelAtlas *drawsLabel_;

	/* is the running scene paused   运行停止*/
	BOOL isPaused_;
    
    /* Is the director running   是否运行*/
    BOOL isAnimating_;

	/* The running scene  运行场景 */
	CCScene *runningScene_;

	/* This object will be visited after the scene. Useful to hook a notification node   回调通知 */
	id notificationNode_;

	/* will be the next 'runningScene' in the next frame
	 nextScene is a weak reference.   定义下一个场景参数 */
	CCScene *nextScene_;

	/* If YES, then "old" scene will receive the cleanup message  是否要清除旧的场景消息 */
	BOOL	sendCleanupToScene_;

	/* scheduled scenes   调度的场景组 */
	NSMutableArray *scenesStack_;

	/* last time the main loop was updated   最新一次更新 */
	struct timeval lastUpdate_;
	/* delta time since last tick to main loop    运行的时间差*/
	ccTime dt;
	/* whether or not the next delta time will be zero   下个时间差为0吗*/
	BOOL nextDeltaTimeZero_;

	/* projection used  使用投影 */
	ccDirectorProjection projection_;

	/* CCDirector delegate   导演代理*/
	id<CCDirectorDelegate>	delegate_;

	/* window size in points   窗口大小*/
	CGSize	winSizeInPoints_;

	/* window size in pixels  窗口像素大小*/
	CGSize	winSizeInPixels_;

	/* the cocos2d running thread  当前运行线程 */
	NSThread	*runningThread_;

	/* scheduler associated with this director  调度  */
	CCScheduler *scheduler_;

	/* action manager associated with this director  运动管理*/
	CCActionManager *actionManager_;
	
	/*  OpenGLView. On iOS it is a copy of self.view  openGL的视图是当前视图的拷贝 */
	CCGLView		*view_;
}

/** returns the cocos2d thread.
 If you want to run any cocos2d task, run it in this thread.
 On iOS usually it is the main thread.
通常运行cocos2d任务，在主线程中
 @since v0.99.5
 */
@property (readonly, nonatomic ) NSThread *runningThread;
/** The current running Scene. Director can only run one Scene at the time  当前运行场景；导演同一时刻只能执行一个场景 */
@property (nonatomic,readonly) CCScene* runningScene;
/** The FPS value  每秒传输帧数值 */
@property (nonatomic,readwrite, assign) NSTimeInterval animationInterval;
/** Whether or not to display director statistics  是否显示统计数 */
@property (nonatomic, readwrite, assign) BOOL displayStats;
/** whether or not the next delta time will be zero  下个时间差是否为0*/
@property (nonatomic,readwrite,assign) BOOL nextDeltaTimeZero;
/** Whether or not the Director is paused  暂停 */
@property (nonatomic,readonly) BOOL isPaused;
/** Whether or not the Director is active (animating)   激活状态 */
@property (nonatomic,readonly) BOOL isAnimating;
/** Sets an OpenGL projection    设置opengl 投影 */
@property (nonatomic,readwrite) ccDirectorProjection projection;
/** How many frames were called since the director started  从开始调用的个数 */
@property (nonatomic,readonly) NSUInteger	totalFrames;
/** seconds per frame 每帧的时间 */
@property (nonatomic, readonly) ccTime secondsPerFrame;

/** Whether or not the replaced scene will receive the cleanup message.
 If the new scene is pushed, then the old scene won't receive the "cleanup" message.
 If the new scene replaces the old one, the it will receive the "cleanup" message.    当新的场景替换旧的场景时，是否要清楚旧的场景
 @since v0.99.0
 */
@property (nonatomic, readonly) BOOL sendCleanupToScene;

/** This object will be visited after the main scene is visited.
 This object MUST implement the "visit" selector.
 Useful to hook a notification object, like CCNotifications (http://github.com/manucorporat/CCNotifications)
 @since v0.99.5    使用通知节点
 */
@property (nonatomic, readwrite, retain) id	notificationNode;

/** CCDirector delegate. It shall implemente the CCDirectorDelegate protocol
 @since v0.99.5   使用代理协议
 */
@property (nonatomic, readwrite, retain) id<CCDirectorDelegate> delegate;

/** CCScheduler associated with this director   调度
 @since v2.0
 */
@property (nonatomic,readwrite,retain) CCScheduler *scheduler;

/** CCActionManager associated with this director   运动管理
 @since v2.0
 */
@property (nonatomic,readwrite,retain) CCActionManager *actionManager;

/** returns a shared instance of the director   返回共享实例*/
+(CCDirector*)sharedDirector;


#pragma mark Director - Stats  统计

#pragma mark Director - Win Size
/** returns the size of the OpenGL view in points   窗口大小 */
- (CGSize) winSize;

/** returns the size of the OpenGL view in pixels.
 On Mac winSize and winSizeInPixels return the same value.
返回像素大小
 */
- (CGSize) winSizeInPixels;

/** changes the projection size   改变投影大小*/
-(void) reshapeProjection:(CGSize)newWindowSize;

/** converts a UIKit coordinate to an OpenGL coordinate
 Useful to convert (multi) touchs coordinates to the current layout (portrait or landscape)   转化为openGL的坐标系统--点
 */
-(CGPoint) convertToGL: (CGPoint) p;
/** converts an OpenGL coordinate to a UIKit coordinate
 Useful to convert node points to window points for calls such as glScissor
从opengl系统转为uikit坐标系统
 */
-(CGPoint) convertToUI:(CGPoint)p;

/// XXX: missing description
-(float) getZEye;

#pragma mark Director - Scene Management   场景管理

/**Enters the Director's main loop with the given Scene.
 * Call it to run only your FIRST scene.
 * Don't call it if there is already a running scene.
 *导演类进入主循环回路时，调用第一个场景。运行当中不要调用此方法。启动场景方法
 * It will call pushScene: and then it will call startAnimation
 */
- (void) runWithScene:(CCScene*) scene;

/**Suspends the execution of the running scene, pushing it on the stack of suspended scenes.
 * The new scene will be executed.
 * Try to avoid big stacks of pushed scenes to reduce memory allocation.
 * ONLY call it if there is a running scene.
将当前场景压入栈中，执行新的场景。尽量避免压入的场景消耗大的内存；仅仅在运行场景中调用此方法
 */
- (void) pushScene:(CCScene*) scene;

/**Pops out a scene from the queue.
 * This scene will replace the running one.
 * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
 * ONLY call it if there is a running scene.
弹出一个场景来执行，当前的场景将会被删除。
 */
- (void) popScene;

/**Pops out all scenes from the queue until the root scene in the queue.
 * This scene will replace the running one.
 * The running scene will be deleted. If there are no more scenes in the stack the execution is terminated.
 * ONLY call it if there is a running scene.
同上，逐个执行到最底部的场景。场景队列
 */
- (void) popToRootScene;

/** Replaces the running scene with a new one. The running scene is terminated.
 * ONLY call it if there is a running scene.
用一个场景替换当前场景，当前将会终止
 */
-(void) replaceScene: (CCScene*) scene;

/** Ends the execution, releases the running scene.
 It doesn't remove the OpenGL view from its parent. You have to do it manually.
结束执行，释放运行场景。 但没有释放opengl的视图，需要手动处理
 */
-(void) end;

/** Pauses the running scene.
 The running scene will be _drawed_ but all scheduled timers will be paused
 While paused, the draw rate will be 4 FPS to reduce CPU consuption
暂停当前场景。当暂停时，绘图频率为4来降低cpu的消耗
 */
-(void) pause;

/** Resumes the paused scene
 The scheduled timers will be activated again.
 The "delta time" will be 0 (as if the game wasn't paused)
恢复暂停的场景
 */
-(void) resume;

/** Stops the animation. Nothing will be drawn. The main loop won't be triggered anymore.
 If you wan't to pause your animation call [pause] instead.
暂停动作。不在绘制 主循环不在触发。
 */
-(void) stopAnimation;

/** The main loop is triggered again.
 Call this function only if [stopAnimation] was called earlier
 @warning Dont' call this function to start the main loop. To run the main loop call runWithScene
触发主循环，开始运动； 不要调用此方法来启动主循环，而是用runWithScene
 */
-(void) startAnimation;

/** Draw the scene.
 This method is called every frame. Don't call it manually.
无需手动。每帧都会调用此方法来绘制场景
 */
-(void) drawScene;


// XXX: Hack. Should be placed on CCDirectorMac.h. Refactoring needed
#if defined(__CC_PLATFORM_MAC)
/** sets the openGL view   设置openGL的视图*/
-(void) setView:(CCGLView*)view;

/** returns the OpenGL view  返回Opengl视图 */
-(CCGLView*) view;
#endif

#pragma mark Director - Memory Helper   内存

/** Removes all the cocos2d data that was cached automatically.
 It will purge the CCTextureCache, CCLabelBMFont cache.
 IMPORTANT: The CCSpriteFrameCache won't be purged. If you want to purge it, you have to purge it manually.
 @since v0.99.3  
消除缓存数据，可以自动消除CCTextCache, CCLabelIBMFont 的缓存。而CCSpriteFrameCache要手动消除缓存
 */
-(void) purgeCachedData;

// OpenGL Helper

/** sets the OpenGL default values   设置Opengl默认值*/
-(void) setGLDefaultValues;
/** enables/disables OpenGL alpha blending  是否开启Opengl混合 */
- (void) setAlphaBlending: (BOOL) on;
/** enables/disables OpenGL depth test   是否开启opengl位深测试*/
- (void) setDepthTest: (BOOL) on;

// helper
/** creates the Stats labels   创建统计标签 */
-(void) createStatsLabel;
@end

// optimization. Should only be used to read it. Never to write it.  只读绘制次数
extern NSUInteger __ccNumberOfDraws;
