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
 *
 */


#import "CCAction.h"
#import "ccMacros.h"
#import "Support/ccCArray.h"
#import "Support/uthash.h"
//运动，宏，数组，哈希值
typedef struct _hashElement
{
	struct ccArray	*actions;
	NSUInteger		actionIndex;
	BOOL			currentActionSalvaged;
	BOOL			paused;
	UT_hash_handle	hh;

	CC_ARC_UNSAFE_RETAINED	id				target;
	CC_ARC_UNSAFE_RETAINED	CCAction		*currentAction;
} tHashElement;


/** CCActionManager the object that manages all the actions.
运动管理类对象管理所有的运动。
 Normally you won't need to use this API directly. 99% of the cases you will use the CCNode interface, which uses this object.
通常你不用直接使用API，99%的情况下你使用节点借口来访问。 但是某些情况下你可以使用： 当运动目标不同于节点；你想暂停/恢复运动时
 But there are some cases where you might need to use this API dirctly:
 Examples:
	- When you want to run an action where the target is different from a CCNode.
	- When you want to pause / resume the actions

 @since v0.8
 */
@interface CCActionManager : NSObject
{
	tHashElement	*targets;
	tHashElement	*currentTarget;
	BOOL			currentTargetSalvaged;
}


// actions

/** Adds an action with a target. 增加一个带有目标的运动
 If the target is already present, then the action will be added to the existing target.
 If the target is not present, a new instance of this target will be created either paused or paused, and the action will be added to the newly created target.
 When the target is paused, the queued actions won't be 'ticked'.
如果目标已经存在，就将其添加到现有的目标中；如果不存在，将会暂停或停顿创建的新目标会被添加到新的实例中。 目标暂停，运动队列不会打钩。
 */
-(void) addAction: (CCAction*) action target:(id)target paused:(BOOL)paused;
/** Removes all actions from all the targers.
从所有对象中移除所有运动
 */
-(void) removeAllActions;

/** Removes all actions from a certain target.
 All the actions that belongs to the target will be removed.
从指定目标中移除所有运动。而所有运动属于该目标
 */
-(void) removeAllActionsFromTarget:(id)target;
/** Removes an action given an action reference.
移除一个指定运动
 */
-(void) removeAction: (CCAction*) action;
/** Removes an action given its tag and the target 
移除一个给定标记和目标的运动
*/
-(void) removeActionByTag:(NSInteger)tag target:(id)target;
/** Gets an action given its tag an a target
 @return the Action the with the given tag
获取一个给定标记的运动
 */
-(CCAction*) getActionByTag:(NSInteger) tag target:(id)target;
/** Returns the numbers of actions that are running in a certain target
 * Composable actions are counted as 1 action. Example:
 *    If you are running 1 Sequence of 7 actions, it will return 1.
 *    If you are running 7 Sequences of 2 actions, it will return 7.
返回运动在序列中的位置。
 */
-(NSUInteger) numberOfRunningActionsInTarget:(id)target;

/** Pauses the target: all running actions and newly added actions will be paused.
暂停目标：所有运行的和新添加的运动都会被停止。
 */
-(void) pauseTarget:(id)target;
/** Resumes the target. All queued actions will be resumed.
恢复对象。所有队列中个的运动都会恢复
 */
-(void) resumeTarget:(id)target;

/** Pauses all running actions, returning a list of targets whose actions were paused.
暂停所有运行中的运动
 */
-(NSSet *) pauseAllRunningActions;

/** Resume a set of targets (convenience function to reverse a pauseAllRunningActions call)
恢复指定目标的运动
 */
-(void) resumeTargets:(NSSet *)targetsToResume;

@end

