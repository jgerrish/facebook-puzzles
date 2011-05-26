#include "prediction.h"


Prediction::Prediction()
{
}

Prediction::Prediction(int st, int e, int sc) : start(st), end(e), score(sc)
{
}

void Prediction::print() const
{
    cout << start << " " << end << " " << score << endl;
}

int Prediction::get_score() const
{
    return score;
}

int Prediction::get_end() const
{
    return end;
}

istream &operator>>(istream &stream, Prediction &o)
{
    stream >> o.start >> o.end >> o.score;
    return stream;
}

ostream &operator<<(ostream &stream, Prediction &o)
{
    stream << o.start << " " << o.end << " " << o.score;
    return stream;
}

ostream &operator<<(ostream &stream, Prediction o)
{
    stream << o.start << " " << o.end << " " << o.score;
    return stream;
}
