/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2011 Ricardo Quesada
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

#import "CCNode.h"
#import "CCProtocols.h"
//节点，协议
@class CCSprite;
@class CCSpriteFrame;

#define kCCItemSize 32

#pragma mark -
#pragma mark CCMenuItem
/** CCMenuItem base class
 *
 *  Subclass CCMenuItem (or any subclass) to create your custom CCMenuItem objects.
 */
@interface CCMenuItem : CCNode
{
	// used for menu items using a block  使用块
	void (^block_)(id sender);

	BOOL isEnabled_;
	BOOL isSelected_;
}

/** returns whether or not the item is selected 是否选中
@since v0.8.2
*/
@property (nonatomic,readonly) BOOL isSelected;

/** Creates a CCMenuItem with a target/selector.
 target/selector will be implemented using blocks.
 "target" won't be retained.  使用目标或选择器来创建。 使用块；目标将不保留
 */
+(id) itemWithTarget:(id)target selector:(SEL)selector;

/** Creates a CCMenuItem with the specified block.
 The block will be "copied". 指定块来创建。 
 */
+(id) itemWithBlock:(void(^)(id sender))block;

/** Initializes a CCMenuItem with a target/selector */
-(id) initWithTarget:(id)target selector:(SEL)selector;

/** Initializes a CCMenuItem with the specified block.
 The block will be "copied".
*/
-(id) initWithBlock:(void(^)(id sender))block;

/** Returns the outside box in points */
-(CGRect) rect;

/** Activate the item  激活 */
-(void) activate;

/** The item was selected (not activated), similar to "mouse-over"  被选中 */
-(void) selected;

/** The item was unselected  未选中*/
-(void) unselected;

/** Enable or disabled the CCMenuItem  可用 */
-(void) setIsEnabled:(BOOL)enabled;

/** Returns whether or not the CCMenuItem is enabled */
-(BOOL) isEnabled;

/** Sets the block that is called when the item is tapped.
 The block will be "copied".  设置块
 */
-(void) setBlock:(void(^)(id sender))block;

/** Sets the target and selector that is called when the item is tapped.
 target/selector will be implemented using blocks.
 "target" won't be retained.
 */
-(void) setTarget:(id)target selector:(SEL)selector;

/** cleanup event. It will release the block and call [super cleanup] */
-(void) cleanup;

@end

#pragma mark -
#pragma mark CCMenuItemLabel

/** An abstract class for "label" CCMenuItemLabel items
任意节点支持CCLabelProtocol协议。
 Any CCNode that supports the CCLabelProtocol protocol can be added.
 Supported nodes:
   - CCLabelBMFont
   - CCLabelAtlas
   - CCLabelTTF
 */
@interface CCMenuItemLabel : CCMenuItem  <CCRGBAProtocol>
{
	CCNode<CCLabelProtocol, CCRGBAProtocol> *label_;
	ccColor3B	colorBackup;
	ccColor3B	disabledColor_;
	float		originalScale_;
}

/** the color that will be used to disable the item  不可用时的颜色 */
@property (nonatomic,readwrite) ccColor3B disabledColor;

/** Label that is rendered. It can be any CCNode that implements the CCLabelProtocol  支持该协议 */
@property (nonatomic,readwrite,assign) CCNode<CCLabelProtocol, CCRGBAProtocol>* label;

/** creates a CCMenuItemLabel with a Label. Block will benil  使用label来创建*/
+(id) itemWithLabel:(CCNode<CCLabelProtocol,CCRGBAProtocol>*)label;

/** creates a CCMenuItemLabel with a Label, target and selector.
 The "target" won't be retained.  用目标，标签，选择器来创建
 */
+(id) itemWithLabel:(CCNode<CCLabelProtocol,CCRGBAProtocol>*)label target:(id)target selector:(SEL)selector;

/** creates a CCMenuItemLabel with a Label and a block to execute.
 The block will be "copied".  使用标签和块执行创建
 */
+(id) itemWithLabel:(CCNode<CCLabelProtocol,CCRGBAProtocol>*)label block:(void(^)(id sender))block;

/** initializes a CCMenuItemLabel with a Label, target and selector.
 Internally it will create a block that executes the target/selector.
 The "target" won't be retained.  同上
 */
-(id) initWithLabel:(CCNode<CCLabelProtocol,CCRGBAProtocol>*)label target:(id)target selector:(SEL)selector;

/** initializes a CCMenuItemLabel with a Label and a block to execute.
 The block will be "copied".
 This is the designated initializer.
 */
-(id) initWithLabel:(CCNode<CCLabelProtocol,CCRGBAProtocol>*)label block:(void(^)(id sender))block;

/** sets a new string to the inner label  设置一个新的字符串 */
-(void) setString:(NSString*)label;

/** Enable or disabled the CCMenuItemFont
 @warning setIsEnabled changes the RGB color of the font
会改变字体颜色
 */
-(void) setIsEnabled: (BOOL)enabled;
@end

#pragma mark -
#pragma mark CCMenuItemAtlasFont

/** A CCMenuItemAtlasFont
 Helper class that creates a CCMenuItemLabel class with a CCLabelAtlas
 */
@interface CCMenuItemAtlasFont : CCMenuItemLabel
{
}

/** creates a menu item from a string and atlas with a target/selector 创建 */
+(id) itemWithString: (NSString*) value charMapFile:(NSString*) charMapFile itemWidth:(int)itemWidth itemHeight:(int)itemHeight startCharMap:(char)startCharMap;

/** creates a menu item from a string and atlas. Use it with CCMenuItemToggle.
 The "target" won't be retained. 字符串和地图
 */
+(id) itemWithString: (NSString*) value charMapFile:(NSString*) charMapFile itemWidth:(int)itemWidth itemHeight:(int)itemHeight startCharMap:(char)startCharMap target:(id)target selector:(SEL)selector;

/** initializes a menu item from a string and atlas with a target/selector.
  The "target" won't be retained.
 */
-(id) initWithString: (NSString*) value charMapFile:(NSString*) charMapFile itemWidth:(int)itemWidth itemHeight:(int)itemHeight startCharMap:(char)startCharMap target:(id)target selector:(SEL)selector;

/** creates a menu item from a string and atlas. Use it with CCMenuItemToggle.
 The block will be "copied".
 */
+(id) itemWithString: (NSString*) value charMapFile:(NSString*) charMapFile itemWidth:(int)itemWidth itemHeight:(int)itemHeight startCharMap:(char)startCharMap block:(void(^)(id sender))block;

/** initializes a menu item from a string and atlas with a  block.
 The block will be "copied".
 */
-(id) initWithString: (NSString*) value charMapFile:(NSString*) charMapFile itemWidth:(int)itemWidth itemHeight:(int)itemHeight startCharMap:(char)startCharMap block:(void(^)(id sender))block;

@end

#pragma mark -
#pragma mark CCMenuItemFont

/** A CCMenuItemFont
 Helper class that creates a CCMenuItemLabel class with a Label
 */
@interface CCMenuItemFont : CCMenuItemLabel
{
	NSUInteger fontSize_;
	NSString *fontName_;
}
/** set default font size  设置默认字体 */
+(void) setFontSize: (NSUInteger) s;

/** get default font size 大小 */
+(NSUInteger) fontSize;

/** set default font name   字体名称*/
+(void) setFontName: (NSString*) n;

/** get default font name */
+(NSString*) fontName;

/** creates a menu item from a string without target/selector. To be used with CCMenuItemToggle   字符串来创建*/
+(id) itemWithString: (NSString*) value;

/** creates a menu item from a string with a target/selector.
 The "target" won't be retained.
 */
+(id) itemWithString: (NSString*) value target:(id) r selector:(SEL) s;

/** creates a menu item from a string with the specified block.
 The block will be "copied".  字符串和块
 */
+(id) itemWithString: (NSString*) value block:(void(^)(id sender))block;

/** initializes a menu item from a string with a target/selector
  The "target" won't be retained.
 */
-(id) initWithString: (NSString*) value target:(id) r selector:(SEL) s;

/** set font size  设置和获取字体大小 */
-(void) setFontSize: (NSUInteger) s;

/** get font size */
-(NSUInteger) fontSize;

/** set the font name   设置和获取字体名称*/
-(void) setFontName: (NSString*) n;

/** get the font name */
-(NSString*) fontName;

/** initializes a menu item from a string with the specified block.
 The block will be "copied".
 */
-(id) initWithString: (NSString*) value block:(void(^)(id sender))block;

@end

#pragma mark -
#pragma mark CCMenuItemSprite

/** CCMenuItemSprite accepts CCNode<CCRGBAProtocol> objects as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
选中，未选中，不可见图片。图片的三种状态
 @since v0.8.0
 */
@interface CCMenuItemSprite : CCMenuItem <CCRGBAProtocol>
{
	CCNode<CCRGBAProtocol> *normalImage_, *selectedImage_, *disabledImage_;
}

// weak references

/** the image used when the item is not selected   正常图片*/
@property (nonatomic,readwrite,assign) CCNode<CCRGBAProtocol> *normalImage;
/** the image used when the item is selected  选中 */
@property (nonatomic,readwrite,assign) CCNode<CCRGBAProtocol> *selectedImage;
/** the image used when the item is disabled  不可见 */
@property (nonatomic,readwrite,assign) CCNode<CCRGBAProtocol> *disabledImage;

/** creates a menu item with a normal and selected image  使用正常和选中图片来创建*/
+(id) itemWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite;
/** creates a menu item with a normal and selected image with target/selector.
 The "target" won't be retained.  正常和选中图片及目标或选择器来创建
 */
+(id) itemWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite target:(id)target selector:(SEL)selector;

/** creates a menu item with a normal,selected  and disabled image with target/selector.
 The "target" won't be retained.
 */
+(id) itemWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite disabledSprite:(CCNode<CCRGBAProtocol>*)disabledSprite target:(id)target selector:(SEL)selector;

/** creates a menu item with a normal and selected image with a block.
 The block will be "copied".
 */
+(id) itemWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite block:(void(^)(id sender))block;

/** creates a menu item with a normal,selected  and disabled image with a block.
 The block will be "copied".
 */
+(id) itemWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite disabledSprite:(CCNode<CCRGBAProtocol>*)disabledSprite block:(void(^)(id sender))block;

/** initializes a menu item with a normal, selected  and disabled image with target/selector.
 The "target" won't be retained.
 */
-(id) initWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite disabledSprite:(CCNode<CCRGBAProtocol>*)disabledSprite target:(id)target selector:(SEL)selector;

/** initializes a menu item with a normal, selected  and disabled image with a block.  块。
 The block will be "copied".块是可以复制的
 */
-(id) initWithNormalSprite:(CCNode<CCRGBAProtocol>*)normalSprite selectedSprite:(CCNode<CCRGBAProtocol>*)selectedSprite disabledSprite:(CCNode<CCRGBAProtocol>*)disabledSprite block:(void(^)(id sender))block;

@end

#pragma mark -
#pragma mark CCMenuItemImage

/** CCMenuItemImage accepts images as items.
 The images has 3 different states:
 - unselected image
 - selected image
 - disabled image
接收图片最为菜单，状态同上：未选中，选中，不可用
 For best results try that all images are of the same size
最好所有图片具有相同的大小
 */
@interface CCMenuItemImage : CCMenuItemSprite
{
}

/** creates a menu item with a normal and selected image*/
+(id) itemWithNormalImage: (NSString*)value selectedImage:(NSString*) value2;

/** creates a menu item with a normal and selected image with target/selector */
+(id) itemWithNormalImage: (NSString*)value selectedImage:(NSString*) value2 target:(id) r selector:(SEL) s;

/** creates a menu item with a normal,selected  and disabled image with target/selector.
 The "target" won't be retained.
 */
+(id) itemWithNormalImage: (NSString*)value selectedImage:(NSString*) value2 disabledImage:(NSString*) value3 target:(id) r selector:(SEL) s;

/** creates a menu item with a normal and selected image with a block.
 The block will be "copied".
 */
+(id) itemWithNormalImage: (NSString*)value selectedImage:(NSString*) value2 block:(void(^)(id sender))block;

/** creates a menu item with a normal,selected  and disabled image with a block.
 The block will be "copied".
*/
+(id) itemWithNormalImage: (NSString*)value selectedImage:(NSString*) value2 disabledImage:(NSString*) value3 block:(void(^)(id sender))block;

/** initializes a menu item with a normal, selected  and disabled image with target/selector.
 The "target" won't be retained.
 */
-(id) initWithNormalImage: (NSString*) value selectedImage:(NSString*)value2 disabledImage:(NSString*) value3 target:(id) r selector:(SEL) s;

/** initializes a menu item with a normal, selected  and disabled image with a block.
 The block will be "copied".
*/
-(id) initWithNormalImage: (NSString*) value selectedImage:(NSString*)value2 disabledImage:(NSString*) value3 block:(void(^)(id sender))block;

/** sets the sprite frame for the normal image */
- (void) setNormalSpriteFrame:(CCSpriteFrame*)frame;

/** sets the sprite frame for the selected image */
- (void) setSelectedSpriteFrame:(CCSpriteFrame*)frame;

/** sets the sprite frame for the disabled image */
- (void) setDisabledSpriteFrame:(CCSpriteFrame*)frame;

@end

#pragma mark -
#pragma mark CCMenuItemToggle

/** A CCMenuItemToggle
 A simple container class that "toggles" its inner items
 The inner itmes can be any MenuItem
菜单切换类
 */
@interface CCMenuItemToggle : CCMenuItem <CCRGBAProtocol>
{
	NSUInteger selectedIndex_;
	NSMutableArray* subItems_;
	GLubyte		opacity_;
	ccColor3B	color_;
}

/** conforms with CCRGBAProtocol protocol  符合CCRGBAProtocol 协议 */
@property (nonatomic,readonly) GLubyte opacity;
/** conforms with CCRGBAProtocol protocol */
@property (nonatomic,readonly) ccColor3B color;

/** returns the selected item   返回选中的菜单*/
@property (nonatomic,readwrite) NSUInteger selectedIndex;
/** NSMutableArray that contains the subitems. You can add/remove items in runtime, and you can replace the array with a new one.
 @since v0.7.2   菜单子项。  可以增加和移除在运行时。
 */
@property (nonatomic,readwrite,retain) NSMutableArray *subItems;

/** creates a menu item from a list of items with a target/selector */
+(id) itemWithTarget:(id)target selector:(SEL)selector items:(CCMenuItem*) item, ... NS_REQUIRES_NIL_TERMINATION;

/** creates a menu item from a list of items and executes the given block when the item is selected.
 The block will be "copied".  用菜单数组和块来创建
 */
+(id) itemWithItems:(NSArray*)arrayOfItems block:(void(^)(id sender))block;

/** initializes a menu item from a list of items with a target selector */
-(id) initWithTarget:(id)target selector:(SEL)selector items:(CCMenuItem*) item vaList:(va_list) args;

/** initializes a menu item from a list of items with a block.
 The block will be "copied".
 */
-(id) initWithItems:(NSArray*)arrayOfItems block:(void (^)(id))block;

/** return the selected item  返回选中的菜单 */
-(CCMenuItem*) selectedItem;
@end

