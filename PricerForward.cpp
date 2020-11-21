#include "PricerForward.h"

#include <cmath>

#include "Global.h"
#include "Macros.h"

namespace minirisk {

PricerForward::PricerForward(
    const TradeFXForward& trd, const std::string& base_ccy)
    : m_amt(trd.quantity()),
      m_strike(trd.strike()),
      m_ccy1(trd.ccy1()),
      m_ccy2(trd.ccy2()),
      m_fixing_date(trd.fixing_date()),
      m_settle_date(trd.settle_date()),
      m_base_ccy(base_ccy) {}

double PricerForward::price(Market& m, const FixingDataServer* fds) const {
  ptr_disc_curve_t df = m.get_discount_curve(ir_curve_discount_name(m_ccy2));
  double disc_factor = df->df(m_settle_date);

  double forward_rate = nan<double>();
  if (fds && m.today() >= m_fixing_date) {
    const auto& fixing_name = fx_spot_name(m_ccy1, m_ccy2);
    if (m.today() > m_fixing_date) {
      // Must contain fixing, otherwise price failure.
      forward_rate = fds->get(fixing_name, m_fixing_date);
    } else {
      // Might contain fixing.
      const auto& res = fds->lookup(fixing_name, m_fixing_date);
      if (res.second) 
        forward_rate = res.first; 
    }
  }
  if (std::isnan(forward_rate)) {
    // Try to resolve price from forward curve.
    ptr_fx_forward_curve_t forward = m.get_fx_forward_curve(fx_forward_name(m_ccy1, m_ccy2));
    forward_rate = forward->forward(m_fixing_date);
  }
  MYASSERT(!std::isnan(forward_rate), "FX forward or fixing not available " 
      << m_ccy1 << m_ccy2 << " for " << m_fixing_date.to_string());
  MYASSERT(!std::isnan(disc_factor), "Disc factor not available " 
      << m_ccy1 << m_ccy2 << " for " << m_settle_date.to_string());
  double fx_spot = 
    m.get_fx_spot(fx_spot_name(m_ccy2, m_base_ccy));
  return m_amt * disc_factor * (forward_rate - m_strike) * fx_spot;
}

} // namespace minirisk
