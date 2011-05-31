#include "prediction.h"


Prediction::Prediction() : start(0), end(0), score(0), cost(0)
{
}

Prediction::Prediction(int st, int e, int sc) : start(st), end(e), score(sc),
                                                cost(0)
{
}

void Prediction::print()
{
    cout << start << " " << end << " " << score << endl;
}

int Prediction::get_score() const
{
    return score;
}

int Prediction::get_start() const
{
    return start;
}

int Prediction::get_end() const
{
    return end;
}

int Prediction::get_cost() const
{
    return cost;
}

void Prediction::set_cost(const int c)
{
    cost = c;
}

istream &operator>>(istream &stream, Prediction &o)
{
    stream >> o.start >> o.end >> o.score;
    return stream;
}

ostream &operator<<(ostream &stream, Prediction *o)
{
    stream << o->start << " " << o->end << " " << o->score;
    return stream;
}

ostream &operator<<(ostream &stream, Prediction o)
{
    stream << o.start << " " << o.end << " " << o.score;
    return stream;
}
