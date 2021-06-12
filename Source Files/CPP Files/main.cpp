#include<cstdlib>
#include<ios>
#include<iostream>
#include<sstream>
#include<string>
#include<utility>
#include<vector>
#include"polynomial.h"

void add_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be added.\n\n";

        return;
    }

    std::cout<<"The polynomials that are available to be added are:\n\n";
    for(unsigned long long int polynomial_index{}; polynomial_index<polynomials.size(); ++polynomial_index)
    {
        std::cout<<polynomial_index<<". "<<polynomials[polynomial_index]<<'\n';
    }

    std::cout<<'\n';

    unsigned long long int polynomial_options_index{};
    std::string polynomial_options_string;
    std::istringstream polynomial_options_stream;
    std::vector<unsigned long long int> polynomial_option_indices;
    polynomial sum_polynomial;

    std::cout<<"Select which polynomials that are to be added by typing the corresponding numbers separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomial_options_string);
    std::cout<<'\n';

    std::cout<<"The selected polynomials will now be added:\n\n";
    polynomial_options_stream.str(polynomial_options_string);
    while(polynomial_options_stream>>polynomial_options_index)
    {
        polynomial_option_indices.push_back(polynomial_options_index);
    }

    for(unsigned long long int polynomial_options_index:polynomial_option_indices)
    {
        if(polynomial_options_index>=polynomials.size())
        {
            continue;
        }

        sum_polynomial+=polynomials[polynomial_options_index];
    }

    std::cout<<"The sum of the selected polynomials are:\n\n";
    std::cout<<sum_polynomial<<"\n\n";
}

void create_polynomials(std::vector<polynomial>& polynomials)
{
    std::istringstream polynomials_stream;
    std::istringstream polynomials_substream;
    std::string polynomials_string;
    polynomial created_polynomial;

    polynomials.clear();
    std::cout<<"Enter the polynomials that you would like to create separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomials_string);
    std::cout<<'\n';

    polynomials_stream.str(polynomials_string);
    while(polynomials_stream>>polynomials_string)
    {
        polynomials_substream.clear();
        polynomials_substream.str(polynomials_string);
        polynomials_substream>>created_polynomial;
        if(polynomials_substream)
        {
            polynomials.push_back(std::move(created_polynomial));
        }
    }

    if(polynomials.empty())
    {
        std::cout<<"None of the typed polynomials were successfully created.\n\n";

        return;
    }

    std::cout<<"The polynomials that have been successfully created are:\n\n";
    for(const polynomial& polynomial:polynomials)
    {
        std::cout<<polynomial<<'\n';
    }

    std::cout<<'\n';
}

void divide_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be divided.\n\n";

        return;
    }

    std::cout<<"The polynomials that are available to be divided are:\n\n";
    for(unsigned long long int polynomial_index{}; polynomial_index<polynomials.size(); ++polynomial_index)
    {
        std::cout<<polynomial_index<<". "<<polynomials[polynomial_index]<<'\n';
    }

    std::cout<<'\n';

    unsigned long long int polynomial_options_index{};
    std::string polynomial_options_string;
    std::istringstream polynomial_options_stream;
    std::vector<unsigned long long int> polynomial_option_indices;
    polynomial quotient_polynomial;

    std::cout<<"Select which polynomials that are to be divided by typing the corresponding numbers separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomial_options_string);
    std::cout<<'\n';

    std::cout<<"The selected polynomials will now be divided:\n\n";
    polynomial_options_stream.str(polynomial_options_string);
    while(polynomial_options_stream>>polynomial_options_index)
    {
        polynomial_option_indices.push_back(polynomial_options_index);
    }

    for(unsigned long long int polynomial_options_index:polynomial_option_indices)
    {
        if(polynomial_options_index>=polynomials.size())
        {
            continue;
        }

        else if(quotient_polynomial==polynomial())
        {
            quotient_polynomial=polynomials[polynomial_options_index];

            continue;
        }

        quotient_polynomial/=polynomials[polynomial_options_index];
    }

    std::cout<<"The quotient of the selected polynomials are:\n\n";
    std::cout<<quotient_polynomial<<"\n\n";
}

void evaluate_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be evaluated.\n\n";

        return;
    }

    long double user_option{};
    std::cout<<"Please type a number at which the polynomial(s) will be evaluated with.\n\n";
    std::cin>>user_option;
    std::cout<<'\n';
    if(!std::cin)
    {
        std::cout<<"An integer or a decimal number needs to be entered to select an option.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return;
    }

    std::ios_base::fmtflags ostream_flags(std::cout.flags());
    std::cout<<"The polynomials will now be evaluated:\n\n";
    std::cout<<std::fixed;
    for(const polynomial& polynomial:polynomials)
    {
        std::cout<<"f(x) = "<<polynomial<<" -> f("<<user_option<<") = "<<polynomial(user_option)<<'\n';
    }

    std::cout.flags(ostream_flags);
    std::cout<<'\n';
}

void exponentiate_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be exponentiated.\n\n";

        return;
    }

    unsigned long long int user_option{};
    std::cout<<"Please type a number at which the polynomials will be exponentiated with.\n\n";
    std::cin>>user_option;
    std::cout<<'\n';
    if(!std::cin)
    {
        std::cout<<"A number needs to be entered to select an option.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return;
    }

    std::cout<<"The polynomials will now be exponentiated:\n\n";
    for(const polynomial& polynomial:polynomials)
    {
        std::cout<<"("<<polynomial<<")^"<<user_option<<" = "<<exponent(polynomial, user_option)<<'\n';
    }

    std::cout<<'\n';
}

void mod_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be modded.\n\n";

        return;
    }

    std::cout<<"The polynomials that are available to be modded are:\n\n";
    for(unsigned long long int polynomial_index{}; polynomial_index<polynomials.size(); ++polynomial_index)
    {
        std::cout<<polynomial_index<<". "<<polynomials[polynomial_index]<<'\n';
    }

    std::cout<<'\n';

    unsigned long long int polynomial_options_index{};
    std::string polynomial_options_string;
    std::istringstream polynomial_options_stream;
    std::vector<unsigned long long int> polynomial_option_indices;
    polynomial modulus_polynomial;

    std::cout<<"Select which polynomials that are to be modded by typing the corresponding numbers separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomial_options_string);
    std::cout<<'\n';

    std::cout<<"The selected polynomials will now be modded:\n\n";
    polynomial_options_stream.str(polynomial_options_string);
    while(polynomial_options_stream>>polynomial_options_index)
    {
        polynomial_option_indices.push_back(polynomial_options_index);
    }

    for(unsigned long long int polynomial_options_index:polynomial_option_indices)
    {
        if(polynomial_options_index>=polynomials.size())
        {
            continue;
        }

        else if(modulus_polynomial==polynomial())
        {
            modulus_polynomial=polynomials[polynomial_options_index];

            continue;
        }

        modulus_polynomial%=polynomials[polynomial_options_index];
    }

    std::cout<<"The modulus of the selected polynomials are:\n\n";
    std::cout<<modulus_polynomial<<"\n\n";
}

void multiply_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be multiplied.\n\n";

        return;
    }

    std::cout<<"The polynomials that are available to be multiplied are:\n\n";
    for(unsigned long long int polynomial_index{}; polynomial_index<polynomials.size(); ++polynomial_index)
    {
        std::cout<<polynomial_index<<". "<<polynomials[polynomial_index]<<'\n';
    }

    std::cout<<'\n';

    unsigned long long int polynomial_options_index{};
    std::string polynomial_options_string;
    std::istringstream polynomial_options_stream;
    std::vector<unsigned long long int> polynomial_option_indices;
    polynomial product_polynomial(1.0l);

    std::cout<<"Select which polynomials that are to be multiplied by typing the corresponding numbers separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomial_options_string);
    std::cout<<'\n';

    std::cout<<"The selected polynomials will now be multiplied:\n\n";
    polynomial_options_stream.str(polynomial_options_string);
    while(polynomial_options_stream>>polynomial_options_index)
    {
        polynomial_option_indices.push_back(polynomial_options_index);
    }

    for(unsigned long long int polynomial_options_index:polynomial_option_indices)
    {
        if(polynomial_options_index>=polynomials.size())
        {
            continue;
        }

        product_polynomial*=polynomials[polynomial_options_index];
    }

    std::cout<<"The product of the selected polynomials are:\n\n";
    std::cout<<product_polynomial<<"\n\n";
}

void nth_root_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be nth rooted.\n\n";

        return;
    }

    unsigned long long int user_option{};
    std::cout<<"Please type a number at which the polynomials will be nth rooted with.\n\n";
    std::cin>>user_option;
    std::cout<<'\n';
    if(!std::cin)
    {
        std::cout<<"A number needs to be entered to select an option.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        return;
    }

    std::cout<<"The polynomials will now be nth rooted:\n\n";
    for(const polynomial& polynomial:polynomials)
    {
        std::cout<<"nth_root("<<polynomial<<", "<<user_option<<") = "<<nth_root(polynomial, user_option)<<'\n';
    }

    std::cout<<'\n';
}

void subtract_polynomials(const std::vector<polynomial>& polynomials)
{
    if(polynomials.empty())
    {
        std::cout<<"No polynomials were created to be subtracted.\n\n";

        return;
    }

    std::cout<<"The polynomials that are available to be subtracted are:\n\n";
    for(unsigned long long int polynomial_index{}; polynomial_index<polynomials.size(); ++polynomial_index)
    {
        std::cout<<polynomial_index<<". "<<polynomials[polynomial_index]<<'\n';
    }

    std::cout<<'\n';

    unsigned long long int polynomial_options_index{};
    std::string polynomial_options_string;
    std::istringstream polynomial_options_stream;
    std::vector<unsigned long long int> polynomial_option_indices;
    polynomial difference_polynomial;

    std::cout<<"Select which polynomials that are to be subtracted by typing the corresponding numbers separated by a space.\n\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, polynomial_options_string);
    std::cout<<'\n';

    std::cout<<"The selected polynomials will now be subtracted:\n\n";
    polynomial_options_stream.str(polynomial_options_string);
    while(polynomial_options_stream>>polynomial_options_index)
    {
        polynomial_option_indices.push_back(polynomial_options_index);
    }

    for(unsigned long long int polynomial_options_index:polynomial_option_indices)
    {
        if(polynomial_options_index>=polynomials.size())
        {
            continue;
        }

        else if(difference_polynomial==polynomial())
        {
            difference_polynomial=polynomials[polynomial_options_index];

            continue;
        }

        difference_polynomial-=polynomials[polynomial_options_index];
    }

    std::cout<<"The difference of the selected polynomials are:\n\n";
    std::cout<<difference_polynomial<<"\n\n";
}

int main()
{
    bool program_running(true);
    unsigned long long int user_option{};
    std::vector<polynomial> user_polynomials;

    std::cout<<"Polynomial Interface - Version 1.0\n\n";
    while(program_running)
    {
        std::cout<<"Select an option by typing the corresponding number:\n\n";
        std::cout<<"0. Create polynomials\n";
        std::cout<<"1. Evaluate polynomials\n";
        std::cout<<"2. Multiply polynomials\n";
        std::cout<<"3. Divide polynomials\n";
        std::cout<<"4. Modulus polynomials\n";
        std::cout<<"5. Add polynomials\n";
        std::cout<<"6. Subtract polynomials\n";
        std::cout<<"7. Exponentiate polynomials\n";
        std::cout<<"8. Nth root polynomials\n";
        std::cout<<"9. Exit program\n\n";
        std::cin>>user_option;
        std::cout<<'\n';
        if(!std::cin)
        {
            std::cout<<"A number needs to be entered to select an option.\n\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        switch(user_option)
        {
            case 0ull:
            {
                create_polynomials(user_polynomials);

                break;
            }

            case 1ull:
            {
                evaluate_polynomials(user_polynomials);

                break;
            }

            case 2ull:
            {
                multiply_polynomials(user_polynomials);

                break;
            }

            case 3ull:
            {
                divide_polynomials(user_polynomials);

                break;
            }

            case 4ull:
            {
                mod_polynomials(user_polynomials);

                break;
            }

            case 5ull:
            {
                add_polynomials(user_polynomials);

                break;
            }

            case 6ull:
            {
                subtract_polynomials(user_polynomials);

                break;
            }

            case 7ull:
            {
                exponentiate_polynomials(user_polynomials);

                break;
            }

            case 8ull:
            {
                nth_root_polynomials(user_polynomials);

                break;
            }

            case 9ull:
            {
                program_running=false;

                break;
            }

            default:
            {
                std::cout<<"The number entered does not correspond to a valid option.\n\n";

                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
