#pragma once

#include <cstddef>
#include <string>
#include <numeric>

using std::string;
using std::size_t;

namespace minirisk {

extern const string ir_rate_prefix;
extern const string ir_curve_discount_prefix;
extern const string fx_spot_prefix;
extern const string fx_fwd_prefix;

inline string ir_curve_discount_name(const string& currency) {
  return ir_curve_discount_prefix + currency;
}

inline string fx_spot_name(const string& currency1, const string& currency2) {
  return fx_spot_prefix + currency1 + "." + currency2;
}

inline string fx_fwd_name(const string& currency1, const string& currency2) {
  return fx_fwd_prefix + currency1 + "." + currency2;
}

template<class T>
T nan() {
  return std::numeric_limits<T>::quiet_NaN();
}

string format_label(const string& s);

} // namespace minirisk
