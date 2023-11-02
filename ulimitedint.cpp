
#include "ulimitedint.h"
using namespace std;

bool is_large(int* num1,int len1, int*num2, int len2){
    if(len1 > len2){
        return true;
    }
    else if(len1 < len2){
        return false;
    }
    else{
        for(int i=0; i<len1; i++){
            if(num1[i]>num2[i]){
                return true;
            }
            if(num1[i]<num2[i]){
                return false;
            }
        }
        return false;
    }
    return false;
}

bool is_equal(int* num1,int len1, int*num2, int len2){
    if(len1 > len2){
        return false;
    }
    else if(len1 < len2){
        return false;
    }
    else{
        for(int i=0; i<len1; i++){
            if(num1[i]>num2[i]){
                return false;
            }
            if(num1[i]<num2[i]){
                return false;
            }
        }
        return true;
    }
    return false;
}

int is_bigger_mod(UnlimitedInt *i1, UnlimitedInt *i2)
{   int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    int* num1 = i1->get_array();
    int* num2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    if (sz1 > sz2)
    {
        return 1;
    }
    else if (sz1 < sz2)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < sz1; i++)
        {
            if (num1[i] > num2[i])
            {
                return 1;
            }
            else if (num1[i] < num2[i])
            {
                return -1;
            }
        }
        return 0;
    }
}

UnlimitedInt::UnlimitedInt()
{
    size = 1;
    sign = 0;
    capacity = size;
    unlimited_int = new int[size]();
}

UnlimitedInt::UnlimitedInt(string s)
{
    if (s.size() == 0 || s[0] == '0')
    {
        size = 1;
        sign = 0;
        capacity = size;
        unlimited_int = new int[size]{};
    }
    else
    {
        if (s[0] == '-')
        {
            size = s.size() - 1;
            sign = -1;
            capacity = size;
            unlimited_int = new int[size];
            for (int i = 0; i < size; i++)
            {
                unlimited_int[i] = int(s[i + 1]) - 48;
            }
        }
        else
        {
            size = s.size();
            sign = +1;
            capacity = size;
            unlimited_int = new int[size];
            for (int i = 0; i < size; i++)
            {
                unlimited_int[i] = int(s[i]) - 48;
            }
        }
    }
}

UnlimitedInt::UnlimitedInt(int i)
{
    int x = i;
    if (x == 0)
    {
        size = 1;
        sign = 0;
        capacity = size;
        unlimited_int = new int[size]{};
    }
    else if (x < 0)
    {
        sign = -1;
            x = -x;
            size = 0;
            int y = x;
            while (y > 0)
            {
                size++;
                y = y / 10;
            }
            unlimited_int = new int[size];
            for (int i = size - 1; i >= 0; i--)
            {
                unlimited_int[i] = x % 10;
                x = x / 10;
            }
        capacity = size;
    }
    else
    {
        sign = 1;
        size = 0;
        int y = x;
        while (y > 0)
        {
            size++;
            y = y / 10;
        }
        unlimited_int = new int[size];
        for (int i = size - 1; i >= 0; i--)
        {
            unlimited_int[i] = x % 10;
            x = x / 10;
        }
        capacity = size;
    }
}

UnlimitedInt::UnlimitedInt(int *ulimited_int, int cap, int sgn, int sz)
{   capacity = cap;
    size = sz;
    sign = sgn;
    unlimited_int = new int[size];
    for (int i = 0; i < size; i++)
    {
        unlimited_int[i] = ulimited_int[i];
    }
}

UnlimitedInt::~UnlimitedInt()
{
    delete[] unlimited_int;
}

int UnlimitedInt::get_size()
{
    return size;
}

int *UnlimitedInt::get_array()
{
    return unlimited_int;
}

int UnlimitedInt::get_sign()
{
    return sign;
}

int UnlimitedInt::get_capacity()
{
    return capacity;
}

UnlimitedInt *UnlimitedInt::add(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i2->get_array(), i2->get_capacity(), i2->get_sign(), i2->get_size());
        return temp;
    }
    else if (i2->get_sign() == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt(i1->get_array(), i1->get_capacity(), i1->get_sign(), i1->get_size());
        return temp;
    }
    else if ((i1->get_sign() == 1 && i2->get_sign() == 1) || (i1->get_sign() == -1 && i2->get_sign() == -1))
    {
        int nsign = i1->get_sign();
        int s1;
        int s2;
        int *a;
        int *b;
        if (i1->get_size() > i2->get_size())
        {
            s1 = i1->get_size();
            s2 = i2->get_size();
            a = i1->get_array();
            b = i2->get_array();
        }
        else
        {
            s1 = i2->get_size();
            s2 = i1->get_size();
            a = i2->get_array();
            b = i1->get_array();
        }
        int nsize = s1 + 1;
        int *narray = new int[nsize]{};
        int carry = 0;

        for (int i = 0; i < s2; i++)
        {
            int x = a[s1 - i - 1] + b[s2 - i - 1] + carry;
            narray[nsize - 1 - i] = x % 10;
            carry = x / 10;
        }
        for (int i = s2; i < s1; i++)
        {
            int x = a[s1 - i - 1] + carry;
            narray[nsize - 1 - i] = x % 10;
            carry = x / 10;
        }

        if (carry != 0)
        {
            narray[0] = carry;
            UnlimitedInt *temp = new UnlimitedInt(narray, nsize, nsign, nsize);
            delete[] narray;
            return temp;
        }
        else
        {
            nsize = s1;
            int *narray2 = new int[nsize];
            for (int i = 0; i < nsize; i++)
            {
                narray2[i] = narray[i + 1];
            }
            delete[] narray;
            UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
            delete[] narray2;
            return temp;
        }
    }
    else
    {
        int more = is_bigger_mod(i1, i2);
        if (more == 0)
        {
            UnlimitedInt *temp = new UnlimitedInt();
            return temp;
        }
        else
        {
            int nsign;
            int *a, *b;
            int s1, s2;
            if (more == 1)
            {
                nsign = i1->get_sign();
                a = i1->get_array();
                s1 = i1->get_size();
                b = i2->get_array();
                s2 = i2->get_size();
            }
            else if (more == -1)
            {
                nsign = -1 * (i1->get_sign());
                a = i2->get_array();
                s1 = i2->get_size();
                b = i1->get_array();
                s2 = i1->get_size();
            }

            int nsize = s1;
            int *narray = new int[nsize]{};
            int carry = 0;

            for (int i = 0; i < s2; i++)
            {
                int x = a[s1 - i - 1] - b[s2 - i - 1] + carry;
                if (x >= 0)
                {
                    narray[nsize - 1 - i] = x;
                    carry = 0;
                }
                else
                {
                    narray[nsize - 1 - i] = x + 10;
                    carry = -1;
                }
            }
            for (int i = s2; i < s1; i++)
            {
                int x = a[s1 - i - 1] + carry;
                narray[nsize - 1 - i] = x % 10;
                if (x >= 0)
                {
                    narray[nsize - 1 - i] = x;
                    carry = 0;
                }
                else
                {
                    narray[nsize - 1 - i] = x + 10;
                    carry = -1;
                }
            }
            for (int i = 0; i < s1; i++)
            {
                if (narray[i] == 0)
                {
                    nsize--;
                }
                else
                {
                    break;
                }
            }
            int *narray2 = new int[nsize]{};
            for (int i = 0; i < nsize; i++)
            {
                narray2[nsize - i - 1] = narray[s1 - i - 1];
            }
            delete[] narray;
            UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
            delete[] narray2;
            return temp;
        }
    }
}

UnlimitedInt *UnlimitedInt::sub(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt *current2 = new UnlimitedInt(i2->get_array(), i2->get_capacity(), -1 * (i2->get_sign()), i2->get_size());
    UnlimitedInt *res = UnlimitedInt::add(i1, current2);
    delete current2;
    return res;
}

UnlimitedInt *UnlimitedInt::mul(UnlimitedInt *i1, UnlimitedInt *i2)
{
    int nsign = i1->get_sign() * i2->get_sign();
    if (nsign == 0)
    {
        UnlimitedInt *temp = new UnlimitedInt();
        return temp;
    }
    else
    {
        int *num1;
        int *num2;
        int s1;
        int s2;
        if (i1->get_size() < i2->get_size())
        {   
            s1 = i2->get_size();
            s2 = i1->get_size();
            num1 = i2->get_array();
            num2 = i1->get_array();
        }
        else
        {   s1 = i1->get_size();
            s2 = i2->get_size();
            num1 = i1->get_array();
            num2 = i2->get_array();
            
        }
        int nsize = s1 + s2;
        int *narray = new int[nsize]{};
        for (int i = s1 - 1; i >= 0; i--)
        {
            for (int j = s2 - 1; j >= 0; j--)
            {
                int mul = num1[i] * num2[j];
                int sum = mul + narray[i + j + 1];

                narray[i + j + 1] = sum % 10;
                narray[i + j] += sum / 10;
            }
        }

        for (int i = 0; i < s1 + s2; i++)
        {
            if (narray[i] == 0)
            {
                nsize--;
            }
            else
            {
                break;
            }
        }
        int *narray2 = new int[nsize]{};
        for (int i = 0; i < nsize; i++)
        {
            narray2[nsize - i - 1] = narray[s1 + s2 - i - 1];
        }
        delete[] narray;
        UnlimitedInt *temp = new UnlimitedInt(narray2, nsize, nsign, nsize);
        delete[] narray2;
        return temp;
    }
}

UnlimitedInt *UnlimitedInt::div(UnlimitedInt *i1, UnlimitedInt *i2)
{   int sign1 = i1->get_sign();
    int sign2 = i2->get_sign();
    int* num1 = i1->get_array();
    int* num2 = i2->get_array();
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int final_sn = sign1 * sign2;
    
    if (final_sn == 0 || (is_bigger_mod(i1, i2) == -1 && final_sn == 1))
    {
        return new UnlimitedInt();
    }
    else if (is_bigger_mod(i1, i2) == -1 && final_sn == -1)
    {
        return new UnlimitedInt(-1);
    }
    else
    {
        UnlimitedInt *curr1 = new UnlimitedInt(i1->get_array(), i1->get_size(), 1, i1->get_size());
        UnlimitedInt *curr2 = new UnlimitedInt(i2->get_array(), i2->get_size(), 1, i2->get_size());
        UnlimitedInt *rem = new UnlimitedInt();
        
        UnlimitedInt *ten = new UnlimitedInt(10);
        UnlimitedInt *temp;
        UnlimitedInt *current;
        UnlimitedInt *q = new UnlimitedInt();
        
        for (int i = 0; i < i1->get_size(); i++)
        {
            temp = rem;
            rem = UnlimitedInt::mul(temp, ten);
            delete temp;
            
            current = new UnlimitedInt(curr1->unlimited_int[i]);
            temp = rem;
            rem = UnlimitedInt::add(temp, current);
            delete temp;
            delete current;

            int x = 0;
            while (is_bigger_mod(rem, curr2) >= 0)
            {
                temp = rem;
                rem = UnlimitedInt::sub(temp, curr2);
                delete temp;
                x++;
            }
            
            temp = q;
            q = UnlimitedInt::mul(temp, ten);
            delete temp;
            
            temp = q;
            UnlimitedInt *faltu = new UnlimitedInt(x);
            q = UnlimitedInt::add(temp, faltu);
            delete temp;
            delete faltu;
        }
        
        delete ten;
        delete curr1;
        delete curr2;
        
        q->sign = final_sn;
        
        if (final_sn == -1 && rem->get_sign() == +1)
        {
            UnlimitedInt *tempo2 = new UnlimitedInt(1);
            UnlimitedInt *tempo = q;
            q = UnlimitedInt::sub(tempo, tempo2);
            delete tempo2;
            delete tempo;
        }
        
        delete rem;
        
        return q;
    }
}

UnlimitedInt *UnlimitedInt::mod(UnlimitedInt *i1, UnlimitedInt *i2)
{
    UnlimitedInt* q = UnlimitedInt::div(i1,i2);
    UnlimitedInt* mult = UnlimitedInt::mul(q,i2);
    UnlimitedInt* mod = UnlimitedInt::sub(i1, mult);
    delete q;
    delete mult;
    return mod;
}

string UnlimitedInt::to_string(){
    string res = "";
    if (sign == 0){
        res = "0";
    }
    else{
        if (sign == -1){
            res = res + "-";
            for(int i = 0; i < size; i++){
            res = res + std::to_string(unlimited_int[i]);
        }
        }
        else{
    
        for(int i = 0; i < size; i++){
            res = res + std::to_string(unlimited_int[i]);
        }
        }
    }
    return res;
}