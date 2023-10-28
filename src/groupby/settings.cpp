#include "settings.hpp"

namespace groupby {

const Settings& Settings::Instance() {
  static Settings instance;
  return instance;
}

}  // namespace groupby
