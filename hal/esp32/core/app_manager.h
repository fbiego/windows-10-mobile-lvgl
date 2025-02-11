

// app_manager.h
#pragma once
#include <vector>

typedef void (*AppInitFunc)();

class AppManager {
public:
    static void registerApp(AppInitFunc func);
    static void initializeApps();
    
private:
    static std::vector<AppInitFunc>& getAppList();
};