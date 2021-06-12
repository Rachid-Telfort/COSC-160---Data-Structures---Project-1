#ifndef POLYNOMIAL_H_INCLUDED
#define POLYNOMIAL_H_INCLUDED

#include<cmath>
#include<initializer_list>
#include<ios>
#include<iostream>
#include<limits>
#include<optional>
#include<sstream>
#include<stack>
#include<string>
#include<utility>

class polynomial
{
    struct term
    {
        const long double coefficient;
        const unsigned long long int exponent;
        term* next;

        term();
        term(const long double, const unsigned long long int, term* const);
        term(const term&);
        term(term&&);

        term operator+() const;
        term operator-() const;
        bool operator<(const term&) const;
        bool operator>(const term&) const;
        bool operator<=(const term&) const;
        bool operator>=(const term&) const;
        bool operator==(const term&) const;
        bool operator!=(const term&) const;
    };

    unsigned long long int term_amount;
    term* leading_term;

    void assign(const polynomial&);
    void assign(polynomial&&);
    void clear();
    void push_term(term* const);
    term* const create_term(std::stringstream&);

    friend std::istream& operator>>(std::istream&, polynomial&);
    friend std::ostream& operator<<(std::ostream&, const polynomial&);
    friend std::ostream& operator<<(std::ostream&, const term&);
    friend polynomial operator*(const long double, const polynomial&);

    public:
        polynomial();
        polynomial(const long double);
        polynomial(const std::initializer_list<const std::pair<const long double, const unsigned long long int>>&);
        polynomial(const polynomial&);
        polynomial(polynomial&&);
        ~polynomial();

        long double operator()(const long double) const;
        polynomial operator+() const;
        polynomial operator-() const;
        polynomial operator*(const long double) const;
        polynomial operator*(const polynomial&) const;
        polynomial operator/(const long double) const;
        polynomial operator/(const polynomial&) const;
        polynomial operator%(const long double) const;
        polynomial operator%(const polynomial&) const;
        polynomial operator+(const long double) const;
        polynomial operator+(const polynomial&) const;
        polynomial operator-(const long double) const;
        polynomial operator-(const polynomial&) const;
        bool operator<(const polynomial&) const;
        bool operator>(const polynomial&) const;
        bool operator<=(const polynomial&) const;
        bool operator>=(const polynomial&) const;
        bool operator==(const polynomial&) const;
        bool operator!=(const polynomial&) const;
        polynomial& operator=(const polynomial&);
        polynomial& operator=(polynomial&&);
        polynomial& operator*=(const long double);
        polynomial& operator*=(const polynomial&);
        polynomial& operator/=(const long double);
        polynomial& operator/=(const polynomial&);
        polynomial& operator%=(const long double);
        polynomial& operator%=(const polynomial&);
        polynomial& operator+=(const long double);
        polynomial& operator+=(const polynomial&);
        polynomial& operator-=(const long double);
        polynomial& operator-=(const polynomial&);

        unsigned long long int term_count() const;
        std::optional<const unsigned long long int> degree() const;

        friend polynomial nth_root(const polynomial&, const unsigned long long int);
};

polynomial exponent(const polynomial&, const unsigned long long int);

#endif
