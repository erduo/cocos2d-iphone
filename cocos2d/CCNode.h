/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2009 Valentin Milea
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

#import "Platforms/CCGL.h"
#import "ccTypes.h"
#import "CCProtocols.h"
#import "ccConfig.h"
#import "ccGLStateCache.h"
#import "Support/CCArray.h"
#import "kazmath/kazmath.h"

enum {
	kCCNodeTagInvalid = -1,
};

@class CCCamera;
@class CCGridBase;
@class CCGLProgram;
@class CCScheduler;
@class CCActionManager;
@class CCAction;

/** CCNode is the main element. Anything thats gets drawn or contains things that get drawn is a CCNode.
节点是主要元素。任何对象都可以是一个节点。主要或常用的场景类，层类，精灵，菜单类都是从节点继承而来
 The most popular CCNodes are: CCScene, CCLayer, CCSprite, CCMenu.

 The main features of a CCNode are:
节点的主要特征：可以还有其他节点（增加子类或删除）；可以进行定期回调;可以执行动作(如运行,停止等)
 - They can contain other CCNode nodes (addChild, getChildByTag, removeChild, etc)
 - They can schedule periodic callback (schedule, unschedule, etc)
 - They can execute actions (runAction, stopAction, etc)

 Some CCNode nodes provide extra functionality for them or their children.
一些节点可以提供附加功能. 如子类可以具有重载初始化资源和回调,可以回调处理时间,重画;
 Subclassing a CCNode usually means (one/all) of:
 - overriding init to initialize resources and schedule callbacks
 - create callbacks to handle the advancement of time
 - overriding draw to render the node

 Features of CCNode:
节点的特征:位置,缩放比例,旋转,摄像,网格,锚点,大小,可见性,z轴次序,opengl z轴位置
 - position
 - scale (x, y)
 - rotation (in degrees, clockwise)
 - CCCamera (an interface to gluLookAt )
 - CCGridBase (to do mesh transformations)
 - anchor point
 - size
 - visible
 - z-order
 - openGL z position

 Default values:
  - rotation: 0
  - position: (x=0,y=0)
  - scale: (x=1,y=1)
  - contentSize: (x=0,y=0)
  - anchorPoint: (x=0,y=0)

 Limitations:限制
 - A CCNode is a "void" object. It doesn't have a texture
节点可以是任意对象。不具有纹理
 Order in transformations with grid disabled
不可编辑的网格转换：节点可以具有转换，旋转，倾斜，缩放，摄像
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be skewed (skewX, skewY)
 -# The node will be scaled (scale, scaleX, scaleY)
 -# The node will be moved according to the camera values (camera)

 Order in transformations with grid enabled
可编辑网格中时：节点具有转换，旋转，倾斜，缩放，摄像，捕捉屏幕，呈现
 -# The node will be translated (position)
 -# The node will be rotated (rotation)
 -# The node will be skewed (skewX, skewY)
 -# The node will be scaled (scale, scaleX, scaleY)
 -# The grid will capture the screen
 -# The node will be moved according to the camera values (camera)
 -# The grid will render the captured screen

 Camera:
 - Each node has a camera. By default it points to the center of the CCNode.
每个节点都有一个摄像。默认为节点的中心位置
 */
@interface CCNode : NSObject
{
	// rotation angle     旋转角度
	float rotation_;

	// scaling factors  缩放矢量
	float scaleX_, scaleY_;

	// openGL real Z vertex opengl z轴真实顶点
	float vertexZ_;

	// position of the node  位置
	CGPoint position_;

	// skew angles 倾斜角度
	float skewX_, skewY_;

	// anchor point in points  锚点
	CGPoint anchorPointInPoints_;
	// anchor point normalized (NOT in points)
	CGPoint anchorPoint_;

	// untransformed size of the node 大小
	CGSize	contentSize_;

	// transform  转换
	CGAffineTransform transform_, inverse_;

	// a Camera 摄像
	CCCamera *camera_;

	// a Grid  网格
	CCGridBase *grid_;

	// z-order value 次序
	NSInteger zOrder_;

	// array of children 子类数组
	CCArray *children_;

	// weakref to parent  父类指针
	CCNode *parent_;

	// a tag. any number you want to assign to the node 标记
	NSInteger tag_;

	// user data field 用户数据
	void *userData_;
	id userObject_;

	// Shader 着色器
	CCGLProgram	*shaderProgram_;

	// Server side state gl服务端状态
	ccGLServerState glServerState_;

	// used to preserve sequence while sorting children with the same zOrder 保存序列
	NSUInteger orderOfArrival_;

	// scheduler used to schedule timers and updates 调度计数和更新
	CCScheduler		*scheduler_;

	// ActionManager used to handle all the actions 运动管理所有运行
	CCActionManager	*actionManager_;

	// Is running  运行中
	BOOL isRunning_;

	BOOL isTransformDirty_;
	BOOL isInverseDirty_;

	// is visible 可见性
	BOOL visible_;
	// If YES, the Anchor Point will be (0,0) when you position the CCNode.
	// Used by CCLayer and CCScene  是否忽视锚点；是，则为(0,0)；
	BOOL ignoreAnchorPointForPosition_;

	BOOL isReorderChildDirty_;	
}

/** The z order of the node relative to its "siblings": children of the same parent 
相对于父类的次序
*/
@property(nonatomic,assign) NSInteger zOrder;
/** The real openGL Z vertex.  真实z轴顶点
 Differences between openGL Z vertex and cocos2d Z order:
   - OpenGL Z modifies the Z vertex, and not the Z order in the relation between parent-children
   - OpenGL Z might require to set 2D projection
   - cocos2d Z order works OK if all the nodes uses the same openGL Z vertex. eg: vertexZ = 0
 @warning: Use it at your own risk since it might break the cocos2d parent-children z order
 @since v0.8
 */
@property (nonatomic,readwrite) float vertexZ;

/** The X skew angle of the node in degrees.
 This angle describes the shear distortion in the X direction.
 Thus, it is the angle between the Y axis and the left edge of the shape
 The default skewX angle is 0. Positive values distort the node in a CW direction.
 */
@property(nonatomic,readwrite,assign) float skewX;

/** The Y skew angle of the node in degrees.
 This angle describes the shear distortion in the Y direction.
 Thus, it is the angle between the X axis and the bottom edge of the shape
 The default skewY angle is 0. Positive values distort the node in a CCW direction.
x,y轴的倾斜角度
 */
@property(nonatomic,readwrite,assign) float skewY;
/** The rotation (angle) of the node in degrees. 0 is the default rotation angle. Positive values rotate node CW.  旋转 */
@property(nonatomic,readwrite,assign) float rotation;
/** The scale factor of the node. 1.0 is the default scale factor. It modifies the X and Y scale at the same time.  缩放比例 */
@property(nonatomic,readwrite,assign) float scale;
/** The scale factor of the node. 1.0 is the default scale factor. It only modifies the X scale factor. 缩放x轴 */
@property(nonatomic,readwrite,assign) float scaleX;
/** The scale factor of the node. 1.0 is the default scale factor. It only modifies the Y scale factor. 缩放y轴 */
@property(nonatomic,readwrite,assign) float scaleY;
/** Position (x,y) of the node in points. (0,0) is the left-bottom corner. 位置；(0,0)为左下角 */
@property(nonatomic,readwrite,assign) CGPoint position;
/** A CCCamera object that lets you move the node using a gluLookAt  使用gluLookAt 摄像 */
@property(nonatomic,readonly) CCCamera* camera;
/** Array of children   子类数组*/
@property(nonatomic,readonly) CCArray *children;
/** A CCGrid object that is used when applying effects 使用网格影响效果 */
@property(nonatomic,readwrite,retain) CCGridBase* grid;
/** Whether of not the node is visible. Default is YES  是否可见*/
@property(nonatomic,readwrite,assign) BOOL visible;
/** anchorPoint is the point around which all transformations and positioning manipulations take place.
 It's like a pin in the node where it is "attached" to its parent.
 The anchorPoint is normalized, like a percentage. (0,0) means the bottom-left corner and (1,1) means the top-right corner.
 But you can use values higher than (1,1) and lower than (0,0) too.
 The default anchorPoint is (0,0). It starts in the bottom-left corner. CCSprite and other subclasses have a different default anchorPoint.
锚点像附加到父类的指针；是归一化的，如百分比。如(0,0)表示开始于左下角。精灵和其他子类具有不同的锚点
 @since v0.8
 */
@property(nonatomic,readwrite) CGPoint anchorPoint;
/** The anchorPoint in absolute pixels.
 Since v0.8 you can only read it. If you wish to modify it, use anchorPoint instead   以绝对像素来表示的锚点。只读属性
 */
@property(nonatomic,readonly) CGPoint anchorPointInPoints;

/** The untransformed size of the node in Points
 The contentSize remains the same no matter the node is scaled or rotated.
 All nodes has a size. Layer and Scene has the same size of the screen.
 @since v0.8 大小
 */
@property (nonatomic,readwrite) CGSize contentSize;

/** whether or not the node is running  使用中*/
@property(nonatomic,readonly) BOOL isRunning;
/** A weak reference to the parent 父类引用 */
@property(nonatomic,readwrite,assign) CCNode* parent;
/**  If YES, the Anchor Point will be (0,0) when you position the CCNode.
 Used by CCLayer and CCScene.  忽视锚点
 */
@property(nonatomic,readwrite,assign) BOOL ignoreAnchorPointForPosition;
/** A tag used to identify the node easily 标记 */
@property(nonatomic,readwrite,assign) NSInteger tag;
/** A custom user data pointer 用户数据 */
@property(nonatomic,readwrite,assign) void* userData;
/** Similar to userData, but instead of holding a void* it holds an id  于用户数据类似 */
@property(nonatomic,readwrite,retain) id userObject;

/** Shader Program
 @since v2.0 着色方案
 */
@property(nonatomic,readwrite,retain) CCGLProgram *shaderProgram;

/** used internally for zOrder sorting, don't change this manually 存储次序，不做手动改变 */
@property(nonatomic,readwrite) NSUInteger orderOfArrival;

/** GL server side state 服务状态
 @since v2.0  
*/
@property (nonatomic, readwrite) ccGLServerState glServerState;

/** CCActionManager used by all the actions.
 IMPORTANT: If you set a new CCActionManager, then previously created actions are going to be removed.  运动管理
 @since v2.0
 */
@property (nonatomic, readwrite, retain) CCActionManager *actionManager;

/** CCScheduler used to schedule all "updates" and timers.
 IMPORTANT: If you set a new CCScheduler, then previously created timers/update are going to be removed.  调度使用
 @since v2.0
 */
@property (nonatomic, readwrite, retain) CCScheduler *scheduler;

// initializators
/** allocates and initializes a node.
 The node will be created as "autorelease".  创建和初始化。自动释放
 */
+(id) node;
/** initializes the node */
-(id) init;


// scene managment 场景管理

/** Event that is called every time the CCNode enters the 'stage'.
 If the CCNode enters the 'stage' with a transition, this event is called when the transition starts.
 During onEnter you can't access a sibling node.
 If you override onEnter, you shall call [super onEnter].
事件就是节点每次进入舞台调用。节点进入过渡时，调用事件；在进入onEnter时，不能访问其他节点；若重载onEnter，可以调用[super onEnter];
 */
-(void) onEnter;

/** Event that is called when the CCNode enters in the 'stage'.
 If the CCNode enters the 'stage' with a transition, this event is called when the transition finishes.
 If you override onEnterTransitionDidFinish, you shall call [super onEnterTransitionDidFinish].
过渡结束时调用
 @since v0.8
 */
-(void) onEnterTransitionDidFinish;

/** Event that is called every time the CCNode leaves the 'stage'.
 If the CCNode leaves the 'stage' with a transition, this event is called when the transition finishes.
 During onExit you can't access a sibling node.
 If you override onExit, you shall call [super onExit].
离开舞台时调用的事件
 */
-(void) onExit;

/** callback that is called every time the CCNode leaves the 'stage'.
 If the CCNode leaves the 'stage' with a transition, this callback is called when the transition starts.  过渡；离开；调用
 */
-(void) onExitTransitionDidStart;

// composition: ADD

/** Adds a child to the container with z-order as 0.
 If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
 @since v0.7.1  增加一个节点；处于运行中，onEnter和onEnterTransitionDidFinish会被立即调用
 */
-(void) addChild: (CCNode*)node;

/** Adds a child to the container with a z-order.
 If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
增加，带有次序
 @since v0.7.1
 */
-(void) addChild: (CCNode*)node z:(NSInteger)z;

/** Adds a child to the container with z order and tag.
 If the child is added to a 'running' node, then 'onEnter' and 'onEnterTransitionDidFinish' will be called immediately.
 @since v0.7.1
带有标记
 */
-(void) addChild: (CCNode*)node z:(NSInteger)z tag:(NSInteger)tag;

// composition: REMOVE

/** Remove itself from its parent node. If cleanup is YES, then also remove all actions and callbacks.
 If the node orphan, then nothing happens.
从父类节点上删除。是，则移除所有运动和回调。
 @since v0.99.3
 */
-(void) removeFromParentAndCleanup:(BOOL)cleanup;

/** Removes a child from the container. It will also cleanup all running actions depending on the cleanup parameter. 移除一个节点
 @since v0.7.1
 */
-(void) removeChild: (CCNode*)node cleanup:(BOOL)cleanup;

/** Removes a child from the container by tag value. It will also cleanup all running actions depending on the cleanup parameter 按标记移除
 @since v0.7.1
 */
-(void) removeChildByTag:(NSInteger) tag cleanup:(BOOL)cleanup;

/** Removes all children from the container and do a cleanup all running actions depending on the cleanup parameter.
 @since v0.7.1  移除所有
 */
-(void) removeAllChildrenWithCleanup:(BOOL)cleanup;

// composition: GET
/** Gets a child from the container given its tag
 @return returns a CCNode object
 @since v0.7.1 用标记获取
 */
-(CCNode*) getChildByTag:(NSInteger) tag;

/** Reorders a child according to a new z value.
 * The child MUST be already added. 按次序获取
 */
-(void) reorderChild:(CCNode*)child z:(NSInteger)zOrder;

/** performance improvement, Sort the children array once before drawing, instead of every time when a child is added or reordered
 don't call this manually unless a child added needs to be removed in the same frame  存储所有子节点 */
- (void) sortAllChildren;

/** Event that is called when the running node is no longer running (eg: its CCScene is being removed from the "stage" ).
 On cleanup you should break any possible circular references.
 CCNode's cleanup removes any possible scheduled timer and/or any possible action.
 If you override cleanup, you shall call [super cleanup]
 @since v0.8  当节点不在运行时调用。移除所有调度计数或运动；可以重载[super cleanup]
 */
-(void) cleanup;

// draw

/** Override this method to draw your own node.
 You should use cocos2d's GL API to enable/disable the GL state / shaders.
 For further info, please see ccGLstate.h.
 You shall NOT call [super draw];
重载此方法绘制本身；使用api开启gl。可以参考ccGLstate.h;不要调用[super draw]方法
 */
-(void) draw;

/** recursive method that visit its children and draw them  访问子节点和绘制 */
-(void) visit;

// transformations

/** performs OpenGL view-matrix transformation based on position, scale, rotation and other attributes.  基于位置，比例，旋转和其他属性转换 */
-(void) transform;

/** performs OpenGL view-matrix transformation of its ancestors.
 Generally the ancestors are already transformed, but in certain cases (eg: attaching a FBO) it is necessary to transform the ancestors again.  转换？？
 @since v0.7.2
 */
-(void) transformAncestors;

/** returns a "local" axis aligned bounding box of the node in points.
 The returned box is relative only to its parent.
 The returned box is in Points.
边界
 @since v0.8.2
 */
- (CGRect) boundingBox;

// actions

/** Executes an action, and returns the action that is executed.
 The node becomes the action's target.
 @warning Starting from v0.8 actions don't retain their target anymore.
 @since v0.7.1
 @return An Action pointer
执行一个运动；节点是运动目标；返回一个运动指针
 */
-(CCAction*) runAction: (CCAction*) action;
/** Removes all actions from the running action list  移除所有运动 */
-(void) stopAllActions;
/** Removes an action from the running action list  从运动列表中移除一个运动 */
-(void) stopAction: (CCAction*) action;
/** Removes an action from the running action list given its tag
 @since v0.7.1  按标记移除
*/
-(void) stopActionByTag:(NSInteger) tag;
/** Gets an action from the running action list given its tag
 @since v0.7.1
 @return the Action the with the given tag   按标记获取一个运动
 */
-(CCAction*) getActionByTag:(NSInteger) tag;
/** Returns the numbers of actions that are running plus the ones that are schedule to run (actions in actionsToAdd and actions arrays).
 * Composable actions are counted as 1 action. Example:
 *    If you are running 1 Sequence of 7 actions, it will return 1.
 *    If you are running 7 Sequences of 2 actions, it will return 7.
返回运动次序
 */
-(NSUInteger) numberOfRunningActions;

// timers

/** check whether a selector is scheduled.  是否调度*/
//-(BOOL) isScheduled: (SEL) selector;

/** schedules the "update" method. It will use the order number 0. This method will be called every frame.
 Scheduled methods with a lower order value will be called before the ones that have a higher order value.
 Only one "udpate" method could be scheduled per node.
调度更新方法；使用次序为0；每帧都会调用；
 @since v0.99.3
 */
-(void) scheduleUpdate;

/** schedules the "update" selector with a custom priority. This selector will be called every frame.
 Scheduled selectors with a lower priority will be called before the ones that have a higher value.
 Only one "udpate" selector could be scheduled per node (You can't have 2 'update' selectors).
按优先级调度
 @since v0.99.3
 */
-(void) scheduleUpdateWithPriority:(NSInteger)priority;

/* unschedules the "update" method.

 @since v0.99.3 不定期调用更新
 */
-(void) unscheduleUpdate;


/** schedules a selector.
 The scheduled selector will be ticked every frame  调度选择器
 */
-(void) schedule: (SEL) s;
/** schedules a custom selector with an interval time in seconds.
 If time is 0 it will be ticked every frame.
 If time is 0, it is recommended to use 'scheduleUpdate' instead.

 If the selector is already scheduled, then the interval parameter will be updated without scheduling it again.
以秒为间隔计算
 */
-(void) schedule: (SEL) s interval:(ccTime)seconds;
/**
 repeat will execute the action repeat + 1 times, for a continues action use kCCRepeatForever
 delay is the amount of time the action will wait before execution
重复次数加延时
 */
-(void) schedule:(SEL)selector interval:(ccTime)interval repeat: (uint) repeat delay:(ccTime) delay;

/**
 Schedules a selector that runs only once, with a delay of 0 or larger
调用一次带有延时
*/
- (void) scheduleOnce:(SEL) selector delay:(ccTime) delay;

/** unschedules a custom selector.不定期调用自定义选择器*/
-(void) unschedule: (SEL) s;

/** unschedule all scheduled selectors: custom selectors, and the 'update' selector.
 Actions are not affected by this method.
@since v0.99.3  运动不受此方法影响
 */
-(void) unscheduleAllSelectors;

/** resumes all scheduled selectors and actions.
 Called internally by onEnter 恢复
 */
-(void) resumeSchedulerAndActions;
/** pauses all scheduled selectors and actions.
 Called internally by onExit 停止，在onExit时调用
 */
-(void) pauseSchedulerAndActions;


// transformation methods   转换方法

/** Returns the matrix that transform the node's (local) space coordinates into the parent's space coordinates.
 The matrix is in Pixels.
 @since v0.7.1
转换节点空间坐标系为父类的空间坐标系；返回矩阵以像素为单位
 */
- (CGAffineTransform)nodeToParentTransform;
/** Returns the matrix that transform parent's space coordinates to the node's (local) space coordinates.
 The matrix is in Pixels.
父类转子类
 @since v0.7.1
 */
- (CGAffineTransform)parentToNodeTransform;
/** Retrusn the world affine transform matrix. The matrix is in Pixels.
 @since v0.7.1
 */
- (CGAffineTransform)nodeToWorldTransform;
/** Returns the inverse world affine transform matrix. The matrix is in Pixels.
 @since v0.7.1
 */
- (CGAffineTransform)worldToNodeTransform;
/** Converts a Point to node (local) space coordinates. The result is in Points.
 @since v0.7.1 返回为点
 */
- (CGPoint)convertToNodeSpace:(CGPoint)worldPoint;
/** Converts a Point to world space coordinates. The result is in Points.
 @since v0.7.1
 */
- (CGPoint)convertToWorldSpace:(CGPoint)nodePoint;
/** Converts a Point to node (local) space coordinates. The result is in Points.
 treating the returned/received node point as anchor relative.
 @since v0.7.1
 */
- (CGPoint)convertToNodeSpaceAR:(CGPoint)worldPoint;
/** Converts a local Point to world space coordinates.The result is in Points.
 treating the returned/received node point as anchor relative.
 @since v0.7.1
 */
- (CGPoint)convertToWorldSpaceAR:(CGPoint)nodePoint;

#ifdef __CC_PLATFORM_IOS
/** Converts a UITouch to node (local) space coordinates. The result is in Points.
 @since v0.7.1  uitouch转节点坐标系
 */
- (CGPoint)convertTouchToNodeSpace:(UITouch *)touch;
/** Converts a UITouch to node (local) space coordinates. The result is in Points.
 This method is AR (Anchor Relative)..
 @since v0.7.1  都是坐标系的转换；
 */
- (CGPoint)convertTouchToNodeSpaceAR:(UITouch *)touch;
#endif // __CC_PLATFORM_IOS
@end
