#include "cocos2d.h"
#include "AppDelegate.h"
#include "SimpleAudioEngine.h"
#include "script_support/CCScriptSupport.h"
#include "HXModules.h"

#include <iostream>
using namespace std;

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{
    // fixed me
    //CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF);
}

AppDelegate::~AppDelegate()
{
    // end simple audio engine here, or it may crashed on win32
    SimpleAudioEngine::getInstance()->end();
    ScriptEngineManager::destroyInstance();
    hx::HXEngine::destroyInstance();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    auto pDirector = Director::getInstance();
    pDirector->setOpenGLView(EGLView::getInstance());

    EGLView::getInstance()->setDesignResolutionSize(480, 320, ResolutionPolicy::NO_BORDER);

    // turn off display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    if (hx::HXEngine::getInstance()->startLuaEngine()) {
        cout << "HXGame:debug:game OK!" << endl;
    }
    else {
        cout << "HXGmae:debug:game FAILD!" << endl;
    }

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
