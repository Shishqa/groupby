#pragma once

#include <cstddef>

namespace groupby {

struct Settings {
 public:
  static const Settings& Instance();

  /* ~ 1 KB */
  static constexpr size_t RECORD_SIZE{1'000};

  /* ~ 1.0 MB */
  static constexpr size_t RECORDS_IN_BLOCK{1'000};

  /* ~ 1.0 GB */
  static constexpr size_t BLOCKS_IN_MEMORY{1'000};

  /* => max = 1 TB */

 private:
  explicit Settings() = default;
};

}  // namespace groupby
