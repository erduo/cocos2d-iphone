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
 *
 */

#import "CCNode.h"

@class CCTMXLayer;
@class CCTMXObjectGroup;

/** Possible oritentations of the TMX map 可能的方向 */
enum
{
	/** Orthogonal orientation 正交*/
	CCTMXOrientationOrtho,

	/** Hexagonal orientation 六角*/
	CCTMXOrientationHex,

	/** Isometric orientation 等距*/
	CCTMXOrientationIso,
};

/** CCTMXTiledMap knows how to parse and render a TMX map.
知道怎样显示tmx地图；
 It adds support for the TMX tiled map format used by http://www.mapeditor.org
 It supports isometric, hexagonal and orthogonal tiles.
 It also supports object groups, objects, and properties.
增加支持tmx瓦片地图格式；支持正交，六角，等距瓦片； 特征具有：
1，作为精灵；2，创建精灵仅仅可以调用[layer titleAt:];3，可以旋转，移动，缩放，透明度；4，可以在运行时增加移除；
5，运行时排序；6，锚点都为(0,0);7，增加子对象；8，默认别名；9，使用纹理缓存载人图片；10，独一无二标示；
11，独一无二z值；12，每个对象组都可以作为可变数组；13，所有属性都在字典中；14，属性可以赋值给地图，层，对象组，对象；
 Features:
 - Each tile will be treated as an CCSprite
 - The sprites are created on demand. They will be created only when you call "[layer tileAt:]"
 - Each tile can be rotated / moved / scaled / tinted / "opacitied", since each tile is a CCSprite
 - Tiles can be added/removed in runtime
 - The z-order of the tiles can be modified in runtime
 - Each tile has an anchorPoint of (0,0)
 - The anchorPoint of the TMXTileMap is (0,0)
 - The TMX layers will be added as a child
 - The TMX layers will be aliased by default
 - The tileset image will be loaded using the CCTextureCache
 - Each tile will have a unique tag
 - Each tile will have a unique z value. top-left: z=1, bottom-right: z=max z
 - Each object group will be treated as an NSMutableArray
 - Object class which will contain all the properties in a dictionary
 - Properties can be assigned to the Map, Layer, Object Group, and Object
限制：每个层仅仅一个瓦片集合；不支持嵌入式图片；只支持xml格式，不支持json格式；
 Limitations:
 - It only supports one tileset per layer.
 - Embeded images are not supported
 - It only supports the XML format (the JSON format is not supported)

 Technical description:
 技术描述：使用CCTMXLayer来创建每个层；如果层的可见性关了，曾不能创建；可以在运行时获取层：[map getChildByTag:tag_number]
   Each layer is created using an CCTMXLayer (subclass of CCSpriteBatchNode). If you have 5 layers, then 5 CCTMXLayer will be created,
   unless the layer visibility is off. In that case, the layer won't be created at all.
   You can obtain the layers (CCTMXLayer objects) at runtime by:
  - [map getChildByTag: tag_number];  // 0=1st layer, 1=2nd layer, 2=3rd layer, etc...
  - [map layerNamed: name_of_the_layer];
每个对象组都可以被认为是可变数组的子类；可以使用[map objectGroupNamed:name_of_object_group]获取
   Each object group is created using a CCTMXObjectGroup which is a subclass of NSMutableArray.
   You can obtain the object groups at runtime by:
   - [map objectGroupNamed: name_of_the_object_group];

   Each object is a CCTMXObject.
每个对象是CCTMXObject; 每个属性都存储在可变字典里；可以在运行时获取属性；
   Each property is stored as a key-value pair in an NSMutableDictionary.
   You can obtain the properties at runtime by:

		[map propertyNamed: name_of_the_property];
		[layer propertyNamed: name_of_the_property];
		[objectGroup propertyNamed: name_of_the_property];
		[object propertyNamed: name_of_the_property];

 @since v0.8.1
 */
@interface CCTMXTiledMap : CCNode
{
	CGSize				mapSize_;
	CGSize				tileSize_;
	int					mapOrientation_;
	NSMutableArray		*objectGroups_;
	NSMutableDictionary	*properties_;
	NSMutableDictionary	*tileProperties_;
}

/** the map's size property measured in tiles 大小 */
@property (nonatomic,readonly) CGSize mapSize;
/** the tiles's size property measured in pixels 以像素为单位的大小*/
@property (nonatomic,readonly) CGSize tileSize;
/** map orientation 方向*/
@property (nonatomic,readonly) int mapOrientation;
/** object groups 对象组*/
@property (nonatomic,readwrite,retain) NSMutableArray *objectGroups;
/** properties 属性*/
@property (nonatomic,readwrite,retain) NSMutableDictionary *properties;

/** creates a TMX Tiled Map with a TMX file. 使用tmx文件来创建*/
+(id) tiledMapWithTMXFile:(NSString*)tmxFile;

/** initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources 资源路径*/
+(id) tiledMapWithXML:(NSString*)tmxString resourcePath:(NSString*)resourcePath;

/** initializes a TMX Tiled Map with a TMX file. tmx文件参数*/
-(id) initWithTMXFile:(NSString*)tmxFile;

/** initializes a TMX Tiled Map with a TMX formatted XML string and a path to TMX resources 使用xml字符串和路径初始化 */
-(id) initWithXML:(NSString*)tmxString resourcePath:(NSString*)resourcePath;

/** return the TMXLayer for the specific layer 返回指定的层*/
-(CCTMXLayer*) layerNamed:(NSString *)layerName;

/** return the TMXObjectGroup for the secific group 返回指定组 */
-(CCTMXObjectGroup*) objectGroupNamed:(NSString *)groupName;

/** return the value for the specific property name返回指定属性值 */
-(id) propertyNamed:(NSString *)propertyName;

/** return properties dictionary for tile GID 用gid参数来返回属性字典 */
-(NSDictionary*)propertiesForGID:(unsigned int)GID;
@end

