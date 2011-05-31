#ifndef _prediction_h_
#define _prediction_h_

#include <iostream>

using namespace std;

class Prediction
{
private:
    int start, end, score, cost;

public:
    Prediction();
    Prediction(int st, int e, int sc);
    int get_score() const;
    int get_start() const;
    int get_end() const;
    int get_cost() const;
    void set_cost(const int c);
    void print();

    friend istream &operator>>(istream &stream, Prediction &o);
    friend ostream &operator<<(ostream &stream, Prediction *o);
    friend ostream &operator<<(ostream &stream, Prediction o);

    /*
    friend bool operator<(const Prediction &lhs, const Prediction &rhs)
    {
        return lhs.start < rhs.start;
    }
    */
};

struct PredictionStartComp
{
    bool operator() (const Prediction &p1, const Prediction &p2) const
    {
        return p1.get_start() < p2.get_start();
    }
};

struct PredictionEndComp
{
    bool operator() (const Prediction &p1, const Prediction &p2) const
    {
        return p1.get_end() < p2.get_end();
    }
};

#endif // _prediction_h_
