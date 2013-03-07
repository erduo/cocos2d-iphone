/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2010 Ricardo Quesada
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

@class CCAnimation;

/** Singleton that manages the CCAnimation objects.
 It saves in a cache the animations. You should use this class if you want to save your animations in a cache.
使用单例对象来保存动画；使用该类来在缓存中保存动画
 @since v0.99.5
 */
@interface CCAnimationCache : NSObject
{
	NSMutableDictionary *animations_;
}

/** Retruns ths shared instance of the Animation cache   返回单例 */
+ (CCAnimationCache *) sharedAnimationCache;

/** Purges the cache. It releases all the CCAnimation objects and the shared instance.
清楚缓存
 */
+(void)purgeSharedAnimationCache;

/** Adds a CCAnimation with a name.
增加一个动画方法
 */
-(void) addAnimation:(CCAnimation*)animation name:(NSString*)name;

/** Deletes a CCAnimation from the cache.
从缓存中删除方法
 */
-(void) removeAnimationByName:(NSString*)name;

/** Returns a CCAnimation that was previously added.
 If the name is not found it will return nil.
 You should retain the returned copy if you are going to use it.
返回一个动画，若使用则使用拷贝方法
 */
-(CCAnimation*) animationByName:(NSString*)name;

/** Adds an animation from an NSDictionary
 Make sure that the frames were previously loaded in the CCSpriteFrameCache.
从字典中增加
 @since v1.1
 */
-(void)addAnimationsWithDictionary:(NSDictionary *)dictionary;

/** Adds an animation from a plist file.
 Make sure that the frames were previously loaded in the CCSpriteFrameCache.
从属性列表中增加
 @since v1.1
 */
-(void)addAnimationsWithFile:(NSString *)plist;

@end
