/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008 Radu Gruian
 *
 * Copyright (c) 2011 Vit Valentin
 *
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
 *
 * Orignal code by Radu Gruian: http://www.codeproject.com/Articles/30838/Overhauser-Catmull-Rom-Splines-for-Camera-Animatio.So
 *
 * Adapted to cocos2d-x by Vit Valentin
 *
 * Adapted from cocos2d-x to cocos2d-iphone by Ricardo Quesada
 */


#import "CCActionInterval.h"

/** An Array that contain control points.
一个数组，即控制点； 可以这样理解：从一个运动点到下一个点构成
 Used by CCCardinalSplineTo and (By) and CCCatmullRomTo (and By) actions.
 */
@interface CCPointArray : NSObject <NSCopying>
{
	NSMutableArray *controlPoints_;
}

/** Array that contains the control points  数组就是控制点*/
@property (nonatomic,readwrite,retain) NSMutableArray *controlPoints;

/** creates and initializes a Points array with capacity 
创建并初始化一个数组，使用容量值
*/
 +(id) arrayWithCapacity:(NSUInteger)capacity;

/** initializes a Catmull Rom config with a capacity hint 使用容量来初始化 */
-(id) initWithCapacity:(NSUInteger)capacity;

/** appends a control point 增加一个控制点*/
-(void) addControlPoint:(CGPoint)controlPoint;

/** inserts a controlPoint at index 插入一个控制点的次序 */
-(void) insertControlPoint:(CGPoint)controlPoint atIndex:(NSUInteger)index;

/** replaces an existing controlPoint at index 替换一个控制点 */
-(void) replaceControlPoint:(CGPoint)controlPoint atIndex:(NSUInteger)index;

/** get the value of a controlPoint at a given index  获取一个控制点的位置*/
-(CGPoint) getControlPointAtIndex:(NSInteger)index;

/** deletes a control point at a given index  删除指定的控制点*/
-(void) removeControlPointAtIndex:(NSUInteger)index;

/** returns the number of objects of the control point array 返回个数 */
-(NSUInteger) count;

/** returns a new copy of the array reversed. User is responsible for releasing this copy  返回一组新的逆向控制点，用户负责要释放掉*/
-(CCPointArray*) reverse;

/** reverse the current control point array inline, without generating a new one  就是将当前的控制点转向，不会产生新的控制点*/
-(void) reverseInline;
@end

/** Cardinal Spline path. 运动的路径？
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 */
@interface CCCardinalSplineTo : CCActionInterval
{
	CCPointArray		*points_;
	CGFloat			deltaT_;
	CGFloat			tension_;
}

/** Array of control points  一组控制点*/
 @property (nonatomic,readwrite,retain) CCPointArray *points;

/** creates an action with a Cardinal Spline array of points and tension
使用阵列点和力来创建一个运动
 */
+(id) actionWithDuration:(ccTime)duration points:(CCPointArray*)points tension:(CGFloat)tension;

/** initializes the action with a duration and an array of points    使用间隔和控制点来初始化运动*/
-(id) initWithDuration:(ccTime)duration points:(CCPointArray*)points tension:(CGFloat)tension;

@end

/** Cardinal Spline path.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Cardinal_spline
 */
@interface CCCardinalSplineBy : CCCardinalSplineTo
{
	CGPoint				startPosition_;
}
@end

/** An action that moves the target with a CatmullRom curve to a destination point.
 A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
一个运动就是讲目标移动到目的地。
 */
@interface CCCatmullRomTo : CCCardinalSplineTo
{
}
/** creates an action with a Cardinal Spline array of points and tension 创建于东使用了cardinal spline就是阵列点 */
+(id) actionWithDuration:(ccTime)dt points:(CCPointArray*)points;

/** initializes the action with a duration and an array of points 使用间隔和控制点来初始化运动 */
-(id) initWithDuration:(ccTime)dt points:(CCPointArray*)points;
@end

/** An action that moves the target with a CatmullRom curve by a certain distance.   一个运动移动目标，要经过移动距离
  A Catmull Rom is a Cardinal Spline with a tension of 0.5.
 http://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull.E2.80.93Rom_spline
 */
@interface CCCatmullRomBy : CCCardinalSplineBy
{
}
/** creates an action with a Cardinal Spline array of points and tension  一如同上解释 */
+(id) actionWithDuration:(ccTime)dt points:(CCPointArray*)points;

/** initializes the action with a duration and an array of points */
-(id) initWithDuration:(ccTime)dt points:(CCPointArray*)points;
@end

/** Returns the Cardinal Spline position for a given set of control points, tension and time */
 CGPoint ccCardinalSplineAt( CGPoint p0, CGPoint p1, CGPoint p2, CGPoint p3, CGFloat tension, ccTime t );
