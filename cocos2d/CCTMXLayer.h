/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2009-2010 Ricardo Quesada
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
 *
 * TMX Tiled Map support:
 * http://www.mapeditor.org
 * TMX:文本文件
 */


#import "CCAtlasNode.h"
#import "CCSpriteBatchNode.h"
#import "CCTMXXMLParser.h"

@class CCTMXMapInfo;
@class CCTMXLayerInfo;
@class CCTMXTilesetInfo;


/** CCTMXLayer represents the TMX layer. 文本层
是批量节点的子类，默认用纹理集合呈现；运行时修改一个瓦片，变为一个精灵，否则没有对象可以创建；可以使用旋转，缩放，移动方法
 It is a subclass of CCSpriteBatchNode. By default the tiles are rendered using a CCTextureAtlas.
 If you mofify a tile on runtime, then, that tile will become a CCSprite, otherwise no CCSprite objects are created.
 The benefits of using CCSprite objects as tiles are:
 - tiles (CCSprite) can be rotated/scaled/moved with a nice API

 cocos2d v2.0 doesn't support the cc_vertexz value. Whenever a the cc_vertexz property is found, it will raise an exception.

 "value" by default is 0, but you can change it from Tiled by adding the "cc_alpha_func" property to the layer.
 The value 0 should work for most cases, but if you have tiles that are semi-transparent, then you might want to use a differnt
 value, like 0.5.

 For further information, please see the programming guide:

	http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:tiled_maps

 @since v0.8.1
 
 Tiles can have tile flags for additional properties. At the moment only flip horizontal and flip vertical are used. These bit flags are defined in CCTMXXMLParser.h.
 瓦片具有标志属性；某一时刻，只有垂直和水平翻转使用，在CCTMXXMLParser.h有定义
 @since 1.1
 */
@interface CCTMXLayer : CCSpriteBatchNode
{
	CCTMXTilesetInfo	*tileset_;
	NSString			*layerName_;
	CGSize				layerSize_;
	CGSize				mapTileSize_;
	uint32_t			*tiles_;			// GID are 32 bit GID: 群体身份（指共享资源系统使用者的身份）
	NSUInteger			layerOrientation_;
	NSMutableArray		*properties_;

	unsigned char		opacity_; // TMX Layer supports opacity 容量

	NSUInteger			minGID_;
	NSUInteger			maxGID_;

	// Only used when vertexZ is used
	NSInteger			vertexZvalue_;
	BOOL				useAutomaticVertexZ_;

	// used for optimization 用于优化
	CCSprite		*reusedTile_;
	ccCArray		*atlasIndexArray_;
}
/** name of the layer 层名称*/
@property (nonatomic,readwrite,retain) NSString *layerName;
/** size of the layer in tiles 层大小*/
@property (nonatomic,readwrite) CGSize layerSize;
/** size of the map's tile (could be differnt from the tile's size) 大小 */
@property (nonatomic,readwrite) CGSize mapTileSize;
/** pointer to the map of tiles 瓦片地图指针 */
@property (nonatomic,readwrite) uint32_t *tiles;
/** Tilset information for the layer  信息*/
@property (nonatomic,readwrite,retain) CCTMXTilesetInfo *tileset;
/** Layer orientation, which is the same as the map orientation 方向*/
@property (nonatomic,readwrite) NSUInteger layerOrientation;
/** properties from the layer. They can be added using Tiled 属性 */
@property (nonatomic,readwrite,retain) NSMutableArray *properties;

/** creates a CCTMXLayer with an tileset info, a layer info and a map info */
+(id) layerWithTilesetInfo:(CCTMXTilesetInfo*)tilesetInfo layerInfo:(CCTMXLayerInfo*)layerInfo mapInfo:(CCTMXMapInfo*)mapInfo;
/** initializes a CCTMXLayer with a tileset info, a layer info and a map info  创建和初始化*/
-(id) initWithTilesetInfo:(CCTMXTilesetInfo*)tilesetInfo layerInfo:(CCTMXLayerInfo*)layerInfo mapInfo:(CCTMXMapInfo*)mapInfo;

/** dealloc the map that contains the tile position from memory. 释放；除非你知道运行时瓦片的位置，才调用此方法；你可以使用[layer tileGIDAt:]
 Unless you want to know at runtime the tiles positions, you can safely call this method.
 If you are going to call [layer tileGIDAt:] then, don't release the map
 */
-(void) releaseMap;

/** returns the tile (CCSprite) at a given a tile coordinate.
 The returned CCSprite will be already added to the CCTMXLayer. Don't add it again.
 The CCSprite can be treated like any other CCSprite: rotated, scaled, translated, opacity, color, etc.
 返回给定坐标的瓦片；已经添加上的，不用再次添加；返回的精灵可以入其他精灵一样可以选择，缩放，转换，透明度，颜色；
 同样也可以删除
 You can remove either by calling:
	- [layer removeChild:sprite cleanup:cleanup];
	- or [layer removeTileAt:ccp(x,y)];
 */
-(CCSprite*) tileAt:(CGPoint)tileCoordinate;

/** returns the tile gid at a given tile coordinate.
 if it returns 0, it means that the tile is empty.
 This method requires the the tile map has not been previously released (eg. don't call [layer releaseMap])
 返回gid；0标示没有；瓦片地图没有被释放，不用调用[layer releaseMap]
 */
-(uint32_t) tileGIDAt:(CGPoint)tileCoordinate;

/** returns the tile gid at a given tile coordinate. It also returns the tile flags.
 This method requires the the tile map has not been previously released (eg. don't call [layer releaseMap])
 标志
 */
-(uint32_t) tileGIDAt:(CGPoint)pos withFlags:(ccTMXTileFlags*)flags;

/** sets the tile gid (gid = tile global id 瓦片全局序号) at a given tile coordinate.
 The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
 If a tile is already placed at that position, then it will be removed.
 */
-(void) setTileGID:(uint32_t)gid at:(CGPoint)tileCoordinate;

/** sets the tile gid (gid = tile global id) at a given tile coordinate.
 The Tile GID can be obtained by using the method "tileGIDAt" or by using the TMX editor -> Tileset Mgr +1.
 If a tile is already placed at that position, then it will be removed.
 
 Use withFlags if the tile flags need to be changed as well
 */

-(void) setTileGID:(uint32_t)gid at:(CGPoint)pos withFlags:(ccTMXTileFlags)flags;

/** removes a tile at given tile coordinate 移除一个*/
-(void) removeTileAt:(CGPoint)tileCoordinate;

/** returns the position in points of a given tile coordinate */
-(CGPoint) positionAt:(CGPoint)tileCoordinate;

/** return the value for the specific property name  返回指定属性名称*/
-(id) propertyNamed:(NSString *)propertyName;

/** Creates the tiles 创建瓦片*/
-(void) setupTiles;

/** CCTMXLayer doesn't support adding a CCSprite manually. 不支持增加精灵手动；
 @warning addchild:z:tag: is not supported on CCTMXLayer. Instead of setTileGID:at:/tileAt:
 */
-(void) addChild: (CCNode*)node z:(NSInteger)z tag:(NSInteger)tag;
@end
