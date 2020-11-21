#include "TradeFXForward.h"
#include "PricerForward.h"

namespace minirisk
{

  ppricer_t TradeFXForward::pricer(const std::string& base_currency) const
  {
    return ppricer_t(new PricerForward(*this, base_currency));
  }

} // namespace minirisk
