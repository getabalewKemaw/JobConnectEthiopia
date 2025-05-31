# JobConnectEthiopia – Data Structure Final Project

A robust, Qt-based desktop application for managing job applications, targeting job seekers, employers, and administrators. Developed as a Data Structures course project, this system highlights key data structure usage, modular architecture, and a database-driven workflow for a real-world job marketplace.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Architecture & Design](#architecture--design)
- [Directory Structure](#directory-structure)
- [Key Components](#key-components)
- [Setup & Installation](#setup--installation)
- [Usage Workflow](#usage-workflow)
- [Data Structures Used](#data-structures-used)
- [Extending & Contributing](#extending--contributing)
- [License](#license)

---

## Project Overview

**JobConnectEthiopia** is a full-featured job portal desktop application built with C++ and Qt, integrating PostgreSQL as its persistent storage engine. It provides a platform for job seekers to search and apply for jobs, employers to post job vacancies, and admins to manage the system. The application demonstrates advanced software engineering practices and in-depth use of data structures for efficient data handling.

- **Branch:** [`DatastructureFinalProjec`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec)
- **Purpose:** Academic demonstration of applied data structures in a real-world context

---

## Architecture & Design

- **Frontend:** Built using Qt Widgets and UI forms, providing a responsive and user-friendly experience.
- **Backend:** Core logic split into authentication, session management, role-based control, and database communication.
- **Data Layer:** Models represent users, jobs, applications, and more, with clear separation for maintainability.
- **Persistence:** Uses PostgreSQL for robust, scalable storage; schema and migrations included.
- **Modularity:** Code is separated into logical directories (core, models, gui) for clarity and extensibility.

---

## Directory Structure

- [`core/`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/core) — Core application logic and utilities
- [`models/`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/models) — Data models for all entities
- [`gui/`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/gui) — UI forms for different roles and workflows
- [`sql/`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/sql) — SQL schema and scripts
- [`config/`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/config) — Configuration files (e.g., DB credentials)
- [`main.cpp`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/main.cpp) — Application entry point
- [`mainwindow.cpp/h/ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec) — Main window logic and layout

*Note: For comprehensive contents, please [browse the branch](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec) directly.*

---

## Key Components

### Core Directory

- [`auth.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/auth.cpp): Handles user authentication, password checks, and session validation.
- [`dbmanager.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/dbmanager.cpp): Database connection pooling, query execution, and transaction management.
- [`job_node.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/job_node.h): Implements job listing nodes, likely forming tree/linked list structures for efficient job management.
- [`role_redirect.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/role_redirect.cpp): Directs users to appropriate dashboards based on their role.
- [`session.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/session.cpp): User session handling, login/logout tracking.
- [`utils.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/core/utils.cpp): Utility functions and helpers.

*API result limits may apply. View more: [core directory](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/core).*

### Models Directory

- [`admin.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/admin.cpp): Admin account representation.
- [`application.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/application.cpp): Models job applications and their states.
- [`employer.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/employer.cpp): Employer entity, including job postings.
- [`job.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/job.cpp): Job listing abstraction.
- [`jobseeker.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/jobseeker.cpp): Job seeker profile and resume data.
- [`user.cpp/.h`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/models/user.cpp): Base user entity.

*API result limits may apply. View more: [models directory](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/models).*

### GUI Directory

- [`dashboard_admin.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/dashboard_admin.ui): Admin dashboard layout.
- [`dashboard_employer.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/dashboard_employer.ui): Employer dashboard.
- [`dashboard_seeker.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/dashboard_seeker.ui): Job seeker dashboard.
- [`job_post_form.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/job_post_form.ui): Form for employers to post new jobs.
- [`login.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/login.ui): Login interface.
- [`signup.ui`](https://github.com/getabalewKemaw/JobConnectEthiopia/blob/DatastructureFinalProjec/gui/signup.ui): User registration interface.

*For a complete list, see the [gui directory](https://github.com/getabalewKemaw/JobConnectEthiopia/tree/DatastructureFinalProjec/gui).*

---

## Setup & Installation

1. **Prerequisites**
   - [Qt 5.x/6.x](https://www.qt.io/download) (with Qt Creator)
   - [PostgreSQL](https://www.postgresql.org/download/)

2. **Database Initialization**
   - Create a PostgreSQL database named `jobapplication`.
   - Run schema creation scripts in `sql/schema.sql`:
     ```sh
     psql -U youruser -d jobapplication -f sql/schema.sql
     ```
   - Configure credentials in `config/db_config.txt`.

3. **Build & Run**
   - Open `JobApplicationSystem.pro` in Qt Creator.
   - Configure the project and build.
   - Run the application.

---

## Usage Workflow

1. **User Authentication**
   - Register as job seeker or employer, or log in as admin.
   - Role-based redirection to appropriate dashboard.

2. **Employers**
   - Post new jobs via the job post form.
   - Manage existing job postings.
   - Review applications from seekers.

3. **Job Seekers**
   - Search, filter, and view available jobs.
   - Submit applications.
   - Track application status.

4. **Admins**
   - Manage users, jobs, and oversee application data.
   - Access system analytics (if implemented).

---

## Data Structures Used

- **Linked Lists / Trees:** For managing dynamic job listings and application queues (see `job_node.h`).
- **Hash Tables / Maps:** For user session management and fast lookups (likely in `session.cpp/.h`).
- **Custom Classes:** Each entity (user, job, employer, etc.) is modeled with C++ classes promoting encapsulation and reusability.
- **Queues:** Processing application submissions in a FIFO manner.
- **Separation of Concerns:** Core logic, models, and UI are strictly separated for clarity and maintainability.

---

## Extending & Contributing

- Fork the repository and create a branch for your feature or fix.
- Write modular, well-documented code following the existing structure.
- Submit a pull request with a clear description of changes.
- For substantial changes, open an issue to discuss ideas first.

---

## License

This project is provided for educational purposes. For commercial or other uses, please contact the repository owner.

---

**Developed by:** [getabalewKemaw](https://github.com/getabalewKemaw)  
**For:** Data Structures Course, Ethiopia
