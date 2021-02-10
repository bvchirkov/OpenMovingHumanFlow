#include "EEsystemAppTask.hpp"

#include <iomanip>

#include "../EsBimCore/JsonView/BimRoot.hpp"
#include "../EsBimCore/JsonView/BimLevels.hpp"
#include "../EsBimCore/JsonView/BimElementSign.hpp"
#include "../EsBimCore/JsonView/BimBaseElement.hpp"

#include "./utils/EsTimer.hpp"
#include "./utils/EsCfgLoader.hpp"

GpQueueLF<EsBlockingMonitor::SP>    EEsystemAppTask::sMessageQueue;
std::time_t                         EEsystemAppTask::sUnixTime      = std::time(nullptr);

EEsystemAppTask::EEsystemAppTask() = default;
EEsystemAppTask::~EEsystemAppTask() = default;

// TODO Добавить путь к конфигу и номер сценария в аргументы запуска программы
// возможность указать несколько сценариев, диапазон
void EEsystemAppTask::ExecuteCoroTask(void)
{
    EsTimer t;

    try {
        const EsCfgRoot::SP&        esCfg       = EsCfgLoader::SLoad("/home/boris/workspace/cpp/rintd/rintd/resources/escfg_b1.json"_sv);

        for (const EsCfgScenarios::SP&   esScenario : esCfg.VCn().getScenarios())
        {
            EsBimTools::SP   btOrigin = EsBimTools::SP::SNew(esScenario);
            //EsBimBinding::SP bimOrigin = btOrigin.Vn().getBim();

            // Preprocessing
            EsBimTools::SP bt = btOrigin.Clone();
            EsBimBinding::SP bim = bt.Vn().getBim();

            EsCfgBlocking::SP _blockElements = esScenario.VCn().getBlockingElements();
            EsCfgBlockingElements::SP blockElements = _blockElements.Vn().getBlockingElements().at(0);
            EsBlockingMonitor::SP blockMonitor = EsBlockingMonitor::SP::SNew(blockElements.Vn().getUuid(), blockElements.Vn().getTime());
            EEsystemAppTask::sMessageQueue.Push(blockMonitor);

            Safety::SP safetyZone = bim.Vn().getSafetyElement();
            bim.Vn().setWidthDoorWay(0.85);
            bim.Vn().setWidthDoorWayOut(0.85);
            bim.Vn().updateWidthDoors();

            const double complexity = bt.Vn().getComplexity();
            const BaseElement::SP& item = bt.Vn().getMaxDistance().first;
            const GpUUID& uuidDoor = bt.Vn().getMaxDistance().second;
            const double maxDistance = item.VCn().getDistanceToExit(uuidDoor);
            const double nop = bim.Vn().getNumOfPeople();

            log_info("EEsystemAppTask"_sv, "JSON file: "_sv + bt.Vn().getPathToBim());
            log_info("EEsystemAppTask"_sv, "Сценарий No: "_sv + esScenario.VCn().getScenarioNo());
            log_info("EEsystemAppTask"_sv, "Количество этажей: "_sv + bim.Vn().getSizeLevels().size());
            log_info("EEsystemAppTask"_sv, "Максимальный путь, м: "_sv + maxDistance + " ("_sv + item.VCn().getName() + " :: "_sv + uuidDoor.ToString() + ")"_sv);
            log_info("EEsystemAppTask"_sv, "Сложность здания: "_sv + complexity);
            log_info("EEsystemAppTask"_sv, "Количество выходов из здания: "_sv + bim.Vn().getDoorsOut().size());
            log_info("EEsystemAppTask"_sv, "Количество помещений: "_sv + bim.Vn().getRooms().size());
            log_info("EEsystemAppTask"_sv, "Количество лестничных шахт: "_sv + bim.Vn().getStairs().size()/bim.Vn().getSizeLevels().size());
            log_info("EEsystemAppTask"_sv, "Количество людей в здании, чел.: "_sv + nop);
            log_info("EEsystemAppTask"_sv, "Плотность распределения людей, чел/м^2: "_sv + nop / bim.Vn().getArea());

            const double sno = esScenario.VCn().getScenarioNo();
            const std::string_view coreReportsDirName = esScenario.VCn().getResultsFolder();
            const std::string suffix = GpStringUtils::DoubleToStr(EEsystemAppTask::sUnixTime).substr(0, 10);
            const std::string reportDir = coreReportsDirName + "_"_sv + suffix;
            std::filesystem::create_directories(reportDir);

            const std::string reportMovingFile = reportDir + "/"_sv + sno + "_in_detail_timing.csv"_sv;

            //std::cout << std::fixed << std::setprecision(5);
            std::ofstream movingFile(reportMovingFile);
            EsOutputRoot::SP esOutputRoot = EsOutputRoot::SP::SNew();
            // Processing
            double timeOfEvac = bt.Vn().runMoving(safetyZone, movingFile, esOutputRoot);

            // Postprocessing
            GpJsonReflectionCfg cfg;
            cfg.SetIsWriteSerialIDs(false);
            cfg.SetIsWriteEmptyValues(true);
            GpJsonIO::SReflectableToFile(esOutputRoot.Vn(), reportDir + "/"_sv + sno + "_in_detail_moving"_sv + ".json"_sv, GpFile::IfExists::OVERRIDE, cfg);

            const std::string reportTimeFile = reportDir + "/"_sv + "s"_sv + sno + "_t"_sv + GpStringUtils::DoubleToStr(std::round(timeOfEvac));
            std::ofstream ostrm(reportTimeFile);
            std::cout << "[EEsystemAppTask::ExecuteCoroTask]: Path to report " << reportDir << std::endl;

            std::cout << "[EEsystemAppTask::ExecuteCoroTask]: ===================== \n" << std::endl;
        }
        GpApp::S().StopAndExit(0);
    } catch(...)
    {
        GpApp::S().StopAndExit(-1);
        throw;
    }

    log_info("EEsystemAppTask", "Время расчета: "_sv + t.elapsed());
}

void EEsystemAppTask::OnTaskEnd() noexcept
{
    std::cout << "[EEsystemAppTask::OnTaskEnd]:..." << std::endl;
    GpTaskCoroutine::OnTaskEnd();
}
