INSERT INTO CONTACT (number, email) VALUES ('+111 111 111', 'ftn@uns.ac.rs');
INSERT INTO CONTACT (number, email) VALUES ('+222 222 222', 'aleksandar.aleksic@uns.ac.rs');

INSERT INTO COMPANY (name, address, contact_id) VALUES ('FTN', 'Trg Dositeja Obradovvica 6', 1);

INSERT INTO DEPARTMENT (name, company_id) VALUES ('Menadžment', 1);
INSERT INTO DEPARTMENT (name, company_id) VALUES ('Računarski centar', 1);

INSERT INTO EMPLOYEE (first_name, last_name, position, department_id, contact_id) VALUES ('Aleksandar', 'Aleksić', 'radnik', 1, 2);
INSERT INTO EMPLOYEE (first_name, last_name, position, department_id, contact_id) VALUES ('Milica', 'Milić', 'menadžer', 1, null);
INSERT INTO EMPLOYEE (first_name, last_name, position, department_id, contact_id) VALUES ('Slavica', 'Slavić', 'radnik', 2, null);

INSERT INTO PROJECT (name, deadline) VALUES ('Biću student FTN', '2019-02-10');
INSERT INTO PROJECT (name, deadline) VALUES ('Podizanje sistema', '2019-05-1');

INSERT INTO WORKING (project_id, employee_id) VALUES (1, 1);
INSERT INTO WORKING (project_id, employee_id) VALUES (1, 2);
INSERT INTO WORKING (project_id, employee_id) VALUES (2, 3);
