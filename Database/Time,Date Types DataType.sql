# CREATE DATABASE Unlucky

use unlucky ;

CREATE TABLE Details
(
    Name varchar(40)      primary key ,
    Varsity_Name varchar(50),
    Age int check ( age>5 )
) ;

CREATE TABLE BORN
(
    ID int primary key auto_increment,
    Name varchar(40) not null,
    `Date of Birth` DATETIME UNIQUE ,       # DateTime shows YYYY-MM-DD hh:mm:ss this format
    `Today Date` Date,                      # Date shows YYYY-MM-DD this format
    Year YEAR ,                             # Year shows YYYY this format
    Time time,                              # Time shows hh:mm:ss this format
    CONSTRAINT fk FOREIGN KEY(Name) references Details(Name)
) ;

INSERT INTO Details
VALUES ('Mansib','SUST',22),
       ('Ibnat','JRRMCH',20),
       ('Wamia','BBSHC',14),
       ('Zohan','BBSHC',6) ;

INSERT INTO BORN(name, `date of birth`, `today date`, year, time)
VALUES ('Mansib','2001-11-27 12:40:55','2024-03-02','2024','11:24:30'),
       ('Ibnat','2003-04:07 12:10:20','2024-03-02','2024','11:25:00'),
       ('Wamia','2009-08-13 04:30:50','2024-03-02','2024','11:29:20'),
       ('Zohan','2021-11-21 08:00:00','2024-03-02','2024','11:30:59') ;

