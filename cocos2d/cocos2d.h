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

/** @mainpage cocos2d for iPhone API reference
 *
 * @image html Icon.png
 *
 * @section intro Introduction
 * This is cocos2d API reference
 *这是cocos2d API参考，可以浏览下面的链接
 * The programming guide is hosted here: http://www.cocos2d-iphone.org/wiki/doku.php/prog_guide:index
 *
 * <hr>
 *
 * @todo A native english speaker should check the grammar. We need your help!
 *
 */

// 0x00 HI ME LO
// 00   02 00 00    定义版本
#define COCOS2D_VERSION 0x00020000


//所有头文件，首先添加配置
// all cocos2d include files
//
#import "ccConfig.h"	// should be included first
//动作
#import "CCActionManager.h"
#import "CCAction.h"
#import "CCActionInstant.h"
#import "CCActionInterval.h"
#import "CCActionEase.h"
#import "CCActionCamera.h"
#import "CCActionTween.h"
#import "CCActionEase.h"
#import "CCActionTiledGrid.h"
#import "CCActionGrid3D.h"
#import "CCActionGrid.h"
#import "CCActionProgressTimer.h"
#import "CCActionPageTurn3D.h"
#import "CCActionCatmullRom.h"
//动画与精灵
#import "CCAnimation.h"
#import "CCAnimationCache.h"
#import "CCSprite.h"
#import "CCSpriteFrame.h"
#import "CCSpriteBatchNode.h"
#import "CCSpriteFrameCache.h"
//标签
#import "CCLabelTTF.h"
#import "CCLabelBMFont.h"
#import "CCLabelAtlas.h"
//粒子
#import "CCParticleSystem.h"
#import "CCParticleSystemQuad.h"
#import "CCParticleExamples.h"
#import "CCParticleBatchNode.h"
//纹理
#import "CCTexture2D.h"
#import "CCTexturePVR.h"
#import "CCTextureCache.h"
#import "CCTextureAtlas.h"
//过渡
#import "CCTransition.h"
#import "CCTransitionPageTurn.h"
#import "CCTransitionProgress.h"
//地图
#import "CCTMXTiledMap.h"
#import "CCTMXLayer.h"
#import "CCTMXObjectGroup.h"
#import "CCTMXXMLParser.h"
#import "CCTileMapAtlas.h"
//层，菜单，场景，调度，对象基类
#import "CCLayer.h"
#import "CCMenu.h"
#import "CCMenuItem.h"
#import "CCDrawingPrimitives.h"
#import "CCScene.h"
#import "CCScheduler.h"
#import "CCCamera.h"
#import "CCProtocols.h"
#import "CCNode.h"
#import "CCNode+Debug.h"
#import "CCDirector.h"
#import "CCAtlasNode.h"
#import "CCGrabber.h"
#import "CCGrid.h"
#import "CCParallaxNode.h"
#import "CCRenderTexture.h"
#import "CCMotionStreak.h"
#import "CCConfiguration.h"

// Shaders  着色器
#import "CCGLProgram.h"
#import "ccGLStateCache.h"
#import "CCShaderCache.h"
#import "ccShaders.h"

//
// cocos2d macros
// 定义的宏
#import "ccTypes.h"
#import "ccMacros.h"

//
// Deprecated methods/classes/functions since v1.0
// 放弃的方法、类，函数
#import "ccDeprecated.h"

// Platform common  平台通用
#import "Platforms/CCGL.h"
#import "Platforms/CCNS.h"
//针对ios
#ifdef __CC_PLATFORM_IOS
#import "Platforms/iOS/CCTouchDispatcher.h"
#import "Platforms/iOS/CCTouchDelegateProtocol.h"
#import "Platforms/iOS/CCTouchHandler.h"
#import "Platforms/iOS/CCGLView.h"
#import "Platforms/iOS/CCDirectorIOS.h"
//针对mac平台
#elif defined(__CC_PLATFORM_MAC)
#import "Platforms/Mac/CCGLView.h"
#import "Platforms/Mac/CCDirectorMac.h"
#import "Platforms/Mac/CCWindow.h"
#import "Platforms/Mac/CCEventDispatcher.h"
#endif

//
// cocos2d helper files
// 相关帮助文件：openGl,文件，字符串，等
#import "Support/OpenGL_Internal.h"
#import "Support/CCFileUtils.h"
#import "Support/CGPointExtension.h"
#import "Support/ccCArray.h"
#import "Support/CCArray.h"
#import "Support/ccUtils.h"
#import "Support/TransformUtils.h"
#import "Support/CCProfiling.h"

//
// external
// 扩展用到的数学库
#import "kazmath/kazmath.h"
#import "kazmath/GL/matrix.h"



// free functions
NSString * cocos2dVersion(void);
//关于设备的系统版本
#ifdef __CC_PLATFORM_IOS
#ifndef __IPHONE_4_0
#error "If you are targeting iPad, you should set BASE SDK = 4.0 (or 4.1, or 4.2), and set the 'iOS deploy target' = 3.2"
#endif
#endif
