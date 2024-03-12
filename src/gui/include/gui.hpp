#ifndef GUI_HPP_HEADER
#define GUI_HPP_HEADER

#include <memory>
#include <functional>
#include <string>

enum GuiModuleType{
    QT5,
    QT6,
    GTK
};

/// <summary>
/// Separate Module that connects between logical component and gui component
/// </summary>
struct GuiLogicStruct{
    public:
        std::function<std::string()> load_highscore;
};

class GuiModule{
    public:
        int argc;
        char** argv;
        GuiLogicStruct logic_interface;

        GuiModule(int argc, char* argv[], GuiLogicStruct logic_interface){
            this->argc = argc;
            this->argv = argv;
            this->logic_interface = logic_interface;
        };
        virtual int start_gui() = 0;
        virtual void switch_to_menu_screen() = 0;
        virtual void switch_to_test_screen() = 0;
        virtual void stop_gui() = 0;
};

class QtGuiModule : public GuiModule{
    public:
        QtGuiModule(int argc, char* argv[], GuiLogicStruct logic_interface): GuiModule(argc, argv, logic_interface){};
        int start_gui() override;
        void switch_to_menu_screen() override;
        void switch_to_test_screen() override;
        void stop_gui() override;
};

class GuiModuleFactory{
    public:
        static std::unique_ptr<GuiModule> createModule(GuiModuleType module, int argc, char* argv[], GuiLogicStruct logic_interface);
};

#endif