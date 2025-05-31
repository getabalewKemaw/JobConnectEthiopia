-- Drop existing tables to ensure a clean setup
DROP TABLE IF EXISTS Notifications;
DROP TABLE IF EXISTS JobViews;
DROP TABLE IF EXISTS Applications;
DROP TABLE IF EXISTS JobSkills;
DROP TABLE IF EXISTS Jobs;
DROP TABLE IF EXISTS JobSeekerSkills;
DROP TABLE IF EXISTS Skills;
DROP TABLE IF EXISTS Employers;
DROP TABLE IF EXISTS JobSeekers;
DROP TABLE IF EXISTS Users;

-- Create Users table for authentication
CREATE TABLE Users (
    user_id SERIAL PRIMARY KEY,
    email VARCHAR(255) UNIQUE NOT NULL,
    password VARCHAR(255) NOT NULL,
    role TEXT CHECK (role IN ('job_seeker', 'employer', 'admin')) NOT NULL,
    is_active BOOLEAN DEFAULT TRUE,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create JobSeekers table for job seeker profiles
CREATE TABLE JobSeekers (
    seeker_id SERIAL PRIMARY KEY,
    user_id INT UNIQUE REFERENCES Users(user_id) ON DELETE CASCADE,
    full_name TEXT NOT NULL,
    location TEXT,
    resume TEXT,
    about TEXT,
    phone VARCHAR(20)
);

-- Create Employers table for employer profiles
CREATE TABLE Employers (
    employer_id SERIAL PRIMARY KEY,
    user_id INT UNIQUE REFERENCES Users(user_id) ON DELETE CASCADE,
    company_name TEXT NOT NULL,
    license_number TEXT UNIQUE,
    license_verified BOOLEAN DEFAULT FALSE,
    website TEXT,
    industry TEXT
);

-- Create Skills table for skill definitions
CREATE TABLE Skills (
    skill_id SERIAL PRIMARY KEY,
    skill_name TEXT UNIQUE NOT NULL
);

-- Create JobSeekerSkills table to associate skills with job seekers
CREATE TABLE JobSeekerSkills (
    seeker_id INT REFERENCES JobSeekers(seeker_id) ON DELETE CASCADE,
    skill_id INT REFERENCES Skills(skill_id) ON DELETE CASCADE,
    PRIMARY KEY (seeker_id, skill_id)
);

-- Create Jobs table for job postings
CREATE TABLE Jobs (
    job_id SERIAL PRIMARY KEY,
    employer_id INT REFERENCES Employers(employer_id) ON DELETE CASCADE,
    title TEXT NOT NULL,
    description TEXT,
    experience_required INT,
    salary_range TEXT,
    posted_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    deadline DATE NOT NULL,
    is_active BOOLEAN DEFAULT TRUE
);

-- Create JobSkills table to associate skills with jobs
CREATE TABLE JobSkills (
    job_id INT REFERENCES Jobs(job_id) ON DELETE CASCADE,
    skill_id INT REFERENCES Skills(skill_id) ON DELETE CASCADE,
    PRIMARY KEY (job_id, skill_id)
);

-- Create Applications table for job applications
CREATE TABLE Applications (
    application_id SERIAL PRIMARY KEY,
    job_id INT REFERENCES Jobs(job_id) ON DELETE CASCADE,
    seeker_id INT REFERENCES JobSeekers(seeker_id) ON DELETE CASCADE,
    status TEXT CHECK (status IN ('pending', 'shortlisted', 'rejected', 'hired')) DEFAULT 'pending',
    applied_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create JobViews table to track job views
CREATE TABLE JobViews (
    view_id SERIAL PRIMARY KEY,
    job_id INT REFERENCES Jobs(job_id) ON DELETE CASCADE,
    seeker_id INT REFERENCES JobSeekers(seeker_id) ON DELETE CASCADE,
    viewed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Create Notifications table for user notifications
CREATE TABLE Notifications (
    notification_id SERIAL PRIMARY KEY,
    user_id INT REFERENCES Users(user_id) ON DELETE CASCADE,
    message TEXT NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    is_read BOOLEAN DEFAULT FALSE
);

-- Insert sample data into Users table
INSERT INTO Users (email, password, role) VALUES
('seeker@example.com', 'password123', 'job_seeker'),
('employer@example.com', 'password123', 'employer'),
('admin@example.com', 'password123', 'admin');

-- Insert sample data into JobSeekers table
INSERT INTO JobSeekers (user_id, full_name, location, resume, about, phone) VALUES
((SELECT user_id FROM Users WHERE email = 'seeker@example.com'), 'John Doe', 'New York', 'resume.pdf', 'Experienced software developer', '123-456-7890');

-- Insert sample data into Employers table
INSERT INTO Employers (user_id, company_name, license_number, license_verified, website, industry) VALUES
((SELECT user_id FROM Users WHERE email = 'employer@example.com'), 'Tech Corp', 'LIC12345', TRUE, 'https://techcorp.com', 'Technology');

-- Insert sample data into Skills table
INSERT INTO Skills (skill_name) VALUES
('Python'),
('JavaScript'),
('Database Management');

-- Insert sample data into JobSeekerSkills table
INSERT INTO JobSeekerSkills (seeker_id, skill_id) VALUES
((SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com')), (SELECT skill_id FROM Skills WHERE skill_name = 'Python')),
((SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com')), (SELECT skill_id FROM Skills WHERE skill_name = 'JavaScript'));

-- Insert sample data into Jobs table
INSERT INTO Jobs (employer_id, title, description, experience_required, salary_range, deadline, is_active) VALUES
((SELECT employer_id FROM Employers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'employer@example.com')), 'Software Engineer', 'Develop web applications', 3, '$80,000-$100,000', '2025-06-30', TRUE),
((SELECT employer_id FROM Employers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'employer@example.com')), 'Data Analyst', 'Analyze business data', 2, '$60,000-$80,000', '2025-06-30', TRUE);

-- Insert sample data into JobSkills table
INSERT INTO JobSkills (job_id, skill_id) VALUES
((SELECT job_id FROM Jobs WHERE title = 'Software Engineer'), (SELECT skill_id FROM Skills WHERE skill_name = 'Python')),
((SELECT job_id FROM Jobs WHERE title = 'Software Engineer'), (SELECT skill_id FROM Skills WHERE skill_name = 'JavaScript')),
((SELECT job_id FROM Jobs WHERE title = 'Data Analyst'), (SELECT skill_id FROM Skills WHERE skill_name = 'Database Management'));

-- Insert sample data into Applications table
INSERT INTO Applications (job_id, seeker_id, status) VALUES
((SELECT job_id FROM Jobs WHERE title = 'Software Engineer'), (SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com')), 'pending'),
((SELECT job_id FROM Jobs WHERE title = 'Data Analyst'), (SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com')), 'pending');

-- Insert sample data into JobViews table
INSERT INTO JobViews (job_id, seeker_id) VALUES
((SELECT job_id FROM Jobs WHERE title = 'Software Engineer'), (SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com'))),
((SELECT job_id FROM Jobs WHERE title = 'Data Analyst'), (SELECT seeker_id FROM JobSeekers WHERE user_id = (SELECT user_id FROM Users WHERE email = 'seeker@example.com')));

-- Insert sample data into Notifications table
INSERT INTO Notifications (user_id, message) VALUES
((SELECT user_id FROM Users WHERE email = 'seeker@example.com'), 'You have a new job application pending review.'),
((SELECT user_id FROM Users WHERE email = 'employer@example.com'), 'A job seeker viewed your job posting.');


select * from jobs;

ALTER TABLE Jobs  ADD COLUMN location VARCHAR(255),
ADD COLUMN job_type VARCHAR(50),
ADD COLUMN work_mode VARCHAR(50),
ADD COLUMN industry VARCHAR(100),
ADD COLUMN skills_required TEXT;


ALTER TABLE Users
ADD COLUMN license_verified VARCHAR(50);

select * from Users;




UPDATE Users
SET license_verified = 'ADMIN123'
WHERE user_id = (SELECT user_id FROM Users WHERE email = 'employer@example.com');




 ALTER TABLE JobSeekers
ADD COLUMN IF NOT EXISTS education TEXT,
ADD COLUMN IF NOT EXISTS skills TEXT,
ADD COLUMN IF NOT EXISTS work_experience TEXT;
select *from JobSeekers;




ALTER TABLE Applications
ADD COLUMN IF NOT EXISTS application_details TEXT;


select * from jobseekers;


select * from Employers;
select * from Users;



-- Add first_name and last_name to Users table
ALTER TABLE Users
ADD COLUMN IF NOT EXISTS first_name TEXT NOT NULL DEFAULT '',
ADD COLUMN IF NOT EXISTS last_name TEXT NOT NULL DEFAULT '';

-- Drop full_name from JobSeekers and ensure first_name/last_name are not added
ALTER TABLE JobSeekers
DROP COLUMN IF EXISTS full_name;

-- Verify Employers table (no changes needed since full_name isn't present)
SELECT * FROM Employers;

-- Verify updated JobSeekers table
SELECT * FROM JobSeekers;

ALTER TABLE Jobs ADD COLUMN additional_details TEXT;