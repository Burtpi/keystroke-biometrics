#include <database/containers/key-hit-container.h>
#include <utils/key/validators/utils-key-validators.h>

void database::containers::KeyHitContainer::AddEntry(int hid, int elapsed_time,
                                                     float pressure) {
    bool is_big = utils::key::validators::CheckIfBigChar();
    bool is_special = utils::key::validators::CheckIfSpecialChar(hid);
    entries_.emplace_back(hid, elapsed_time, pressure, is_big, is_special);
}
