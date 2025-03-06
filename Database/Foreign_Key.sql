use university ;

/*
 For Foreign Key We should keep mind that 'Reference Table' should come first(Creation and Insertion Values)
 */

CREATE Table Airline
(
    Id int primary key AUTO_INCREMENT,
    name varchar(40) not null ,
    country varchar(20),
   constraint fk foreign key(name) references Airname(name)
    # If we not use 'constraint' then just use 'foreign key(name) references Airname(name)'
) ;
CREATE Table Airname
(
    name varchar(40) primary key ,
    `Number of planes` int
) ;

INSERT INTO Airline(name, country)
VALUES ('Bangladesh Biman','Australia'),
       ('Emirates','England'),
       ('Bangladesh Biman','USA'),
       ('Novo Air','CANADA'),
       ('Novo Air','Thailand'),
       ('Us Bangla','Oman'),
       ('Bangladesh Biman','China') ;

INSERT INTO Airname
VALUES ('Bangladesh Biman',10),
       ('US Bangla',15),
       ('Novo Air',10),
       ('Emirates',20)
