//
// TGA lib for cocos2d-iphone
//
// sources from: http://www.lighthouse3d.com/opengl/terrain/index.php3?tgasource
//

//#ifndef TGA_LIB
//#define TGA_LIB

/**
 @file
 TGA image support  支持的图片格式：TGA支持压缩，使用不失真的压缩算法，可以带通道图，另外还支持行程编码压缩
 */

enum {
	TGA_OK,
	TGA_ERROR_FILE_OPEN,
	TGA_ERROR_READING_FILE,
	TGA_ERROR_INDEXED_COLOR,
	TGA_ERROR_MEMORY,
	TGA_ERROR_COMPRESSED_FILE,
};

/** TGA format 格式 */
typedef struct sImageTGA {
	int status;
	unsigned char type, pixelDepth;

	/** map width */
	short int width;

	/** map height */
	short int height;

	/** raw data */
	unsigned char *imageData;
	int flipped;
} tImageTGA;

/// load the image header fields. We only keep those that matter! 文件，信息
void tgaLoadHeader(FILE *file, tImageTGA *info);

/// loads the image pixels. You shouldn't call this function directly
void tgaLoadImageData(FILE *file, tImageTGA *info);

/// this is the function to call when we want to load an image 图片
tImageTGA * tgaLoad(const char *filename);

// /converts RGB to greyscale
void tgaRGBtogreyscale(tImageTGA *info);

/// releases the memory used for the image 释放内存从图片
void tgaDestroy(tImageTGA *info);

//#endif // TGA_LIB
