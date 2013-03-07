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
 * Portions of this code are based and inspired on:
 *   http://www.71squared.co.uk/2009/04/iphone-game-programming-tutorial-4-bitmap-font-class
 *   by Michael Daley
 *
 * Use any of these editors to generate BMFonts:
 *   http://glyphdesigner.71squared.com/ (Commercial, Mac OS X)
 *   http://www.n4te.com/hiero/hiero.jnlp (Free, Java)
 *   http://slick.cokeandcode.com/demos/hiero.jnlp (Free, Java)
 *   http://www.angelcode.com/products/bmfont/ (Free, Windows only)
 */

#import "CCSpriteBatchNode.h"
#import "Support/uthash.h"

enum {
	kCCLabelAutomaticWidth = -1,
};

struct _KerningHashElement;

/** @struct ccBMFontDef
 BMFont definition  BMFont是一个写字库。 声明
 */
typedef struct _BMFontDef {
	//! ID of the character
	unichar charID;
	//! origin and size of the font  大小
	CGRect rect;
	//! The X amount the image should be offset when drawing the image (in pixels) 偏移量x
	short xOffset;
	//! The Y amount the image should be offset when drawing the image (in pixels) y轴偏移量
	short yOffset;
	//! The amount to move the current position after drawing the character (in pixels) 像素数
	short xAdvance;
} ccBMFontDef;

/** @struct ccBMFontPadding
 BMFont padding  填充
 @since v0.8.2
 */
typedef struct _BMFontPadding {
	/// padding left
	int	left;
	/// padding top
	int top;
	/// padding right
	int right;
	/// padding bottom
	int bottom;
} ccBMFontPadding;


/** CCBMFontConfiguration has parsed configuration of the the .fnt file
 @since v0.8 配置
 */
@interface CCBMFontConfiguration : NSObject
{
	// atlas name
	NSString		*atlasName_;

    // XXX: Creating a public interface so that the bitmapFontArray[] is accesible
@public

	// BMFont definitions  声明定义
	struct _FontDefHashElement	*fontDefDictionary_;

	// FNTConfig: Common Height. Should be signed (issue #1343) 通用高
	NSInteger		commonHeight_;

	// Padding
	ccBMFontPadding	padding_;

	// values for kerning  字距
	struct _KerningHashElement	*kerningDictionary_;
}

// atlasName
@property (nonatomic, readwrite, retain) NSString *atlasName;

/** allocates a CCBMFontConfiguration with a FNT file 使用字体文件来配置创建和初始化。 fnt是字体文件*/
+(id) configurationWithFNTFile:(NSString*)FNTfile;
/** initializes a CCBMFontConfiguration with a FNT file */
-(id) initWithFNTfile:(NSString*)FNTfile;
@end


/** CCLabelBMFont is a subclass of CCSpriteBatchNode
是CCSpriteBatchNode的子类。
特征：每个字符就如一个精灵。就代表具有以下特性：可以旋转，缩放，转化，着色，改变透明度，作为菜单子项，对齐格式
 Features:
 - Treats each character like a CCSprite. This means that each individual character can be:
 - rotated
 - scaled
 - translated
 - tinted
 - chage the opacity
 - It can be used as part of a menu item.
 - anchorPoint can be used to align the "label"
 - Supports AngelCode text format

 Limitations:限制：使用锚点(0.5f, 0.5f)，不推荐改变，可能会影响效果
 - All inner characters are using an anchorPoint of (0.5f, 0.5f) and it is not recommend to change it
 because it might affect the rendering

 CCLabelBMFont implements the protocol CCLabelProtocol, like CCLabel and CCLabelAtlas.
 CCLabelBMFont has the flexibility of CCLabel, the speed of CCLabelAtlas and all the features of CCSprite.
 If in doubt, use CCLabelBMFont instead of CCLabelAtlas / CCLabel.
CCLabelBMFont 实现了CCLabelProtocol的相关协议，具有CCLabel的灵活性，CCLabelAtlas的速度和所有CCSprite的特征
 Supported editors:
 - http://glyphdesigner.71squared.com/
 - http://www.bmglyph.com/
 - http://www.n4te.com/hiero/hiero.jnlp
 - http://slick.cokeandcode.com/demos/hiero.jnlp
 - http://www.angelcode.com/products/bmfont/

 @since v0.8
 */

@interface CCLabelBMFont : CCSpriteBatchNode <CCLabelProtocol, CCRGBAProtocol>
{
	// string to render
	NSString		*string_;
    
    // name of fntFile  fat文件名
    NSString        *fntFile_;

    // initial string without line breaks  初始字符串
    NSString *initialString_;
    // max width until a line break is added  最大宽，直到换行
    float width_;
    // alignment of all lines  对齐所有行
    CCTextAlignment alignment_;

	CCBMFontConfiguration	*configuration_;

	// texture RGBA  纹理
	GLubyte		opacity_;
	ccColor3B	color_;
	BOOL opacityModifyRGB_;
	
	// offset of the texture atlas  偏移
	CGPoint			imageOffset_;
}

/** Purges the cached data.  清除缓存数据
 Removes from memory the cached configurations and the atlas name dictionary.
 @since v0.99.3
 */
+(void) purgeCachedData;

/** alignment used for the label  对齐*/
@property (nonatomic,assign,readonly) CCTextAlignment alignment;
/** fntFile used for the font  fnt文件 */
@property (nonatomic,retain) NSString* fntFile;
/** conforms to CCRGBAProtocol protocol  符合CCRGBProtocol协议 */
@property (nonatomic,readwrite) GLubyte opacity;
/** conforms to CCRGBAProtocol protocol  同上*/
@property (nonatomic,readwrite) ccColor3B color;


/** creates a BMFont label with an initial string and the FNT file.  通过字符串和fnt文件创建*/
+(id) labelWithString:(NSString*)string fntFile:(NSString*)fntFile;
/** creates a BMFont label with an initial string, the FNT file, width, and alignment option       字符串，fnt文件，宽，和对齐选项来创建 */
+(id) labelWithString:(NSString*)string fntFile:(NSString*)fntFile width:(float)width alignment:(CCTextAlignment)alignment;
/** creates a BMFont label with an initial string, the FNT file, width, alignment option and the offset of where the glpyhs start on the .PNG image  增加偏移参数 */
+(id) labelWithString:(NSString*)string fntFile:(NSString*)fntFile width:(float)width alignment:(CCTextAlignment)alignment imageOffset:(CGPoint)offset;

/** init a BMFont label with an initial string and the FNT file  初始化方法 */
-(id) initWithString:(NSString*)string fntFile:(NSString*)fntFile;
/** init a BMFont label with an initial string and the FNT file, width, and alignment option*/
-(id) initWithString:(NSString*)string fntFile:(NSString*)fntFile width:(float)width alignment:(CCTextAlignment)alignment;
/** init a BMFont label with an initial string and the FNT file, width, alignment option and the offset of where the glyphs start on the .PNG image */
-(id) initWithString:(NSString*)string fntFile:(NSString*)fntFile width:(float)width alignment:(CCTextAlignment)alignment imageOffset:(CGPoint)offset;

/** updates the font chars based on the string to render  更新字体*/
-(void) createFontChars;

/** set label width  设置宽度 */
- (void)setWidth:(float)width;

/** set label alignment 设置对齐方式 */
- (void)setAlignment:(CCTextAlignment)alignment;

@end

/** Free function that parses a FNT file a place it on the cache 载人配置fnt文件
 */
CCBMFontConfiguration * FNTConfigLoadFile( NSString *file );
/** Purges the FNT config cache   清除配置缓存
 */
void FNTConfigRemoveCache( void );


