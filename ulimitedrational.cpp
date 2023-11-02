
#include "ulimitedrational.h"
using namespace std;

int abs_big(UnlimitedInt *i1, UnlimitedInt *i2)
{   
    int sz1 = i1->get_size();
    int sz2 = i2->get_size();
    int* num1 = i1->get_array();
    int* num2 = i2->get_array();
    if (sz1 > sz2)
    {
        return 1;
    }
    else if (sz1 < sz2)
    {
        return -1;
    }
    else{
        for (int i = 0; i < i1->get_size(); i++){
            if (num1[i] < num2[i])
            {
                return -1;
            }
            else if (num1[i] > num2[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

UnlimitedInt *gcd(UnlimitedInt *a, UnlimitedInt *b)
{   int sn1 = a->get_sign();
    int sn2 = b->get_sign();
    int sz1 = a->get_size();
    int sz2 = b->get_size();
    int* num1 = a->get_array();
    int* num2 = b->get_array();
    if (sn2 == 0){
        UnlimitedInt *curr = new UnlimitedInt(num1, a->get_capacity(), sn1, sz1);
        return curr;
    }
    else{
        if (abs_big(a, b) == -1)
        {
            return gcd(b, a);
        }
        else
        {
            UnlimitedInt *a_mod_b = UnlimitedInt::mod(a, b);
            UnlimitedInt *res = gcd(b, a_mod_b);
            delete a_mod_b;
            return res;
        }
    }
}

UnlimitedRational::UnlimitedRational()
{
    p = new UnlimitedInt();
    q = new UnlimitedInt();
}

UnlimitedRational::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{   int sn1 = num->get_sign();
    int sn2 = den->get_sign();
    int sz1 = num->get_size();
    int sz2 = den->get_size();
    int* num1 = num->get_array();
    int* num2 = den->get_array();
    if (sn1 && sn2 == -1)
    {
        p = new UnlimitedInt(num1, num->get_capacity(), -1, sz1);
        q = new UnlimitedInt(num2, den->get_capacity(), 1, sz2);
    }
    else if (sn1 == -1 && sn2 == -1)
    {
        p = new UnlimitedInt(num1, num->get_capacity(), 1, sz1);
        q = new UnlimitedInt(num2, den->get_capacity(), 1, sz2);
    }
    else if (sn2 == 0)
    {
        p = new UnlimitedInt();
        q = new UnlimitedInt();
    }
    else
    {

        p = new UnlimitedInt(num1, num->get_capacity(), sn1, sz1);
        q = new UnlimitedInt(num2, den->get_capacity(), sn2, sz2);
    }
}

UnlimitedRational::~UnlimitedRational()
{
    delete p;
    delete q;
}

UnlimitedInt *UnlimitedRational::get_p()
{
    return p;
}

UnlimitedInt *UnlimitedRational::get_q()
{
    return q;
}

string UnlimitedRational::get_p_str()
{
    return p->to_string();
}

string UnlimitedRational::get_q_str()
{
    return q->to_string();
}

string UnlimitedRational::get_frac_str()
{
    string temp1 = p->to_string();
    string temp2 = q->to_string();
    string result = temp1+"/"+temp2;
    return result;
}

UnlimitedRational *UnlimitedRational::add(UnlimitedRational *i1, UnlimitedRational *i2)
{   
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *q2 = i2->get_q();
    if (p1->get_sign() == 0)
    {
        UnlimitedRational *curr = new UnlimitedRational(p2, q2);
        return curr;
    }
    else if (p2->get_sign() == 0)
    {
        UnlimitedRational *curr = new UnlimitedRational(p1, q1);
        return curr;
    }
    else
    {
        UnlimitedInt *curr1 = UnlimitedInt::mul(p1, q2);
        UnlimitedInt *curr2 = UnlimitedInt::mul(p2, q1);
        UnlimitedInt *curr3 = UnlimitedInt::add(curr1, curr2);
        UnlimitedInt *curr4 = UnlimitedInt::mul(q1, q2);
        UnlimitedInt *curr5 = new UnlimitedInt(curr3->get_array(), curr3->get_capacity(), 1, curr3->get_size());
        UnlimitedInt *curr6 = new UnlimitedInt(curr4->get_array(), curr4->get_capacity(), 1, curr4->get_size());
        UnlimitedInt *gcdpq = gcd(curr5, curr6);
        delete curr5;
        delete curr6;
        UnlimitedInt *newp = UnlimitedInt::div(curr3, gcdpq);
        UnlimitedInt *newq = UnlimitedInt::div(curr4, gcdpq);
        UnlimitedRational *ans = new UnlimitedRational(newp, newq);
        delete curr1;
        delete curr2;
        delete curr3;
        delete curr4;
        delete gcdpq;
        delete newp;
        delete newq;
        return ans;
    }
}

UnlimitedRational *UnlimitedRational::sub(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *temp = new UnlimitedInt(i2->get_p()->get_array(), i2->get_p()->get_capacity(), (-1) * i2->get_p()->get_sign(), i2->get_p()->get_size());
    UnlimitedRational *r2 = new UnlimitedRational(temp, i2->get_q());
    UnlimitedRational *ans = UnlimitedRational::add(i1, r2);
    delete temp;
    delete r2;
    return ans;
}

UnlimitedRational *UnlimitedRational::mul(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *q2 = i2->get_q();
    if (i1->get_q()->get_sign() == 0 || i2->get_q()->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational();
        return temp;
    }
    else if (i1->get_p()->get_sign() == 0 || i2->get_p()->get_sign() == 0)
    {
        UnlimitedInt *zero = new UnlimitedInt(0);
        UnlimitedInt *one = new UnlimitedInt(1);
        UnlimitedRational *temp = new UnlimitedRational(zero, one);
        delete zero;
        delete one;
        return temp;
    }
    else
    {
        UnlimitedInt *curr1 = UnlimitedInt::mul(p1, p2);
        UnlimitedInt *curr2 = UnlimitedInt::mul(q1, q2);

        UnlimitedInt *curr3 = new UnlimitedInt(curr1->get_array(), curr1->get_capacity(), 1, curr1->get_size());
        UnlimitedInt *curr4 = new UnlimitedInt(curr2->get_array(), curr2->get_capacity(), 1, curr2->get_size());
        UnlimitedInt *gcdpq = gcd(curr3, curr4);
        delete curr3;
        delete curr4;
        
        UnlimitedInt *newq = UnlimitedInt::div(curr2, gcdpq);
        UnlimitedInt *newp = UnlimitedInt::div(curr1, gcdpq);
        delete curr1;
        delete curr2;
        UnlimitedRational *result = new UnlimitedRational(newp, newq);
        delete newp;
        delete newq;
        return result;
    }
}

UnlimitedRational *UnlimitedRational::div(UnlimitedRational *i1, UnlimitedRational *i2)
{
    UnlimitedInt *p1 = i1->get_p();
    UnlimitedInt *p2 = i2->get_p();
    UnlimitedInt *q1 = i1->get_q();
    UnlimitedInt *q2 = i2->get_q();
    if (i1->get_q()->get_sign() == 0 || i2->get_p()->get_sign() == 0 || i2->get_q()->get_sign() == 0)
    {
        UnlimitedRational *temp = new UnlimitedRational();
        return temp;
    }
    else if (i1->get_p()->get_sign() == 0)
    {
        UnlimitedInt *zero = new UnlimitedInt(0);
        UnlimitedInt *one = new UnlimitedInt(1);
        UnlimitedRational *temp = new UnlimitedRational(zero, one);
        delete zero;
        delete one;
        return temp;
    }
    else
    {
       UnlimitedInt *curr1 = UnlimitedInt::mul(p1, q2);
        UnlimitedInt *curr2 = UnlimitedInt::mul(q1, p2);

        UnlimitedInt *curr3 = new UnlimitedInt(curr1->get_array(), curr1->get_capacity(), 1, curr1->get_size());
        UnlimitedInt *curr4 = new UnlimitedInt(curr2->get_array(), curr2->get_capacity(), 1, curr2->get_size());
        UnlimitedInt *gcdpq = gcd(curr3, curr4);
        delete curr3;
        delete curr4;
        
        UnlimitedInt *newq = UnlimitedInt::div(curr2, gcdpq);
        UnlimitedInt *newp = UnlimitedInt::div(curr1, gcdpq);
        delete curr1;
        delete curr2;
        UnlimitedRational *result = new UnlimitedRational(newp, newq);
        delete newp;
        delete newq;
        return result;
    }
}

