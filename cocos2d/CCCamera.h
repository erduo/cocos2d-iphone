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



#import "CCNode.h"
#import "kazmath/mat4.h"//用于3D中的数学库

/**
    A CCCamera is used in every CCNode.
    Useful to look at the object from different views.
    The OpenGL gluLookAt() function is used to locate the
    camera.
摄像类被节点使用，通常是查看对象从不同的视图，而openGL中的gluLookAt()函数就是用来放置位置的。 可以重载摄像类来改变对象的任意比例旋转位置等属性
    If the object is transformed by any of the scale, rotation or
    position attributes, then they will override the camera.

	IMPORTANT: Either your use the camera or the rotation/scale/position properties. You can't use both. 不能同时使用。  
    World coordinates won't work if you use the camera.

    Limitations:
限制：有些节点如 CCParallaxNode, CCParticle使用节点坐标系统，你不能使用摄像类移动这些类的对象。
     - Some nodes, like CCParallaxNode, CCParticle uses world node coordinates, and they won't work properly if you move them (or any of their ancestors)
       using the camera.

     - It doesn't work on batched nodes like CCSprite objects when they are parented to a CCSpriteBatchNode object.
但为成批对象时不行。
	 - It is recommended to use it ONLY if you are going to create 3D effects. For 2D effecs, use the action CCFollow or position/scale/rotate.
推荐在构建3D效果时使用。 对于2D效果可以结合跟随类使用
*/

@interface CCCamera : NSObject
{
    float eyeX_;
    float eyeY_;
    float eyeZ_;

    float centerX_;
    float centerY_;
    float centerZ_;

    float upX_;
    float upY_;
    float upZ_;

	BOOL dirty_;

	kmMat4	lookupMatrix_;//矩阵
}

/** whether of not the camera is dirty   摄像是否是脏的*/
@property (nonatomic,readwrite) BOOL dirty;

/** returns the Z eye  返回z值*/
+(float) getZEye;

/** sets the camera in the defaul position 设定摄像在默认位置 */
-(void) restore;
/** Sets the camera using gluLookAt using its eye, center and up_vector   放置位置*/
-(void) locate;
/** sets the eye values in points   设置眼的值*/
-(void) setEyeX: (float)x eyeY:(float)y eyeZ:(float)z;
/** sets the center values in points 设置中心点*/
-(void) setCenterX: (float)x centerY:(float)y centerZ:(float)z;
/** sets the up values */
-(void) setUpX: (float)x upY:(float)y upZ:(float)z;

/** get the eye vector values in points  获取向量点值*/
-(void) eyeX:(float*)x eyeY:(float*)y eyeZ:(float*)z;
/** get the center vector values in points */
-(void) centerX:(float*)x centerY:(float*)y centerZ:(float*)z;
/** get the up vector values 获取向上的向量值 */
-(void) upX:(float*)x upY:(float*)y upZ:(float*)z;


@end
