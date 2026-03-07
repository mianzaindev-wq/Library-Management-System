#ifndef FINE_H
#define FINE_H

#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

class Fine {
private:
    static constexpr float RATE_PER_DAY = 100.0f;
    float fineAmount;

public:
    Fine(float rate = RATE_PER_DAY) : fineAmount(0.0f) {}
    
    ~Fine() = default;

    void calculateFine(const string& dueDate, const string& returnDate) {
        int returnDay, returnMonth, returnYear;
        int dueDay, dueMonth, dueYear;

        sscanf(returnDate.c_str(), "%d/%d/%d", &returnDay, &returnMonth, &returnYear);
        sscanf(dueDate.c_str(), "%d/%d/%d", &dueDay, &dueMonth, &dueYear);

        // Calculate fine based on the difference in days
        int daysLate = (returnYear - dueYear) * 365 + 
                       (returnMonth - dueMonth) * 30 + 
                       (returnDay - dueDay);

        if (daysLate > 0) {
            fineAmount = daysLate * RATE_PER_DAY;
        } else {
            fineAmount = 0.0f;
        }
    }

    float getFineAmount() const { return fineAmount; }
    
    void reset() { fineAmount = 0.0f; }
};

#endif // FINE_H
