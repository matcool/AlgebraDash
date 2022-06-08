#include "../../includes.h"

#define PROFILER_HOOK_THIS_ARGS(address, ret, space, type, name, argsC, ...) PROFILER_HOOK(address, space##::##type##::##name, ret, __thiscall, __fastcall, space##_##type##_##name, (space##::##type*, __VA_ARGS__), (space##::##type* self, void*, __VA_ARGS__), argsC)
#define PROFILER_HOOK_THIS(address, ret, space, type, name) PROFILER_HOOK(address, space##::##type##::##name, ret, __thiscall, __fastcall, space##_##type##_##name, (space##::##type*), (space##::##type* self), (self))
#define PROFILER_HOOK_2_ARGS(address, ret, callConv, space, type, name, argsC, ...) PROFILER_HOOK(address, space##::##type##::##name, ret, callConv, callConv, space##_##type##_##name, (__VA_ARGS__), (__VA_ARGS__), argsC)
#define PROFILER_HOOK_2(address, ret, callConv, space, type, name) PROFILER_HOOK(address, space##::##type##::##name, ret, callConv, callConv, space##_##type##_##name, (), (), ())
#define PROFILER_HOOK_1_ARGS(address, ret, callConv, space, name, argsC, ...) PROFILER_HOOK(address, space##::##name, ret, callConv, callConv, space##_##name, (__VA_ARGS__), (__VA_ARGS__), argsC)
#define PROFILER_HOOK_1(address, ret, callConv, space, name) PROFILER_HOOK(address, space##::##name, ret, callConv, callConv, space##_##name, (), (), ())
#define PROFILER_HOOK_0_ARGS(address, ret, callConv, name, argsC, ...) PROFILER_HOOK(address, name, ret, callConv, callConv, name, (__VA_ARGS__), (__VA_ARGS__), argsC)
#define PROFILER_HOOK_0(address, ret, callConv, name) PROFILER_HOOK(address, name, ret, callConv, callConv, name, (), (), ())

// haha rip dll size

// pre frame
PROFILER_HOOK_THIS(COCOS2D + 0xc44b0, void, cocos2d, CCEGLView, pollEvents)
PROFILER_HOOK_2_ARGS(COCOS2D + 0x110dc0, void, __cdecl, cocos2d, CCEGLView, FUN_10110dc0, (idk), int idk)
PROFILER_HOOK_2_ARGS(COCOS2D + 0x111a80, void, __cdecl, cocos2d, CCEGLView, FUN_10111a80, (idk1, idk2, idk3, idk4, idk5), int idk1, int idk2, int idk3, int idk4, int idk5)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x100470, void, cocos2d, CCDirector, setDeltaTime, (self, dt), float dt)

// actual frame
PROFILER_HOOK_THIS(COCOS2D + 0xff410, void, cocos2d, CCDirector, drawScene)
PROFILER_HOOK_THIS(COCOS2D + 0x1005b0, void, cocos2d, CCDirector, setNextScene)

// gd init
PROFILER_HOOK_THIS_ARGS(GD + 0x16c4d0, bool, gd, DrawGridLayer, init, (self, idk1, idk2), void* idk1, void* idk2)
PROFILER_HOOK_THIS_ARGS(GD + 0x6f5d0, bool, gd, EditLevelLayer, init, (self, level), gd::GJGameLevel* level)
PROFILER_HOOK_THIS_ARGS(GD + 0x76310, bool, gd, EditorUI, init, (self, level), gd::GJGameLevel* level)
PROFILER_HOOK_THIS_ARGS(GD + 0x15ee00, bool, gd, LevelEditorLayer, init, (self, level), gd::GJGameLevel* level)
PROFILER_HOOK_THIS_ARGS(GD + 0x18c080, bool, gd, LoadingLayer, init, (self, idk), char idk)
PROFILER_HOOK_THIS(GD + 0x1907b0, bool, gd, MenuLayer, init)
PROFILER_HOOK_THIS(GD + 0x198b20, bool, gd, ObjectToolbox, init)
PROFILER_HOOK_THIS_ARGS(GD + 0x1e6da0, bool, gd, PlayerObject, init, (self, idk1, idk2, idk3), int idk1, int idk2, CCLayer* idk3)
PROFILER_HOOK_THIS_ARGS(GD + 0x1fb780, bool, gd, PlayLayer, init, (self, level), gd::GJGameLevel* level)

// gd update
PROFILER_HOOK_THIS_ARGS(GD + 0x16cd80, void, gd, DrawGridLayer, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(GD + 0x23b20, void, gd, FMODAudioEngine, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(GD + 0xce440, void, gd, GameManager, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(GD + 0x16a660, void, gd, LevelEditorLayer, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(GD + 0x1e8200, void, gd, PlayerObject, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(GD + 0x2029c0, void, gd, PlayLayer, update, (self, dt), float dt)

// gd draw
PROFILER_HOOK_THIS(GD + 0x16ce90, void, gd, DrawGridLayer, draw)
PROFILER_HOOK_THIS(GD + 0x18fbe0, void, gd, EditorUI, draw)
PROFILER_HOOK_THIS(GD + 0x16b7c0, void, gd, LevelEditorLayer, draw)

// loading
PROFILER_HOOK_THIS(GD + 0x18c8e0, void, gd, LoadingLayer, loadAssets)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xeb860, CCTexture2D*, cocos2d, CCTextureCache, addImage, (self, path, idk), const char* path, bool idk)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xebcb0, CCTexture2D*, cocos2d, CCTextureCache, addImageAsync, (self, path, target, selector), const char* path, CCObject* target, SEL_CallFuncO selector)
PROFILER_HOOK_2_ARGS(COCOS2D + 0xec7c0, void*, __cdecl, cocos2d, CCTextureCache, loadImage, (data), void* data)
PROFILER_HOOK_2_ARGS(COCOS2D + 0xec9a0, void, __cdecl, cocos2d, CCTextureCache, loadImageData, (pAsyncStruct), void* pAsyncStruct)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd7e30, void, cocos2d, CCSpriteFrameCache, addSpriteFramesWithDictionary, (self, dict, texture), CCDictionary* dict, CCTexture2D* texture)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd8820, void, cocos2d, CCSpriteFrameCache, addSpriteFramesWithFile_pp, (self, plistPath, texturePath), const char* plistPath, const char* texturePath)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd8860, void, cocos2d, CCSpriteFrameCache, addSpriteFramesWithFile_p, (self, plistPath), const char* plistPath)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd8b80, void, cocos2d, CCSpriteFrameCache, addSpriteFramesWithFile_pt, (self, plistPath, texture), const char* plistPath, CCTexture2D* texture)
PROFILER_HOOK_2_ARGS(COCOS2D + 0x9c600, CCLabelBMFont*, __cdecl, cocos2d, CCLabelBMFont, create, (idk1, idk2, idk3, idk4, idk5), const char* idk1, const char* idk2, float idk3, CCTextAlignment idk4, CCPoint idk5)
PROFILER_HOOK_THIS(GD + 0x25520, void, gd, GameSoundManager, asynchronousSetup)
PROFILER_HOOK_THIS(GD + 0xc9420, void, gd, GameManager, FUN_0049420)
PROFILER_HOOK_THIS(GD + 0xa8cb0, void, gd, GameLevelManager, FUN_004a8cb0)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xea010, void, cocos2d, CCTexture2D, initWithImage, (self, image), CCImage* image)
PROFILER_HOOK_2_ARGS(COCOS2D + 0x9c490, CCBMFontConfiguration*, __cdecl, cocos2d, CCBMFontConfiguration, create, (fntFile), const char* fntFile)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x9e240, void*, cocos2d, CCBMFontConfiguration, parseConfigFile, (self, fntFile), const char* fntFile)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd5e30, bool, cocos2d, CCSpriteBatchNode, initWithTexture, (self, texture, capacity), CCTexture2D* texture, unsigned int capacity)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd3910, bool, cocos2d, CCSprite, initWithTexture, (self, texture, rect, rotated), CCTexture2D* texture, CCRect* rect, bool rotated)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xeabb0, bool, cocos2d, CCTextureAtlas, initWithTexture, (self, texture, capacity), CCTexture2D* texture, unsigned int capacity)
PROFILER_HOOK_THIS(COCOS2D + 0xeb340, void, cocos2d, CCTextureAtlas, setupIndices)
PROFILER_HOOK_THIS(COCOS2D + 0xeaf30, void, cocos2d, CCTextureAtlas, mapBuffers)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x103430, void, cocos2d, CCScheduler, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xc09a0, void, cocos2d, CCAccelerometer, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x103650, void, cocos2d, CCTimer, update, (self, dt), float dt)

// actions
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8f640, void, cocos2d, CCActionManager, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e2a0, void, cocos2d, CCTargetedAction, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80ae0, void, cocos2d, CCActionEase, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x938d0, void, cocos2d, CCActionTween, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8d760, void, cocos2d, CCAnimate, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87010, void, cocos2d, CCCallFunc, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e110, void, cocos2d, CCSequence, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8d960, void, cocos2d, CCBezierBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8db10, void, cocos2d, CCBlink, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x7da40, void, cocos2d, CCCardinalSplineBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x7d710, void, cocos2d, CCCardinalSplineTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dbc0, void, cocos2d, CCFadeIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dc10, void, cocos2d, CCFadeOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x92670, void, cocos2d, CCFadeOutTRTiles, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dc60, void, cocos2d, CCFadeTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87020, void, cocos2d, CCFlipX, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87030, void, cocos2d, CCFlipY, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dcc0, void, cocos2d, CCJumpBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dde0, void, cocos2d, CCMoveBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87050, void, cocos2d, CCPlace, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87070, void, cocos2d, CCRemoveSelf, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8de80, void, cocos2d, CCRepeat, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dfb0, void, cocos2d, CCReverseTime, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8dfe0, void, cocos2d, CCRotateBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e050, void, cocos2d, CCRotateTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e0c0, void, cocos2d, CCScaleTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e260, void, cocos2d, CCSpawn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e2c0, void, cocos2d, CCTintBy, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x8e380, void, cocos2d, CCTintTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x870a0, void, cocos2d, CCToggleVisibility, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87040, void, cocos2d, CCHide, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x87090, void, cocos2d, CCShow, update, (self, dt), float dt)

// progress
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x90050, void, cocos2d, CCProgressFromTo, update, (self, dt), float dt)
PROFILER_HOOK_THIS(COCOS2D + 0xafc70, void, cocos2d, CCProgressTimer, updateBar)
PROFILER_HOOK_THIS(COCOS2D + 0xb03e0, void, cocos2d, CCProgressTimer, updateColor)
PROFILER_HOOK_THIS(COCOS2D + 0xb0440, void, cocos2d, CCProgressTimer, updateProgress)
PROFILER_HOOK_THIS(COCOS2D + 0xb0460, void, cocos2d, CCProgressTimer, updateRadial)

// easings
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80b00, void, cocos2d, CCEaseBackIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80b40, void, cocos2d, CCEaseBackInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80bd0, void, cocos2d, CCEaseBackOut, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80c20, void, cocos2d, CCEaseBounceIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80c60, void, cocos2d, CCEaseBounceInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80ce0, void, cocos2d, CCEaseBounceOut, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80d10, void, cocos2d, CCEaseElasticIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80dd0, void, cocos2d, CCEaseElasticInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80f00, void, cocos2d, CCEaseElasticOut, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x80fb0, void, cocos2d, CCEaseExponentialIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x81010, void, cocos2d, CCEaseExponentialInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x81090, void, cocos2d, CCEaseExponentialOut, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x810f0, void, cocos2d, CCEaseIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x81130, void, cocos2d, CCEaseInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x811d0, void, cocos2d, CCEaseOut, update, (self, dt), float dt)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x81210, void, cocos2d, CCEaseSineIn, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x81250, void, cocos2d, CCEaseSineInOut, update, (self, dt), float dt)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x812a0, void, cocos2d, CCEaseSineOut, update, (self, dt), float dt)

// particles
PROFILER_HOOK_THIS(COCOS2D + 0xb2c50, void, cocos2d, CCParticleBatchNode, draw)
PROFILER_HOOK_THIS(COCOS2D + 0xb3380, void, cocos2d, CCParticleBatchNode, visit)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xb9600, void, cocos2d, CCParticleSystem, update, (self, dt), float dt)
PROFILER_HOOK_THIS(COCOS2D + 0xb9bc0, void, cocos2d, CCParticleSystem, updateWithNoTime)
PROFILER_HOOK_THIS(COCOS2D + 0xba0a0, void, cocos2d, CCParticleSystemQuad, draw)

// sprites
PROFILER_HOOK_THIS(COCOS2D + 0xd4f40, void, cocos2d, CCSprite, updateTransform)
PROFILER_HOOK_THIS(COCOS2D + 0xd3650, void, cocos2d, CCSprite, draw)
PROFILER_HOOK_THIS(COCOS2D + 0xd3560, CCSpriteFrame*, cocos2d, CCSprite, displayFrame)
PROFILER_HOOK_THIS(COCOS2D + 0xd5bd0, void, cocos2d, CCSpriteBatchNode, draw)
PROFILER_HOOK_THIS_ARGS(COCOS2D + 0xd68f0, void, cocos2d, CCSpriteBatchNode, swap, (self, idk1, idk2), int idk1, int idk2)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x9fb60, void, cocos2d, CCLabelBMFont, setString, (self, str, needUpdateLabel), const char* str, bool needUpdateLabel)
PROFILER_HOOK_THIS(COCOS2D + 0x9fd60, void, cocos2d, CCLabelBMFont, updateLabel)

PROFILER_HOOK_THIS_ARGS(COCOS2D + 0x60a50, void, cocos2d, CCNode, update, (self, dt), float dt)
PROFILER_HOOK_THIS(COCOS2D + 0x60c50, void, cocos2d, CCNode, visit)
PROFILER_HOOK_THIS(COCOS2D + 0x60c10, void, cocos2d, CCNode, updateTransform)

// post frame? haven't actually seen this getting called so idk
PROFILER_HOOK_THIS(COCOS2D + 0xc22a0, void, cocos2d, CCApplication, updateVerticalSync)
PROFILER_HOOK_THIS(COCOS2D + 0xc1d30, void, cocos2d, CCApplication, updateControllerKeys)