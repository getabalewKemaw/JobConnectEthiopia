#ifndef JOB_NODE_H
#define JOB_NODE_H

#include <QString>

class JobNode {
public:
    int jobId;
    QString title;
    QString companyName;
    QString location;
    QString salaryRange;
    QString deadline;
    QString jobType;
    QString workMode;
    QString industry;
    QString skillsRequired;
    QString additionalDetails;
    JobNode* next;

    JobNode(int id, const QString& t, const QString& c, const QString& l, const QString& s, const QString& d,
            const QString& jt, const QString& wm, const QString& i, const QString& sr, const QString& ad)
        : jobId(id), title(t), companyName(c), location(l), salaryRange(s), deadline(d),
        jobType(jt), workMode(wm), industry(i), skillsRequired(sr), additionalDetails(ad), next(nullptr) {}

    // Constructor used in dashboard_employer.cpp (simplified version)
    JobNode(int id, const QString& t, const QString& d, int exp, const QString& sal, const QString& dl)
        : jobId(id), title(t), companyName(""), location(""), salaryRange(sal), deadline(dl),
        jobType(""), workMode(""), industry(""), skillsRequired(""), additionalDetails(d), next(nullptr) {}
};

#endif // JOB_NODE_H
