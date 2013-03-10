/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2009 Jason Booth
 *
 * Copyright (c) 2009 Robert J Payne
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
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
 */


/*创建精灵帧和纹理地图，可以该工具
 * To create sprite frames and texture atlas, use this tool:
 * http://zwoptex.zwopple.com/
 */

#import <Foundation/Foundation.h>

#import "CCSpriteFrame.h"

@class CCSprite;
@class CCTexture2D;

/** Singleton that handles the loading of the sprite frames.
 It saves in a cache the sprite frames.
 @since v0.9 单例来管理精灵帧
 */
@interface CCSpriteFrameCache : NSObject
{
	NSMutableDictionary *spriteFrames_;
	NSMutableDictionary *spriteFramesAliases_;
	NSMutableSet		*loadedFilenames_;
}

/** Retruns ths shared instance of the Sprite Frame cache 返回共享实例*/
+ (CCSpriteFrameCache *) sharedSpriteFrameCache;

/** Purges the cache. It releases all the Sprite Frames and the retained instance. 清除缓存
 */
+(void)purgeSharedSpriteFrameCache;


/** Adds multiple Sprite Frames from a plist file. 从链表文件中增加多个精灵帧；纹理自动载人，名称被其文件名替换；
 * A texture will be loaded automatically. The texture name will composed by replacing the .plist suffix with .png .
 * If you want to use another texture, you should use the addSpriteFramesWithFile:texture method.
 */
-(void) addSpriteFramesWithFile:(NSString*)plist;

/** Adds multiple Sprite Frames from a plist file. The texture filename will be associated with the created sprite frames.
 */
-(void) addSpriteFramesWithFile:(NSString*)plist textureFilename:(NSString*)filename;

/** Adds multiple Sprite Frames from a plist file. The texture will be associated with the created sprite frames.
 */
-(void) addSpriteFramesWithFile:(NSString*)plist texture:(CCTexture2D*)texture;

/** Adds an sprite frame with a given name. 给定名称增加一个精灵帧；如果该名称已经存在，旧的将会被取代；
 If the name already exists, then the contents of the old name will be replaced with the new one.
 */
-(void) addSpriteFrame:(CCSpriteFrame*)frame name:(NSString*)frameName;


/** Purges the dictionary of loaded sprite frames.
 * Call this method if you receive the "Memory Warning".
 * In the short term: it will free some resources preventing your app from being killed.
 * In the medium term: it will allocate more resources.
 * In the long term: it will be the same.
 * 如果接收到了内存警告：1，先释放一些资源防止杀死应用；2，释放更多；3，同上；
 */
-(void) removeSpriteFrames;

/** Removes unused sprite frames.移除不在使用的精灵帧
 * Sprite Frames that have a retain count of 1 will be deleted.
 * It is convinient to call this method after when starting a new Scene.
 */
-(void) removeUnusedSpriteFrames;

/** Deletes an sprite frame from the sprite frame cache. 删除一个
 */
-(void) removeSpriteFrameByName:(NSString*)name;

/** Removes multiple Sprite Frames from a plist file.
* Sprite Frames stored in this file will be removed.
* It is convinient to call this method when a specific texture needs to be removed.
* @since v0.99.5 从链表文件中删除多个
*/
- (void) removeSpriteFramesFromFile:(NSString*) plist;

/** Removes all Sprite Frames associated with the specified textures.
 * It is convinient to call this method when a specific texture needs to be removed.
 * @since v0.995. 删除所有用指定纹理的精灵帧；
 */
- (void) removeSpriteFramesFromTexture:(CCTexture2D*) texture;

/** Returns an Sprite Frame that was previously added.
 If the name is not found it will return nil.
 You should retain the returned copy if you are going to use it. 获取指定的精灵帧
 */
-(CCSpriteFrame*) spriteFrameByName:(NSString*)name;

@end
