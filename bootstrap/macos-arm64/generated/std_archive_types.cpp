#include "std_archive_types.hpp"

namespace std_::archive::types {




std::shared_ptr<std::vector<uint8_t>> TarArchive::entryData(const std::shared_ptr<TarEntry>& entry) {
    return doof::array_slice(this->data, static_cast<int32_t>(entry->contentOffset), static_cast<int32_t>((entry->contentOffset + entry->size)), "", 0);
}

}
