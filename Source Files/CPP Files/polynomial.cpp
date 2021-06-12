#include"polynomial.h"

namespace
{
    bool addition_flows(const long double augend_argument, const long double addend_argument)
    {
        if(addend_argument>=0.0l&&augend_argument>std::numeric_limits<const long double>::max()-addend_argument)
        {
            return false;
        }

        else if(addend_argument<0.0l&&augend_argument<std::numeric_limits<const long double>::lowest()-addend_argument)
        {
            return false;
        }

        return true;
    }

    bool addition_flows(const unsigned long long int augend_argument, const unsigned long long int addend_argument)
    {
        if(augend_argument>std::numeric_limits<const unsigned long long int>::max()-addend_argument)
        {
            return false;
        }

        return true;
    }

    bool division_flows(const long double dividend_argument, const long double divisor_argument)
    {
        if(dividend_argument==std::numeric_limits<const long double>::min()&&divisor_argument==-1.0l)
        {
            return false;
        }

        else if(!divisor_argument)
        {
            return false;
        }

        return true;
    }

    bool multiplication_flows(const long double multiplicand_argument, const long double multiplier_argument)
    {
        if(multiplier_argument>=0.0l&&multiplicand_argument>=0.0l&&multiplicand_argument>std::numeric_limits<const long double>::max()/multiplier_argument)
        {
            return false;
        }

        else if(multiplier_argument<0.0l&&multiplicand_argument<0.0l&&multiplicand_argument<std::numeric_limits<const long double>::max()/multiplier_argument)
        {
            return false;
        }

        else if(multiplier_argument>=0.0l&&multiplicand_argument<0.0l&&multiplicand_argument<std::numeric_limits<const long double>::lowest()/multiplier_argument)
        {
            return false;
        }

        else if(multiplier_argument<0.0l&&multiplicand_argument>=0.0l&&multiplicand_argument>std::numeric_limits<const long double>::lowest()/multiplier_argument)
        {
            return false;
        }

        return true;
    }

    bool subtraction_flows(const unsigned long long int minuend_argument, const unsigned long long int subtrahend_argument)
    {
        if(minuend_argument<std::numeric_limits<const unsigned long long int>::min()+subtrahend_argument)
        {
            return false;
        }

        return true;
    }
}

polynomial::term::term():coefficient(), exponent(), next(){}

polynomial::term::term(const long double coefficient_argument, const unsigned long long int exponent_argument, term* const next_argument):coefficient(coefficient_argument), exponent(exponent_argument), next(next_argument){}

polynomial::term::term(const term& term_argument):coefficient(term_argument.coefficient), exponent(term_argument.exponent), next(){}

polynomial::term::term(term&& term_argument):coefficient(std::move(term_argument.coefficient)), exponent(std::move(term_argument.exponent)), next(){}

polynomial::term polynomial::term::operator+() const
{
    return *this;
}

polynomial::term polynomial::term::operator-() const
{
    return term(-coefficient, exponent, nullptr);
}

bool polynomial::term::operator<(const term& term_argument) const
{
    return exponent<term_argument.exponent||(exponent==term_argument.exponent&&coefficient<term_argument.coefficient);
}

bool polynomial::term::operator>(const term& term_argument) const
{
    return term_argument<*this;
}

bool polynomial::term::operator<=(const term& term_argument) const
{
    return !(*this>term_argument);
}

bool polynomial::term::operator>=(const term& term_argument) const
{
    return !(*this<term_argument);
}

bool polynomial::term::operator==(const term& term_argument) const
{
    return !(*this<term_argument||*this>term_argument);
}

bool polynomial::term::operator!=(const term& term_argument) const
{
    return !(*this==term_argument);
}

void polynomial::assign(const polynomial& polynomial_argument)
{
    clear();
    for(const term* assign_term(polynomial_argument.leading_term); assign_term; assign_term=assign_term->next)
    {
        push_term(new term(*assign_term));
    }
}

void polynomial::assign(polynomial&& polynomial_argument)
{
    clear();
    term_amount=std::move(polynomial_argument.term_amount);
    leading_term=std::move(polynomial_argument.leading_term);
    polynomial_argument.term_amount=0ull;
    polynomial_argument.leading_term=nullptr;
}

void polynomial::clear()
{
    term_amount=0ull;
    for(const term* clear_term(leading_term); leading_term; clear_term=leading_term)
    {
        leading_term=leading_term->next;
        delete clear_term;
    }
}

void polynomial::push_term(term* const term_argument)
{
    if(!term_argument)
    {
        return;
    }

    else if(!term_argument->coefficient||term_amount==std::numeric_limits<const unsigned long long int>::max())
    {
        delete term_argument;

        return;
    }

    else if(!leading_term)
    {
        term_amount=1ull;
        leading_term=term_argument;

        return;
    }

    term* previous_traverse_term{};
    for(term* next_traverse_term(leading_term); next_traverse_term; previous_traverse_term=next_traverse_term, next_traverse_term=next_traverse_term->next)
    {
        if(next_traverse_term->exponent<term_argument->exponent)
        {
            ++term_amount;
            (previous_traverse_term?previous_traverse_term->next:leading_term)=term_argument;
            term_argument->next=next_traverse_term;

            return;
        }

        else if(next_traverse_term->exponent==term_argument->exponent)
        {
            if(!addition_flows(next_traverse_term->coefficient, term_argument->coefficient)||!(next_traverse_term->coefficient+term_argument->coefficient))
            {
                --term_amount;
                (previous_traverse_term?previous_traverse_term->next:leading_term)=next_traverse_term->next;
            }

            else
            {
                term* const combined_term(new term(next_traverse_term->coefficient+term_argument->coefficient, next_traverse_term->exponent, next_traverse_term->next));
                (previous_traverse_term?previous_traverse_term->next:leading_term)=combined_term;
            }

            delete term_argument;
            delete next_traverse_term;

            return;
        }
    }

    ++term_amount;
    previous_traverse_term->next=term_argument;
}

polynomial::term* const polynomial::create_term(std::stringstream& stringstream_argument)
{
    char extracted_caret{};
    char extracted_variable{};
    long double extracted_coefficient{};
    unsigned long long int extracted_exponent{};
    const std::string extracted_data(stringstream_argument.str());
    const bool has_caret=extracted_data.find('^')!=std::string::npos;
    const std::string::size_type extracted_variable_index=extracted_data.find('x');
    const bool has_variable=extracted_variable_index!=std::string::npos;
    if(has_caret&&has_variable)
    {
        if(extracted_data.front()=='x')
        {
            extracted_coefficient=1.0l;
            stringstream_argument>>extracted_variable>>extracted_caret>>extracted_exponent;
        }

        else if(extracted_data[extracted_variable_index-1u]=='+')
        {
            extracted_coefficient=1.0l;
            stringstream_argument.ignore();
            stringstream_argument>>extracted_variable>>extracted_caret>>extracted_exponent;
        }

        else if(extracted_data[extracted_variable_index-1u]=='-')
        {
            extracted_coefficient=-1.0l;
            stringstream_argument.ignore();
            stringstream_argument>>extracted_variable>>extracted_caret>>extracted_exponent;
        }

        else
        {
            stringstream_argument>>extracted_coefficient>>extracted_variable>>extracted_caret>>extracted_exponent;
        }
    }

    else if(!has_caret&&has_variable)
    {
        extracted_exponent=1ull;
        if(extracted_data.front()=='x'||extracted_data[extracted_variable_index-1u]=='+')
        {
            extracted_coefficient=1.0l;
        }

        else if(extracted_data[extracted_variable_index-1u]=='-')
        {
            extracted_coefficient=-1.0l;
        }

        else
        {
            stringstream_argument>>extracted_coefficient;
        }
    }

    else if(!has_caret&&!has_variable)
    {
        extracted_exponent=0ull;
        stringstream_argument>>extracted_coefficient;
    }

    if(stringstream_argument)
    {
        return new term(extracted_coefficient, extracted_exponent, nullptr);
    }

    return nullptr;
}

std::istream& operator>>(std::istream& istream_argument, polynomial& polynomial_argument)
{
    char extracted_character{};
    std::stringstream extracted_data_stream;
    polynomial::term* extracted_term{};
    polynomial_argument.clear();
    while(istream_argument)
    {
        istream_argument.get(extracted_character);
        if((istream_argument.eof()||extracted_character=='\n'||extracted_character=='+'||extracted_character=='-')&&extracted_data_stream.rdbuf()->in_avail())
        {
            extracted_term=polynomial_argument.create_term(extracted_data_stream);
            if(!extracted_term)
            {
                istream_argument.setstate(std::ios_base::failbit);
                polynomial_argument.clear();

                return istream_argument;
            }

            polynomial_argument.push_term(extracted_term);
            if(istream_argument.eof()||extracted_character=='\n')
            {
                istream_argument.clear();

                return istream_argument;
            }

            extracted_data_stream.clear();
            extracted_data_stream.str("");
            extracted_data_stream<<extracted_character;
        }

        else if(extracted_character=='+'||extracted_character=='-'||extracted_character=='.'||(extracted_character>='0'&&extracted_character<='9')||extracted_character=='^'||extracted_character=='x')
        {
            extracted_data_stream<<extracted_character;
        }

        else
        {
            istream_argument.setstate(std::ios_base::failbit);
            polynomial_argument.clear();

            return istream_argument;
        }
    }

    istream_argument.setstate(std::ios_base::failbit);
    polynomial_argument.clear();

    return istream_argument;
}

std::ostream& operator<<(std::ostream& ostream_argument, const polynomial& polynomial_argument)
{
    if(!polynomial_argument.leading_term)
    {
        return ostream_argument<<0.0l;
    }

    std::ios_base::fmtflags ostream_flags(ostream_argument.flags());
    for(const polynomial::term* os_term(polynomial_argument.leading_term); os_term; os_term=os_term->next)
    {
        if(os_term!=polynomial_argument.leading_term&&os_term->coefficient>0.0l)
        {
            ostream_argument<<'+';
        }

        ostream_argument<<*os_term;
        if(!ostream_argument)
        {
            ostream_argument.flags(ostream_flags);
            ostream_argument.setstate(std::ios_base::failbit);

            return ostream_argument;
        }
    }

    ostream_argument.flags(ostream_flags);

    return ostream_argument;
}

std::ostream& operator<<(std::ostream& ostream_argument, const polynomial::term& term_argument)
{
    if(!term_argument.coefficient)
    {
        ostream_argument.setstate(std::ios_base::failbit);

        return ostream_argument;
    }

    else if(!term_argument.exponent)
    {
        return ostream_argument<<std::fixed<<term_argument.coefficient;
    }

    else if(term_argument.exponent==1ull)
    {
        if(term_argument.coefficient==1.0l)
        {
            return ostream_argument<<'x';
        }

        else if(term_argument.coefficient==-1.0l)
        {
            return ostream_argument<<"-x";
        }

        else
        {
            return ostream_argument<<std::fixed<<term_argument.coefficient<<'x';
        }
    }

    else
    {
        if(term_argument.coefficient==1.0l)
        {
            return ostream_argument<<"x^"<<term_argument.exponent;
        }

        else if(term_argument.coefficient==-1.0l)
        {
            return ostream_argument<<"-x^"<<term_argument.exponent;
        }

        else
        {
            return ostream_argument<<std::fixed<<term_argument.coefficient<<"x^"<<term_argument.exponent;
        }
    }

    ostream_argument.setstate(std::ios_base::failbit);

    return ostream_argument;
}

polynomial operator*(const long double constant_argument, const polynomial& polynomial_argument)
{
    return polynomial(constant_argument)*polynomial_argument;
}

polynomial::polynomial():term_amount(), leading_term(){}

polynomial::polynomial(const long double constant_argument):term_amount(constant_argument?1ull:0ull), leading_term(constant_argument?new term(constant_argument, 0ull, nullptr):nullptr){}

polynomial::polynomial(const std::initializer_list<const std::pair<const long double, const unsigned long long int>>& term_list_argument):term_amount(), leading_term()
{
    for(const std::pair<const long double, const unsigned long long int>& term_pair:term_list_argument)
    {
        push_term(new term(term_pair.first, term_pair.second, nullptr));
    }
}

polynomial::polynomial(const polynomial& polynomial_argument):term_amount(), leading_term()
{
    assign(polynomial_argument);
}

polynomial::polynomial(polynomial&& polynomial_argument):term_amount(), leading_term()
{
    assign(std::move(polynomial_argument));
}

polynomial::~polynomial()
{
    clear();
}

long double polynomial::operator()(const long double input_argument) const
{
    if(!leading_term)
    {
        return 0.0l;
    }

    long double remainder{};
    unsigned long long int degree(leading_term->exponent);
    term* evaluate_term(leading_term);
    while(true)
    {
        if(evaluate_term==leading_term)
        {
            remainder=evaluate_term->coefficient;
            evaluate_term=evaluate_term->next;
        }

        else if(evaluate_term&&degree==evaluate_term->exponent)
        {
            remainder=evaluate_term->coefficient+input_argument*remainder;
            evaluate_term=evaluate_term->next;
        }

        else
        {
            remainder=input_argument*remainder;
        }

        if(!degree)
        {
            break;
        }

        --degree;
    }

    return remainder;
}

polynomial polynomial::operator+() const
{
    return *this;
}

polynomial polynomial::operator-() const
{
    polynomial unary_minus_polynomial;
    for(const term* unary_minus_term(leading_term); unary_minus_term; unary_minus_term=unary_minus_term->next)
    {
        unary_minus_polynomial.push_term(new term(-*unary_minus_term));
    }

    return unary_minus_polynomial;
}

polynomial polynomial::operator*(const long double constant_argument) const
{
    return *this*polynomial(constant_argument);
}

polynomial polynomial::operator*(const polynomial& polynomial_argument) const
{
    polynomial product_polynomial;
    if(!leading_term||!polynomial_argument.leading_term)
    {
        return product_polynomial;
    }

    for(const term* multiplicand_term(leading_term); multiplicand_term; multiplicand_term=multiplicand_term->next)
    {
        for(const term* multiplier_term(polynomial_argument.leading_term); multiplier_term; multiplier_term=multiplier_term->next)
        {
            if(!multiplication_flows(multiplicand_term->coefficient, multiplier_term->coefficient)||!addition_flows(multiplicand_term->exponent, multiplier_term->exponent))
            {
                product_polynomial.clear();

                return product_polynomial;
            }

            product_polynomial.push_term(new term(multiplicand_term->coefficient*multiplier_term->coefficient, multiplicand_term->exponent+multiplier_term->exponent, nullptr));
        }
    }

    return product_polynomial;
}

polynomial polynomial::operator/(const long double constant_argument) const
{
    return *this/polynomial(constant_argument);
}

polynomial polynomial::operator/(const polynomial& polynomial_argument) const
{
    polynomial quotient_polynomial;
    if(!leading_term||!polynomial_argument.leading_term)
    {
        return quotient_polynomial;
    }

    polynomial dividend_polynomial(*this);
    polynomial leading_quotient_polynomial;
    while(dividend_polynomial.leading_term&&dividend_polynomial.leading_term->exponent>=polynomial_argument.leading_term->exponent)
    {
        if(!division_flows(dividend_polynomial.leading_term->coefficient, polynomial_argument.leading_term->coefficient)||!subtraction_flows(dividend_polynomial.leading_term->exponent, polynomial_argument.leading_term->exponent))
        {
            quotient_polynomial.clear();

            return quotient_polynomial;
        }

        leading_quotient_polynomial.push_term(new term(dividend_polynomial.leading_term->coefficient/polynomial_argument.leading_term->coefficient, dividend_polynomial.leading_term->exponent-polynomial_argument.leading_term->exponent, nullptr));
        quotient_polynomial.push_term(new term(dividend_polynomial.leading_term->coefficient/polynomial_argument.leading_term->coefficient, dividend_polynomial.leading_term->exponent-polynomial_argument.leading_term->exponent, nullptr));
        dividend_polynomial-=leading_quotient_polynomial*polynomial_argument;
        leading_quotient_polynomial.clear();
    }

    return quotient_polynomial;
}

polynomial polynomial::operator%(const long double constant_argument) const
{
    return *this%polynomial(constant_argument);
}

polynomial polynomial::operator%(const polynomial& polynomial_argument) const
{
    const polynomial quotient_polynomial(*this/polynomial_argument);
    polynomial modulus_polynomial(*this-polynomial_argument*quotient_polynomial);

    return modulus_polynomial;
}

polynomial polynomial::operator+(const long double constant_argument) const
{
    return *this+polynomial(constant_argument);
}

polynomial polynomial::operator+(const polynomial& polynomial_argument) const
{
    polynomial sum_polynomial(*this);
    for(const term* addend_term(polynomial_argument.leading_term); addend_term; addend_term=addend_term->next)
    {
        sum_polynomial.push_term(new term(*addend_term));
    }

    return sum_polynomial;
}

polynomial polynomial::operator-(const long double constant_argument) const
{
    return *this+-constant_argument;
}

polynomial polynomial::operator-(const polynomial& polynomial_argument) const
{
    return *this+-polynomial_argument;
}

bool polynomial::operator<(const polynomial& polynomial_argument) const
{
    for(const term* this_term(leading_term), *argument_term(polynomial_argument.leading_term); this_term&&argument_term; this_term=this_term->next, argument_term=argument_term->next)
    {
        if(*this_term<*argument_term)
        {
            return true;
        }

        else if(*this_term>*argument_term)
        {
            return false;
        }
    }

    if(term_amount<polynomial_argument.term_amount)
    {
        return true;
    }

    return false;
}

bool polynomial::operator>(const polynomial& polynomial_argument) const
{
    return polynomial_argument<*this;
}

bool polynomial::operator<=(const polynomial& polynomial_argument) const
{
    return !(*this>polynomial_argument);
}

bool polynomial::operator>=(const polynomial& polynomial_argument) const
{
    return !(*this<polynomial_argument);
}

bool polynomial::operator==(const polynomial& polynomial_argument) const
{
    return !(*this<polynomial_argument||*this>polynomial_argument);
}

bool polynomial::operator!=(const polynomial& polynomial_argument) const
{
    return !(*this==polynomial_argument);
}

polynomial& polynomial::operator=(const polynomial& polynomial_argument)
{
    const polynomial copy_polynomial_argument(polynomial_argument);
    assign(copy_polynomial_argument);

    return *this;
}

polynomial& polynomial::operator=(polynomial&& polynomial_argument)
{
    polynomial copy_polynomial_argument(std::move(polynomial_argument));
    assign(std::move(copy_polynomial_argument));

    return *this;
}

polynomial& polynomial::operator*=(const long double constant_argument)
{
    return *this=*this*constant_argument;
}

polynomial& polynomial::operator*=(const polynomial& polynomial_argument)
{
    return *this=*this*polynomial_argument;
}

polynomial& polynomial::operator/=(const long double constant_argument)
{
    return *this=*this/constant_argument;
}

polynomial& polynomial::operator/=(const polynomial& polynomial_argument)
{
    return *this=*this/polynomial_argument;
}

polynomial& polynomial::operator%=(const long double constant_argument)
{
    return *this=*this%constant_argument;
}

polynomial& polynomial::operator%=(const polynomial& polynomial_argument)
{
    return *this=*this%polynomial_argument;
}

polynomial& polynomial::operator+=(const long double constant_argument)
{
    return *this=*this+constant_argument;
}

polynomial& polynomial::operator+=(const polynomial& polynomial_argument)
{
    return *this=*this+polynomial_argument;
}

polynomial& polynomial::operator-=(const long double constant_argument)
{
    return *this=*this-constant_argument;
}

polynomial& polynomial::operator-=(const polynomial& polynomial_argument)
{
    return *this=*this-polynomial_argument;
}

unsigned long long int polynomial::term_count() const
{
    return term_amount;
}

std::optional<const unsigned long long int> polynomial::degree() const
{
    if(!leading_term)
    {
        return std::nullopt;
    }

    return leading_term->exponent;
}

polynomial nth_root(const polynomial& polynomial_argument, const unsigned long long int index_argument)
{
    polynomial root_polynomial;
    if(!index_argument)
    {
        return root_polynomial;
    }

    else if(index_argument==1ull||!polynomial_argument.leading_term||polynomial_argument==polynomial(1.0l))
    {
        return polynomial_argument;
    }

    long double divide_factor{};
    std::stack<const polynomial::term*> term_stack;
    polynomial dividend_polynomial;
    polynomial divisor_polynomial;
    polynomial quotient_polynomial;
    polynomial radicand_polynomial(polynomial_argument);
    polynomial subtrahend_polynomial;

    subtrahend_polynomial.push_term(new polynomial::term(*radicand_polynomial.leading_term));
    root_polynomial.push_term(new polynomial::term(std::pow(radicand_polynomial.leading_term->coefficient, 1.0l/index_argument), radicand_polynomial.leading_term->exponent/index_argument, nullptr));
    radicand_polynomial-=subtrahend_polynomial;
    while(radicand_polynomial.leading_term&&radicand_polynomial.leading_term->exponent>=root_polynomial.leading_term->exponent)
    {
        dividend_polynomial.push_term(new polynomial::term(*radicand_polynomial.leading_term));
        divisor_polynomial.push_term(new polynomial::term(*root_polynomial.leading_term));
        divisor_polynomial=exponent(divisor_polynomial, index_argument-1ull);
        divisor_polynomial*=index_argument;
        quotient_polynomial=dividend_polynomial/divisor_polynomial;
        if(!quotient_polynomial.leading_term)
        {
            root_polynomial.clear();

            return root_polynomial;
        }

        root_polynomial.push_term(new polynomial::term(*quotient_polynomial.leading_term));
        divisor_polynomial=root_polynomial;
        divisor_polynomial=exponent(divisor_polynomial, index_argument-1ull);
        divisor_polynomial*=index_argument;
        divisor_polynomial*=quotient_polynomial;
        for(const polynomial::term* divisor_term(divisor_polynomial.leading_term); divisor_term; divisor_term=divisor_term->next)
        {
            term_stack.push(divisor_term);
        }

        divide_factor=index_argument;
        subtrahend_polynomial.clear();
        while(!term_stack.empty())
        {
            subtrahend_polynomial.push_term(new polynomial::term(divide_factor?term_stack.top()->coefficient/divide_factor:term_stack.top()->coefficient, term_stack.top()->exponent, nullptr));
            term_stack.pop();
            if(divide_factor)
            {
                --divide_factor;
            }
        }

        dividend_polynomial.clear();
        divisor_polynomial.clear();
        radicand_polynomial-=subtrahend_polynomial;
    }

    return root_polynomial;
}

polynomial exponent(const polynomial& polynomial_argument, const unsigned long long int exponent_argument)
{
    polynomial exponent_polynomial(1.0l);
    if(!exponent_argument)
    {
        return exponent_polynomial;
    }

    else if(exponent_argument==1ull)
    {
        return polynomial_argument;
    }

    polynomial multiplier_polynomial(polynomial_argument);
    for(unsigned long long int copy_exponent_argument(exponent_argument); copy_exponent_argument; copy_exponent_argument>>=1ull)
    {
        if(copy_exponent_argument&1ull)
        {
            exponent_polynomial*=multiplier_polynomial;
        }

        multiplier_polynomial*=multiplier_polynomial;
    }

    return exponent_polynomial;
}
