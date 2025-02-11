// app_manager.cpp
#include "app_manager.h"

std::vector<AppInitFunc>& AppManager::getAppList() {
    static std::vector<AppInitFunc> appList;
    return appList;
}

void AppManager::registerApp(AppInitFunc func) {
    getAppList().push_back(func);
}

void AppManager::initializeApps() {
    for (auto func : getAppList()) {
        func();  // Call each registered app function
    }
}
