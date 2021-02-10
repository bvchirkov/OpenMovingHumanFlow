#include "EEsystemApp.hpp"

EEsystemApp::EEsystemApp(const int aArgc,
                         const char **aArgv,
                         const EEsystemAppConfig& aConfig) :
        GpApp(aArgc,
              aArgv,
              aConfig)
{
}

EEsystemApp::~EEsystemApp(void) {
}

GpTask::SP EEsystemApp::OnAppStart(void) {
    std::cout << "[EEsystemApp::OnAppStart]:..." << std::endl;
    return EEsystemAppTask::SP::SNew();
}

void EEsystemApp::OnAppError(std::string_view aMessage) noexcept {
    std::cout << "[EEsystemApp::OnAppError]: " << aMessage << std::endl;
}

void EEsystemApp::OnAppClose(void) noexcept {
    std::cout << "[EEsystemApp::OnAppClose]:... " << std::endl;
}
