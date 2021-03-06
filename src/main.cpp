#include "main.hpp"
#include "GlobalNamespace/MainMenuViewController.hpp"
#include "UnityEngine/UI/Button.hpp"
#include "UnityEngine/GameObject.hpp"
#include "HMUI/CurvedTextMeshPro.hpp"
#include "questui/shared/BeatSaberUI.hpp"
#include "questui/shared/QuestUI.hpp"

#include "ModConfig.hpp"

DEFINE_CONFIG(ModConfig);

static ModInfo modInfo; // Mod Data

// General format: MAKE_HOOK_MATCH(HookName, method, method return type, method class pointer, arguments...) { 
//  HookName(arguments...);
//  // your code here 
//}

// Loads the config file
Configuration& getConfig() {
    static Configuration config(modInfo);
    config.Load();
    return config;
}

MAKE_HOOK_MATCH(mainMenuHook, &GlobalNamespace::MainMenuViewController::DidActivate, void, GlobalNamespace::MainMenuViewController *self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling){
    mainMenuHook(self,firstActivation,addedToHierarchy,screenSystemEnabling);

    UnityEngine::UI::Button *soloMenuButton = self->dyn__soloButton();
    UnityEngine::GameObject *gameObject = soloMenuButton->get_gameObject();
    HMUI::CurvedTextMeshPro *soloMenuText = gameObject->GetComponentInChildren<HMUI::CurvedTextMeshPro *>();

    soloMenuText->SetText("Skill Issue");
}

// Returns a logger
Logger& getLogger() {
    static Logger* logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo& info) {
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;
	
    getConfig().Load(); // Load the config file
    getLogger().info("Completed setup!");
}

// Called later on in the game loading
extern "C" void load() {
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);

    getLogger().info("Installing hooks...");
    
    INSTALL_HOOK(getLogger(), mainMenuHook);

    getLogger().info("Installed all hooks!");
}

void DidActivate(HMUI::ViewController* self, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling) {
    // Create our UI elements only when shown for the first time.
    if(firstActivation) {
        // Create a container that has a scroll bar.
        UnityEngine::GameObject* container = QuestUI::BeatSaberUI::CreateScrollableSettingsContainer(self->get_transform());

        // Create a text that says "Hello World!" and set the parent to the container.
        QuestUI::BeatSaberUI::CreateText(container->get_transform(), "Hello World!");
    }
}