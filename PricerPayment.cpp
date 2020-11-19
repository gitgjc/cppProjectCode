#include "PricerPayment.h"
#include "TradePayment.h"
#include "CurveDiscount.h"

namespace minirisk {

PricerPayment::PricerPayment(
    const TradePayment& trd, const std::string& base_currency)
    : m_amt(trd.quantity())
    , m_dt(trd.delivery_date())
    , m_ir_curve(ir_curve_discount_name(trd.currency()))
    , m_fx_currency(fx_spot_name(trd.currency(), base_currency)) {}

double PricerPayment::price(Market& mkt, const FixingDataServer* fds) const {
  ptr_disc_curve_t disc = mkt.get_discount_curve(m_ir_curve);
  double df = disc->df(m_dt); // this throws an exception if m_dt<today

  const auto fx_spot = mkt.get_fx_spot(m_fx_currency); 

  return m_amt * df * fx_spot;
}

} // namespace minirisk


