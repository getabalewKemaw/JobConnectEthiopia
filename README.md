# JobConnectEthiopia

**JobConnectEthiopia** is a professional, full-featured desktop application designed to streamline the job search and recruitment process in Ethiopia. Built with C++ using the Qt framework, and backed by a PostgreSQL database, it provides a robust platform for job seekers, employers, and administrators. The system supports secure authentication, role-based dashboards, job posting and application workflows, and comprehensive administrative controls.

---

## Table of Contents

- [Features](#features)
- [System Architecture](#system-architecture)
- [Role-Based Dashboards](#role-based-dashboards)
- [Installation & Setup](#installation--setup)
- [Usage Guide](#usage-guide)
- [Contributing](#contributing)
- [License](#license)

---

## Features

### For Job Seekers
- **Profile Management**: Create, update, and manage professional profiles including education, skills, and work experience.
- **Job Browsing**: View, search, and sort job listings by various criteria (company, salary, location, deadline).
- **Application Workflow**: Apply for jobs with a cover letter and custom responses to employer questions. Track applications and view statuses.
- **User-Friendly Dashboard**: Personalized dashboard for managing jobs and applications.

### For Employers
- **Job Posting**: Post new jobs specifying title, description, experience required, salary range, and deadlines.
- **Applicant Management**: View, filter, and manage applicants for posted jobs.
- **Company Profile**: Manage organizational information and job postings via a dedicated dashboard.

### For Administrators
- **System Monitoring**: View system stats and user activity.
- **User Management**: Approve/block employers and job seekers. Sort and search users.
- **Data Integrity**: Ensure platform compliance and remove inappropriate content.

---

## System Architecture

**JobConnectEthiopia** is organized using modular C++ classes, leveraging Qt for the GUI and PostgreSQL for persistent storage.

- **Core Modules**: Manage authentication, session handling, and utilities.
- **Models**: Represent users (job seekers, employers, admins), jobs, and applications.
- **UI Layer**: Separate dashboards for each role, implemented using Qt’s forms/UI classes.
- **Database Layer**: Encapsulated in the `DBManager` class, which handles all database connections and queries.

**Key Data Structures**:
- Linked lists are used extensively in dashboards (e.g., for managing jobs or users in admin view) for efficient traversal and sorting.

---

## Role-Based Dashboards

### Job Seeker Dashboard
- View and update profile.
- Browse and filter jobs.
- Apply to jobs with guided forms (cover letter, custom questions).
- Track submitted applications.

### Employer Dashboard
- Post new jobs.
- Browse and manage applicant lists.
- Edit existing job posts.

### Admin Dashboard
- View system statistics.
- Approve or block users.
- Sort/filter user lists using custom criteria.

---

## Installation & Setup

### Prerequisites

- **Qt Framework** (recommended: Qt 6.x)
- **C++17** or higher
- **PostgreSQL**

### Setup Steps

1. **Install Dependencies**
   - Download and install [Qt](https://www.qt.io/download) and [PostgreSQL](https://www.postgresql.org/download/).

2. **Database Setup**
   - Create the database:  
     ```bash
     createdb jobapplication
     ```
   - Run the schema SQL to set up tables (see `sql/schema.sql` in the project):
     ```bash
     psql -d jobapplication -f sql/schema.sql
     ```

3. **Configure Database Connection**
   - Update `config/db_config.txt` with your PostgreSQL connection details.

4. **Build the Application**
   - Open the project (`JobApplicationSystem.pro`) in Qt Creator.
   - Configure Kits for your compiler and Qt version.
   - Build and run the project.

---

## Usage Guide

After launching the application:

- **Welcome Screen**: Choose to log in or sign up.
- **Authentication**: Secure login for job seekers, employers, or admins.
- **Role-Specific Dashboard**: Access features based on your role.
- **Job Application**: Job seekers can apply to jobs by filling out application forms, including mandatory cover letters and custom questions set by employers.
- **Administration**: Admins can approve or block users, and monitor system statistics from a specialized dashboard.

---

## Contributing

We welcome contributions from the community! Please follow these steps:

1. Fork the repository.
2. Create a new feature branch.
3. Write clear, well-documented code.
4. Submit a pull request describing your changes.

Please ensure all contributions comply with the coding standards and include appropriate documentation.

---

## License

This project is licensed under the MIT License.

---

## Contact

For any questions or support, please contact the repository owner via GitHub issues.

---

**JobConnectEthiopia**  
A Professional Job Matching & Recruitment System for Ethiopia  
Powered by Qt, C++, and PostgreSQL
