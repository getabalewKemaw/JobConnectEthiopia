#ifndef JOB_NODE_H
#define JOB_NODE_H

#include <QString>

class JobNode {
public:
    int jobId;
    QString title;
    QString description;       // For employer dashboard
    int experienceRequired;    // For employer dashboard
    QString salaryRange;
    QString deadline;
    QString companyName;       // For seeker dashboard
    QString location;          // For seeker dashboard
    JobNode* next;

    // Constructor for employer dashboard
    JobNode(int id, const QString& t, const QString& d, int exp, const QString& sal, const QString& dl)
        : jobId(id), title(t), description(d), experienceRequired(exp), salaryRange(sal), deadline(dl),
        companyName(""), location(""), next(nullptr) {}

    // Constructor for seeker dashboard
    JobNode(int id, const QString& t, const QString& c, const QString& loc, const QString& sal, const QString& dl)
        : jobId(id), title(t), description(""), experienceRequired(0), salaryRange(sal), deadline(dl),
        companyName(c), location(loc), next(nullptr) {}
};

#endif // JOB_NODE_H
