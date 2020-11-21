#pragma once

#include "Trade.h"

namespace minirisk 
{

    struct TradePayment : Trade<TradePayment>
    {
        friend struct Trade<TradePayment>;

        static const guid_t m_id;
        static const std::string m_name;

        TradePayment() {}

        void init(const std::string& currency, double quantity, const Date& delivery_date)
        {
            Trade::init(quantity);
            m_currency = currency;
            m_delivery_date = delivery_date;
        }

        virtual ppricer_t pricer(const std::string& base_currency) const;

        const string& currency() const
        {
            return m_currency;
        }

        const Date& delivery_date() const
        {
            return m_delivery_date;
        }

    private:
        void save_details(my_ofstream& os) const
        {
            os << m_currency << m_delivery_date;
        }

        void load_details(my_ifstream& is)
        {
            is >> m_currency >> m_delivery_date;
        }

        void print_details(std::ostream& os) const
        {
            os << format_label("Currency") << m_currency << std::endl;
            os << format_label("Delivery Date") << m_delivery_date << std::endl;
        }

    private:
        string m_currency;
        Date m_delivery_date;
    };

} // namespace minirisk
