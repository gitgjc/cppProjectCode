#pragma once

#include "IPricer.h"
#include "TradeFXForward.h"

namespace minirisk {

struct PricerForward : IPricer {
  PricerForward(const TradeFXForward& trd, const std::string& base_currency);
  virtual double price(Market& m, const FixingDataServer* fds) const;
 private:
  double m_amt;
  double m_strike;
  std::string m_currency1;
  std::string m_currency2;
  Date m_fixing_date;
  Date m_settle_date;
  std::string m_base_currency;
};

} // namespace minirisk
