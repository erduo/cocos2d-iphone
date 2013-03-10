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
#import <CoreGraphics/CGImage.h>
#endif

#import <Foundation/Foundation.h>

@class CCTexture2D;

/** Singleton that handles the loading of textures 单例管理纹理，一次载人。
 * Once the texture is loaded, the next time it will return
 * a reference of the previously loaded texture reducing GPU & CPU memory
 */
@interface CCTextureCache : NSObject
{
	NSMutableDictionary *textures_;

	dispatch_queue_t _loadingQueue;
	dispatch_queue_t _dictQueue;
}

/** Retruns ths shared instance of the cache */
+ (CCTextureCache *) sharedTextureCache;

/** purges the cache. It releases the retained instance. 清除缓存
 @since v0.99.0
 */
+(void)purgeSharedTextureCache;


/** Returns a Texture2D object given an file image
 * 参数为一个图片文件；如果文件没有载人，先创建一个纹理对象返回。 支持的图片格式：png,bmp,tiff,jpeg,pvr,gif
 * If the file image was not previously loaded, it will create a new CCTexture2D
 *  object and it will return it. It will use the filename as a key.
 * Otherwise it will return a reference of a previosly loaded image.
 * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr, .gif
 */
-(CCTexture2D*) addImage: (NSString*) fileimage;

/** Asynchronously, load a texture2d from a file.
 * 异步，载人一个纹理
 * If the file image was previously loaded, it will use it.
 * Otherwise it will load a texture in a new thread, and when the image is loaded, the callback will be called with the Texture2D as a parameter.
 * The callback will be called in the cocos2d thread, so it is safe to create any cocos2d object from the callback.
 * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr, .gif
 * @since v0.8
 */
-(void) addImageAsync:(NSString*) filename target:(id)target selector:(SEL)selector;

/** Asynchronously, load a texture2d from a file.
 * 使用块
 * If the file image was previously loaded, it will use it.
 * Otherwise it will load a texture in a new thread, and when the image is loaded, the block will be called.
 * The callback will be called in the cocos2d thread, so it is safe to create any cocos2d object from the callback.
 * Supported image extensions: .png, .bmp, .tiff, .jpeg, .pvr, .gif
 * @since v2.0
 */
-(void) addImageAsync:(NSString*) filename withBlock:(void(^)(CCTexture2D *tex))block;


/** Returns a Texture2D object given an CGImageRef image
 * 使用CGImageRef参数
 * If the image was not previously loaded, it will create a new CCTexture2D object and it will return it.
 * Otherwise it will return a reference of a previously loaded image
 * The "key" parameter will be used as the "key" for the cache.
 * If "key" is nil, then a new texture will be created each time.
 * @since v0.8
 */
-(CCTexture2D*) addCGImage: (CGImageRef) image forKey: (NSString *)key;

/** Returns an already created texture. Returns nil if the texture doesn't exist.
 @since v0.99.5 通过键值来返回纹理
 */
-(CCTexture2D *) textureForKey:(NSString *)key;

/** Purges the dictionary of loaded textures.
 * 清除载人的纹理
 * Call this method if you receive the "Memory Warning"
 * In the short term: it will free some resources preventing your app from being killed
 * In the medium term: it will allocate more resources
 * In the long term: it will be the same
 */
-(void) removeAllTextures;

/** Removes unused textures
 * 移除未使用的纹理
 * Textures that have a retain count of 1 will be deleted
 * It is convinient to call this method after when starting a new Scene
 * @since v0.8
 */
-(void) removeUnusedTextures;

/** Deletes a texture from the cache given a texture 删除
 */
-(void) removeTexture: (CCTexture2D*) tex;

/** Deletes a texture from the cache given a its key name 
 @since v0.99.4
 */
-(void) removeTextureForKey: (NSString*) textureKeyName;

@end


@interface CCTextureCache (PVRSupport)

/** Returns a Texture2D object given an PVR filename.
 * 给定pvr文件名，增加
 * If the file image was not previously loaded, it will create a new CCTexture2D
 *  object and it will return it. Otherwise it will return a reference of a previosly loaded image
 *
 */
-(CCTexture2D*) addPVRImage:(NSString*) filename;

@end


@interface CCTextureCache (Debug)
/** Output to CCLOG the current contents of this CCTextureCache
 * This will attempt to calculate the size of each texture, and the total texture memory in use
 *
 * @since v1.0
 */
-(void) dumpCachedTextureInfo;

@end
