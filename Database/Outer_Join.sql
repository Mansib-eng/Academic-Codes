/*
Outer Join -> Three types = 1. Left Outer Join
                            2. Right Outer Join
                            3. Full Outer Join
 */

use employment ;

create table employ
(
    E_no varchar(10),
    E_name varchar(20),
    D_no varchar(5)
) ;

create table department
(
    D_no varchar(5),
    D_name varchar(20),
    Loc varchar(15)
) ;

INSERT INTO employ
VALUES ('E1','Sakib','D1'),
       ('E2','Rakib','D2'),
       ('E3','Nasir','D1'),
       ('E4','Rohan',Null) ;

INSERT INTO department
VALUES ('D1','HR','Sylhet'),
       ('D2','TR','Dhaka'),
       ('D3','TP','Khulna'),
       ('D4','RR','Barisal') ;

# Left Outer Join -> It will pick all the rows of left table if the right table row doesn't have value according then fill up with 'Null'
SELECT *
from employ left outer join department
on employ.D_no = department.D_no ;

# Right Outer Join -> It will pick all the rows of right table if the left table row doesn't have value according then fill up with 'Null'
SELECT *
from department right outer join employ
on employ.D_no = department.D_no ;

# Full Outer Join = Left Outer Join + Left Outer Join
# Left Outer Join Union Right Outer Join
SELECT *
from employ left outer join department
on employ.D_no = department.D_no
UNION (
    SELECT *
from employ right outer join department
on employ.D_no = department.D_no
) ;

