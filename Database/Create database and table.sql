# CREATE DATABASE University ;

Create Table Student
(
    ID varchar(60) PRIMARY KEY ,    # There are many other STRING data types available such as 'char' , 'text' etc
    Name varchar(60),
    Department varchar(60)
    #CONSTRAINT FOREIGN KEY (Department) references Department(Name)
) ;

INSERT INTO Student
values('2020331061','Mansib','CSE'),
      ('2020331009','Unayes','CSE'),
('20203310107','Munna','CSE'),
('2020441060','Dipu','EEE'),
('2020221050','Shahed','SWE'),
('2020331012','Monika','SWE'),
('2020331020','Rasel','MATH') ;

Create Table Department
(
    Name varchar(10) primary key,  # PRIMARY KEY can't be null and always have to be unique
    `Number of teachers` int ,    # There many other INTEGER Data types available like 'smallint', 'bigint'
    Budget decimal(8,2)           # There many other FLOAT Data types available like 'float', 'double(M,S)'
) ;

INSERT INTO Department
VALUES('CSE', 20 , 500000.00),
      ('EEE', 20 , 100000.50),
      ('SWE', 15 , 200000.00),
      ('MATH', 30 , 400000.00);