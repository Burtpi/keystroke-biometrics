#ifndef KEY_HIT_CONTAINER_H_
#define KEY_HIT_CONTAINER_H_

#include <config/config-manager.h>
#include <database/containers/container.h>
#include <database/models/key-hit.h>

#include <vector>

namespace database::containers {
class KeyHitContainer : public Container<database::models::KeyHit> {
    // -----------------------------------------------------------
    // Inherits from container.h
    // Container for KeyHits
    //
    // Changes:
    //  - AddEntry logic modified
    //  - AddModifierEntry for adding objects to ModifierKeyHitContainer
    //  - SaveToFile and LoadFromFile used for reuse of calculated data
    //  - GenerateCalcKeyHitHashMap and FindEntry for easier lookup
    // -----------------------------------------------------------
   public:
    void AddEntry(int hid, int elapsed_time, float pressure);
    void AddModifierEntry(int hid, int elapsed_time, float pressure);
    void SaveToFile();
    void LoadFromFile(
        std::string base_path =
            global_config_manager.GetAppConfig().GetExternalDataKeyHitsPath());
};
}  // namespace database::containers

#endif