#ifndef CPL_TIMESTAMP_H
#define CPL_TIMESTAMP_H

/** Timestamp, which is used to record modification and/or execution time. */
class cpl_TimeStamp {

public:
    /** create instance */
    static cpl_TimeStamp * New();

    /** delete itself. */
    void Delete() { delete this; };

    /** increase modification time */
    void Modified();

    /** return this object's modified time. */
    unsigned long int GetMTime() { return this->ModifiedTime; };

    /** support comparisons of time stamp objects directly. */
    int operator > (cpl_TimeStamp & ts) { return (this->ModifiedTime > ts.ModifiedTime); };

    int operator < (cpl_TimeStamp & ts) { return (this->ModifiedTime < ts.ModifiedTime); };

    /** allow for typecasting to unsigned long. */
    operator unsigned long() { return this->ModifiedTime; };

public:
    //constructor.
    cpl_TimeStamp() { this->ModifiedTime = 0; };

private:
    unsigned long ModifiedTime;
};

#endif //CPL_TIMESTAMP_H
