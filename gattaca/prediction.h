#ifndef _prediction_h_
#define _prediction_h_

#include <iostream>

using namespace std;

class Prediction
{
private:
    int start, end, score;

public:
    Prediction();
    Prediction(int st, int e, int sc);
    int get_score() const;
    int get_end() const;
    void print() const;

    friend istream &operator>>(istream &stream, Prediction &o);
    friend ostream &operator<<(ostream &stream, Prediction &o);
    friend ostream &operator<<(ostream &stream, Prediction o);

    friend bool operator<(const Prediction &lhs, const Prediction &rhs)
    {
        return lhs.start < rhs.start;
    }
};

struct PredictionComp
{
    bool operator() (const Prediction &p1, const Prediction &p2) const
    {
        return p1 < p2;
    }
};

#endif // _prediction_h_
