QT += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

TEMPLATE = app
TARGET = JobApplicationSystem

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    core/dbmanager.cpp \
    core/session.cpp \
    core/auth.cpp \
    core/role_redirect.cpp \
    core/utils.cpp \
    models/user.cpp \
    models/jobseeker.cpp \
    models/employer.cpp \
    models/admin.cpp \
    models/job.cpp \
    models/application.cpp \
    ui/login.cpp \
    ui/dashboard_seeker.cpp \
    ui/dashboard_employer.cpp \
    ui/dashboard_admin.cpp \
    ui/job_post_form.cpp \
    ui/signup.cpp

HEADERS += \
    mainwindow.h \
    core/dbmanager.h \
    core/session.h \
    core/auth.h \
    core/role_redirect.h \
    core/utils.h \
    core/job_node.h\
    models/user.h \
    models/jobseeker.h \
    models/employer.h \
    models/admin.h \
    models/job-no.h \
    models/application.h \
    ui/login.h \
    ui/dashboard_seeker.h \
    ui/dashboard_employer.h \
    ui/dashboard_admin.h \
    ui/job_post_form.h \
    ui/signup.h

FORMS += \
    mainwindow.ui \
    gui/login.ui \
    gui/dashboard_seeker.ui \
    gui/dashboard_employer.ui \
    gui/dashboard_admin.ui \
    gui/job_post_form.ui \
    gui/signup.ui
