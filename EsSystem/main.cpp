#include "EEsystemAppConfig.hpp"
#include "EEsystemApp.hpp"
#include "utils/EsCfgLoader.hpp"
#include "utils/EsArgs.hpp"

int main (int aArgc, const char** aArgv)
{
    std::cout << "[Main::main]: " << "Try to load config..." << std::endl;
    EEsystemAppConfig::SP config = EEsystemAppConfig::SP::SNew();
    GpJsonReflectionCfg cfg;
    GpJsonIO::SFileToReflectable("/home/boris/workspace/cpp/rintd/rintd/resources/config.json"_sv,
                                 config.V(),
                                 cfg);

    EEsystemApp app(aArgc, aArgv, config.VC());

    return app.Run();
}
